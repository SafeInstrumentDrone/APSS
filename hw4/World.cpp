#include "World.hpp"
#include "Painter.hpp"
#include <fstream>

// Длительность одного тика симуляции.
// Подробнее см. update()
// Изменять не следует
static constexpr double timePerTick = 0.001;
// Количество пылинок
static constexpr int dustCount = 100;

/**
 * Конструирует объект мира для симуляции
 * @param worldFilePath путь к файлу модели мира
 */
    std::istream& operator>>(std::istream& stream, Point& variable) {
        //  double x;
        //  double y;
        stream >> variable.x >> variable.y;
        // variable.x = x;
        // variable.y = y;      
        return stream;  
    };

    std::istream& operator>>(std::istream& stream, Velocity& variable) {
        double vx;
        double vy;        
        stream >> vx >> vy;
        variable.setVector({vx,vy});
        return stream;
    };

    std::istream& operator>>(std::istream& stream, Color& variable) {
        double red;
        double green;
        double blue;
        stream >> red >> green >> blue;
        variable = {red, green, blue};    //(red,green,blue);
        return stream;
    };


World::World(const std::string& worldFilePath) {

    std::ifstream stream(worldFilePath);
    /**
     * TODO: хорошее место для улучшения.
     * Чтение границ мира из модели
     * Обратите внимание, что здесь и далее мы многократно
     * читаем в объект типа Point, последовательно
     * заполняя координаты x и у. Если что-то делаем
     * многократно - хорошо бы вынести это в функцию
     * и не дублировать код...
     */
    stream >> topLeft.x >> topLeft.y >> bottomRight.x >> bottomRight.y;
    physics.setWorldBox(topLeft, bottomRight);

    /**
     * TODO: хорошее место для улучшения.
     * (x, y) и (vx, vy) - составные части объекта, также
     * как и (red, green, blue). Опять же, можно упростить
     * этот код, научившись читать сразу Point, Color...
     */


    // double x;
    // double y;
    Point p;

    // double vx;
    // double vy;
    Velocity v;

    double radius;

    // double red;
    // double green;
    // double blue;
    Color c;

    bool isCollidable;

    // Здесь не хватает обработки ошибок, но на текущем
    // уровне прохождения курса нас это устраивает
    while (stream.peek(), stream.good()) {
        // Читаем координаты центра шара (x, y) и вектор
        // его скорости (vx, vy)
        //stream >> x >> y >> vx >> vy;
        stream >> p; 
        //stream >> vx >> vy;
        stream >> v;
        // Читаем три составляющие цвета шара
        //stream >> red >> green >> blue;
        stream >> c;
        // Читаем радиус шара
        stream >> radius;
        // Читаем свойство шара isCollidable, которое
        // указывает, требуется ли обрабатывать пересечение
        // шаров как столкновение. Если true - требуется.
        // В базовой части задания этот параметр
        stream >> std::boolalpha >> isCollidable;
        // TODO: место для доработки.
        // Здесь не хватает самого главного - создания
        // объекта класса Ball со свойствами, прочитанными
        // выше, и его помещения в контейнер balls
        Ball ball;
        ball.setCenter(p);//{x,y});
        ball.setVelocity(v);//{vx,vy});//v
        ball.m_color = c;//{red, green, blue};
        ball.setRadius(radius);
        ball.isCollision = isCollidable;

        //if(radius>51.0){ball.isCollision=false;}
        // После того как мы каким-то образом
        // сконструируем объект Ball ball;
        // добавьте его в конец контейнера вызовом
         balls.push_back(ball);
    }

    srand (time(NULL));
    for (size_t i = 0; i < dustCount; i++)
    {
        Ball dust;
        //dust.setCenter({2400,1500});
        dust.m_color = {0.1,0.1,0.1};
        dust.isCollision = false;        
        //double b = std::rand() % 360 + 1;
        //Velocity a = {1000., std::rand() % 360 + 1}; 
        //dust.setVelocity({1000., std::rand() % 360 + 1});
        dust.setRadius(10);
        //int a = dust.getTimeLive;
        dusts.push_back(dust);
    }
    
    

}

/// @brief Отображает состояние мира
void World::show(Painter& painter) const {
    // Рисуем белый прямоугольник, отображающий границу
    // мира
    painter.draw(topLeft, bottomRight, Color(1, 1, 1));

    // Вызываем отрисовку каждого шара
    for (const Ball& ball : balls) {
        ball.draw(painter);
    }

    for (const Ball& dust : dusts){   //Dust
        dust.draw(painter);
    }

}

/// @brief Обновляет состояние мира
void World::update(double time) {
    /**
     * В реальном мире время течет непрерывно. Однако
     * компьютеры дискретны по своей природе. Поэтому
     * симуляцию взаимодействия шаров выполняем дискретными
     * "тиками". Т.е. если с момента прошлой симуляции
     * прошло time секунд, time / timePerTick раз обновляем
     * состояние мира. Каждое такое обновление - тик -
     * в physics.update() перемещаем шары и обрабатываем
     * коллизии - ситуации, когда в результате перемещения
     * один шар пересекается с другим или с границей мира.
     * В общем случае время не делится нацело на
     * длительность тика, сохраняем остаток в restTime
     * и обрабатываем на следующей итерации.
     */

    // учитываем остаток времени, который мы не "доработали" при прошлом update
    time += restTime;
    const auto ticks = static_cast<size_t>(std::floor(time / timePerTick));
    restTime = time - double(ticks) * timePerTick;

    
    physics.update(balls, ticks, collision);

    if(collision.isCollision){
         for (size_t i = 0; i < dustCount; i++){
             //double x = std::rand() % 2400 + 1;
             //double y = std::rand() % 1500 + 1;
               dusts[i].setCenter({collision.x,collision.y});  
               dusts[i].setVelocity({std::rand() % 3000 + 1, std::rand() % 360 + 1});
            } 
         collision.isCollision = false;   
    }

    physics.update(dusts, ticks, collision);
    
}