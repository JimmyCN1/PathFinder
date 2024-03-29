
#ifndef COSC_ASS_ONE_PATH_PLANNING
#define COSC_ASS_ONE_PATH_PLANNING

#include "PDList.h"
#include "PositionDistance.h"
#include "Types.h"

class PathPlanning {
  public:
  /*                                           */
  /* DO NOT MODIFY ANY CODE IN THIS SECTION    */
  /*                                           */

  // Initialise a with a given maze of size (x,y)
  PathPlanning(Grid maze, int rows, int cols);

  // Clean-up
  ~PathPlanning();

  // The initial position
  void initialPosition(int x, int y);

  // Method for Milestone 2
  // Return a DEEP COPY of the PDList of all position-distance's
  //    that the robot can reach
  PDList* getReachablePositions();

  // Method for Milestone 3
  // Get the path from the starting position to the given co-ordinate
  //    The path should be a DEEP COPY
  PDList* getPath(const int& toX, const int& toY);

  /*                                           */
  /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
  /*                                           */

  void setReachablePositions(PDPtr currentPosition, PDList* reachablePositions);

  bool checkStep(const int xStep, const int yStep, const PDPtr currentPosition);

  void setNextReachablePosition(int xStep, int yStep, PDPtr currentPosition,
      PDList* reachablePositions);

  bool isSingleStep(PDPtr currentPosition, PDPtr potentialPosition);

  Grid maze;
  int rows;
  int cols;
  int initialX;
  int initialY;
};

#endif // COSC_ASS_ONE_PATH_PLANNING
