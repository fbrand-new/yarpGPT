#include <yarpGPT.h>

yarpGPT::yarpGPT():
    period{0.2},
    initialPrompt{},
    systemContext{},
    initialPromptFile{},
    apiConf{"Fake"}
    {}

bool yarpGPT::configure(yarp::os::ResourceFinder &rf)
{

    initialPromptFile = rf.find("system_context").asString();

    // Reading the prompt written in initialPromptFile into initialPrompt
    if(initialPromptFile != "")
    {
        try
        {
            std::ifstream t(initialPromptFile);
            std::stringstream buffer;
            buffer << t.rdbuf();
            initialPrompt = buffer.str();
        }
        catch(const std::ifstream::failure& e)
        {
            yError() << "Unable to open file: " << initialPromptFile; 
        }
    }

    apiConf = rf.find("api_conf").asString();

    // Local factory to create the right core of the api
    if(apiConf == "OpenAI")
    {
        core = std::make_unique<GPTCore>(systemContext,initialPrompt);
    }
    else if(apiConf == "Azure")
    {

    }

}