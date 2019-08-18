
#define EMPTY 0
#define INITIAL_DISTANCE 0
#define NO_STEP 0
#define STEP 1
#define FORWARD_STEP 1
#define BACKWARCK_STEP -1
#define FIRST_POSITION 0
#define FIRST_STEP 1

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
        // check one step up
        checkStep(NO_STEP, BACKWARCK_STEP, currentSelection,
                  reachablePositions);
        // check one step down
        checkStep(NO_STEP, FORWARD_STEP, currentSelection, reachablePositions);
        // check one step left
        checkStep(BACKWARCK_STEP, NO_STEP, currentSelection,
                  reachablePositions);
        // check one step right
        checkStep(FORWARD_STEP, NO_STEP, currentSelection, reachablePositions);

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
  bool goalReached = false;
  PDPtr startingPoint =
      new PositionDistance(initialX, initialY, INITIAL_DISTANCE);
  PDList* quickestPath = new PDList();
  PDList* reachablePositions = getReachablePositions();

  // add starting point to thie quickest path array
  quickestPath->addBack(startingPoint);

  for (int i = FIRST_POSITION; i < reachablePositions->size(); i++) {
    PDPtr nextPosition = reachablePositions->get(i);
    PDPtr previousPosition;
    if (i == FIRST_POSITION) {
      previousPosition = startingPoint;
    } else {
      previousPosition = quickestPath->get(quickestPath->size() - 1);
    }
    // add next position
    // if the next position has same distance but is closer to the goal,
    // replace the last added position with the new position
    if (!goalReached) {
      if (nextPosition->getDistance() > previousPosition->getDistance()) {
        quickestPath->addBack(nextPosition);
      } else if (nextPosition->getDistance() ==
                 previousPosition->getDistance()) {
        if (isCloserToGoal(nextPosition, previousPosition, toX, toY)) {
          quickestPath->setLast(nextPosition);
        }
      }
    }
    // check to see if goal is reached
    if (nextPosition->getX() == toX && nextPosition->getY() == toY) {
      goalReached = true;
    }
  }

  return quickestPath;
}

void PathPlanning::checkStep(int xStep,
                             int yStep,
                             PDPtr currentSelection,
                             PDList* reachablePositions) {
  // check to see if next position is traversible
  if (maze[currentSelection->getY() + yStep]
          [currentSelection->getX() + xStep] == '.') {
    PDPtr nextPosition = new PositionDistance(
        currentSelection->getX() + xStep, currentSelection->getY() + yStep,
        currentSelection->getDistance() + STEP);
    // if reachablePositions doesnt already contain the next position,
    // add it to the list
    if (!reachablePositions->containsCoordinate(nextPosition)) {
      reachablePositions->addBack(nextPosition);
    }
  }
}

bool PathPlanning::isCloserToGoal(PositionDistance* nextPosition,
                                  PositionDistance* previousPosition,
                                  int goalX,
                                  int goalY) {
  bool isCloser = false;
  if ((std::abs(previousPosition->getX() - goalX) >
       std::abs(nextPosition->getX() - goalX)) ||
      (std::abs(previousPosition->getY() - goalY) >
       std::abs(nextPosition->getY() - goalY))) {
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
    isCloser = true;
  }

  return isCloser;
}