#include "Timer.h"
#include <SDL/SDL.h>

namespace gameLib{
	Timer::Timer(){
		startTicks = 0;
		pausedTicks = 0;
		paused = false;
		started = false;
	}

	void Timer::start(){
		// Start timer
		started = true;

		// Unpause timer;
		paused = false;

		// Get current clock time
		startTicks = SDL_GetTicks();
	}

	void Timer::stop(){
		// Stop the timer
		started = false;

		// Unpause the timer
		paused = false;
	}

	int Timer::getTicks(){
		// If the timer is running
		if(started){
			// If the timer is pausd, return the number of ticks paused
			if(paused){
				return pausedTicks;
			}
			else{ // Else, return the current time minus the start time.
				return SDL_GetTicks() - startTicks;
			}
		}

		// If the timer isn't running, return 0.
		return 0;
	}

	void Timer::pause(){
		//If timer is running and isn't paused
		if(started && !paused){
			paused = true;

			// Calculate when the timer was paused
			pausedTicks = SDL_GetTicks() - startTicks;
		}
	}

	void Timer::unpause(){
		if(paused){
			paused=false; //Unpause

			// Reset starting ticks
			startTicks = SDL_GetTicks() - pausedTicks;

			// Reset paused ticks
			pausedTicks=0;
		}
	}

	bool Timer::isStarted(){
		return started;
	}

	bool Timer::isPaused(){
		return paused;
	}
} // gameLib
