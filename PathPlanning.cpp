
#define EMPTY 0
#define INITIAL_DISTANCE 0
#define NO_STEP 0
#define STEP 1
#define FORWARD_STEP 1
#define BACKWARCK_STEP -1

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
  // // print grid
  // for (int i = 0; i < rows; i++) {
  //   for (int j = 0; j < cols; j++) {
  //     std::cout << maze[i][j];
  //   }
  //   std::cout << std::endl;
  // }
  // if (rows > EMPTY && cols > EMPTY) {
  //   grid = new char*[rows];
  //   for (int i = 0; i < rows; i++) {
  //     grid[i] = new char[cols];
  //   }
  // }
}

PathPlanning::~PathPlanning() {
  for (int i = 0; i < rows; i++) {
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
    std::cout << "hiyaaaaaa" << std::endl;
    std::cout << "has all coordinates = false!!!" << std::endl;
    int iterations = reachablePositions->size();
    for (int i = 0; i < iterations; i++) {
      std::cout << "~~~~~~~~~~~~~~~~~new round~~~~~~~~~~~~~~~~~" << std::endl
                << std::endl;
      std::cout << "iterarions: " << iterations << std::endl;
      currentSelection = reachablePositions->get(i);
      if (!tempPositions->containsCoordinate(currentSelection)) {
        // check one step up
        std::cout << "up" << std::endl;
        checkStep(NO_STEP, BACKWARCK_STEP, currentSelection,
                  reachablePositions);
        // check one step down
        std::cout << "down" << std::endl;
        checkStep(NO_STEP, FORWARD_STEP, currentSelection, reachablePositions);
        // check one step left
        std::cout << "right" << std::endl;
        checkStep(BACKWARCK_STEP, NO_STEP, currentSelection,
                  reachablePositions);
        // check one step right
        std::cout << "left" << std::endl;
        checkStep(FORWARD_STEP, NO_STEP, currentSelection, reachablePositions);

        tempPositions->addBack(currentSelection);
      }
    }

    
    std::cout << "getting reachable postions" << std::endl;
    // for (int i = 0; i < reachablePositions->size(); i++) {
    //   std::cout << "reachable : "
    //             << reachablePositions->get(i)->getPositionDistance()
    //             << std::endl
    //             << std::endl;
    // }

    for (int i = 0; i < tempPositions->size(); i++) {
      std::cout << "temp : " << tempPositions->get(i)->getPositionDistance()
                << std::endl
                << std::endl;
    }

  } while (!tempPositions->containsAllCoordinatesFromArray(reachablePositions));

  std::cout << "are we there yet_________________________" << std::endl;

  // print reachable positions
  // for (int i = 0; i < reachablePositions->size(); i++) {
  //   std::cout << reachablePositions->get(i)->getPositionDistance() << " ";
  // }
  // std::cout << " \n" << std::endl;

  // delete tempPositions;
  // delete currentSelection;

  PDList* deepCopyReachablePositions = new PDList;
  for (int i = 1; i < reachablePositions->size(); i++) {
    deepCopyReachablePositions->addBack(reachablePositions->get(i));
  }
  // delete reachablePositions;

  // return reachablePositions;
  return deepCopyReachablePositions;
}

// THIS IS FOR MILESTONE 3 ONLY
//    ONLY IMPLEMENT THIS IF YOU ATTEMPT MILESTONE 3
PDList* PathPlanning::getPath(int toX, int toY) {
  return NULL;
}

void PathPlanning::checkStep(int xStep,
                             int yStep,
                             PDPtr currentSelection,
                             PDList* reachablePositions) {
  std::cout << "NEXT SPOT ON MAZE: "
            << maze[currentSelection->getY() + yStep]
                   [currentSelection->getX() + xStep]
            << std::endl;
  // check to see if next position is traversible
  if (maze[currentSelection->getY() + yStep]
          [currentSelection->getX() + xStep] == '.') {
    PDPtr nextPosition = new PositionDistance(
        currentSelection->getX() + xStep, currentSelection->getY() + yStep,
        currentSelection->getDistance() + STEP);
    // std::cout << "xStep: " << xStep << "yStep: " << yStep << std::endl
    //           << nextPosition->getPositionDistance() << std::endl;
    // std::cout << "add new position?" << std::endl;
    // if reachablePositions doesnt already contain the next position,
    // add it to the list
    if (!reachablePositions->containsCoordinate(nextPosition)) {
      reachablePositions->addBack(nextPosition);
      // std::cout << "new position added to reachable positions" << std::endl;
    } else {
      // std::cout << "not added" << std::endl;
    }
  }
}