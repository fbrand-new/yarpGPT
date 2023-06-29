/*
 * SPDX-FileCopyrightText: 2006-2023 Istituto Italiano di Tecnologia (IIT)
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#include <yarp/dev/IGPTMsgs.h>
#include <yarp/dev/Message.h>
#include <ILLM.hpp>

class IGPTRPCd : public yarp::dev::IGPTMsgs
{
private:
    yarp::dev::ILLM *m_iLlm = nullptr;

public:
    void setInterface(yarp::dev::ILLM *_iLlm) { m_iLlm = _iLlm; }
    // From IGPTMsgs
    bool setPrompt(const std::string &prompt) override;
    std::string readPrompt() override;
    std::string ask(const std::string &question) override;
    std::vector<yarp::dev::Message> getConversation() override;
};