/*
 * SPDX-FileCopyrightText: 2023-2023 Istituto Italiano di Tecnologia (IIT)
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#include "GPT_nwc_yarp.h"
#include <yarp/os/Log.h>
#include <yarp/os/LogComponent.h>
#include <yarp/os/LogStream.h>
#include <yarp/dev/GenericVocabs.h>

namespace
{
    YARP_LOG_COMPONENT(GPT_NWC_YARP, "yarp.device.GPT_nwc_yarp")
}

bool GPT_nwc_yarp::open(yarp::os::Searchable &config)
{
    std::string local_rpc = "/GPT/rpc";
    std::string remote_rpc = "/chat/rpc";
    if (!m_rpc_port_to_GPT_server.open(local_rpc))
    {
        yCError(GPT_NWC_YARP, "Cannot open rpc port, check network");
    }

    bool ok = false;

    ok = yarp::os::Network::connect(local_rpc, remote_rpc);

    if (!ok)
    {
        yCError(GPT_NWC_YARP, "open() error could not connect to %s", remote_rpc.c_str());
        return false;
    }

    if (!m_GPT_RPC.yarp().attachAsClient(m_rpc_port_to_GPT_server))
    {
        yCError(GPT_NWC_YARP, "Cannot attach the m_rpc_port_to_GPT_server port as client");
    }

    yCDebug(GPT_NWC_YARP) << "Opening of nwc successful";
    return true;
}

bool GPT_nwc_yarp::close()
{
    m_rpc_port_to_GPT_server.close();
    return true;
}

bool GPT_nwc_yarp::setPrompt(const std::string &prompt)
{
    return m_GPT_RPC.setPrompt(prompt);
}

bool GPT_nwc_yarp::readPrompt(std::string &oPrompt)
{
    auto ret = m_GPT_RPC.readPrompt();

    oPrompt = ret.prompt;
    return ret.ret;
}

bool GPT_nwc_yarp::ask(const std::string &question, std::string &oAnswer)
{
    auto ret = m_GPT_RPC.ask(question);

    oAnswer = ret.answer;
    return ret.ret;
}

bool GPT_nwc_yarp::getConversation(std::vector<std::pair<Author, Content>> &oConversation)
{
    auto ret = m_GPT_RPC.getConversation();
    for (const auto &[author, message] : ret.conversation)
    {
        oConversation.push_back(std::make_pair(author, message));
    }

    return true;
}

bool GPT_nwc_yarp::deleteConversation()
{
    return m_GPT_RPC.deleteConversation();
}