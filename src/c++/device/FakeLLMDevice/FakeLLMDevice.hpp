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
    void setPrompt(const std::string &prompt) override;
    std::string readPrompt() override;
    std::string ask(const std::string &question) override;
    std::vector<std::pair<Author, Content>> getConversation() override;
    void deleteConversation() noexcept override;

private:
    std::vector<std::pair<Author, Content>> m_conversation;
};
