/*
 * SPDX-FileCopyrightText: 2006-2023 Istituto Italiano di Tecnologia (IIT)
 * SPDX-FileCopyrightText: 2006-2010 RobotCub Consortium
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef YARP_DEV_ILLM_H
#define YARP_DEV_ILLM_H

#include <yarp/dev/api.h>
#include <string>
#include <vector>
#include <map>

typedef std::string Author;
typedef std::string Content;

namespace yarp::dev
{

    class YARP_dev_API ILLM
    {
    public:
        ILLM() {}

        virtual ~ILLM() {}

        virtual void setPrompt(const std::string &prompt) = 0;

        virtual std::string readPrompt() = 0;

        virtual std::string ask(const std::string &question) = 0;

        virtual std::vector<std::pair<Author, Content>> getConversation() = 0;

        virtual void deleteConversation() = 0;
    };

}

#endif