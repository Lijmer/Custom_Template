#ifndef INLCUDED_COMPONENTS_API_H
#define INCLUDED_COMPONENTS_API_H

#ifdef COMPONENTS_API_EXPORT
#define COMPONENTS_API __declspec(dllexport)
#else
#define COMPONENTS_API __declspec(dllimport)
#endif//COMPONENTS_API_EXPORT

#endif//INCLUDED_COMPONENTS_API_H
