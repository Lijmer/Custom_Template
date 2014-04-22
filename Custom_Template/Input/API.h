#ifndef INCLUDED_API_H
#define INLCUDED_API_H

#ifdef INPUT_API_EXPORT
#define INPUT_API __declspec(dllexport)
#else
#define INPUT_API __declspec(dllimport)
#endif//INPUT_API_EXPORT

#endif//INCLUDED_API_H
