/*
 * SPDX-FileCopyrightText: 2006-2023 Istituto Italiano di Tecnologia (IIT)
 * SPDX-License-Identifier: BSD-3-Clause
 */

namespace yarp yarp.dev

struct Message {
    string sender
    string content
}

service IGPTMsgs {
    bool setPrompt_rpc(1: string prompt);
    string readPrompt_rpc();
    string ask_rpc(1: string question);
    list<Message> getConversation_rpc();
}