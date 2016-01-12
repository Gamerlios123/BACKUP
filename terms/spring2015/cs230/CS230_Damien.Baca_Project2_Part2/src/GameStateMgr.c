// ---------------------------------------------------------------------------
// Project Name		:	Asteroid
// File Name		:	GameStateMgr.cpp
// Author			:	Damien.Baca
// Creation Date	:	2015/02/15
// Purpose			:	implementation of the game state manager
// History			:
// - 2008/02/08		:	- modified to be used like the old style game state
//						  manager
// - 2008/01/31		:	- initial implementation
// ---------------------------------------------------------------------------

#include "GameStateMgr.h"
#include "GameState_Asteroids.h"

// ---------------------------------------------------------------------------
// globals

// variables to keep track the current, previous and next game state
unsigned int	gGameStateInit;
unsigned int	gGameStateCurr;
unsigned int	gGameStatePrev;
unsigned int	gGameStateNext;

// pointer to functions for game state life cycles functions
void (*GameStateLoad)()		= 0;
void (*GameStateInit)()		= 0;
void (*GameStateUpdate)()	= 0;
void (*GameStateDraw)()		= 0;
void (*GameStateFree)()		= 0;
void (*GameStateUnload)()	= 0;

// ---------------------------------------------------------------------------
// Functions implementations

void GameStateMgrInit(unsigned int gameStateInit)
{
	// set the initial game state
	gGameStateInit = gameStateInit;

	// reset the current, previoud and next game
	gGameStateCurr = gGameStateInit;
	gGameStatePrev = gGameStateInit;
	gGameStateNext = gGameStateInit;

	// call the update to set the function pointers
	GameStateMgrUpdate();
}

// ---------------------------------------------------------------------------

void GameStateMgrUpdate()
{
	if ((gGameStateCurr == GS_RESTART) || (gGameStateCurr == GS_QUIT))
		return;

	switch (gGameStateCurr)
	{
	case GS_ASTEROIDS:
	{
		GameStateLoad   =  GameStateAsteroidsLoad;
		GameStateInit   =  GameStateAsteroidsInit;
		GameStateUpdate =  GameStateAsteroidsUpdate;
		GameStateDraw   =  GameStateAsteroidsDraw;
		GameStateFree   =  GameStateAsteroidsFree;
		GameStateUnload =  GameStateAsteroidsUnload;

		break;
	}

	default:
		AE_FATAL_ERROR("invalid state!!");
	}
}

// ---------------------------------------------------------------------------
