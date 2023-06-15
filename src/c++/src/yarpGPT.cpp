#include <yarpGPT.h>
#include "liboai.h"

using namespace liboai;

bool yarpGPT::configure(yarp::os::ResourceFinder &rf)
{
    // Configure system context and initial prompt from file
    std::string systemMessageFile = rf.findFile("system_context");
    std::string initialPrompFile = rf.findFile("initial-prompt");

    // Warn the user if the file is not found. Maybe it is intended
    if(systemMessageFile == "")
    {
        yWarning() << "system message file was not found";
    }
    if(initialPrompFile == "")
    {
        yWarning() << "initial prompt file was not found";
    }

    // Read the file containing the system context.
    try
    {
        std::ifstream t(systemMessageFile);
        std::stringstream buffer;
        buffer << t.rdbuf();
        systemContext = buffer.str();
    }
    catch(const std::ifstream::failure& e)
    {
        yError() << "File " << systemMessageFile << " was found but I was not able to open it.";
        return -1; 
    }

    // Read the file containing the initial prompt.
    try
    {
        std::ifstream t(initialPrompFile);
        std::stringstream buffer;
        buffer << t.rdbuf();
        initialPrompt = buffer.str();
    }
    catch(const std::ifstream::failure& e)
    {
        yError() << "File " << initialPrompFile << " was found but I was not able to open it.";
        return -1; 
    }

    // Set system data if present
    if(systemContext != "")
    {
        convo.SetSystemData(systemContext);        
    }
    
    // Set initial prompt if present
    if(initialPrompt != "")
    {
        convo.AddUserData(initialPrompt);
    }

    model = rf.check("model",yarp::os::Value("gpt-3.5-turbo")).asString();

    // Azure settings
    azure_api_version = rf.check("api_version",yarp::os::Value("2023-05-15")).asString();
    azure_deployment_id = std::getenv("DEPLOYMENT_ID");
    azure_resource = std::getenv("AZURE_RESOURCE");

    if(!azure_resource)
    {
        yError() << "Could not read env variable AZURE_RESOURCE, please provide it";
        return false;
    }

    if(!oai.auth.SetAzureKeyEnv("AZURE_API_KEY"))
    {
        yError() << "Invalid azure key provided";
        return false; //TODO:not only return false but also gracefully close the module. check how it is done
    }

    
    // yarp module configuration
    period = rf.check("period",yarp::os::Value(0.1)).asFloat32();
    inPort.open("/yarpGPT/text:i");

    return true;

}

bool yarpGPT::updateModule()
{

    yarp::os::Bottle prompt;

    if(inPort.read(prompt,true))
    {
        //Adding prompt to conversation
        convo.AddUserData(prompt.toString());

        //Asking chat gpt for an answer
        try
        {
            Response res = oai.Azure->create_chat_completion(
                azure_resource,azure_deployment_id,azure_api_version,
            convo);
            convo.Update(res);        
        }
        catch(const std::exception& e)
        {
            yError() << e.what() << '\n';
        }
        
        yarp::os::Bottle answer;
        answer.addString(convo.GetLastResponse());
        inPort.reply(answer);
    }
}

double yarpGPT::getPeriod()
{
    return period;
}

bool yarpGPT::interruptModule()
{
    inPort.close();
    return true;
}

bool yarpGPT::close()
{
    inPort.close();
    return true;
}