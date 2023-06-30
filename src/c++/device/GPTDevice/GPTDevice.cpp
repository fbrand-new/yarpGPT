#include "GPTDevice.hpp"

bool GPTDevice::open(yarp::os::Searchable &config)
{
    // Azure settings
    azure_api_version = config.check("api_version", yarp::os::Value("2023-05-15")).asString();
    azure_deployment_id = std::getenv("DEPLOYMENT_ID");
    azure_resource = std::getenv("AZURE_RESOURCE");

    if (azure_resource.empty())
    {
        yError() << "Could not read env variable AZURE_RESOURCE, please provide it";
        return false;
    }

    if (!oai.auth.SetAzureKeyEnv("AZURE_API_KEY"))
    {
        yError() << "Invalid azure key provided";
        return false; // TODO:not only return false but also gracefully close the module. check how it is done
    }

    return true;
}

// bool GPTDevice::read(yarp::os::ConnectionReader &connection)
// {

//     // Read the message from the input port
//     yarp::os::Bottle command;
//     yarp::os::Bottle reply;

//     bool ok = command.read(connection);

//     if (!ok)
//     {
//         return false;
//     }

//     if (command.get(0).asString() == "setPrompt")
//     {
//         std::string prompt = command.get(1).asString();
//         if (prompt.size() > 0)
//         {
//             setPrompt(prompt);
//             reply.addString("ack");
//         }
//         else
//         {
//             reply.addString("err");
//         }
//     }
//     else if (command.get(0).asString() == "readPrompt")
//     {
//         reply.addString(readPrompt());
//     }
//     else if (command.get(0).asString() == "ask")
//     {
//         std::string question = command.get(1).asString();
//         if (question.size() > 0)
//         {
//             const std::string &answer = ask(question);
//             reply.addString(answer);
//         }
//         else
//         {
//             reply.addString("No question received");
//         }
//     }
//     else if (command.get(0).asString() == "getConversation")
//     {
//         reply.addString(getConversation());
//     }
//     else if (command.get(0).asString() == "help")
//     {
//         reply.addString("Usage:");
//         reply.addString("   setPrompt <prompt> ");
//         reply.addString("   readPrompt");
//         reply.addString("   ask <question>");
//         reply.addString("   getConversation");
//     }
//     else
//     {
//         reply.addString("Unknown command. Use help to see available commands");
//     }

//     yarp::os::ConnectionWriter *returnToSender = connection.getWriter();
//     if (returnToSender != nullptr)
//     {
//         reply.write(*returnToSender);
//     }

//     return true;
// }

std::string GPTDevice::ask(const std::string &question)
{
    // Adding prompt to conversation
    m_convo->AddUserData(question);

    // Asking chat gpt for an answer
    try
    {
        liboai::Response res = oai.Azure->create_chat_completion(
            azure_resource, azure_deployment_id, azure_api_version,
            *m_convo);
        m_convo->Update(res);
    }
    catch (const std::exception &e)
    {
        yError() << e.what() << '\n';
    }

    return m_convo->GetLastResponse();
}

void GPTDevice::setPrompt(const std::string &prompt)
{
    m_convo->PopSystemData();
    m_convo->SetSystemData(prompt);
}

std::string GPTDevice::readPrompt()
{
    auto &convo_json = m_convo->GetJSON();
    for (auto &message : convo_json["messages"])
    {
        if (message["role"] == "system")
            return message["content"];
    }

    yWarning() << "No system message was found. Set it with setPrompt(string)";

    return "";
}

std::vector<std::pair<Author,Content>> GPTDevice::getConversation()
{
    std::vector<std::pair<std::string, std::string>> conversation;

    auto &convo_json = m_convo->GetJSON();
    for (auto &message : convo_json["messages"])
    {
        std::string role = message["role"].get<std::string>();
        std::string content = message["content"].get<std::string>();
        conversation.push_back(std::make_pair(role, content));
    }

    return conversation;
}

void GPTDevice::deleteConversation() noexcept
{
    //Api does not provide a method to empty the conversation: we are better of if we rebuild an object from scratch
    m_convo.reset(new liboai::Conversation());
}

bool GPTDevice::close()
{
    return true;
}