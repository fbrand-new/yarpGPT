/*
 * SPDX-FileCopyrightText: 2006-2023 Istituto Italiano di Tecnologia (IIT)
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#include <GPTServerImpl.h>
#include <yarp/os/LogComponent.h>
#include <yarp/os/LogStream.h>
#include <yarp/os/Log.h>

namespace {
YARP_LOG_COMPONENT(GPTSERVER, "yarp.device.GPTServer")
}

bool IGPTRPCd::setPrompt(const std::string &prompt)
{
    if (m_iLlm == nullptr)
    {
        yCError(GPTSERVER, "Invalid interface");
        return false;
    }
    // TODO: maybe we can catch errors here, that would be better
    m_iLlm->setPrompt(prompt);
    return true;
}

std::string IGPTRPCd::readPrompt()
{

    std::string ret;

    if (m_iLlm == nullptr)
    {
        yCError(GPTSERVER, "Invalid interface");
        return ret;
    }
    ret = m_iLlm->readPrompt();
    return ret;
}

std::string IGPTRPCd::ask(const std::string &question)
{
    std::string ret;
    if (m_iLlm == nullptr)
    {
        yCError(GPTSERVER, "Invalid interface");
        return ret;
    }
    ret = m_iLlm->ask(question);
    return ret;
}

std::vector<yarp::dev::Message> IGPTRPCd::getConversation()
{
    std::vector<yarp::dev::Message> ret;
    if (m_iLlm == nullptr)
    {
        yCError(GPTSERVER, "Invalid interface");
        return ret;
    }
    // TODO: here we actually realize that this is not doable like this. We should actually return a string.
    // Actually this is not true, RPC should be able to handle this, after all if you can define it in thrift I expect some magic stuff to happen behind the curtains
    const auto &conversation = m_iLlm->getConversation();

    for (const auto &[author, message] : conversation)
    {
        ret.push_back(yarp::dev::Message(author, message));
    }

    return ret;
}

bool IGPTRPCd::deleteConversation()
{
    if(m_iLlm == nullptr)
    {
        yCError(GPTSERVER, "Invalid interface");
    }

    m_iLlm->deleteConversation();
    return true;
}