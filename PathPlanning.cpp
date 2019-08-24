
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
#define INITIAL 0

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
    this->badPositionDistances = new PDList();
  }
}

PathPlanning::~PathPlanning() {
  for (int i = FIRST_POSITION; i < rows; i++) {
    delete maze[i];
  }
  delete[] maze;
  delete this->quickestPath;
}

void PathPlanning::initialPosition(int x, int y) {
  this->initialX = x;
  this->initialY = y;
}

PDList* PathPlanning::getReachablePositions() {
  // initialisation
  PDPtr startingPoint =
      new PositionDistance(initialX, initialY, INITIAL_DISTANCE);
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

  for (int i = 0; i < tempPositions->size(); i++) {
    std::cout << &tempPositions[i] << "\t";
  }
  std::cout << std::endl;
  for (int i = 0; i < tempPositions->size(); i++) {
    std::cout << tempPositions->get(i)->getPositionDistance() << "\t";
  }
  std::cout << std::endl;
  for (int i = 0; i < reachablePositions->size(); i++) {
    std::cout << &reachablePositions[i] << "\t";
  }
  std::cout << std::endl;
  for (int i = 0; i < reachablePositions->size(); i++) {
    std::cout << reachablePositions->get(i)->getPositionDistance() << "\t";
  }
  std::cout << std::endl;
  for (int i = 0; i < deepCopyReachablePositions->size(); i++) {
    std::cout << &deepCopyReachablePositions[i] << "\t";
  }
  std::cout << std::endl;
  for (int i = 0; i < deepCopyReachablePositions->size(); i++) {
    std::cout << deepCopyReachablePositions->get(i)->getPositionDistance()
              << "\t";
  }
  std::cout << std::endl;

  delete reachablePositions;
  delete tempPositions;

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
  trialPath->addBack(new PositionDistance(startingPoint));

  delete startingPoint;

  // recursive helper function call
  getPath(trialPath, toX, toY, pathFound);
  delete this->badPositionDistances;

  for (int i = 0; i < this->quickestPath->size(); i++) {
    std::cout << "quickestPath: "
              << this->quickestPath->get(i)->getPositionDistance() << std::endl;
  }

  std::cout << trialPath->size() << std::endl;
  delete trialPath;

  return new PDList(this->quickestPath);
}

// recursive helper function for getPath
void PathPlanning::getPath(PDList* path,
                           const int& toX,
                           const int& toY,
                           bool& pathFound) {
  std::cout << "getting last position from path: "
            << path->getLast()->getPositionDistance() << std::endl;
  PDPtr currentPosition = path->getLast();
  static int recursionCount = INITIAL;
  recursionCount++;
  std::cout << "recursionCount: " << recursionCount << std::endl;

  if (goalReached(currentPosition, toX, toY)) {
    if (!pathFound || (pathFound && path->size() < quickestPath->size())) {
      this->quickestPath = new PDList(path);
    }
    pathFound = true;
  } else if (isDeadEnd(currentPosition, path)) {
    std::cout << "reached dead end" << std::endl;
  } else if (pathFound && quickestPath->size() < path->size()) {
    std::cout << "already found a shorter path" << std::endl;
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
    if ((checkStep(stepUp) && !path->containsCoordinate(stepUp))) {
      std::cout << "getting last position from path in up: "
                << path->getLast()->getPositionDistance() << std::endl;
      PDList* pathUp = new PDList(path, new PositionDistance(stepUp));
      getPath(pathUp, toX, toY, pathFound);
    } else {
      badPositionDistances->addBack(stepUp);
    }
    if ((checkStep(stepDown) && !path->containsCoordinate(stepDown))) {
      PDList* pathDown = new PDList(path, new PositionDistance(stepDown));
      getPath(pathDown, toX, toY, pathFound);
    } else {
      badPositionDistances->addBack(stepDown);
    }
    if ((checkStep(stepLeft) && !path->containsCoordinate(stepLeft))) {
      PDList* pathLeft = new PDList(path, new PositionDistance(stepLeft));
      getPath(pathLeft, toX, toY, pathFound);
    } else {
      badPositionDistances->addBack(stepLeft);
    }
    if ((checkStep(stepRight) && !path->containsCoordinate(stepRight))) {
      PDList* pathRight = new PDList(path, new PositionDistance(stepRight));
      getPath(pathRight, toX, toY, pathFound);
    } else {
      badPositionDistances->addBack(stepRight);
    }
  }
  delete path;
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
bool PathPlanning::checkStep(const int xStep,
                             const int yStep,
                             const PDPtr currentPosition) {
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