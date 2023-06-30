/*
 * SPDX-FileCopyrightText: 2006-2023 Istituto Italiano di Tecnologia (IIT)
 * SPDX-FileCopyrightText: 2006-2010 RobotCub Consortium
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef YARP_GPTDevice_H
#define YARP_GPTDevice_H

#include <ILLM.hpp>
#include <yarp/dev/DeviceDriver.h>
#include <yarp/os/RpcServer.h>
#include <yarp/os/LogStream.h>
#include <yarp/os/Log.h>
#include <yarp/os/LogComponent.h>
#include <liboai.h>

class GPTDevice : public yarp::dev::ILLM,
                  public yarp::dev::DeviceDriver
{
public:
    GPTDevice() : ILLM(), m_convo{std::make_unique<liboai::Conversation>()}
    {
    }

    // Rpc methods
    void setPrompt(const std::string &prompt) override;

    std::string readPrompt() override;

    std::string ask(const std::string &question) override;

    std::vector<std::pair<Author, Content>> getConversation() override;

    void deleteConversation() noexcept override;


    // Device initialization
    bool open(yarp::os::Searchable &config) override;

    bool close() override;

private:
    // data
    std::unique_ptr<liboai::Conversation> m_convo;

    // configuration
    std::string azure_resource;
    std::string azure_deployment_id;
    std::string azure_api_version;
    liboai::OpenAI oai;

    // model
    std::string m_model;
};

#endif