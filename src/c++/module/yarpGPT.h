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
#include <liboai.h>

class yarpGPT : public yarp::os::RFModule
{
    private:
        double period;
        std::string initialPrompt;
        std::string systemContext;
        
        char* azure_resource;
        std::string azure_deployment_id;
        std::string azure_api_version;

        liboai::OpenAI oai;
        liboai::Conversation convo;
        std::string model;

        yarp::os::RpcServer inPort;

    public:

        bool configure(yarp::os::ResourceFinder &rf) override;
        bool updateModule() override;
        bool interruptModule() override; //TODO: do we really need this?
        bool close() override;
        double getPeriod() override;

        yarp::os::Bottle createResponse(std::string& res);
};

#endif


