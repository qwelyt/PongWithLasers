#ifndef TIMER_H
#define TIMER_H

namespace gameLib{
	class Timer{
		private:
			// Clock time when timer started
			int startTicks;

			// Ticks stored when the timer was paused
			int pausedTicks;

			// Timerstatus
			bool paused;
			bool started;

		public:
			// Initializes variables
			Timer();

			// Clock actions
			void start();
			void stop();
			void pause();
			void unpause();

			// Get timers time
			int getTicks();

			// Check the timer status
			bool isStarted();
			bool isPaused();
	};
}

#endif
