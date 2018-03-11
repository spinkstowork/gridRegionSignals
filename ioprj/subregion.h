#ifndef SUBREGION_H
#define SUBREGION_H

/*
 * Written By: S. D. Pinkston, Mar 2018.
 */

#include <algorithm> // todo: I think this is dup
#include <fstream>
#include <vector>

#include "gridcell.h"

class SubRegion
{

    vector<GridCell*> srMembers;

    bool memberExists( GridCell *member );

public:
    SubRegion();

    unsigned size();
    GridCell* getFirst();
    void addMember( GridCell *member );
    void addNeighboors( vector<GridCell*> *vect );
    bool regionBelongs( GridCell *region );
    void sortMembersOnSignalMass();
    void print( ostream &outputStream );
};

#endif // SUBREGION_H
