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

bool GPTDevice::ask(const std::string &question, std::string &oAnswer)
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
        return false;
    }

    oAnswer = m_convo->GetLastResponse();
    return true;
}

bool GPTDevice::setPrompt(const std::string &prompt)
{
    try
    {
        m_convo->PopSystemData();
        m_convo->SetSystemData(prompt);
    }
    catch (const std::exception& e){
        yError() << e.what() << '\n';
        return false;
    }

    return true;
}

bool GPTDevice::readPrompt(std::string& oPrompt)
{
    auto &convo_json = m_convo->GetJSON();
    for (auto &message : convo_json["messages"])
    {
        if (message["role"] == "system")
        {
            oPrompt = message["content"];
            return true;
        }
    }

    yWarning() << "No system message was found. Set it with setPrompt(string)";

    return false;
}

bool GPTDevice::getConversation(std::vector<std::pair<Author, Content>>& oConversation)
{
    std::vector<std::pair<std::string, std::string>> conversation;

    auto &convo_json = m_convo->GetJSON();

    if(convo_json.empty())
    {
        yWarning() << "Conversation is empty!";
        return false;
    }

    for (auto &message : convo_json["messages"])
    {
        std::string role = message["role"].get<std::string>();
        std::string content = message["content"].get<std::string>();
        conversation.push_back(std::make_pair(role, content));
    }

    oConversation = conversation;
    return true;
}

bool GPTDevice::deleteConversation() noexcept
{
    // Api does not provide a method to empty the conversation: we are better of if we rebuild an object from scratch
    m_convo.reset(new liboai::Conversation());
    return false;
}

bool GPTDevice::close()
{
    return true;
}