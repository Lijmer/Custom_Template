#ifndef INCLUDED_RENDERER_API_H
#define INCLUDED_RENDERER_API_H

#ifdef RENDERER_DLL_EXPORT
#define RENDERER_API __declspec(dllexport) 
#else
#define RENDERER_API __declspec(dllimport) 
#endif

#endif//INCLUDED_RENDERER_API_H
