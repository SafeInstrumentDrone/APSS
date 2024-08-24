#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Dust {
private:
    Point m_center;    
    Velocity m_velosity;
    double m_mass;   
    double m_radius = 5;
    int timeLive = 10;
public:
    //~Dust();
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;    
    int getTimeLive();
    bool isCollision;
    Color m_color;
};
