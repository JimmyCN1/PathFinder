#define EMPTY 0

#include "PDList.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

// constructor
PDList::PDList() {
  // creates list and sets all to nullptr
  for (int i = 0; i < MAX_POSITIONS; i++) {
    positions[i] = nullptr;
  }
  // set initial numPositions
  numPositions = 0;
}

// deconstructor
PDList::~PDList() {
  clear();
}

// returns the number of indexes that contain positions
int PDList::size() {
  int size = EMPTY;
  while (positions[size] != nullptr) {
    size++;
  }
  return size;
}

PDPtr PDList::get(int i) {
  return positions[i];
}

void PDList::setLast(PDPtr position) {
  this->positions[this->numPositions - 1] = position;
}

void PDList::addBack(PDPtr position) {
  positions[PDList::numPositions] = position;
  numPositions++;
}

bool PDList::containsAllCoordinatesFromArray(PDList* coordinates) {
  bool hasCoordinates = true;
  if (numPositions != EMPTY) {
    int i = 0;
    int size = coordinates->size();
    while (i < size && hasCoordinates == true) {
      if (!this->containsCoordinate(coordinates->get(i))) {
        hasCoordinates = false;
      } else {
        i++;
      }
    }
  }
  return hasCoordinates;
}

bool PDList::containsCoordinate(PDPtr position) {
  bool isContained = false;
  if (numPositions != EMPTY) {
    int i = 0;
    while (i < numPositions && isContained == false) {
      if (position->getX() == positions[i]->getX() &&
          position->getY() == positions[i]->getY()) {
        isContained = true;
      } else {
        i++;
      }
    };
  }
  return isContained;
}

void PDList::clear() {
  // deletes all PDPtrs in the array
  for (int i = 0; i < MAX_POSITIONS; i++) {
    delete positions[i];
  }
  // delete[] positions;
}
