#include "liboai.h"
#include <iostream>

using namespace liboai;

int main() {
    
    OpenAI oai;
    Conversation convo;
    
    convo.AddUserData("What is the capital of Italy?");

    if(oai.auth.SetKeyEnv("OPENAI_API_KEY"))
    {
        try {
            Response res = oai.ChatCompletion->create(
                "gpt-3.5-turbo",convo
            );

            convo.Update(res);

            std::cout << convo.GetLastResponse() << std::endl;
        }
        catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }
}