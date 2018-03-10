#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "gridstorage.h"

// TESTPLAN Initially, verify that the results mentioned in the requirements pdf can be duplicated
// DESIGN Prefer an object oriented implementation verses a straight 'C' style implementation
// DESIGN Make use of the C++11 language specification
// DESIGN Performance considerations are taken as a secondary concern in this implementation
// DESIGN Demonstrate separation of concerns (encapsulation) via the organization of behavior into the GridStorage, GridRegion, and SubRegion classes
// DESIGN Screen memory leaks reasonably (track new operator usage), but dont go so far as to implement macros or external tools to verify 100% compliance

// TESTPLAN Use a data file containing a set of integers, one per row, for the app to process
// Very handy thing for testing

// TESTPLAN I am including 3 file based data sets (8x8,10x10,100x100) in addition to the 6x6 original
#define DATA_FILENAME "sd6-6.dat"

// Amount of lines allocated during initial file read
#define PREALLOC_LINES 100

// REQ This determines the row width of the int's contained in the hard coded array
// todo: we may wish to calculate the square root of the number of input lines instead
#define GRID_WIDTH 6
#define GRID_HEIGHT GRID_WIDTH

// REQ set upper signal limit for later use to determine regions of interest
#define MAX_SIG_THRESHOLD 200

// This method is NOT required, however its useful to test with different input files
void processGridFromFile() {
    GridStorage gStorage;
    gStorage.readFromFile( DATA_FILENAME, PREALLOC_LINES );

    gStorage.calculateFindings();
    gStorage.showResults( cout );
}

// REQ create a function, expressed either in C# or C++, that takes two inputs: two-dimensional array of values, a threshold T
void calculateTwoDimResults( const int (*array)[GRID_WIDTH][GRID_HEIGHT], unsigned T )
{
    GridStorage gStorage( T );
    gStorage.setWidth( GRID_WIDTH );

    for( int y = 0; y < GRID_HEIGHT; y++ ) {
        for( int x = 0; x < GRID_WIDTH; x++ ) {
            // cout << (*array)[x][y] << endl;
            gStorage.addGridRegion( x, y, (*array)[x][y] );
        }
    }

    gStorage.calculateFindings();
    gStorage.showResults( cout );
}

// Setup method (adapter) for primary required function calculateTwoDimResults()
void processGridFromHardCodedArray() {

    // REQ These values taken from problem assessment dot PDF
    const int grid[GRID_WIDTH][GRID_HEIGHT] = { { 0, 80, 45, 95, 170, 145 },
                            { 115, 210, 60, 5, 230, 220 },
                            { 5, 0, 145, 250, 245, 140 },
                            { 15, 5, 175, 250, 185, 160 },
                            { 0, 5, 95, 112, 165, 250 },
                            { 5, 0, 25, 5, 145, 250 } };

    unsigned T = MAX_SIG_THRESHOLD;

    calculateTwoDimResults( &grid, T );
}

int main(int argc, char *argv[])
{
    // TESTPLAN method processGridFromFile() can be used to drive the logic from an input file
    // processGridFromFile();
    processGridFromHardCodedArray();

    return 0;
}

