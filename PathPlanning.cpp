
#define EMPTY 0
#define INITIAL_DISTANCE 0

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
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      std::cout << maze[i][j];
    }
    std::cout << std::endl;
  }
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
  // PDPtr
}

PDList* PathPlanning::getReachablePositions() {
  PDList* reachablePositions = new PDList;
  // PDList* tempPositions = new PDList;
  std::cout << "getting reachable postions" << std::endl;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (this->maze[i][j] == '.') {
        std::cout << "(" << j << ", " << i << ")" << std::endl;
      }
    }
  }
  PDPtr startingPoint =
      new PositionDistance(initialX, initialY, INITIAL_DISTANCE);
  reachablePositions->addBack(startingPoint);
  // PDPtr first = new PositionDistance(6, 2, 1);
  // PDPtr dummy = new PositionDistance(5, 2, 2);
  // PDPtr third = new PositionDistance(4, 2, 3);
  // PDPtr fourth = new PositionDistance(4, 1, 4);
  // std::cout << "we made it" << std::endl;
  // add dummys to array
  // reachablePositions->addBack(first);
  // reachablePositions->addBack(dummy);
  // reachablePositions->addBack(third);
  // reachablePositions->addBack(fourth);
  // print dummy reachable positions
  for (int i = 0; i < reachablePositions->size(); i++) {
    std::cout << reachablePositions->get(i)->getPositionDistance() << " ";
  }
  std::cout << " \n" << std::endl;

  return reachablePositions;
}

// THIS IS FOR MILESTONE 3 ONLY
//    ONLY IMPLEMENT THIS IF YOU ATTEMPT MILESTONE 3
PDList* PathPlanning::getPath(int toX, int toY) {
  return NULL;
}
