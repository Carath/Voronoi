#ifndef MAP_H
#define MAP_H


#include "settings.h"
#include "geom_tools.h"


typedef struct
{
	const int PointsNumber;
	Point *Locations; // array of Point, length PointsNumber.
	Line ***Bisectors; // matrix of Line adresses, PointsNumber x PointsNumber.
	Segment ***Edges; // matrix of Segment adresses, PointsNumber x PointsNumber.
} Map;


Map* createMap(int PointsNumber);


void freeMap(Map *map);


void printMap(Map *map);


void initMap(Map *map);


#endif
