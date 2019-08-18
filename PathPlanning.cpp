
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
  PDPtr currentSelection = nullptr;

  // P initially containing x (initial position)
  reachablePositions->addBack(startingPoint);

  do {
    int iterations = reachablePositions->size();
    for (int i = FIRST_POSITION; i < iterations; i++) {
      currentSelection = reachablePositions->get(i);
      if (!tempPositions->containsCoordinate(currentSelection)) {
        setReachablePositions(currentSelection, reachablePositions);
        tempPositions->addBack(currentSelection);
      }
    }

  } while (!tempPositions->containsAllCoordinatesFromArray(reachablePositions));

  PDList* deepCopyReachablePositions = new PDList();
  for (int i = FIRST_STEP; i < reachablePositions->size(); i++) {
    deepCopyReachablePositions->addBack(
        new PositionDistance(reachablePositions->get(i)));
    // std::cout << reachablePositions->get(i)->getPositionDistance() <<
    // std::endl;
  }

  delete reachablePositions;

  return deepCopyReachablePositions;
}

// THIS IS FOR MILESTONE 3 ONLY
//    ONLY IMPLEMENT THIS IF YOU ATTEMPT MILESTONE 3
PDList* PathPlanning::getPath(const int& toX, const int& toY) {
  // initialisation
  PDPtr startingPoint =
      new PositionDistance(initialX, initialY, INITIAL_DISTANCE);
  PDList* quickestPath = new PDList();
  PDList* reachablePositions = getReachablePositions();

  // add starting point to thie quickest path array
  quickestPath->addBack(startingPoint);

  bool isGoalReached = false;
  PDList* alreadyTraversed = new PDList();
  bool isFirstRun = true;
  while (!isGoalReached) {
    // int forkDistances[this->rows * this->cols];
    // int forkDistance = EMPTY;

    for (int i = 0; i < alreadyTraversed->size(); i++) {
      quickestPath->remove(alreadyTraversed->get(i));
      // std::cout << quickestPath->size() << std::endl;
    }

    for (int i = FIRST_POSITION; i < reachablePositions->size(); i++) {
      PDPtr nextPosition = reachablePositions->get(i);
      PDPtr previousPosition;
      if (isFirstRun) {
        previousPosition = startingPoint;
        isFirstRun = false;
      } else {
        previousPosition = quickestPath->get(quickestPath->size() - 1);
      }
      // add next position
      // if the next position has same distance but is closer to the goal,
      // replace the last added position with the new position

      if (!isGoalReached) {
        std::cout << "previousPosition: "
                  << previousPosition->getPositionDistance() << std::endl;
        std::cout << "nextPosition: " << nextPosition->getPositionDistance()
                  << std::endl;
        if (!alreadyTraversed->containsCoordinate(nextPosition)) {
          if (oneStep(nextPosition, previousPosition)) {
            if (nextPosition->getDistance() - previousPosition->getDistance() ==
                STEP) {
              quickestPath->addBack(nextPosition);
            }
            if (nextPosition->getDistance() ==
                    previousPosition->getDistance() &&
                (oneStepCloser(nextPosition, previousPosition, toX, toY))) {
              quickestPath->setLast(nextPosition);
            }
            if (singlePath(nextPosition, previousPosition)) {
              alreadyTraversed->addBack(nextPosition);
            }
          }
        }
      }
      isGoalReached = goalReached(nextPosition, toX, toY) &&
                      quickestPath->containsCoordinate(nextPosition);
    }
    for (int i = 0; i < reachablePositions->size(); i++) {
      std::cout << "reachable: "
                << reachablePositions->get(i)->getPositionDistance()
                << std::endl;
    }
    std::cout << std::endl;
    for (int i = 0; i < alreadyTraversed->size(); i++) {
      std::cout << "already traveresed: "
                << alreadyTraversed->get(i)->getPositionDistance() << std::endl;
    }
    std::cout << std::endl;
    for (int i = 0; i < quickestPath->size(); i++) {
      std::cout << "quickest Path: "
                << quickestPath->get(i)->getPositionDistance() << std::endl;
      // std::cout << "goal reached? " << isGoalReached << std::endl;
    }
    std::cout << std::endl;
  }

  return quickestPath;
}

void PathPlanning::setReachablePositions(PDPtr currentSelection,
                                         PDList* reachablePositions) {
  // check one step up
  if (checkStep(NO_STEP, BACKWARD_STEP, currentSelection)) {
    setNextReachablePosition(NO_STEP, BACKWARD_STEP, currentSelection,
                             reachablePositions);
  }

  // check one step down
  if (checkStep(NO_STEP, FORWARD_STEP, currentSelection)) {
    setNextReachablePosition(NO_STEP, FORWARD_STEP, currentSelection,
                             reachablePositions);
  }

  // check one step left
  if (checkStep(BACKWARD_STEP, NO_STEP, currentSelection)) {
    setNextReachablePosition(BACKWARD_STEP, NO_STEP, currentSelection,
                             reachablePositions);
  }

  // check one step right
  if (checkStep(FORWARD_STEP, NO_STEP, currentSelection)) {
    setNextReachablePosition(FORWARD_STEP, NO_STEP, currentSelection,
                             reachablePositions);
  }
}

bool PathPlanning::checkStep(int xStep, int yStep, PDPtr currentSelection) {
  // check to see if next position is traversible
  return (this->maze[currentSelection->getY() + yStep]
                    [currentSelection->getX() + xStep] == '.');
}

void PathPlanning::setNextReachablePosition(int xStep,
                                            int yStep,
                                            PDPtr currentSelection,
                                            PDList* reachablePositions) {
  PDPtr nextPosition = new PositionDistance(
      currentSelection->getX() + xStep, currentSelection->getY() + yStep,
      currentSelection->getDistance() + STEP);
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
    // std::cout << "prev pos: " << previousPosition->getPositionDistance()
    //           << std::endl;
    // std::cout << "position: " << nextPosition->getPositionDistance()
    //           << std::endl;
    // std::cout << "goal: " << goalX << "," << goalY << std::endl;
    // std::cout << "x prev abs: " << std::abs(previousPosition->getX() - goalX)
    //           << std::endl;
    // std::cout << "x curr abs: " << std::abs(nextPosition->getX() - goalX)
    //           << std::endl;
    // std::cout << "y prev abs: " << std::abs(previousPosition->getY() - goalY)
    //           << std::endl;
    // std::cout << "y curr abs: " << std::abs(nextPosition->getY() - goalY)
    //           << std::endl;
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
  int x = position->getX();
  int y = position->getY();
  std::cout << "x: " << x << "goal x: " << goalX << std::endl;
  std::cout << "y: " << y << "goal y: " << goalY << std::endl;
  return position->getX() == goalX && position->getY() == goalY;
}