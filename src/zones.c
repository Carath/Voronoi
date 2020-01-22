#include <stdio.h>

#include "zones.h"
#include "drawing.h"


// Find the influence zone of each point:
void findZones(Map *map, AnimationOption opt)
{
	printf("-> Finding the zones.\n");

	int n = map -> PointsNumber;

	// For the point 'i':
	for (int i = 0; i < n - 1; ++i) // no treatment for the last point.
	{
		// For the edge '(i, j)':
		for (int j = 0; j < n - 1; ++j)
		{
			// Intersect with edge '(i, k)':
			for (int k = j + 1; k < n; ++k)
			{
				if (j != i && k != i)
				{
					// printf("\n(%d, %d) vs (%d, %d)\n", i, j, i, k);

					updateEdges(map, i, j, k);

					// Showing the computation step by step:
					if (opt == STEP_BY_STEP)
						show_steps(map);
				}
			}
		}
	}

	printf("Done.\n");
}


// Update the map edges by intersecting them two by two:
void updateEdges(Map *map, int i, int j, int k)
{
	Point *point_ref = map -> Locations + i;

	Line *line_ij = map -> Bisectors[i][j];
	Line *line_ik = map -> Bisectors[i][k];

	Segment *segment_ij = map -> Edges[i][j];
	Segment *segment_ik = map -> Edges[i][k];

	if (segment_ij == NULL || segment_ik == NULL)
	{
		// printf("At least one of the two edges is NULL: ij -> %d, ik -> %d\n", *segment_ij == NULL, *segment_ik == NULL);
		return;
	}

	Point *intersection = linesIntersection(line_ij, line_ik);

	// For debugging:
	// drawPoint(intersection, &Yellow);

	int free_order_ij = retract_method(segment_ij, line_ik, point_ref, intersection);
	int free_order_ik = retract_method(segment_ik, line_ij, point_ref, intersection);

	// Freeing what is no more useful:

	if (free_order_ij)
	{
		freeSegmentCompletely(segment_ij);

		map -> Edges[i][j] = NULL;
		map -> Edges[j][i] = NULL;
	}

	if (free_order_ik)
	{
		freeSegmentCompletely(segment_ik);

		map -> Edges[i][k] = NULL;
		map -> Edges[k][i] = NULL;
	}

	free(intersection);
}


// Framework for the retractation. Returns 1 if the segment needs to be freed:
int retract_method(Segment *segment, Line *line, Point *point_ref, Point *intersection)
{
	Point *start = segment -> Start;
	Point *end = segment -> End;

	int domain_check_start = isPointInHalfPlanePoint(start, point_ref, line);
	int domain_check_end = isPointInHalfPlanePoint(end, point_ref, line);

	if (domain_check_start && domain_check_end)
	{
		// printf("Both start and end are in the correct domain.\n");
		return 0;
	}

	if (!domain_check_start && !domain_check_end)
	{
		// printf("Both start and end are NOT in the correct domain. Freeing the segment.\n");
		return 1;
	}

	// Finding the direction to follow in order to retract:

	Direction dir;

	if (!pointEquality(start, intersection))
		dir = domain_check_start ? NEG : POS;

	else
		dir = domain_check_end ? POS : NEG;

	// Retracting, if possible:
	return retract(segment, intersection, dir);
}
