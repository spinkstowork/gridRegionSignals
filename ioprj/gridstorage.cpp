/*
 * Written By: S. D. Pinkston, Mar 2018.
 */

#include <string>

#include "gridstorage.h"


GridStorage::GridStorage()
{

}

GridStorage::GridStorage(unsigned limit)
{
    this->thresholdLimit = limit;
}

int GridStorage::size()
{
    return opGrid.size();
}

int GridStorage::getWidth()
{
    return width;
}

void GridStorage::setWidth( int width )
{
    this->width = width;
}

/**
 * Read a file containing a set of integers that are used to define our 2D grid.
 * Useful for testing different sets of data.
 * @brief GridStorage::readFromFile
 * @param filename
 * @param rowWidth
 * @param preAllocLines
 * @return the number of lines read from the input file
 */
int GridStorage::readFromFile( string filename, int preAllocLines )
{
    int rowWidth = 0, tlimit = 0;
    string line;
    vector<unsigned> rawArray;
    rawArray.reserve(preAllocLines);

    ifstream infile;
    infile.open( filename );

    if (infile.is_open())
      {
        // TESTPLAN Read the row width from the 1st line of the input data file
        getline( infile,line );
        rowWidth = stoi( line );

        // TESTPLAN Read the signal strength limit from the 2nd line of the input data file
        getline( infile,line );
        tlimit = stoi( line );

        while( getline( infile,line ) )
        {
          // immediately convert line contents to an integer
          rawArray.push_back( stoi( line ) );
        }

        rawArray.shrink_to_fit();

        if( rawArray.size() % rowWidth != 0 ) {
            cerr << "incorrect number of lines in " << filename << endl;
            cerr << "expected a number divisable by: " << rowWidth << endl;
            return ERR_IN_DATA_FILE;
        }
        else {
            this->width = rowWidth;
            this->thresholdLimit = tlimit;

            vector<unsigned>::const_iterator it;
            int x, y; x = y = 0;

            for( it = rawArray.begin(); it != rawArray.end(); it++ ) {

                addGridRegion( x++, y, *it );

                if( x % rowWidth == 0 ) {
                    x = 0;
                    y++;
                }

            }
        }

        infile.close();
    }
    else {
        cerr << "Cannot open file: " << filename << endl;
    }

    return rawArray.size();
}

/**
 * This helper method aids with setting up the 2D grid from 2 ints and an unsigned.
 * @brief GridStorage::addGridRegion
 * @param x
 * @param y
 * @param signalStrength
 */
void GridStorage::addGridRegion( int x, int y, unsigned signalStrength )
{
    GridCell *tgr = new GridCell( x, y, signalStrength );
    tgr->setStorage( this );
    tgr->setExceedsLimitFlag( (signalStrength > this->thresholdLimit) ? true : false );
    opGrid.push_back( tgr );
}

/**
 * Use a set of coordinates to locate a region.
 * @brief GridStorage::getRegion
 * @param x these inputs are 0 based coordinates
 * @param y these inputs are 0 based coordinates
 * @return
 */
GridCell* GridStorage::getRegion( int x, int y )
{
    unsigned idx = x + (y * this->width );

    if( idx < opGrid.size() ) {
        return opGrid[idx];
    }
    else {
        // todo: this should probably be an exception thrown
        cerr << "Attempt to retrieve grid region that is out of bounds" << endl;
        return 0;
    }
}

/**
 * REQ Find all GridRegions whose threshold value exceeds the threshold limit.
 * @brief GridStorage::findAllOverLimit
 * @param vect
 */
void GridStorage::findAllOverLimit( vector<GridCell*> *vect )
{
    for( unsigned z = 0; z < opGrid.size(); z++ ) {
        if( opGrid[z]->getExceedsLimitFlag() == true ) {
            vect->push_back( opGrid[z] );
        }
    }
}

/**
 * Indicate if a region already exists in any known subregion.
 * @brief GridStorage::findInAnySubRegion
 * @param region
 * @return
 */
bool GridStorage::findInAnySubRegion( GridCell *region )
{
    for( unsigned z = 0; z < opSubRegions.size(); z++ ) {
        SubRegion *tsub = opSubRegions[z];
        if( tsub->regionBelongs( region ) ) {
            return true;
        }
    }
    return false;
}

void GridStorage::calculateFindings()
{
    vector<GridCell*> overLimit;

    findAllOverLimit( &overLimit );

    vector<GridCell*>::const_iterator i;

    for( i=overLimit.begin(); i != overLimit.end(); i++ ) {
        GridCell *tgr = *i;
        createSubRegion( tgr );
    }
}

/**
 * REQ Create a subregion given a starting region.
 * @brief GridStorage::createSubRegion
 * @param init
 */
void GridStorage::createSubRegion( GridCell *init )
{
    // assume creation of a subregion only if the region is not yet part of an existing subregion
    // REQ Each subregions members are unique to the subregion (cant exist in 2 subregions at once)
    if( !findInAnySubRegion( init ) ) {
        // todo: probably should verify that this GridCell exceeds the signal limit
        SubRegion *sreg = new SubRegion();
        sreg->addMember( init );
        opSubRegions.push_back( sreg );

        vector<GridCell*> neighboors;
        unsigned tmpMass = init->findAdjacent( &neighboors );

        // REQ Only assign signal mass (weight) to those regions that exceed threshold
        init->setRMass( tmpMass );

        sreg->addNeighboors( &neighboors );
    }
}

/**
 * REQ Output a report showing the subregions we have discovered based on signal strength.
 * REQ Also output runtime grid dimensions, signal strength limit, region coords with the greatest mass of the subregion
 * REQ Output count of runtime subregions found
 * assume DESC sort on signal mass when listing regions within a subregion
 * @brief GridStorage::showResults
 * @param outputStream
 */
void GridStorage::showResults( ostream &outputStream )
{
    int cnt = 0;
    outputStream << "grid dimension is " << getWidth() << " by " << getWidth();
    outputStream << ", signal limit is " << this->thresholdLimit << endl;

    outputStream << opSubRegions.size() << " subregions were discovered" << endl;

    for( SubRegion *sbr : opSubRegions ) {
        sbr->sortMembersOnSignalMass();

        // assume that if all regions exceeding threshold have equal rMass, then they are equally weighted

        outputStream << "subregion [" << ++cnt << "] contains " << sbr->size() << " region(s)" << endl;
        outputStream << "    " << " subregion identified by region ";
        sbr->getFirst()->print( outputStream );
        outputStream << endl;

        sbr->print( outputStream );
        outputStream << endl;
    }
}

/**
 * Ensure memory for opGrid and opSubRegions is not leaked.
 * @brief GridStorage::~GridStorage
 */
GridStorage::~GridStorage()
{
    for ( auto p : opGrid ) { // Note: C++11 syntax here
        delete p;
    }

    for ( auto p : opSubRegions ) { // Note: C++11 syntax here
        delete p;
    }
}
