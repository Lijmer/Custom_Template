#include "StringFunctions.h"
#include <cstring>

namespace str_funcs
{
  char* StringDuplicate(const char* original)
  {
    int len = strlen(original);
    char* retVal = new char[len + 1]; //add null terminator
    CopyString(retVal, original);
    return retVal;
  }

  void CopyString(char* dst, const char* src)
  {
    while((*dst++ = *src++) != 0) {}
  }
}
