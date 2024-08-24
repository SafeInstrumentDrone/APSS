#include "Dust.hpp"
#include <cmath>
#include <cstdlib>

/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Dust::setVelocity(const Velocity& velocity) {
    // TODO: место для доработки
    srand (time(NULL));
    m_velosity = {1000., std::rand() % 360 + 1 };//velocity;
}

/**
 * @return скорость объекта
 */
Velocity Dust::getVelocity() const {
    // TODO: место для доработки
    return {m_velosity};
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Dust абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Dust::draw(Painter& painter) const {
    // TODO: место для доработки
    
//    Point a {100,200};
 //   double d = 1000;
//    Color c {123,200,100};

    painter.draw(m_center,m_radius,m_color);
   // painter.draw( {100,200}, {200,300},{23,99,127});

}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Dust::setCenter(const Point& center) {
    // TODO: место для доработки
    m_center = center;
    //m_center.x = center.x;
    //m_center.y = center.y;
}

/**
 * @return центр объекта
 */
Point Dust::getCenter() const {
    // TODO: место для доработки

    //Point a {m_center.x,m_center.y};
    return m_center;//{};
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Dust::getRadius() const {
    // TODO: место для доработки
    return m_radius;//{};
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double Dust::getMass() const {
    // TODO: место для доработки
    return m_mass;//{};
}

int Dust::getTimeLive() {
    if (timeLive<0){
       this -> ~Dust();
    }
    return --timeLive;
}


