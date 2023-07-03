/*
 * SPDX-FileCopyrightText: 2023-2023 Istituto Italiano di Tecnologia (IIT)
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include <FakeLLMDevice.hpp>

void FakeLLMDevice::setPrompt(const std::string &prompt)
{
    m_conversation.push_back(std::make_pair("system",prompt));
}

std::string FakeLLMDevice::readPrompt()
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

std::string FakeLLMDevice::ask(const std::string &question)
{
    //In the fake device we ignore the question
    std::string answer = "Fatti non foste per viver come bruti \n ma per seguir virtute e canoscenza.";
    m_conversation.push_back(std::make_pair("user",question));
    m_conversation.push_back(std::make_pair("assistant",answer));
    return answer;
}

std::vector<std::pair<Author,Content>> FakeLLMDevice::getConversation() 
{
    return m_conversation;
}

void FakeLLMDevice::deleteConversation() noexcept
{
    m_conversation.clear();
}