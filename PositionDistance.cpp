
#include "PositionDistance.h"

PositionDistance::PositionDistance(int x, int y, int dist) {
  this->x = x;
  this->y = y;
  this->dist = dist;
}

PositionDistance::PositionDistance(PositionDistance* originalPositionDistance) {
  this->x = originalPositionDistance->getX();
  this->y = originalPositionDistance->getY();
  this->dist = originalPositionDistance->getDistance();
}

PositionDistance::PositionDistance() {
  this->x = 0;
  this->y = 0;
  this->dist = 0;
}

int PositionDistance::getX() {
  return this->x;
}
int PositionDistance::getY() {
  return this->y;
}
int PositionDistance::getDistance() {
  return this->dist;
}

std::string PositionDistance::getPositionDistance() {
  return "PosiDistance__ x: " + std::to_string(x) +
         ", y: " + std::to_string(y) + ", dist: " + std::to_string(dist);
}