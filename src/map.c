#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "utilities.h"


Map* createMap(int PointsNumber)
{
	Map *map = (Map*) calloc(1, sizeof(Map));

	*(int*) &(map -> PointsNumber) = PointsNumber;

	map -> Locations = (Point*) calloc(PointsNumber, sizeof(Point));

	map -> Bisectors = (Line***) calloc(PointsNumber, sizeof(Line**));

	map -> Edges = (Segment***) calloc(PointsNumber, sizeof(Segment**));

	if (map -> Locations == NULL || map -> Bisectors == NULL || map -> Edges == NULL)
	{
		printf("\nImpossible to allocate enough memory.\n\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < PointsNumber; ++i)
	{
		map -> Bisectors[i] = (Line**) calloc(PointsNumber, sizeof(Line*));

		map -> Edges[i] = (Segment**) calloc(PointsNumber, sizeof(Segment*));

		if (map -> Bisectors[i] == NULL || map -> Edges[i] == NULL)
		{
			printf("\nImpossible to allocate enough memory.\n\n");
			exit(EXIT_FAILURE);
		}
	}

	initMap(map);

	return map;
}


void freeMap(Map *map)
{
	free(map -> Locations);

	for (int i = 0; i < map -> PointsNumber; ++i)
	{
		for (int j = i + 1; j < map -> PointsNumber; ++j)
		{
			// Bisectors:

			if (map -> Bisectors[i][j] != NULL)
				free(map -> Bisectors[i][j]);

			// Edges:

			if (map -> Edges[i][j] != NULL)
				freeSegmentCompletely(map -> Edges[i][j]); // freeing the tips too.
		}

		free(map -> Bisectors[i]);

		free(map -> Edges[i]);
	}

	free(map -> Bisectors);

	free(map -> Edges);

	free(map);
}


void printMap(Map *map)
{
	printf("\n-> Map:\n\nNumber of points: %d\n\nLocations:\n\n", map -> PointsNumber);

	for (int i = 0; i < map -> PointsNumber; ++i)
		printPoint(map -> Locations + i);

	for (int i = 0; i < map -> PointsNumber; ++i)
	{
		for (int j = i + 1; j < map -> PointsNumber; ++j)
		{
			printf("\nmap -> Bisectors[%d][%d]:\n", i, j);
			printLine(map -> Bisectors[i][j]);

			printf("\nmap -> Edges[%d][%d]:\n", i, j);
			printSegment(map -> Edges[i][j]);
		}
	}
}


void initMap(Map *map)
{
	for (int i = 0; i < map -> PointsNumber; ++i)
	{
		(map -> Locations[i]).X = uniform_random(SMALL_MARGIN, WINDOW_WIDTH - SMALL_MARGIN);

		(map -> Locations[i]).Y = uniform_random(SMALL_MARGIN, WINDOW_HEIGHT - SMALL_MARGIN);
	}

	for (int i = 0; i < map -> PointsNumber; ++i)
	{
		for (int j = i + 1; j < map -> PointsNumber; ++j)
		{
			// Bisectors:

			if (map -> Bisectors[i][j] != NULL)
				free(map -> Bisectors[i][j]);

			map -> Bisectors[i][j] = bisector(map -> Locations + i, map -> Locations + j);

			map -> Bisectors[j][i] = map -> Bisectors[i][j];

			// Edges:

			if (map -> Edges[i][j] != NULL)
				freeSegmentCompletely(map -> Edges[i][j]); // freeing the tips too.

			map -> Edges[i][j] = SegmentFromLine(map -> Bisectors[i][j]);

			map -> Edges[j][i] = map -> Edges[i][j];
		}
	}
}
