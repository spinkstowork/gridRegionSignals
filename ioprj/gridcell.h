#ifndef GRIDCELL_H
#define GRIDCELL_H

/*
 * Written By: S. D. Pinkston, Mar 2018.
 */

#include <iostream>
#include <vector>

using namespace std;

class GridStorage; // make use of forward declaration to solve circular dependency

class GridCell
{

    int xCoord; // REQ Work within a 2 dimensional grid
    int yCoord;

    // assume that signalStrength is always a positive integer
    unsigned signalStrength; // REQ refers potentially to a signal strength

    bool exceedsLimitFlag = false;

    // REQ Must weight each region based on its "mass" meaning the total of regions strength and its neighboors
    unsigned rMass = 0;

    GridStorage *storage;

public:
    GridCell();
    GridCell( int x, int y, unsigned signalStrength);

    int getXCoord();
    int getYCoord();
    unsigned getSignalStrength();
    bool getExceedsLimitFlag();
    void setExceedsLimitFlag( bool flag );
    void setRMass( unsigned rMass );
    unsigned getRMass();

    void setStorage( GridStorage *storage );
    void print( ostream &outputStream );
    unsigned findAdjacent( vector<GridCell*> *vect);
};

#endif // GRIDCELL_H
