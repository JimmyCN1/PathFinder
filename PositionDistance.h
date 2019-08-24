
#ifndef COSC_ASS_ONE_POSITION
#define COSC_ASS_ONE_POSITION

#include "Types.h"

#include <string>

class PositionDistance {
public:
  /*                                           */
  /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
  /*                                           */

  // x-co-ordinate
  int getX();

  // y-co-ordinate
  int getY();

  // Distance
  int getDistance();

  /*                                           */
  /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
  /*                                           */
  // constructor
  PositionDistance(const int &x, const int &y, const int &dist);

  // copy constructor
  PositionDistance(PositionDistance *originalPositionDistance);

  PositionDistance();

  ~PositionDistance();

  std::string getPositionDistance();

  // return true if x, y coordinates equal position's x, y coordinates
  bool equals(PositionDistance *position);

private:
  int x;
  int y;
  int dist;
};

/*                                           */
/* DO NOT MOFIFY THIS TYPEDEF                */
/*                                           */
// Pointer to a Position-Distance
typedef PositionDistance *PDPtr;

#endif // COSC_ASS_ONE_POSITION
