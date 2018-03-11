#ifndef GRIDSTORAGE_H
#define GRIDSTORAGE_H

/*
 * Written By: S. D. Pinkston, Mar 2018.
 */

#include <vector>
#include <fstream>

using namespace std;

#include "gridcell.h"
#include "subregion.h"

// Data file contents are incorrect
#define ERR_IN_DATA_FILE -1

class GridStorage
{

    int width = 0; // horizontal width of the grid

    // defines a 2 dimensional "map" or grid, in which our regions are located
    // operating grid
    vector<GridCell*> opGrid;

    // REQ maintain a list of subregions that are over the max limit
    vector<SubRegion*> opSubRegions;

    // assume signal threshold Limit is a positive integer
    unsigned thresholdLimit = 0;

    bool findInAnySubRegion( GridCell *region );

    // define private methods
    void findAllOverLimit( vector<GridCell*> *vect);
    void createSubRegion( GridCell *init );

public:
    GridStorage();
    GridStorage( unsigned limit );

    int size();
    int getWidth();
    void setWidth( int width );
    GridCell* getRegion( int x, int y );

    // Row width is now the first line of the input file
    int readFromFile( string filename, int preAllocLines );

    void calculateFindings();
    void showResults( ostream &outputStream );

    // This method used when loading from hard coded 2D array
    void addGridRegion( int x, int y, unsigned signalStrength );

    ~GridStorage();
};

#endif // GRIDSTORAGE_H
