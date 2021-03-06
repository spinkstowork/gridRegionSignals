/*
 * Written By: S. D. Pinkston, Mar 2018.
 */

#include "gridcell.h"
#include "gridstorage.h"

// DESIGN GridCell defines a region on the grid which contains location and threshold

GridCell::GridCell()
{
}

GridCell::GridCell( int x, int y, unsigned signalStrength )
{
   this->xCoord = x;
   this->yCoord = y;
   this->signalStrength = signalStrength;

}

int GridCell::getXCoord()
{
    return this->xCoord;
}

int GridCell::getYCoord()
{
    return this->yCoord;
}

unsigned GridCell::getSignalStrength()
{
    return this->signalStrength;
}

bool GridCell::getExceedsLimitFlag()
{
    return this->exceedsLimitFlag;
}

void GridCell::setExceedsLimitFlag( bool flag )
{
    this->exceedsLimitFlag = flag;
}

void GridCell::setRMass( unsigned rMass )
{
    this->rMass = rMass;
}

void GridCell::setStorage( GridStorage *storage )
{
    this->storage = storage;
}

unsigned GridCell::getRMass()
{
    return this->rMass;
}

/**
 * REQ Utility report method to list GridCell properties to a stream.
 * @brief GridCell::print
 * @param outputStream
 */
void GridCell::print( ostream &outputStream )
{
    outputStream << this->xCoord << ",";
    outputStream << this->yCoord << ", T=";

    if( this->getExceedsLimitFlag() == true ) {
        outputStream << this->signalStrength << '*';
    }
    else {
        outputStream << this->signalStrength;
    }

    if( this->getRMass() > 0 ) {
        outputStream << ", RM=" << getRMass();
    }
    outputStream << endl;
}

/**
 * Using our reference to the master grid storage, find which regions are adjacent.
 * (i.e. neighboors)
 * @brief GridCell::findAdjacent
 * @param vect
 * @return assume Total mass equals the signal "mass" of this region and its neighboor regions.
 */
unsigned GridCell::findAdjacent( vector<GridCell*> *vect )
{
    // REQ: region is considered adjacent even if its touching diagonally
    int hRange = 3, vRange = 3;
    int xCoord, yCoord;
    unsigned tmpMass = this->getSignalStrength();

    // establish some bounds for x
    if( (getXCoord()-1 >= 0) ) {
        xCoord = getXCoord()-1; // note conversion to 0 based

        if( getXCoord()+1 > (this->storage->getWidth()-1) ) {
            hRange--;
        }
    }
    else {
        xCoord = 0;
        hRange--;
    }

    // establish some bounds for y
    if( (getYCoord()-1 >= 0) ) {
        yCoord = getYCoord()-1; // note conversion to 0 based

        // For now y equals x (e.g. square grid)
        if( getYCoord()+1 > (this->storage->getWidth()-1) ) {
            vRange--;
        }
    }
    else {
        yCoord = 0;
        vRange--;
    }

    for( int x=0; x < hRange; x++ ) {
        for( int y=0; y < vRange; y++ ) {
            // We cant be a neighboor of ourselves
            if( !((this->xCoord) == (xCoord+x) && (this->yCoord) == (yCoord+y)) ) {
                // cout << (xCoord+x) << ", " << (yCoord+y) << endl;
                GridCell *tgr = this->storage->getRegion( xCoord+x, yCoord+y );
                vect->push_back( tgr );

                // REQ Only consider regions for weighting that exceed the threshold limit
                if( tgr->getExceedsLimitFlag() ) {
                    tmpMass += tgr->getSignalStrength();
                }
            }
        }
    }
    return tmpMass;
}
