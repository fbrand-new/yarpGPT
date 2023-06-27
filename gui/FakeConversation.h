#ifndef __FAKECONVERSATION_H__
#define __FAKECONVERSATION_H__

#include <vector>
#include <string>

using author = std::string;

class FakeConversation
{

protected:
    std::vector<std::pair<author, std::string>> conversation;
};

#endif
