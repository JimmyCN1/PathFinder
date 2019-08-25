
#include "PositionDistance.h"

#include <iostream>

PositionDistance::PositionDistance(const int& x, const int& y,
    const int& dist)
{
  this->x = x;
  this->y = y;
  this->dist = dist;
}

PositionDistance::PositionDistance(PositionDistance* originalPositionDistance)
{
  this->x = originalPositionDistance->getX();
  this->y = originalPositionDistance->getY();
  this->dist = originalPositionDistance->getDistance();
}

PositionDistance::~PositionDistance() {}

int PositionDistance::getX() { return this->x; }
int PositionDistance::getY() { return this->y; }
int PositionDistance::getDistance() { return this->dist; }

std::string PositionDistance::getPositionDistance()
{
  return "PosiDistance__ x: " + std::to_string(x) + ", y: " + std::to_string(y) + ", dist: " + std::to_string(dist);
}

// return true if x, y coordinates equal position's x, y coordinates
bool PositionDistance::equals(PositionDistance* position)
{
  return (this->x == position->getX() && this->y == position->getY());
}