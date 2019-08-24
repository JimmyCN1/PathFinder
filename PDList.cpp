#define EMPTY 0
#define ONE 1

#include "PDList.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

PDList::PDList() {
  this->positions = new PDPtr[0];
  this->numPositions = EMPTY;
}

PDList::PDList(PDList* pdList) {
  this->positions = new PDPtr[0];
  // this->addAll(pdList);
  for (int i = 0; i < pdList->size(); i++) {
    this->addBack(new PositionDistance(pdList->get(i)));
  }
  this->numPositions = this->size();
}

// a copy constructor which also adds the passed PDPtr to the end of the new
// PDList
PDList::PDList(PDList* pdList, PDPtr pdPtr) {
  this->positions = new PDPtr[0];
  // this->addAll(pdList);
  for (int i = 0; i < pdList->size(); i++) {
    this->addBack(new PositionDistance(pdList->get(i)));
  }
  this->addBack(pdPtr);
}

PDList::~PDList() {
  clear();
}

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

// void PDList::addAll(PDList* pdList) {
//   for (int i = 0; i < pdList->size(); i++) {
//     this->addBack(new PositionDistance(pdList->get(i)));
//   }
// }

// copies the contents into a new array of size+=1 and adds the new position
void PDList::addBack(PDPtr position) {
  PDPtr* tempList = new PDPtr[this->numPositions + 1];
  for (int i = 0; i < this->numPositions; i++) {
    tempList[i] = new PositionDistance(this->get(i));
  }
  tempList[this->numPositions] = new PositionDistance(position);
  this->positions = tempList;

  this->numPositions++;
}

// removes the desired position and copies
// over the content to a new smaller array
void PDList::remove(PDPtr position) {
  if (!this->containsCoordinate(position)) {
    std::cout << "Error: PDList does not contain this postion:: "
              << position->getPositionDistance() << std::endl;
  } else {
    int positionIndex = this->getIndexOf(position);
    removeAt(positionIndex);
  }
}

// removes the position at the passed index from positions
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
bool PDList::containsCoordinate(const PDPtr position) {
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

// deletes all PDPtrs in the positions array
void PDList::clear() {
  for (int i = 0; i < this->numPositions; i++) {
    if (this->positions != nullptr) {
      delete this->positions[i];
    }
  }
  // delete[] positions;
}
