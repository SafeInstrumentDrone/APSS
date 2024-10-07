#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"
#include "Ball.hpp"

class Dust : public Ball{
private:
    int timeLive = 10;
public:
    int DeathKlockTick();
};
