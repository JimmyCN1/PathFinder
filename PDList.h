
#ifndef COSC_ASS_ONE_POSITION_LIST
#define COSC_ASS_ONE_POSITION_LIST
#define MAX_POSITIONS 55

#include "PositionDistance.h"
#include "Types.h"

class PDList {
 public:
  /*                                           */
  /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
  /*                                           */

  // Create a New Empty List
  PDList();

  // Clean-up the list
  ~PDList();

  // Number of items in the list
  int size();

  // Get a pointer to the position-distance at index i
  PDPtr get(int i);

  // Add a position-distance (as a pointer) to the list
  //    This class now has control over the pointer
  //    And should delete the pointer if the position-distance is removed from
  //    the list
  void addBack(PDPtr position);

  // Checks if the list contains a position-distance with the same co-ordinate
  //    as the given position.
  bool containsCoordinate(PDPtr position);

  // Remove everything from the list
  // Don't forget to clean-up the memory!
  void clear();

  /*                                           */
  /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
  /*                                           */
  void setNumPositions();

  bool containsAllCoordinateFromArray(PDList* coordinates);

  /* This is a suggestion of what you could use. */
  /* You can change this code.                   */
 private:
  PDPtr positions[MAX_POSITIONS];
  int numPositions;
};

#endif  // COSC_ASS_ONE_POSITION_LIST
