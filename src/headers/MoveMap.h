#pragma once

#include "Global.h"

void MoveMap()
{
	BACKGROUND_POSX += MapVel+5;
	GROUND_POSX += MapVel+5;

	if (BACKGROUND_POSX > BACKGROUND_WIDTH)
		BACKGROUND_POSX = 0;

	if (GROUND_POSX > GROUND_WIDTH)
		GROUND_POSX = 0;
}
