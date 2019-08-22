
#define EMPTY 0
#define INITIAL_DISTANCE 0
#define NO_STEP 0
#define STEP 1
#define FORWARD_STEP 1
#define BACKWARD_STEP -1
#define FIRST_POSITION 0
#define FIRST_STEP 1
#define NO_PATH 0
#define SINGLE_PATH 2

#include "PathPlanning.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

PathPlanning::PathPlanning(Grid maze, int rows, int cols) {
  if (rows > EMPTY && cols > EMPTY) {
    this->maze = new char*[rows];
    for (int i = FIRST_POSITION; i < rows; i++) {
      this->maze[i] = new char[cols];
    }
    for (int i = FIRST_POSITION; i < rows; i++) {
      for (int j = FIRST_POSITION; j < cols; j++) {
        this->maze[i][j] = maze[i][j];
      }
    }
    this->rows = rows;
    this->cols = cols;
    this->quickestPath = new PDList();
  }
}

PathPlanning::~PathPlanning() {
  for (int i = FIRST_POSITION; i < rows; i++) {
    delete maze[i];
  }
  delete maze;
}

void PathPlanning::initialPosition(int x, int y) {
  this->initialX = x;
  this->initialY = y;
}

PDList* PathPlanning::getReachablePositions() {
  // initialisation
  PDPtr startingPoint =
      new PositionDistance(initialX, initialY, INITIAL_DISTANCE);
  PDList* reachablePositions = new PDList;
  PDList* tempPositions = new PDList;
  PDPtr currentPosition = nullptr;

  // P initially containing x (initial position)
  reachablePositions->addBack(startingPoint);

  do {
    int iterations = reachablePositions->size();
    for (int i = FIRST_POSITION; i < iterations; i++) {
      currentPosition = reachablePositions->get(i);
      if (!tempPositions->containsCoordinate(currentPosition)) {
        setReachablePositions(currentPosition, reachablePositions);
        tempPositions->addBack(currentPosition);
      }
    }

  } while (!tempPositions->containsAllCoordinatesFromArray(reachablePositions));

  PDList* deepCopyReachablePositions = new PDList(reachablePositions);
  deepCopyReachablePositions->removeAt(FIRST_POSITION);

  delete reachablePositions;

  // for (int i = 0; i < deepCopyReachablePositions->size(); i++) {
  //   std::cout << "deepCopy: "
  //             << deepCopyReachablePositions->get(i)->getPositionDistance()
  //             << std::endl;
  // }

  return deepCopyReachablePositions;
}

// THIS IS FOR MILESTONE 3 ONLY
//    ONLY IMPLEMENT THIS IF YOU ATTEMPT MILESTONE 3
PDList* PathPlanning::getPath(const int& toX, const int& toY) {
  // recursive Implementation (might take a while on some tests cases)
  // initialisation
  bool pathFound = false;
  PDPtr startingPoint =
      new PositionDistance(initialX, initialY, INITIAL_DISTANCE);
  PDList* trialPath = new PDList();
  trialPath->addBack(startingPoint);
  PDList* traversed = new PDList();
  traversed->addBack(startingPoint);

  // recursive helper function call
  getPath(trialPath, traversed, toX, toY, pathFound);

  for (int i = 0; i < this->quickestPath->size(); i++) {
    std::cout << "quickestPath: "
              << this->quickestPath->get(i)->getPositionDistance() << std::endl;
  }
  delete trialPath;
  // delete traversed;

  return this->quickestPath;
}

// recursive helper function for getPath
void PathPlanning::getPath(PDList* path,
                           PDList* traversed,
                           //  PDList* reachables,
                           const int& toX,
                           const int& toY,
                           bool& pathFound) {
  PDPtr currentPosition = path->getLast();

  if (goalReached(currentPosition, toX, toY)) {
    if (!pathFound || (pathFound && path->size() < quickestPath->size())) {
      this->quickestPath = new PDList(path);
    }
    pathFound = true;
  } else {
    // create new PositionDistance* for potential reachable positions
    PDPtr stepUp = new PositionDistance(currentPosition->getX() + NO_STEP,
                                        currentPosition->getY() + BACKWARD_STEP,
                                        currentPosition->getDistance() + STEP);
    PDPtr stepDown =
        new PositionDistance(currentPosition->getX() + NO_STEP,
                             currentPosition->getY() + FORWARD_STEP,
                             currentPosition->getDistance() + STEP);
    PDPtr stepLeft =
        new PositionDistance(currentPosition->getX() + BACKWARD_STEP,
                             currentPosition->getY() + NO_STEP,
                             currentPosition->getDistance() + STEP);
    PDPtr stepRight =
        new PositionDistance(currentPosition->getX() + FORWARD_STEP,
                             currentPosition->getY() + NO_STEP,
                             currentPosition->getDistance() + STEP);
    // if pathExists, recurse up || down || left || right
    if ((checkStep(stepUp) && !traversed->containsCoordinate(stepUp))) {
      PDList* pathUp = new PDList(path, stepUp);
      PDList* newTraversed = new PDList(traversed, stepUp);
      getPath(pathUp, newTraversed, toX, toY, pathFound);
    }
    if ((checkStep(stepDown) && !traversed->containsCoordinate(stepDown))) {
      PDList* pathDown = new PDList(path, stepDown);
      PDList* newTraversed = new PDList(traversed, stepDown);
      getPath(pathDown, newTraversed, toX, toY, pathFound);
    }
    if ((checkStep(stepLeft) && !traversed->containsCoordinate(stepLeft))) {
      PDList* pathLeft = new PDList(path, stepLeft);
      PDList* newTraversed = new PDList(traversed, stepLeft);
      getPath(pathLeft, newTraversed, toX, toY, pathFound);
    }
    if ((checkStep(stepRight) && !traversed->containsCoordinate(stepRight))) {
      PDList* pathRight = new PDList(path, stepRight);
      PDList* newTraversed = new PDList(traversed, stepRight);
      getPath(pathRight, newTraversed, toX, toY, pathFound);
    }
  }
}

// add a step in all traversible directions to the
// passed reachable positions array
void PathPlanning::setReachablePositions(PDPtr currentPosition,
                                         PDList* reachablePositions) {
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

// returns true if the robot cannot move forward in any direction
bool PathPlanning::isDeadEnd(PDPtr currentPosition, PDList* traversed) {
  bool isDeadEnd = true;
  PDPtr stepUp = new PositionDistance(currentPosition->getX() + NO_STEP,
                                      currentPosition->getY() + BACKWARD_STEP,
                                      currentPosition->getDistance() + STEP);
  PDPtr stepDown = new PositionDistance(currentPosition->getX() + NO_STEP,
                                        currentPosition->getY() + FORWARD_STEP,
                                        currentPosition->getDistance() + STEP);
  PDPtr stepLeft = new PositionDistance(currentPosition->getX() + BACKWARD_STEP,
                                        currentPosition->getY() + NO_STEP,
                                        currentPosition->getDistance() + STEP);
  PDPtr stepRight = new PositionDistance(currentPosition->getX() + FORWARD_STEP,
                                         currentPosition->getY() + NO_STEP,
                                         currentPosition->getDistance() + STEP);
  if ((checkStep(stepUp) && !traversed->containsCoordinate(stepUp)) ||
      (checkStep(stepDown) && !traversed->containsCoordinate(stepDown)) ||
      (checkStep(stepLeft) && !traversed->containsCoordinate(stepLeft)) ||
      (checkStep(stepRight) && !traversed->containsCoordinate(stepRight))) {
    isDeadEnd = false;
  }
  return isDeadEnd;
}

// returns true if the postion passed is traversible
bool PathPlanning::checkStep(int xStep, int yStep, PDPtr currentPosition) {
  return (this->maze[currentPosition->getY() + yStep]
                    [currentPosition->getX() + xStep] == '.');
}

// returns true if the postion passed is traversible
bool PathPlanning::checkStep(PDPtr nextPosition) {
  return (this->maze[nextPosition->getY()][nextPosition->getX()] == '.');
}

// adds the next reachable position to the passes array
void PathPlanning::setNextReachablePosition(int xStep,
                                            int yStep,
                                            PDPtr currentPosition,
                                            PDList* reachablePositions) {
  PDPtr nextPosition = new PositionDistance(
      currentPosition->getX() + xStep, currentPosition->getY() + yStep,
      currentPosition->getDistance() + STEP);
  // if reachablePositions doesnt already contain the next position,
  // add it to the list
  if (!reachablePositions->containsCoordinate(nextPosition)) {
    reachablePositions->addBack(nextPosition);
  }
}

// return true if position cordinates matches the goal
bool PathPlanning::goalReached(PositionDistance* position,
                               int goalX,
                               int goalY) {
  return position->getX() == goalX && position->getY() == goalY;
}