#include "../include/Helpers.hpp"

std::string readFile(std::string filepath)
{
    std::ifstream t(filepath);

    if (!t)
    {
        IXLOG("IO Error: ", LOG_ERROR, false);
        IXLOG(filepath.c_str(), LOG_INFO, false);
        IXLOG(" - No such file or directory.", LOG_PLAIN, true);
        std::exit(-1);
    }

    std::string str((std::istreambuf_iterator<char>(t)),
                     std::istreambuf_iterator<char>());
    return str;
}


std::string uint8_tToString(uint8_t *text, size_t len)
{
    return std::string(text, text+len);
}

void ix_logprint(const char *msg, int type, bool breakln)
{
    switch (type)
    {
        case LOG_ERROR:
            printf("%s%s%s", ANSI_COLOR_RED, msg, ANSI_COLOR_RESET);
            break;
        case LOG_INFO:
            printf("%s%s%s", ANSI_COLOR_BLUE, msg, ANSI_COLOR_RESET);
            break;
        case LOG_LUA_ERR:
            printf("%s%s%s", ANSI_COLOR_RED, msg, ANSI_COLOR_RESET);
            break;
        case LOG_PLAIN:
            printf("%s%s%s", ANSI_COLOR_RESET, msg, ANSI_COLOR_RESET);
            break;
        case LOG_WARNING:
            printf("%s%s%s", ANSI_COLOR_YELLOW, msg, ANSI_COLOR_RESET);
            break;
    }
    if (breakln)
        printf("\n");
}
