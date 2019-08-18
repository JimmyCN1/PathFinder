#define EMPTY 0
#define ONE 1

#include "PDList.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

// constructor
PDList::PDList() {
  // creates list and sets all to nullptr
  // for (int i = 0; i < MAX_POSITIONS; i++) {
  //   positions[i] = nullptr;
  // }
  this->positions = new PDPtr[0];
  // set initial numPositions
  this->numPositions = EMPTY;
}

// deconstructor
PDList::~PDList() {
  clear();
}

// returns the number of indexes that contain positions
int PDList::size() {
  return this->numPositions;
}

PDPtr PDList::get(const int& i) {
  return positions[i];
}

void PDList::setLast(PDPtr position) {
  this->positions[this->numPositions - ONE] = position;
}

void PDList::addBack(PDPtr position) {
  PDPtr* tempList = new PDPtr[this->numPositions + 1];
  for (int i = 0; i < this->numPositions; i++) {
    tempList[i] = new PositionDistance(this->positions[i]);
    std::cout << tempList[i]->getPositionDistance() << std::endl;
  }
  tempList[this->numPositions] = position;

  this->positions = tempList;
  this->numPositions++;
}

// returns true if all the coordinates int the parameter list
// are contained within this
bool PDList::containsAllCoordinatesFromArray(PDList* coordinates) {
  bool hasCoordinates = true;
  if (this->numPositions != EMPTY) {
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

// returns true if the position passed is contained in this
bool PDList::containsCoordinate(PDPtr position) {
  bool isContained = false;
  if (this->numPositions != EMPTY) {
    int i = 0;
    while (i < this->numPositions && isContained == false) {
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
  for (int i = 0; i < this->numPositions; i++) {
    delete this->positions[i];
  }
}
