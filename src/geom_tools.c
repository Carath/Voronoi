#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "geom_tools.h"
#include "utilities.h"


/////////////////////////////////////////////
// Points:
/////////////////////////////////////////////


// This can be freed with a regular 'free()'.
Point* createPoint(Number x, Number y)
{
	Point *point = (Point*) calloc(1, sizeof(Point));

	point -> X = x;
	point -> Y = y;

	return point;
}


void printPoint(Point *point)
{
	if (point == NULL)
		printf("NULL Point.\n");

	else
		printf("Point: (%.2f, %.2f)\n", point -> X, point -> Y);
}


// Checks if the two given points are equal:
int pointEquality(Point *A, Point *B)
{
	if (A == NULL || B == NULL)
	{
		printf("Cannot test the equality of NULL points.\n");
		return 0;
	}

	return epsilonEquality(A -> X, B -> X) && epsilonEquality(A -> Y, B -> Y);
}


// Euclidean distance between the Points A and B:
Number distance(Point *A, Point *B)
{
	if (A == NULL || B == NULL)
	{
		printf("Cannot find a distance between NULL points.\n");
		return 0;
	}

	Number delta_x = A -> X - B -> X, delta_y = A -> Y - B -> Y;

	return sqrt(delta_x * delta_x + delta_y * delta_y);
}


/////////////////////////////////////////////
// Segments:
/////////////////////////////////////////////


// A segment may be freed with 'free()', but references to its tips must be kept!
// Otherwise, memory will leak. Use 'freeSegmentCompletely()' to free the tips along the segment.
Segment* createSegment(Point *start, Point *end)
{
	if (start == NULL || end == NULL)
	{
		printf("Segment's tips must not be NULL.\n");
		return NULL;
	}

	Segment *segment = (Segment*) calloc(1, sizeof(Segment));

	segment -> Start = start;
	segment -> End = end;

	return segment;
}


void printSegment(Segment *segment)
{
	if (segment == NULL)
		printf("NULL Segment.\n");

	else if (segment -> Start == NULL || segment -> End == NULL)
		printf("Segment's start or end is NULL.\n");

	else
		printf("Segment: start = (%.2f, %.2f), end = (%.2f, %.2f)\n",
			(segment -> Start) -> X, (segment -> Start) -> Y, (segment -> End) -> X, (segment -> End) -> Y);
}


// Careful, this frees the segment tips too!
void freeSegmentCompletely(Segment *segment)
{
	free(segment -> Start);
	free(segment -> End);
	free(segment);
}


Number length(Segment *segment)
{
	if (segment == NULL)
	{
		printf("NULL Segment.\n");
		return 0;
	}

	return distance(segment -> Start, segment -> End);
}


// Bounding a line:
Segment* SegmentFromLine(Line *line)
{
	if (line == NULL)
	{
		printf("NULL line.\n");
		return NULL;
	}

	Number a = line -> a;
	Number b = line -> b;
	Number c = line -> c;

	Point *start, *end;

	if (epsilonEquality(b, 0)) // Vertical line.
	{
		if (epsilonEquality(a, 0))
		{
			printf("Invalid line equation.\n");
			return NULL;
		}

		start = createPoint(- c / a, 0);
		end = createPoint(- c / a, WINDOW_HEIGHT);
	}

	else
	{
		start = createPoint(0, - c / b);
		end = createPoint(WINDOW_WIDTH, - (a * WINDOW_WIDTH + c) / b);
	}

	// Careful, start and end are not freed!
	return createSegment(start, end);
}


/////////////////////////////////////////////
// Lines:
/////////////////////////////////////////////


// This can be freed with a regular 'free()'.
Line* createLine(Number a, Number b, Number c)
{
	if (epsilonEquality(a, 0) && epsilonEquality(b, 0))
	{
		printf("Invalid line equation.\n");
		return NULL;
	}

	Line *line = (Line*) calloc(1, sizeof(Line));

	line -> a = a;
	line -> b = b;
	line -> c = c;

	return line;
}


void printLine(Line *line)
{
	if (line == NULL)
	{
		printf("NULL line.\n");
		return;
	}

	printf("a = %.2f, b = %.2f, c = %.2f\n", line -> a, line -> b, line -> c);
}


Line* lineFromPoints(Point *A, Point *B)
{
	if (A == NULL || B == NULL)
	{
		printf("Cannot find a line going through NULL points.\n");
		return NULL;
	}

	Number a = B -> Y - A -> Y;
	Number b = A -> X - B -> X;
	Number c = B -> X * A -> Y - A -> X * B -> Y;

	return createLine(a, b, c);
}


/////////////////////////////////////////////
// More 'advanced' geometric utilities:
/////////////////////////////////////////////


// Returns the bisector of A and B. If A and B are equals, will return NULL.
Line* bisector(Point *A, Point *B)
{
	if (A == NULL || B == NULL)
	{
		printf("Cannot find a bisector of NULL points.\n");
		return NULL;
	}

	Number a = B -> X - A -> X;
	Number b = B -> Y - A -> Y;
	Number c = (A -> X * A -> X + A -> Y * A -> Y - B -> X * B -> X - B -> Y * B -> Y) / 2;

	return createLine(a, b, c);
}


// Returns the intersection of the two lines if it exists, NULL otherwise:
Point* linesIntersection(Line *line1, Line *line2)
{
	Number a1 = line1 -> a, b1 = line1 -> b, c1 = line1 -> c;
	Number a2 = line2 -> a, b2 = line2 -> b, c2 = line2 -> c;

	Number det = a1 * b2 - b1 * a2;

	if (epsilonEquality(det, 0))
	{
		printf("Lines don't intersect, or are equal.\n");
		return NULL;
	}

	Number interX = (b1 * c2 - b2 * c1) / det;
	Number interY = (a2 * c1 - a1 * c2) / det;

	return createPoint(interX, interY);
}


// Checks if the given point is in the half plane defined by a line and another point:
int isPointInHalfPlanePoint(Point *point_test, Point *point_ref, Line *line)
{
	if (point_test == NULL || point_ref == NULL || line == NULL)
	{
		printf("Cannot do a domain check, invalid arguments.\n");
		return 0;
	}

	int sign = line -> a * point_ref -> X + line -> b * point_ref -> Y + line -> c >= 0 ? 1 : -1;

	return sign * (line -> a * point_test -> X + line -> b * point_test -> Y + line -> c) >= 0;
}


// Checks the position of a points versus a segment.
// Returns -2 if the point isn't on the segment's line, -1 if it is before the start,
// 1 if it is after the end, and 0 if the point is on the segment.
int posPointSegment(Point *A, Segment *segment)
{
	Point *start = segment -> Start;
	Point *end = segment -> End;

	Number dirTo_End_X = end -> X - start -> X;
	Number dirTo_End_Y = end -> Y - start -> Y;

	Number dirTo_A_X = A -> X - start -> X;
	Number dirTo_A_Y = A -> Y - start -> Y;

	if (epsilonEquality(dirTo_End_X, 0) && epsilonEquality(dirTo_End_Y, 0)) // start equals end.
		return (epsilonEquality(dirTo_A_X, 0) && epsilonEquality(dirTo_A_Y, 0));

	Number ratioX = dirTo_A_X / dirTo_End_X;
	Number ratioY = dirTo_A_Y / dirTo_End_Y;

	if (!epsilonEquality(ratioX, ratioY)) // A isn't anywhere on the line.
		return -2;

	if (epsilonStrInequality(ratioX, 0)) // A is before the start of the segment.
		return -1;

	if (epsilonStrInequality(1, ratioX)) // A is after the end of the segment.
		return 1;

	else
		return 0; // A is on the segment.
}


// Retract a segment according to a carefully crafted pattern. Returns 1 if the segment needs to be freed:
int retract(Segment *segment, Point *wannabe_newtip, Direction dir)
{
	if (wannabe_newtip == NULL)
	{
		printf("New tip is NULL.\n");
		return 0;
	}

	Point *oldtip = dir == POS ? segment -> Start : segment -> End;

	int pos_newtip = posPointSegment(wannabe_newtip, segment);

	if (pos_newtip == -2)
	{
		// printf("New tip is not located on the segment's line...\n");
		return 0;
	}

	else if ((pos_newtip == -1 && dir == NEG) || (pos_newtip == 1 && dir == POS))
	{
		return 1; // Setting the segment to be freed.
	}

	else if (pos_newtip == 0) // new tip is on the segment.
	{
		// printf("Retracting with direction: %d\n", dir);

		// Copying to prevent side effects:

		oldtip -> X = wannabe_newtip -> X;
		oldtip -> Y = wannabe_newtip -> Y;
	}

	return 0;
}
