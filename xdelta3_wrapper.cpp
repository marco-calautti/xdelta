#include "xdelta3_wrapper.h"

#include <stdlib.h>
#include <string.h>

extern "C"
{
    /**
    * Default command line like interface. The first parameter must be a dummy param for the executable name (e.g. xdelta 3)
    **/
    int xd3_main_cmdline(int argc, char** argv);
    extern void (*xprintf_message_func)(const char* msg);
}


static std::string _messages;
static void internal_printf(const char* msg) {
    _messages.append(msg);
}


std::string xd3_messages()
{
    return _messages;
}

int xd3_main_exec(const std::vector<std::string>& params)
{
    char** argv = new char* [params.size() + 2];
    argv[0] = new char[8] {'x', 'd', 'e', 'l', 't', 'a', '3', '\0'};

    int count = 1;
    for (auto& entry : params)
    {
        size_t len = entry.length() + 1;
        argv[count] = new char[len];
        std::copy(entry.begin(), entry.end(), argv[count]);
        argv[count][len - 1] = '\0';
        count++;
    }

    argv[count] = nullptr;

    xprintf_message_func = &internal_printf;
    _messages.clear();

    int ret = xd3_main_cmdline(count, argv);

    xprintf_message_func = nullptr;
    for (int i = 0; i < count; i++)
    {
        delete[] argv[i];
    }
    delete[] argv;
    return ret;
}
