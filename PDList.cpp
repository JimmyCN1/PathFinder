#define EMPTY 0

#include "PDList.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

// constructor
PDList::PDList() {
  // creates list and sets all to nullptr
  std::cout << "1" << std::endl;
  for (int i = 0; i < MAX_POSITIONS; i++) {
    positions[i] = nullptr;
  }
  // set initial numPositions
  // PDList::setNumPositions();
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

// sets the numPositions property
void PDList::setNumPositions() {
  PDList::numPositions = PDList::size();
}

PDPtr PDList::get(int i) {
  return positions[i];
}

void PDList::addBack(PDPtr position) {
  std::cout << "adding " << position->getPositionDistance() << " to list"
            << std::endl;
  positions[PDList::numPositions] = position;
  setNumPositions();
  std::cout << "added" << std::endl;
}

bool PDList::containsAllCoordinateFromArray(PDList* coordinates) {
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
      std::cout << positions[i]->getPositionDistance() << std::endl;
      if (position->getX() == positions[i]->getX() &&
          position->getY() == positions[i]->getY())
      //  &&
      // position->getDistance() == positions[i]->getDistance())
      {
        isContained = true;
      } else {
        i++;
      }
      std::cout << "isContained? " << isContained << std::endl;
    }
  }
  return isContained;
}

void PDList::clear() {
  // deletes all PDPtrs in the array
  for (int i = 0; i < MAX_POSITIONS; i++) {
    delete positions[i];
  }
}
