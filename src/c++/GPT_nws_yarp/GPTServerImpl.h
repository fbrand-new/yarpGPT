/*
 * SPDX-FileCopyrightText: 2023-2023 Istituto Italiano di Tecnologia (IIT)
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
    yarp::dev::return_readPrompt readPrompt() override;
    yarp::dev::return_ask ask(const std::string &question) override;
    yarp::dev::return_getConversation getConversation() override;
    bool deleteConversation() override;
};