#include <algorithm>

#include "subregion.h"
#include "contains.h"

SubRegion::SubRegion()
{

}

unsigned SubRegion::size()
{
    return srMembers.size();
}

GridRegion* SubRegion::getFirst()
{
    if( srMembers.size() > 0 ) {
        return srMembers[0];
    }
    else {
        return 0; // todo: should probably throw an exception here
    }
}

/**
 * Add a region to this SubRegion if its not already present.
 * @brief SubRegion::addMember
 * @param member
 */
void SubRegion::addMember( GridRegion *member )
{
    // dont add a member more than once
    if( !Contains( srMembers, member ) ) {
        srMembers.push_back( member );
    }
}

/**
 * Recursive method to build this subregion from a list of neighbooring regions.
 * @brief SubRegion::addNeighboors
 * @param vect
 */
void SubRegion::addNeighboors( vector<GridRegion*> *vect )
{
    vector<GridRegion*>::const_iterator i;

    for( i=vect->begin(); i != vect->end(); i++ ) {
        GridRegion *tgr = *i;

        if( (tgr->getExceedsLimitFlag() == true) && !Contains( srMembers, tgr ) ) {
            this->addMember( tgr );
            vector<GridRegion*> neighboors;
            unsigned tmpMass = tgr->findAdjacent( &neighboors );

            tgr->setRMass( tmpMass );

            addNeighboors( &neighboors ); // note recursion
        }
    }
}

/**
 * Given a region, use a templated function to check if it exists in the vector.
 * @brief SubRegion::regionBelongs
 * @param region
 * @return
 */
bool SubRegion::regionBelongs( GridRegion *region )
{
    return Contains( srMembers, region );
}

// implements a DESCENDING sort
bool sortByRMass( GridRegion *a, GridRegion *b )
{
    return a->getRMass() > b->getRMass();
}

/**
 * Simple sort routine takes advantage of std::sort.
 * @brief SubRegion::sortMembersOnSignalMass
 */
void SubRegion::sortMembersOnSignalMass()
{
    if( srMembers.size() > 1 ) {
        sort( srMembers.begin(), srMembers.end(), sortByRMass );
    }
}

/**
 * Output each member grid region to the stream.
 * @brief SubRegion::print
 * @param outputStream
 */
void SubRegion::print( ostream &outputStream )
{
    for( GridRegion *reg : srMembers ) {
        outputStream << "        ";
        reg->print( outputStream );
    }
}
