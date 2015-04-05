#ifndef __HELPERS__
#define __HELPERS__
#pragma once

#include <cstdint>
#include <stdio.h>
#include <string>
#include <fstream>
#include <streambuf>

std::string readFile(std::string filepath);
//

template <class DstType, class SrcType>
bool IsType(const SrcType* src)
{
  return dynamic_cast<const DstType*>(src) != 0;
}
std::string uint8_tToString(uint8_t* text, size_t len);

#endif
