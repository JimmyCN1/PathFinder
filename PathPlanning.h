
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

  void getPath(PDList* path, const int& toX, const int& toY, bool& pathFound);

  void setReachablePositions(PDPtr currentPosition, PDList* reachablePositions);

  bool isDeadEnd(PDPtr currentPosition, PDList* traversed);

  // goes to one of the four possible next positions in th maze
  // and checks to see if they are traversable
  // if true, they are added to the reachable list
  bool checkStep(const int xStep, const int yStep, const PDPtr currentPosition);

  // returns true if passed position is traversible
  bool checkStep(PDPtr nextPosition);

  void setNextReachablePosition(int xStep,
                                int yStep,
                                PDPtr currentPosition,
                                PDList* reachablePositions);

  bool goalReached(PositionDistance* position, int goalX, int goalY);

  Grid maze;
  int rows;
  int cols;
  int initialX;
  int initialY;
  PDList* quickestPath;
  PDList* badPositionDistances;
};

#endif  // COSC_ASS_ONE_PATH_PLANNING
