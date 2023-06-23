/*
 * SPDX-FileCopyrightText: 2006-2023 Istituto Italiano di Tecnologia (IIT)
 * SPDX-FileCopyrightText: 2006-2010 RobotCub Consortium
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef YARP_GPTDevice_H
#define YARP_GPTDevice_H

#include "ILLM.hpp"
#include <yarp/dev/DeviceDriver.h>
#include <yarp/os/RpcServer.h>
#include <yarp/os/LogStream.h>
#include <yarp/os/Log.h>
#include <yarp/os/LogComponent.h>
#include <liboai.h>

class GPTDevice : public yarp::dev::ILLM,
                  public yarp::dev::DeviceDriver,
                  public yarp::os::PortReader
{
public:
    GPTDevice() : ILLM(), m_convo{}
    {
    }

    // Rpc methods
    void setPrompt(const std::string &prompt) override;

    const std::string readPrompt() const override;

    const std::string ask(const std::string &question) override;

    const std::string getConversation() const override;

    // Device initialization
    bool open(yarp::os::Searchable &config) override;

    bool close() override;

    bool read(yarp::os::ConnectionReader &connection) override;

private:
    // data
    liboai::Conversation m_convo;

    // configuration
    std::string azure_resource;
    std::string azure_deployment_id;
    std::string azure_api_version;
    liboai::OpenAI oai;

    // model
    std::string m_model;

    // Ports
    yarp::os::Port m_rpcPort;
};

#endif