#ifndef __HELPERS__
#define __HELPERS__
#pragma once

#include <cstdint>
#include <cstdarg>

#include <stdio.h>
#include <string>
#include <fstream>
#include <streambuf>

#define LOG_ERROR -1
#define LOG_WARNING 1
#define LOG_PLAIN 0
#define LOG_INFO 2
#define LOG_LUA_ERR 3

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define IXLOG(x, y, z) { ix_logprint(x, y, z); }

string readFile(string filepath);
//
string uint8_tToString(uint8_t* text, size_t len);

void ix_logprint(const char* msg, int type, bool breakln=false);

template <class DstType, class SrcType>
bool IsType(const SrcType* src)
{
  return dynamic_cast<const DstType*>(src) != 0;
}

#endif
