#include "../include/Helpers.hpp"

std::string readFile(std::string filepath)
{
    std::ifstream t(filepath);
    std::string str((std::istreambuf_iterator<char>(t)),
                     std::istreambuf_iterator<char>());
    return str;
}



int stringToInt(std::string text)
{
    int ret = 0;
    for (char& c : text)
    {
        ret += (int)c;
    }
    return ret;
}
