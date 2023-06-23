/*
 * SPDX-FileCopyrightText: 2006-2023 Istituto Italiano di Tecnologia (IIT)
 * SPDX-FileCopyrightText: 2006-2010 RobotCub Consortium
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef YARP_DEV_ILLM_H
#define YARP_DEV_ILLM_H

#include <yarp/dev/api.h>
#include <string>

namespace yarp::dev
{

    class YARP_dev_API ILLM
    {
    public:
        ILLM() {}

        virtual ~ILLM() {}

        virtual void setPrompt(const std::string &prompt) = 0;

        virtual const std::string readPrompt() const = 0;

        virtual const std::string ask(const std::string &question) = 0;

        virtual const std::string getConversation() const = 0;

    };

}

#endif