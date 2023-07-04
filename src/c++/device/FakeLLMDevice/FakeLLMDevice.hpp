/*
 * SPDX-FileCopyrightText: 2023-2023 Istituto Italiano di Tecnologia (IIT)
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <ILLM.hpp>
#include <vector>
#include <yarp/dev/DeviceDriver.h>

class FakeLLMDevice : public yarp::dev::ILLM,
                      public yarp::dev::DeviceDriver
{

public:
    FakeLLMDevice() : m_conversation{} {}
    bool setPrompt(const std::string &prompt) override;
    bool readPrompt(std::string &oPromp) override;
    bool ask(const std::string &question, std::string &oAnswer) override;
    bool getConversation(std::vector<std::pair<Author, Content>> &oConversation) override;
    bool deleteConversation() noexcept override;

private:
    std::vector<std::pair<Author, Content>> m_conversation;
};
