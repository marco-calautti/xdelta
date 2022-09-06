#include "xdelta3_wrapper.h"

#include <vector>

static std::string _messages;
static void internal_printf(const char* msg){
    _messages.append(msg);
}
/**
 * Default command line like interface. The first parameter must be a dummy param for the executable name (e.g. xdelta 3)
 **/
int xd3_main_cmdline(int argc, char **argv);

extern void (*xprintf_message_func)(const char* msg);

std::string xd3_messages()
{
    return _messages;
}

int xd3_main_exec(std::map<std::string,std::string> params)
{
    char** argv = new char*[params.size()*2];
    argv[0] = new char[8]{'x','d','e','l','t','a','3','\0'};
    int count = 1;
    for(auto entry: params)
    {
        size_t len = entry.first.length()+1;
        argv[count] = new char[len];
        std::copy(entry.first.begin(),entry.first.end(),argv[count]);
        argv[count][len]='\0';
        count++;
        if(!entry.second.empty())
        {
            len = entry.second.length()+1;
            argv[count] = new char[len];
            std::copy(entry.second.begin(),entry.second.end(),argv[count]);
            argv[count][len]='\0';
            count++;
        }
    }

    xprintf_message_func = &internal_printf;
    _messages.clear();

    int ret = xd3_main_cmdline(count, argv);

    xprintf_message_func = nullptr;
    return ret;
}
