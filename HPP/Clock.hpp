#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <chrono>

class Clock
{
public:
  Clock()
  {
    this->tStamp1 = std::chrono::system_clock::now();
    this->tStamp2 = std::chrono::system_clock::now();
  }

  void Restart()
  {
    this->tStamp1 = std::chrono::system_clock::now();
  }

  float GetElapsedTime()
  {
    this->tStamp2 = std::chrono::system_clock::now();

    std::chrono::duration<float> elapsedTime = this->tStamp2 - this->tStamp1;

    float LastElapsedTime = elapsedTime.count();

    return LastElapsedTime;
  }

  float GetTimeSinceLast()
  {
    float elapsed = this->GetElapsedTime();
    this->Restart();

    return elapsed;
  }

private:

  std::chrono::time_point<std::chrono::system_clock> tStamp1, tStamp2;
};

#endif
