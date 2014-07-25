#ifndef SCREEN_H
#define SCREEN_H

#include <SDL/SDL.h>
#include "Object.h"
#include "Timer.h"
#include <vector>
#include <string>

namespace gameLib{
	class Screen{
		typedef void (*Action)(void);
		private:
			SDL_Surface *screen;
			const int WIDTH;
			const int HEIGHT;
			const int BPP;
			const int FPS;

			bool running;
			bool paused;
			bool regulateFPS;
			int keyDelay;
			int keyInterval;
			Timer timer;
			Uint32 bgColor;

			std::vector<Object*> comps;
			std::vector<Object*>::iterator pos;
			std::map<SDLKey, Action> downActions;
			std::map<SDLKey, Action>::iterator it;
			std::vector<Action> tickActions;

			Screen(int w, int h, int fps);
		public:
			static Screen* create(int w, int h, int fps);
			~Screen();

			void drawScreen();
			void quit();
			void run();

			void pause();
			void unpause();
			bool isPaused();

			bool isRunning();

			void addObject(Object *obj);
			void removeObject(Object *obj);
			void deleteObject(Object *obj);

			void setBackground(int r, int g, int b);
			
			void setTitle(std::string title);
			
			void regulateFrameRate(bool cap);
			void keyRepeat(int delay, int interval);

			void addKeyDownAction(SDLKey key, Action a);
			void addTickAction(Action a);

			SDL_Surface* getScreen();
	};
}

#endif
