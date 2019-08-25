
/*
  Milestone 2
  This milestone involved implementing the given algorithm and to return the deep copy of all the reachable positions.
  The implementation of this algorithm was pretty straight forward. In order to make the algorithm more efficient, 
  I deleted the heap allocated startingPosition directly after it was added to the reachable positions array since,
  after this, it would not be referenced again in the algorithm.
  Similarly, the heap allocated reachablePositions array and the tempPositions array were deleted at the end of the 
  algorithm, after the deep copy had been performed.
  I decided to create the methods containsAllCoordinatesFromArray, setReachablPositions and removeAt in order to 
  improve the code readability of the function.
  The positive aspects of this algorithm is that it effienctly deallocates memory at the right times. However, the 
  negative aspects could be that there could maybe be less heap allocation going on as heap allocation of memory is 
  more costly than allocating memory on the stack

  Milestone 3/4
  The approach taken in the algorithm designed for milestone three was to start at the goal and work backwards towards
  the initial position, appending the next closest step to the back of an array, before reversing the array and returning
  this as a deep copy of the quickest path from the initial position to the goal. 
  This implementation is efficient because it uses the previously generated reachable positions from the previous milestone
  rather than to find the positions from scratch. Because it uses the distance penalty of each position distance as a check
  and the the relative position of the next position from the current position, the algorthim really only has a few 
  posibilities to check at each step. Another method way to develop this algorithm would have been via recursion to 
  recursively generate all the traversible positions from the current position and havent already been traversed in that
  path and then recurse again on the newly incremented path. This method might be more flexible or more widely applicable 
  in however, with the help of the algortithm from milestone 2, this option quickly becomes much more inefficient than 
  simply working backwards from the goal.
  This implementation is efficient since it uses the previously generated reachablePositions array to generate the quickest
  path. The algoritihm will only check steps that are one step closer to the goal and that are adjacent, hence, the amount
  of computation required to get the quickest path is at a minimum. the algorithm also prevents any memory leakage and 
  uses the addBack helper function which creates arrays of the correct size in order to efficiently use memory.

*/
#define EMPTY 0
#define INITIAL_DISTANCE 0
#define NO_STEP 0
#define STEP 1
#define FORWARD_STEP 1
#define BACKWARD_STEP -1
#define FIRST_POSITION 0
#define FIRST_STEP 1

#include "PathPlanning.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

PathPlanning::PathPlanning(Grid maze, int rows, int cols)
{
  if (rows > EMPTY && cols > EMPTY) {
    this->maze = new char*[rows];
    for (int row = FIRST_POSITION; row < rows; row++) {
      this->maze[row] = new char[cols];
    }
    for (int row = FIRST_POSITION; row < rows; row++) {
      for (int col = FIRST_POSITION; col < cols; col++) {
        this->maze[row][col] = maze[row][col];
      }
    }
    this->rows = rows;
    this->cols = cols;
  }
}

PathPlanning::~PathPlanning()
{
  for (int row = FIRST_POSITION; row < rows; row++) {
    delete maze[row];
  }
  delete[] maze;
}

void PathPlanning::initialPosition(int x, int y)
{
  this->initialX = x;
  this->initialY = y;
}

PDList* PathPlanning::getReachablePositions()
{
  // initialisation
  PDPtr startingPoint = new PositionDistance(initialX, initialY, INITIAL_DISTANCE);
  PDList* reachablePositions = new PDList();
  PDList* tempPositions = new PDList();
  PDPtr currentPosition = nullptr;

  // P initially containing x (initial position)
  reachablePositions->addBack(new PositionDistance(startingPoint));
  delete startingPoint;

  // main algorithm to obtain reachable positions
  do {
    int iterations = reachablePositions->size();
    for (int i = FIRST_POSITION; i < iterations; i++) {
      currentPosition = reachablePositions->get(i);
      if (!tempPositions->containsCoordinate(currentPosition)) {
        setReachablePositions(currentPosition, reachablePositions);
        tempPositions->addBack(new PositionDistance(currentPosition));
      }
    }
  } while (!tempPositions->containsAllCoordinatesFromArray(reachablePositions));

  // create deepCopy of reachable positions
  PDList* deepCopyReachablePositions = new PDList(reachablePositions);
  deepCopyReachablePositions->removeAt(FIRST_POSITION);

  delete reachablePositions;
  delete tempPositions;

  return deepCopyReachablePositions;
}

// THIS IS FOR MILESTONE 3 ONLY
//    ONLY IMPLEMENT THIS IF YOU ATTEMPT MILESTONE 3
PDList* PathPlanning::getPath(const int& toX, const int& toY)
{
  // initialisation
  PDPtr startingPoint = new PositionDistance(this->initialX, this->initialY, NO_STEP);
  PDList* reachablePositions = getReachablePositions();
  reachablePositions->addBack(startingPoint);
  // find and set the goal pointer
  PDPtr goal = nullptr;
  for (int i = 0; i < reachablePositions->size(); i++) {
    if (reachablePositions->get(i)->getX() == toX &&
        reachablePositions->get(i)->getY() == toY) {
      goal = new PositionDistance(toX, toY, reachablePositions->get(i)->getDistance());
    }
  }

  PDList* reversePath = new PDList();
  reversePath->addBack(goal);
  int steps = NO_STEP;
  bool startingPointReached = false;

  // path finding algorithm
  while (!startingPointReached || steps < goal->getDistance()) {
    PDPtr currentPosition = reversePath->getLast();
    for (int i = 0; i < reachablePositions->size(); i++) {
      PDPtr potentialPosition = reachablePositions->get(i);
      if (!reversePath->containsCoordinate(potentialPosition)) {
        // check if potentialPosition is one step closer to the initPos
        if (currentPosition->getDistance() - potentialPosition->getDistance() == STEP) {
          // check if potentialPosition is adjacent to currentPosition
          if (isSingleStep(currentPosition, potentialPosition)) {
            reversePath->addBack(new PositionDistance(potentialPosition));
          }
        }
      }
    }
    if (currentPosition->equals(startingPoint)) {
      startingPointReached = true;
    }
    steps++;
  }

  // deep copy of path in the correct order (initPos -> goal)
  PDList* deepCopyPath = new PDList();
  for (int i = reversePath->size() - STEP; i >= NO_STEP; i--) {
    deepCopyPath->addBack(new PositionDistance(reversePath->get(i)));
  }

  delete goal;
  delete startingPoint;
  delete reversePath;

  return deepCopyPath;
}

// add a step in all traversible directions to the
// passed reachable positions array
void PathPlanning::setReachablePositions(PDPtr currentPosition,
    PDList* reachablePositions)
{
  // check one step up
  if (checkStep(NO_STEP, BACKWARD_STEP, currentPosition)) {
    setNextReachablePosition(NO_STEP, BACKWARD_STEP, currentPosition,
        reachablePositions);
  }
  // check one step down
  if (checkStep(NO_STEP, FORWARD_STEP, currentPosition)) {
    setNextReachablePosition(NO_STEP, FORWARD_STEP, currentPosition,
        reachablePositions);
  }
  // check one step left
  if (checkStep(BACKWARD_STEP, NO_STEP, currentPosition)) {
    setNextReachablePosition(BACKWARD_STEP, NO_STEP, currentPosition,
        reachablePositions);
  }
  // check one step right
  if (checkStep(FORWARD_STEP, NO_STEP, currentPosition)) {
    setNextReachablePosition(FORWARD_STEP, NO_STEP, currentPosition,
        reachablePositions);
  }
}

// returns true if the postion passed is traversible
bool PathPlanning::checkStep(const int xStep, const int yStep,
    const PDPtr currentPosition)
{
  return (this->maze[currentPosition->getY() + yStep]
                    [currentPosition->getX() + xStep]
      == '.');
}

// adds the next reachable position to the passes array
void PathPlanning::setNextReachablePosition(int xStep, int yStep,
    PDPtr currentPosition,
    PDList* reachablePositions)
{
  PDPtr nextPosition = new PositionDistance(
      currentPosition->getX() + xStep, currentPosition->getY() + yStep,
      currentPosition->getDistance() + STEP);
  // if reachablePositions doesnt already contain the next position,
  // add it to the list
  if (!reachablePositions->containsCoordinate(nextPosition)) {
    reachablePositions->addBack(nextPosition);
  }
}

// returns true if the potential position is one step away from the current position
bool PathPlanning::isSingleStep(PDPtr currentPosition, PDPtr potentialPosition)
{
  return (std::abs(currentPosition->getX() - potentialPosition->getX()) == STEP && 
                   currentPosition->getY() == potentialPosition->getY()) 
                   || 
                  (currentPosition->getX() == potentialPosition->getX() && 
          std::abs(currentPosition->getY() - potentialPosition->getY()) == STEP);
}