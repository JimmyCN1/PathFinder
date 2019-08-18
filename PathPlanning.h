
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

  // goes to one of the four possible next positions in th maze
  // and checks to see if they are traversable
  // if true, they are added to the reachable list
  void checkStep(int xStep,
                 int yStep,
                 PDPtr currentSelection,
                 PDList* reachablePositions);

  bool oneStepCloser(PositionDistance* position,
                     PositionDistance* previousPosition,
                     int goalX,
                     int goalY);

  bool oneStep(PositionDistance* nextPosition,
               PositionDistance* previousPosition);

  bool goalReached(PositionDistance* position, int goalX, int goalY);

  Grid maze;
  int rows;
  int cols;
  int initialX;
  int initialY;
};

#endif  // COSC_ASS_ONE_PATH_PLANNING
