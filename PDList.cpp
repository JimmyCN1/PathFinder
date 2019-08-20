#define EMPTY 0
#define ONE 1

#include "PDList.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

// constructor
PDList::PDList() {
  // creates list and sets all to nullptr
  this->positions = new PDPtr[0];
  // set initial numPositions
  this->numPositions = EMPTY;
}

PDList::PDList(PDList* pdList) {
  this->positions = new PDPtr[0];
  //
  // std::cout << pdList->get(0) << std::endl;
  // std::cout << "base+2: " << this->get(0) << std::endl;
  this->addAll(pdList);
  this->numPositions = this->size();
}

// deconstructor
PDList::~PDList() {
  clear();
}

// returns the number of indexes that contain positions
int PDList::size() {
  return this->numPositions;
}

PDPtr PDList::get(int i) {
  return positions[i];
}

PDPtr PDList::getLast() {
  return get(this->size() - 1);
}

void PDList::setLast(PDPtr position) {
  this->positions[this->numPositions - ONE] = position;
}

void PDList::addAll(PDList* pdList) {
  for (int i = 0; i < pdList->size(); i++) {
    //
    // std::cout << pdList->get(0) << std::endl;
    // std::cout << this->get(i) << std::endl;
    this->addBack(new PositionDistance(pdList->get(i)));
  }
}

void PDList::addBack(PDPtr position) {
  PDPtr* tempList = new PDPtr[this->numPositions + 1];
  for (int i = 0; i < this->numPositions; i++) {
    //
    // std::cout << "last good call " << position << std::endl;
    // std::cout << "base+1: " << this->get(i) << std::endl;
    tempList[i] = new PositionDistance(this->get(i));
  }
  // std::cout << "made it passed " << position->getPositionDistance()
  //           << std::endl;
  tempList[this->numPositions] = position;
  this->positions = tempList;

  this->numPositions++;

  // PDPtr tempList[this->size() + 1];
  // for (int i = 0; i < this->numPositions; i++) {
  //   tempList[i] = new PositionDistance(this->positions[i]);
  // }
  // tempList[this->size()] = position;
  // this->positions = tempList;

  // this->numPositions++;
}

void PDList::remove(PDPtr position) {
  if (!this->containsCoordinate(position)) {
    std::cout << "Error: PDList does not contain this postion:: "
              << position->getPositionDistance() << std::endl;
  } else {
    int positionIndex = this->getIndexOf(position);
    removeAt(positionIndex);
  }
}

void PDList::removeAt(const int index) {
  PDPtr* tempList = new PDPtr[this->numPositions - 1];
  int tempIndex = 0;
  for (int i = 0; i < this->size(); i++) {
    if (i != index) {
      tempList[tempIndex] = new PositionDistance(this->positions[i]);
      tempIndex++;
    }
  }
  this->positions = tempList;
  this->numPositions--;
  std::cout << "Removed!!!!!!!!!!!!!!!!!!." << std::endl;
}

// returns the index of the passed postion in a pdlist
int PDList::getIndexOf(PDPtr position) {
  bool matchFound = false;
  int index = -1;
  for (int i = 0; i < this->size(); i++) {
    if (!matchFound) {
      if (this->positions[i]->equals(position)) {
        matchFound = true;
        index = i;
      }
    }
  }
  return index;
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
      if (position->equals(positions[i])) {
        isContained = true;
      } else {
        i++;
      }
    }
  } else {
    std::cout << "Error: Does not contain coordinates as the list is empty"
              << std::endl;
  }
  return isContained;
}

void PDList::toString() {}

void PDList::clear() {
  // deletes all PDPtrs in the array
  for (int i = 0; i < this->numPositions; i++) {
    delete this->positions[i];
  }
}
