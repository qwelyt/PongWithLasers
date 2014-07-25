#include "Screen.h"
#include "Object.h"
#include "Timer.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdexcept>
#include <iostream>
#include <string>
#include <algorithm>

namespace gameLib{
	Screen* Screen::create(int w, int h, int fps){
		return new Screen(w,h,fps);
	}

	Screen::Screen(int w, int h, int fps): WIDTH(w), HEIGHT(h), BPP(32), FPS(fps), keyDelay(0), keyInterval(0){
		int flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
		if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
			throw std::runtime_error("SDL could not initialize.");
		}
		else if(TTF_Init() == -1){
			throw std::runtime_error("SDL_ttf could not initialize.");
		}
		else if(IMG_Init(flags) != flags){
			throw std::runtime_error("SDL_image could not initialize.");
		}
		else{
			screen = SDL_SetVideoMode(WIDTH,HEIGHT,BPP, SDL_SWSURFACE | SDL_DOUBLEBUF);
		}
		bgColor = SDL_MapRGB(screen->format, 0,0,0); //Start with a black screen
		regulateFPS=true;
		running = true;
		paused=false;
	}

	Screen::~Screen(){
		//delete screen;
	}

	void Screen::drawScreen(){
		if(running){
			SDL_FillRect(screen, NULL, bgColor);

			for(int i=0; i<comps.size(); i++){
				comps[i]->draw(getScreen());
			}
			SDL_Flip(screen);
		}
	}

	bool Screen::isRunning(){
		return running;
	}

	void Screen::quit(){
		running=false;
		for(int i=0; i<comps.size(); i++)
			delete comps[i];
			//SDL_FreeSurface(comps[i]->getObject());
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();

	}
	void Screen::run(){
		SDL_Event event;
		SDL_EnableKeyRepeat(keyDelay, keyInterval);
		int frame=0;

		while(running){
			timer.start();
			//Actions
			while(SDL_PollEvent(&event)){
				if(event.type==SDL_QUIT)
					quit();

				if(event.type==SDL_KEYDOWN){ // The screens actions
					it=downActions.find(event.key.keysym.sym);
					if(it != downActions.end()){
						downActions[event.key.keysym.sym]();
					}
				}
					
				if(running){
					if(!paused){
						for(int j=0; j<comps.size(); j++){ // The objects actions.
							if(event.type==SDL_MOUSEBUTTONDOWN)
								comps[j]->mouseDown(event.button.x, event.button.y);

							if(event.type==SDL_MOUSEBUTTONUP)
								comps[j]->mouseUp(event.button.x, event.button.y);

							if(event.type==SDL_MOUSEMOTION)
								comps[j]->mouseMotion(event.motion.x, event.motion.y);

							if(event.type==SDL_KEYDOWN)
								comps[j]->keyDown(event.key.keysym.sym);

							if(event.type==SDL_KEYUP)
								comps[j]->keyUp(event.key.keysym.sym);
						}
					}
				}
			}
			if(running){
				if(!paused){
					//Logic
					for(int i=0; i<tickActions.size(); i++){
						tickActions[i]();
					}

					for(int i=0; i<comps.size(); i++){
						comps[i]->move();
					}


					for(int i=0; i<comps.size(); i++){
						comps[i]->collision(comps);
					}
				}

				//Display
				drawScreen();

				//Regulate framerate
				frame++;
				if(regulateFPS && timer.getTicks()<1000/FPS )
					SDL_Delay((1000/FPS)-timer.getTicks());
				
			}
		}
	}

	void Screen::setBackground(int r, int g, int b){
		// Correct the values so they fall within the 0-255 range.
		if(r>255)
			r=255;
		if(g>255)
			g=255;
		if(b > 255)
			b=255;

		if(r<0)
			r=0;
		if(g<0)
			g=0;
		if(b<0)
			b=0;

		bgColor = SDL_MapRGB(screen->format, r, g, b);
		SDL_FillRect(screen, NULL, bgColor);
	}


	void Screen::setTitle(std::string title){
		SDL_WM_SetCaption(title.c_str(), NULL);
	}

	void Screen::regulateFrameRate(bool cap){
		regulateFPS=cap;
	}

	void Screen::keyRepeat(int delay, int interval){
		keyDelay = delay;
		keyInterval = interval;
	}

	SDL_Surface* Screen::getScreen(){
		return screen;
	}

	void Screen::addObject(Object *obj){
		comps.push_back(obj);
	}

	void Screen::removeObject(Object *obj){
		// Removes the object from the screen.
		pos = std::find(comps.begin(), comps.end(),obj);
		if(pos != comps.end()){
			comps.erase(pos);
		}
	}

	void Screen::deleteObject(Object *obj){
		// Delete the object
		if(obj){
			removeObject(obj); // Remove if from the screen first.
			delete obj;
		}
	}
		

	void Screen::pause(){
		paused = true;
	}
	void Screen::unpause(){
		paused = false;
	}
	bool Screen::isPaused(){
		return paused;
	}

	void Screen::addKeyDownAction(SDLKey key, Action a){
		if(a == NULL)
			return;
		else
			downActions[key] = a;
	}

	void Screen::addTickAction(Action a){
		if(a == NULL)
			return;
		else
			tickActions.push_back(a);
	}

}//gameLib
