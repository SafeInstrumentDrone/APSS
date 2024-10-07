#include "Dust.hpp"
#include <cmath>
#include <cstdlib>

/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
// void Dust::setVelocity(const Velocity& velocity) {
//     // TODO: место для доработки
//     srand (time(NULL));
//     m_velosity = {1000., std::rand() % 360 + 1 };//velocity;
// }


int Dust::DeathKlockTick() {
    if (timeLive<0){
       this -> ~Dust();
    };
    return --timeLive;
}


