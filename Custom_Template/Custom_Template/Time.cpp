#include "Time.h"
#include <Windows.h>

static LARGE_INTEGER ticksPerSecond;
static LARGE_INTEGER initTime;
static LARGE_INTEGER lastUpdate;

static float currentTime;
static float deltaTime;

namespace time
{
  namespace impl
  {
    void Init()
    {
      QueryPerformanceFrequency(&ticksPerSecond);
      QueryPerformanceCounter(&initTime);
      QueryPerformanceCounter(&lastUpdate);
    }
    void Update()
    {
      LARGE_INTEGER end = lastUpdate;
      QueryPerformanceCounter(&lastUpdate);
      deltaTime = float(lastUpdate.QuadPart - end.QuadPart) / float(ticksPerSecond.QuadPart);
      currentTime = float(lastUpdate.QuadPart - initTime.QuadPart) / float(ticksPerSecond.QuadPart);
    }
  }

  float GetDeltaTime()
  {
    return deltaTime;
  }
  float GetTime()
  {
    return currentTime;
  }
}
