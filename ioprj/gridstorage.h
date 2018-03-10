#ifndef GRIDSTORAGE_H
#define GRIDSTORAGE_H

#include <vector>
#include <fstream>

using namespace std;

#include "gridregion.h"
#include "subregion.h"

// Data file contents are incorrect
#define ERR_IN_DATA_FILE -1

class GridStorage
{

    int width = 0; // horizontal width of the grid

    // defines a 2 dimensional "map" or grid, in which our regions are located
    // operating grid
    vector<GridRegion*> opGrid;

    // REQ maintain a list of subregions that are over the max limit
    vector<SubRegion*> opSubRegions;

    // assume signal threshold Limit is a positive integer
    unsigned thresholdLimit = 0;

    bool findInAnySubRegion( GridRegion *region );

    // define private methods
    void findAllOverLimit( vector<GridRegion*> *vect);
    void createSubRegion( GridRegion *init );

public:
    GridStorage();
    GridStorage( unsigned limit );

    int size();
    int getWidth();
    void setWidth( int width );
    GridRegion* getRegion( int x, int y );

    // Row width is now the first line of the input file
    int readFromFile( string filename, int preAllocLines );

    void calculateFindings();
    void showResults( ostream &outputStream );
    void addGridRegion( int x, int y, unsigned signalStrength );

    ~GridStorage();
};

#endif // GRIDSTORAGE_H
