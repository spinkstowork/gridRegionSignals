#ifndef CONTAINS_H
#define CONTAINS_H

/*
 * Usage: bool flag = Contains( v1, e1 );
 * Where: v1 is a vector in which element pointer e1 might exist.
 * */
template <typename T>
const bool Contains( std::vector<T>& Vect, const T& Element )
{
    if (std::find(Vect.begin(), Vect.end(), Element) != Vect.end()) {
        return true;
    }

    return false;
}

#endif // CONTAINS_H
