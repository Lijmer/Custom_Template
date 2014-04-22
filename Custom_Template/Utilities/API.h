#ifndef INCLUDED_UTILITIES_API_H
#define INCLUDED_UTILITIES_API_H

#ifdef UTILITIES_API_EXPORT
#define UTILITIES_API __declspec(dllexport)
#else
#define UTILITIES_API __declspec(dllimport)
#endif

#endif//INCLUDED_UTILITIES_API_H
