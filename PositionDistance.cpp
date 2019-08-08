
#include "PositionDistance.h"

int PositionDistance::getX() { return std::get<0>(PDTuple); }
int PositionDistance::getY() { return std::get<1>(PDTuple); }
int PositionDistance::getDistance() { return std::get<2>(PDTuple); }
