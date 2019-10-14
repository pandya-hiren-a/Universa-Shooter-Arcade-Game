/**********************************
Filename: Timer.h
Author: F-Racing Team
Created On: 26/03/2019
Modified On: As Above
***********************************/
#pragma once
#include "SDL.h"

class Timer {
public:
	static int m_iStartTick;					// Starting Tick from SDL_GetTicks
	static int m_iElapsedTicks;					// Passed time 
	static float m_fDeltaTime;					// Delta between start and current
	static bool m_bTimerNeeded;					// If timer is required 
	static int m_iBlinks;						// Total number of blinks through timer
	static int m_iCurrentBlink;					// Current blink of the texture

	static float GetDeltaTime();				// Get delta time
	static void ResetTimer();					// Reset the timer member variables
};