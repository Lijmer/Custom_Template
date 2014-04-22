#include "Time.h"
#include "TimeImpl.h"
#include <Windows.h>

static LARGE_INTEGER ticksPerSecond;
static LARGE_INTEGER initTime;
static LARGE_INTEGER lastUpdate;

static LARGE_INTEGER updateDelay;
static LARGE_INTEGER nextGameTick;

static void(*fixedUpdateFunctor)();

static float deltaTime;
static float currentTime;


namespace time
{
  namespace impl
  {
    
    void Init()
    {
      QueryPerformanceFrequency(&ticksPerSecond);
      QueryPerformanceCounter(&initTime);
      QueryPerformanceCounter(&lastUpdate);
      nextGameTick.QuadPart = lastUpdate.QuadPart + updateDelay.QuadPart;
      updateDelay.QuadPart = (long long)(ticksPerSecond.QuadPart / 60);
    }

    void Update()
    {
      LARGE_INTEGER end = lastUpdate;
      QueryPerformanceCounter(&lastUpdate);
      
      deltaTime = float(lastUpdate.QuadPart - end.QuadPart) / float(ticksPerSecond.QuadPart);
      currentTime = float(lastUpdate.QuadPart - initTime.QuadPart) / float(ticksPerSecond.QuadPart);
      
      int loops = 0;
      while(lastUpdate.QuadPart > nextGameTick.QuadPart && ++loops < 10)
      {
        if(fixedUpdateFunctor)
          fixedUpdateFunctor();
        nextGameTick.QuadPart += updateDelay.QuadPart;
      }
    }

    void SetFixedUpdateCallback(void(*f)())
    {
      fixedUpdateFunctor = f;
    }

  } //impl

  float GetDeltaTime()
  {
    return deltaTime;
  }
  float GetTime()
  {
    return currentTime;
  }
} //time
