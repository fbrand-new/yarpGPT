/*
 * SPDX-FileCopyrightText: 2023-2023 Istituto Italiano di Tecnologia (IIT)
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <FakeLLMDevice.hpp>

bool FakeLLMDevice::setPrompt(const std::string &prompt)
{
    m_conversation.push_back(std::make_pair("system", prompt));
}

bool FakeLLMDevice::readPrompt(std::string &oPrompt)
{
    for (const auto &[author, content] : m_conversation)
    {
        if (author == "prompt")
        {
            oPrompt = content;
            return false;
        }
    }

    return false;
}

bool FakeLLMDevice::ask(const std::string &question, std::string &oAnswer)
{
    // In the fake device we ignore the question
    std::string answer = "Fatti non foste per viver come bruti ma per seguir virtute e canoscenza";
    m_conversation.push_back(std::make_pair("user", question));
    m_conversation.push_back(std::make_pair("assistant", answer));
    oAnswer = answer;
    return true;
}

bool FakeLLMDevice::getConversation(std::vector<std::pair<Author, Content>>& oConversation)
{
    oConversation = m_conversation;
    return true;
}

bool FakeLLMDevice::deleteConversation() noexcept
{
    m_conversation.clear();
    return true;
}