#ifndef INCLUDED_STRING_FUNCTIONS_H
#define INCLUDED_STRING_FUNCTIONS_H
#include "API.h"
namespace str_funcs
{
  //Allocates string using new, copies string
  UTILITIES_API char* StringDuplicate(const char*);

  UTILITIES_API void CopyString(char* dst, const char* src);
}

#endif//INCLUDED_STRING_FUNCTIONS_H
