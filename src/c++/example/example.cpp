#include <yarp/dev/PolyDriver.h>
#include <yarp/os/Property.h>
#include <ILLM.hpp>
#include <iostream>

using namespace yarp::dev;
using namespace yarp::os;

int main()
{

    ILLM* iLlm;

    Property prop;
    prop.put("device","GPT_nwc_yarp");
    PolyDriver poly;
    poly.open(prop);

    poly.view(iLlm);

    iLlm->setPrompt("Ciao!");
    std::string oPrompt;
    iLlm->readPrompt(oPrompt);
    std::cout << oPrompt << std::endl;
}