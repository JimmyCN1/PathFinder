
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
    this->maze = maze;
    this->rows = rows;
    this->cols = cols;
    this->myReachablePositions = new PDList();
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

  // this->myReachablePositions = new PDList(deepCopyReachablePositions);

  return deepCopyReachablePositions;
}

// THIS IS FOR MILESTONE 3 ONLY
//    ONLY IMPLEMENT THIS IF YOU ATTEMPT MILESTONE 3
PDList* PathPlanning::getPath(const int& toX, const int& toY) {
  // // initialisation
  // PDPtr startingPoint =
  //     new PositionDistance(initialX, initialY, INITIAL_DISTANCE);
  // PDList* quickestPath = new PDList();
  // PDList* reachablePositions = getReachablePositions();

  // // add starting point to thie quickest path array
  // quickestPath->addBack(startingPoint);

  // bool isGoalReached = false;
  // PDList* alreadyTraversed = new PDList();
  // bool isFirstRun = true;
  // while (!isGoalReached) {
  //   // int forkDistances[this->rows * this->cols];
  //   // int forkDistance = EMPTY;

  //   for (int i = 0; i < alreadyTraversed->size(); i++) {
  //     quickestPath->remove(alreadyTraversed->get(i));
  //     // std::cout << quickestPath->size() << std::endl;
  //   }

  //   for (int i = FIRST_POSITION; i < reachablePositions->size(); i++) {
  //     PDPtr nextPosition = reachablePositions->get(i);
  //     PDPtr previousPosition;
  //     if (isFirstRun) {
  //       previousPosition = startingPoint;
  //       isFirstRun = false;
  //     } else {
  //       previousPosition = quickestPath->get(quickestPath->size() - 1);
  //     }
  //     // add next position
  //     // if the next position has same distance but is closer to the goal,
  //     // replace the last added position with the new position

  //     if (!isGoalReached) {
  //       // std::cout << "previousPosition: "
  //       //           << previousPosition->getPositionDistance() << std::endl;
  //       // std::cout << "nextPosition: " <<
  //       nextPosition->getPositionDistance()
  //       //           << std::endl;
  //       if (!alreadyTraversed->containsCoordinate(nextPosition)) {
  //         if (oneStep(nextPosition, previousPosition)) {
  //           if (nextPosition->getDistance() - previousPosition->getDistance()
  //           ==
  //               STEP) {
  //             quickestPath->addBack(nextPosition);
  //           }
  //           if (nextPosition->getDistance() ==
  //                   previousPosition->getDistance() &&
  //               (oneStepCloser(nextPosition, previousPosition, toX, toY))) {
  //             quickestPath->setLast(nextPosition);
  //           }
  //           if (singlePath(nextPosition, previousPosition)) {
  //             alreadyTraversed->addBack(nextPosition);
  //           }
  //         }
  //       }
  //     }
  //     isGoalReached = goalReached(nextPosition, toX, toY) &&
  //                     quickestPath->containsCoordinate(nextPosition);
  //   }
  //   // for (int i = 0; i < reachablePositions->size(); i++) {
  //   //   std::cout << "reachable: "
  //   //             << reachablePositions->get(i)->getPositionDistance()
  //   //             << std::endl;
  //   // }
  //   // std::cout << std::endl;
  //   // for (int i = 0; i < alreadyTraversed->size(); i++) {
  //   //   std::cout << "already traveresed: "
  //   //             << alreadyTraversed->get(i)->getPositionDistance() <<
  //   //             std::endl;
  //   // }
  //   // std::cout << std::endl;
  //   // for (int i = 0; i < quickestPath->size(); i++) {
  //   //   std::cout << "quickest Path: "
  //   //             << quickestPath->get(i)->getPositionDistance() <<
  //   std::endl;
  //   //   // std::cout << "goal reached? " << isGoalReached << std::endl;
  //   // }
  //   // std::cout << std::endl;
  // }

  // recursive Implementation
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

  return this->quickestPath;
}

// recursive helper function for getPath
void PathPlanning::getPath(PDList* path,
                           PDList* traversed,
                           //  PDList* reachables,
                           const int& toX,
                           const int& toY,
                           bool& pathFound) {
  std::cout << "recurse!!!!!!!!!!!!!!" << std::endl;
  PDPtr currentPosition = path->getLast();

  if (goalReached(currentPosition, toX, toY)) {
    std::cout << "goal found!!!!!!!****************************************!"
              << std::endl;
    // std::cout << "current position: " <<
    // currentPosition->getPositionDistance()
    //           << std::endl;
    for (int i = 0; i < this->quickestPath->size(); i++) {
      std::cout << "quickestPath: "
                << this->quickestPath->get(i)->getPositionDistance()
                << std::endl;
    }
    // for (int i = 0; i < path->size(); i++) {
    //   std::cout << "currentPath: " << path->get(i)->getPositionDistance()
    //             << std::endl;
    // }
    if (!pathFound || (pathFound && path->size() < quickestPath->size())) {
      std::cout << "quickestPath&: " << this->quickestPath << std::endl;
      std::cout << "changing address......... " << std::endl;
      // delete[] quickestPath;
      this->quickestPath = new PDList(path);
      std::cout << "quickestPath&: " << this->quickestPath << std::endl;
      std::cout << "path&: " << path << std::endl;
      std::cout << "quickestPath&: " << this->quickestPath->size() << std::endl;
      std::cout << "path&: " << path->size() << std::endl;
      // delete[] path;
    }
    pathFound = true;
  } else if (isDeadEnd(currentPosition, traversed)) {
    std::cout << "deadend position: " << currentPosition->getPositionDistance()
              << std::endl;
    std::cout << "reached dead end(((((((((((((((((((((((((" << std::endl;
    // delete[] path;
  } else {
    std::cout << "Reached recursion" << std::endl;
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
    if ((checkStep(stepUp) && !traversed->containsCoordinate(stepUp))) {
      std::cout << "step up available" << std::endl;
      PDList* pathUp = new PDList(path);
      pathUp->addBack(stepUp);
      PDList* newTraversed = new PDList(traversed);
      newTraversed->addBack(stepUp);
      getPath(pathUp, newTraversed, toX, toY, pathFound);
    } else {
      // delete stepUp;
    }
    if ((checkStep(stepDown) && !traversed->containsCoordinate(stepDown))) {
      std::cout << "step down available" << std::endl;
      PDList* pathDown = new PDList(path);
      pathDown->addBack(stepDown);
      PDList* newTraversed = new PDList(traversed);
      newTraversed->addBack(stepDown);
      getPath(pathDown, newTraversed, toX, toY, pathFound);
    } else {
      // delete stepDown;
    }
    if ((checkStep(stepLeft) && !traversed->containsCoordinate(stepLeft))) {
      std::cout << "step left available" << std::endl;
      // //
      // std::cout << path->get(0) << std::endl;
      PDList* pathLeft = new PDList(path);
      pathLeft->addBack(stepLeft);
      PDList* newTraversed = new PDList(traversed);
      newTraversed->addBack(stepLeft);
      getPath(pathLeft, newTraversed, toX, toY, pathFound);
    } else {
      // delete stepLeft;
    }
    if ((checkStep(stepRight) && !traversed->containsCoordinate(stepRight))) {
      std::cout << "step right available" << std::endl;
      PDList* pathRight = new PDList(path);
      pathRight->addBack(stepRight);
      PDList* newTraversed = new PDList(traversed);
      newTraversed->addBack(stepRight);
      getPath(pathRight, newTraversed, toX, toY, pathFound);
    } else {
      // delete stepRight;
    }
  }
}

// add a step in all traversible directions to the passed reachable posisions
// array;
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
  // check to see if next position is traversible
  // std::cout << "checking step" << std::endl;
  // std::cout << this->maze[currentPosition->getY() + yStep]
  //                        [currentPosition->getX() + xStep]
  //           << std::endl;
  return (this->maze[currentPosition->getY() + yStep]
                    [currentPosition->getX() + xStep] == '.');
}

// returns true if the postion passed is traversible
bool PathPlanning::checkStep(PDPtr nextPosition) {
  // check to see if next position is traversible
  // std::cout << "checking step" << std::endl;
  // std::cout << nextPosition->getX() << "," << nextPosition->getY() << " "
  //           << this->maze[nextPosition->getY()][nextPosition->getX()]
  //           << std::endl;
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

bool PathPlanning::singlePath(PDPtr nextPosition, PDPtr previousPosition) {
  bool isSinglePath = false;
  int paths = NO_PATH;
  // check one step up
  if (checkStep(NO_STEP, BACKWARD_STEP, nextPosition)) {
    paths++;
  }
  // check one step down
  if (checkStep(NO_STEP, FORWARD_STEP, nextPosition)) {
    paths++;
  }
  // check one step left
  if (checkStep(BACKWARD_STEP, NO_STEP, nextPosition)) {
    paths++;
  }
  // check one step right
  if (checkStep(FORWARD_STEP, NO_STEP, nextPosition)) {
    paths++;
  }
  if (paths < 3) {
    isSinglePath = true;
  }
  return isSinglePath;
}

bool PathPlanning::oneStepCloser(PositionDistance* nextPosition,
                                 PositionDistance* previousPosition,
                                 int goalX,
                                 int goalY) {
  bool isOneStepCloser = false;
  if ((std::abs(previousPosition->getX() - goalX) -
       std::abs(nextPosition->getX() - goalX)) == STEP ||
      (std::abs(previousPosition->getY() - goalY) -
       std::abs(nextPosition->getY() - goalY)) == STEP) {
    isOneStepCloser = true;
  }

  return isOneStepCloser;
}

// return true if next position is one step
bool PathPlanning::oneStep(PositionDistance* nextPosition,
                           PositionDistance* previousPosition) {
  return ((std::abs(nextPosition->getX() - previousPosition->getX()) == STEP) &&
          (nextPosition->getY() == previousPosition->getY())) ||
         (((std::abs(nextPosition->getY() - previousPosition->getY()) ==
            STEP) &&
           (nextPosition->getX() == previousPosition->getX())));
}

// return true if position cordinates matches the goal
bool PathPlanning::goalReached(PositionDistance* position,
                               int goalX,
                               int goalY) {
  // int x = position->getX();
  // int y = position->getY();
  // std::cout << "x: " << x << "goal x: " << goalX << std::endl;
  // std::cout << "y: " << y << "goal y: " << goalY << std::endl;
  return position->getX() == goalX && position->getY() == goalY;
}