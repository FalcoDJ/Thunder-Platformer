#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <chrono>

class Clock
{
public:
  Clock()
  {
    tStamp1 = std::chrono::system_clock::now();
    tStamp2 = std::chrono::system_clock::now();
  }

  void Restart()
  {
    tStamp1 = std::chrono::system_clock::now();
  }

  float GetElapsedTime()
  {

    tStamp2 = std::chrono::system_clock::now();

    std::chrono::duration<float> elapsedTime = tStamp2 - tStamp1;

    float LastElapsedTime = elapsedTime.count();

    return LastElapsedTime;
  }

private:

  std::chrono::time_point<std::chrono::system_clock> tStamp1, tStamp2;
};

#endif
