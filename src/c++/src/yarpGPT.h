/******************************************************************************
 *                                                                            *
 * Copyright (C) 2023 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

/**
 * @file yarpGPT.h
 * @authors: Francesco Brand <francesco.brand@iit.it>
 */

#ifndef __YARP_GPT_H__
#define __YARP_GPT_H__

#include <fstream>
#include <sstream>
#include <memory>
#include <yarp/os/all.h>

class Core
{

};

class FakeCore : public Core
{

};

class GPTCore: public Core
{

};

class yarpGPT : public yarp::os::RFModule
{
    private:
        double period;
        std::string initialPrompt;
        std::string systemContext;
        std::string initialPromptFile;
        std::string apiConf;
        std::unique_ptr<Core> core;

    public:
        
        //Default constructor
        yarpGPT();

        bool configure(yarp::os::ResourceFinder &rf) override;
        bool updateModule() override;
        bool interruptModule() override; //TODO: do we really need this?
        bool close() override;
        double getPeriod() override;
};

#endif


