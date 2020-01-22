#include <stdio.h>

#include "drawing.h"


void drawPoint(Point *point, SDL_Color *color)
{
	if (point == NULL)
	{
		printf("Cannot draw a NULL Point.\n");
		return;
	}

	SDLA_SetDrawColor(color -> r, color -> g, color -> b);

	// Rectangle centered on 'point':
	SDL_Rect rect = {point -> X - POINT_SIZE / 2, point -> Y - POINT_SIZE / 2, POINT_SIZE, POINT_SIZE};

	SDL_RenderFillRect(renderer, &rect);
}


void drawSegment(Segment *segment, SDL_Color *color)
{
	if (segment == NULL)
	{
		// printf("Cannot draw a NULL Segment.\n");
		return;
	}

	else if (segment -> Start == NULL && segment -> End == NULL)
	{
		printf("Cannot draw: Segment's start and end are NULL.\n");
		return;
	}

	else
	{
		SDLA_SetDrawColor(color -> r, color -> g, color -> b);

		SDL_RenderDrawLine(renderer, (segment -> Start) -> X, (segment -> Start) -> Y,
			(segment -> End) -> X, (segment -> End) -> Y);
	}
}


void drawMap(Map *map)
{
	// Drawing the points:

	for (int i = 0; i < map -> PointsNumber; ++i)
		drawPoint(map -> Locations + i, &Lime);

	// Drawing the borders:

	for (int i = 0; i < map -> PointsNumber; ++i)
	{
		for (int j = i + 1; j < map -> PointsNumber; ++j)
			drawSegment(map -> Edges[i][j], &Red);
	}
}


// Showing the computation step by step:
void show_steps(Map *map)
{
	int ms_delay = map -> PointsNumber <= 10 ? 10 : 1; // animation refresh rate, in ms.

	SDLA_ClearWindow(NULL);

	drawMap(map);

	SDL_RenderPresent(renderer);

	SDL_Delay(ms_delay);
}
