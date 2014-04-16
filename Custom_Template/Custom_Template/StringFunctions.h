#ifndef INCLUDED_STRING_FUNCTIONS_H
#define INCLUDED_STRING_FUNCTIONS_H

namespace str_funcs
{
  //Allocates string using new, copies string
  char* StringDuplicate(const char*);

  void CopyString(char* dst, const char* src);
}

#endif//INCLUDED_STRING_FUNCTIONS_H