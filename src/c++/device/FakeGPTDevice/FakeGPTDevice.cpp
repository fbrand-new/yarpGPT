/*
 * SPDX-FileCopyrightText: 2006-2023 Istituto Italiano di Tecnologia (IIT)
 * SPDX-FileCopyrightText: 2006-2010 RobotCub Consortium
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include <FakeGPTDevice.hpp>

void FakeGPTDevice::setPrompt(const std::string &prompt)
{
    m_conversation.push_back(std::make_pair("system",prompt));
}

std::string FakeGPTDevice::readPrompt()
{
    for (const auto& [author, content]: m_conversation)
    {
        if(author == "prompt")
        {
            return content;
        }
    }

    return "";
}

std::string FakeGPTDevice::ask(const std::string &question)
{
    //In the fake device we ignore the question
    std::string answer = "Fatti non foste per viver come bruti \n ma per seguir virtute e canoscenza.";
    m_conversation.push_back(std::make_pair("user",question));
    m_conversation.push_back(std::make_pair("assistant",answer));
    return answer;
}

std::vector<std::pair<Author,Content>> FakeGPTDevice::getConversation() 
{
    return m_conversation;
}

void FakeGPTDevice::deleteConversation() noexcept
{
    m_conversation.clear();
}