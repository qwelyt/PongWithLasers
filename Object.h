#ifndef OBJECT_H
#define OBJECT_H

#include "Image.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <vector>
#include <map>

namespace gameLib{
	class Object{
		typedef void (*Action)(void);
		private:
			int width;
			int height;
			int x;
			int y;
			int xVel;
			int yVel;
			bool collided;
			bool Collidable;
			Image image;
			SDL_Surface *object = NULL;
			std::map<SDLKey, Action> downActions;
			std::map<SDLKey, Action> upActions;
			std::map<SDLKey, Action>::iterator it;
			std::vector<Action> tickMoves;
		protected:
			Object(int x, int y, int w, int h);
			Object(int x, int y, std::string img);
			Object(int x, int y, std::string img, bool trans);
		public:

			virtual ~Object();
			
			int getW() const;
			int getH() const;
			int getX() const;
			int getY() const;
			int getXVel() const;
			int getYVel() const;
			bool hasCollided() const;
			bool canCollide() const;
			SDL_Surface* getObject() const;

			void setX(int newX);
			void setY(int newY);
			void setXVel(int newXvel);
			void setYVel(int newYvel);
			void setCollided(bool col);
			void setImage(std::string img);
			void setImage(std::string img, bool trans);
			void setObject(SDL_Surface *box);
			void collidable(bool collid);

			void fillColour(int r, int g, int b);
			virtual void draw(SDL_Surface* dest);
			virtual void move();

			void addKeyDownAction(SDLKey key, Action a);
			void addKeyUpAction(SDLKey key, Action a);
			void addTickMove(Action a);

			virtual void keyDown(SDLKey key);
			virtual void keyUp(SDLKey key);
			virtual void mouseDown(int mX, int mY);
			virtual void mouseUp(int mX, int mY);
			virtual void mouseMotion(int mX, int mY);
			virtual bool collision(std::vector<Object*>)=0;
	};
}
#endif
