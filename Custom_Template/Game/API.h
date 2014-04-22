#ifndef INCLUDED_GAME_API_H
#define INCLUDED_GAME_API_H

#ifdef GAME_API_EXPORT
#define GAME_API __declspec(dllexport) 
#else
#define GAME_API __declspec(dllimport) 
#endif

#endif//INCLUDED_RENDERER_API_H
