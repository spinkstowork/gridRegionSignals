#ifndef SUBREGION_H
#define SUBREGION_H

/*
 * Written By: S. D. Pinkston, Mar 2018.
 */

#include <algorithm> // todo: I think this is dup
#include <fstream>
#include <vector>

#include "gridregion.h"

class SubRegion
{

    vector<GridRegion*> srMembers;

    bool memberExists( GridRegion *member );

public:
    SubRegion();

    unsigned size();
    GridRegion* getFirst();
    void addMember( GridRegion *member );
    void addNeighboors( vector<GridRegion*> *vect );
    bool regionBelongs( GridRegion *region );
    void sortMembersOnSignalMass();
    void print( ostream &outputStream );
};

#endif // SUBREGION_H
