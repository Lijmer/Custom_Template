#ifndef INCLUDED_CYCLE_TIMER
#define INCLUDED_CYCLE_TIMER

#include <intrin.h>

class CycleTimer
{
public:
  CycleTimer() : m_start(0), m_end(0) {}

  void Start() { m_start = __rdtsc(); }
  __int64 End() { m_end = __rdtsc(); return m_end - m_start; }
  __int64 Interval() const { return m_end - m_start; }
private:
  __int64 m_start, m_end;
};

#endif//INCLUDED_CYCLE_TIMER