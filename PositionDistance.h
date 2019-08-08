
#ifndef COSC_ASS_ONE_POSITION
#define COSC_ASS_ONE_POSITION

#include "Types.h"

#include <tuple>

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
 private:
  std::tuple<int, int, int> PDTuple;
};

/*                                           */
/* DO NOT MOFIFY THIS TYPEDEF                */
/*                                           */
// Pointer to a Position-Distance
typedef PositionDistance* PDPtr;
typedef std::tuple<int, int, int> PDTuple;

#endif  // COSC_ASS_ONE_POSITION
