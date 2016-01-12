// ---------------------------------------------------------------------------
// Project Name		:	Cage Game
// File Name		:	GameState_Menu.cpp
// Author			:	Antoine Abi Chakra
// Creation Date	:	2012/03/16
// Purpose			:	main entry point for the test program
// History			:
// - 
// ---------------------------------------------------------------------------
// includes

#include "main.h"

// include game state functions
#include "GameState_Play.h"
#include <stdio.h>

// ---------------------------------------------------------------------------
// Static function protoypes

// ---------------------------------------------------------------------------
// main

int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR command_line, int show)
{
	//LineSegment2D Line;

	//Vector2D P0, P1, P, Ps, Pe, Pi, RC, RP, RCorrect;

	//float A, B, C, D, E, F;

	//Vector2DSet(&P0, 1.0f, 1.0f); // Wall Start

	//Vector2DSet(&P1, 5.0f, 1.0f); // Wall End

	//Vector2DSet(&P, 2.0f, 4.0f);  // Point On Line

	//Vector2DSet(&Ps, 4.0f, 3.0f); // Trajectory Start

	//Vector2DSet(&Pe, 2.0f, 0.0f); // Trajectory End

	//BuildLineSegment2D(&Line, &P0, &P1);

	//A = StaticPointToStaticLineSegment(&P, &Line);  // Is it on the line, 0 = yes 

	//B = AnimatedPointToStaticLineSegment(&Ps, &Pe, &Line, &Pi);  // Returns Intersection Time if intersection occurs

	//C = AnimatedCircleToStaticLineSegment(&Ps, &Pe, 0.5f, &Line, &Pi);

	//D = ReflectAnimatedPointOnStaticLineSegment(&Ps, &Pe, &Line, &Pi, &RP);

	//E = ReflectAnimatedCircleOnStaticLineSegment(&Ps, &Pe, 0.5f, &Line, &Pi, &RC);

	//F = AEReflectAnimatedCircleOnStaticLineSegment(&Ps, &Pe, 0.5f, &Line, &Pi, &RCorrect);

	//A = A;

	// Initialize the system
	AESysInitInfo sysInitInfo;
	
	sysInitInfo.mAppInstance		    = instanceH;
	sysInitInfo.mShow				    = show;
	sysInitInfo.mWinWidth			    = 800; 
	sysInitInfo.mWinHeight	            = 600;
	sysInitInfo.mCreateConsole          = 1;
	sysInitInfo.mMaxFrameRate		    = 60;
	sysInitInfo.mpWinCallBack		    = NULL;//MyWinCallBack;
	sysInitInfo.mClassStyle		        = CS_HREDRAW | CS_VREDRAW;											
	sysInitInfo.mWindowStyle		    = WS_OVERLAPPEDWINDOW;//WS_POPUP | WS_VISIBLE | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
							    
	sysInitInfo.mCreateWindow		    = 1;
	sysInitInfo.mWindowHandle		    = NULL;
	sysInitInfo.mHandleWindowMessages   = 1;
	
	
	if(0 == AESysInit (&sysInitInfo))
		return 1;
	
	GameStateMgrInit(GS_PLAY);
	
	while(gGameStateCurr != GS_QUIT)
	{
		// reset the system modules
		AESysReset();
	
		// If not restarting, load the gamestate
		if(gGameStateCurr != GS_RESTART)
		{
			GameStateMgrUpdate();
			GameStateLoad();
		}
		else
			gGameStateNext = gGameStateCurr = gGameStatePrev;
	
		// Initialize the gamestate
		GameStateInit();
	
		while(gGameStateCurr == gGameStateNext)
		{
			AESysFrameStart();
	
			AEInputUpdate();
	
			GameStateUpdate();
	
			GameStateDraw();
			
			AESysFrameEnd();
	
			// check if forcing the application to quit
			if (AEInputCheckTriggered(VK_ESCAPE) || 0 == AESysDoesWindowExist())
				gGameStateNext = GS_QUIT;
		}
		
		GameStateFree();
	
		if(gGameStateNext != GS_RESTART)
			GameStateUnload();
	
		gGameStatePrev = gGameStateCurr;
		gGameStateCurr = gGameStateNext;
	}
	
	// free the system
	AESysExit();
}



// ---------------------------------------------------------------------------


