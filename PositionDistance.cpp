
#include "PositionDistance.h"

class PositionDistance {
 private:
  int posDis[3];

 public:
  int getX() { return posDis[0]; }
  int getY() { return posDis[1]; }
  int getDistance() { return posDis[2]; }
};
