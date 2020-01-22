#ifndef GEOM_TOOLS_H
#define GEOM_TOOLS_H


#include "settings.h"


typedef struct
{
	Number X;
	Number Y;
} Point;


typedef struct
{
	Point *Start;
	Point *End;
} Segment;


// Line of equation: ax + by + c = 0:
typedef struct
{
	Number a;
	Number b;
	Number c;
} Line;


// Orientation of a segment. POS: from start to end, NEG: the reverse.
typedef enum {POS, NEG} Direction;


/////////////////////////////////////////////
// Points:
/////////////////////////////////////////////


// This can be freed with a regular 'free()'.
Point* createPoint(Number x, Number y);


void printPoint(Point *point);


// Checks if the two given points are equal:
int pointEquality(Point *A, Point *B);


// Euclidean distance between the Points A and B:
Number distance(Point *A, Point *B);


/////////////////////////////////////////////
// Segments:
/////////////////////////////////////////////


// A segment may be freed with 'free()', but references to its tips must be kept!
// Otherwise, memory will leak. Use 'freeSegmentCompletely()' to free the tips along the segment.
Segment* createSegment(Point *start, Point *end);


void printSegment(Segment *segment);


// Careful, this frees the segment tips too!
void freeSegmentCompletely(Segment *segment);


Number length(Segment *segment);


// Bounding a line:
Segment* SegmentFromLine(Line *line);


/////////////////////////////////////////////
// Lines:
/////////////////////////////////////////////


// This can be freed with a regular 'free()'.
Line* createLine(Number a, Number b, Number c);


void printLine(Line *line);


Line* lineFromPoints(Point *A, Point *B);


/////////////////////////////////////////////
// More 'advanced' geometric utilities:
/////////////////////////////////////////////


// Returns the bisector of A and B. If A and B are equals, will return NULL.
Line* bisector(Point *A, Point *B);


// Returns the intersection of the two lines if it exists, NULL otherwise:
Point* linesIntersection(Line *line1, Line *line2);


// Checks if the given point is in the half plane defined by a line and another point:
int isPointInHalfPlanePoint(Point *point_test, Point *point_ref, Line *line);


// Checks the position of a points versus a segment.
// Returns -2 if the point isn't on the segment's line, -1 if it is before the start,
// 1 if it is after the end, and 0 if the point is on the segment.
int posPointSegment(Point *A, Segment *segment);


// Retract a segment according to a carefully crafted pattern. Returns 1 if the segment needs to be freed:
int retract(Segment *segment, Point *wannabe_newtip, Direction dir);


#endif
