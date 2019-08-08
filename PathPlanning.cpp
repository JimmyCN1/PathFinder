
#include "PathPlanning.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

PathPlanning::PathPlanning(Grid maze, int rows, int cols) {
  this->maze = maze;
  this->rows = rows;
  this->cols = cols;
}

PathPlanning::~PathPlanning() { delete maze; }

void PathPlanning::initialPosition(int x, int y) {
  initialX = x;
  initialY = y;
}

PDList *PathPlanning::getReachablePositions() { return NULL; }

// THIS IS FOR MILESTONE 3 ONLY
//    ONLY IMPLEMENT THIS IF YOU ATTEMPT MILESTONE 3
PDList *PathPlanning::getPath(int toX, int toY) { return NULL; }
