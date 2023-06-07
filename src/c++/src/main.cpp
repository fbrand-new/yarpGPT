#include <iostream>
#include <yarp/os/all.h>
#include <yarpGPT.h>

int main(int argc, char** argv)
{
    yarp::os::Network yarp;
    if(!yarp.checkNetwork())
    {
        yError()<<"Unable to find yarp server!";
        return EXIT_FAILURE;
    }

    yarp::os::ResourceFinder rf;
    rf.setDefaultContext("yarpGPT");
    rf.setDefaultConfigFile("yarpGPT.ini");
    rf.configure(argc,argv);

    yarpGPT yarpGPT;
    return yarpGPT.runModule(rf);
    std::cout << "Hello world!" << std::endl;
}