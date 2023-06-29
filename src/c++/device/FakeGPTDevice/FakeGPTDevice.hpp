/*
 * SPDX-FileCopyrightText: 2006-2023 Istituto Italiano di Tecnologia (IIT)
 * SPDX-FileCopyrightText: 2006-2010 RobotCub Consortium
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <ILLM.hpp>
#include <vector>
#include <yarp/dev/DeviceDriver.h>

class FakeGPTDevice : public yarp::dev::ILLM,
                      public yarp::dev::DeviceDriver
{

public:
    FakeGPTDevice() : m_conversation{} {}
    void setPrompt(const std::string &prompt) override;
    std::string readPrompt() override;
    std::string ask(const std::string &question) override;
    std::vector<std::pair<Author, Content>> getConversation() override;

private:
    std::vector<std::pair<Author, Content>> m_conversation;
};
