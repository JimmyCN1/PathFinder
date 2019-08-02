
#include "PDList.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

#define POSITIONS_LENGTH 100

// constructor
PDList::PDList() {
  // NULL all values in initialised array
  for (int i = 0; i < POSITIONS_LENGTH; i++) {
    positions[i] = NULL;
  }
  // set initial numPositions
  PDList::setNumPositions();
}

// deconstructor
PDList::~PDList() { delete positions[100]; }

// returns the number of indexes that contain positions
int PDList::size() {
  int size = 0;
  for (int i = 0; i < POSITIONS_LENGTH; i++) {
    if (positions[i] != NULL) {
      size += 1;
    }
  }
  return size;
}

// sets the numPositions property
void PDList::setNumPositions() { PDList::numPositions = PDList::size(); }

PDPtr PDList::get(int i) { return positions[i]; }

void PDList::addBack(PDPtr position) {
  positions[PDList::numPositions] = position;
  setNumPositions();
}

bool PDList::containsCoordinate(PDPtr position) {
  bool isContained = false;
  int i = 0;
  while (i < PDList::numPositions && isContained == false) {
    if (position->getX() == positions[i]->getX() &&
        position->getX() == positions[i]->getX() &&
        position->getDistance() == positions[i]->getDistance()) {
      isContained = true;
    }
    i++;
  }
  return isContained;
}

void PDList::clear() {}
