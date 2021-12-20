#ifndef COORDINATES_H
#define COORDINATES_H

struct CoordinatePair
{
    int x;
    int y;
    int z;
};
// Starting point from original game @ pier
CoordinatePair PlayerCoordinate = {15,1,0};
CoordinatePair LastPlayerCoordinate = {15,1,0};

#endif
