/*
 * SPDX-FileCopyrightText: 2006-2023 Istituto Italiano di Tecnologia (IIT)
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#include <yarp/os/Network.h>
#include <yarp/dev/DeviceDriver.h>
#include <yarp/dev/Message.h>
#include <yarp/dev/IGPTMsgs.h>
#include <ILLM.hpp>

class GPT_nwc_yarp : public yarp::dev::DeviceDriver,
                     public yarp::dev::ILLM
{
protected:
    // thrift interface
    yarp::dev::IGPTMsgs m_GPT_RPC;

    // rpc port
    yarp::os::Port m_rpc_port_to_GPT_server;

public:

    //From DeviceDriver
    bool open(yarp::os::Searchable& config) override;
    bool close() override;

    //From ILLM
    void setPrompt(const std::string& prompt) override;
    std::string readPrompt() override;
    std::string ask(const std::string& question) override;
    std::vector<std::pair<Author,Content>> getConversation() override;
    void deleteConversation() override;
};