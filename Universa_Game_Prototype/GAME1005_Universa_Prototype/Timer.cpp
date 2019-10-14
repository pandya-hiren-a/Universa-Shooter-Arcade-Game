/**********************************
Filename: Timer.cpp
Author: F-Racing Team
Created On: 26/03/2019
Modified On: As Above
***********************************/
#include "stdafx.h"
#include "Timer.h"

int Timer::m_iStartTick = SDL_GetTicks();					// Get start time from SDL_GetTicks
int Timer::m_iElapsedTicks = 0;								// Elapsed time as zero
float Timer::m_fDeltaTime = 0.0f;							// Delta time as zero
bool Timer::m_bTimerNeeded = false;							// Initial timer requirement - not needed
int Timer::m_iBlinks = 8;									// Total number of blinks the texture should perform
int Timer::m_iCurrentBlink = 0;								// Current blink of the texture

// Get delta between elapsed and start
float Timer::GetDeltaTime() {
	// Get elapsed time
	m_iElapsedTicks = SDL_GetTicks() - m_iStartTick;
	// Multiply elapsed time to convert from the time into s from ms
	m_fDeltaTime = m_iElapsedTicks * 0.001f;
	// Return the calculated delta
	return m_fDeltaTime;
}

// Reset the member variables for future reference
void Timer::ResetTimer() {
	m_iStartTick = SDL_GetTicks();
	m_iCurrentBlink = 0;
	m_iElapsedTicks = 0;
	m_fDeltaTime = 0.0f;
}