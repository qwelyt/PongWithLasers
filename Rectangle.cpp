#include "Rectangle.h"
#include "Object.h"
#include "Screen.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <stdexcept>
#include <iostream>

namespace gameLib{
	Rectangle* Rectangle::create(int X, int Y, int w, int h){
		return new Rectangle(X,Y,w,h);
	}
	
	Rectangle* Rectangle::create(int X, int Y, std::string img){
		return new Rectangle(X, Y, img);
	}
	
	Rectangle* Rectangle::create(int X, int Y, std::string img, bool trans){
		return new Rectangle(X, Y, img, trans);
	}

	Rectangle::Rectangle(int X, int Y, int w, int h): Object(X,Y,w,h){
	}

	Rectangle::Rectangle(int X, int Y, std::string img): Object(X,Y,img){
	}

	Rectangle::Rectangle(int X, int Y, std::string img, bool trans): Object(X,Y,img,trans){
	}

	bool Rectangle::collision(std::vector<Object*> objects){
		if(canCollide()){
			for(int i=0; i<objects.size(); i++){
				if(objects[i] != this){
					if(objects[i]->canCollide()){
						if(collis(objects[i])){
							setCollided(true);
							objects[i]->setCollided(true);
							return true;
						}
					}
				}
			}
			setCollided(false);
		}
		return false;
	}

	bool Rectangle::collis(Object* other){
		int leftA, leftB;
		int rightA, rightB;
		int topA, topB;
		int bottomA, bottomB;

		leftA = getX();
		rightA = getX() + getW();
		topA = getY();
		bottomA = getY() + getH();

		leftB = other->getX();
		rightB = other->getX() + other->getW();
		topB = other->getY();
		bottomB = other->getY() + other->getH();

		if(bottomA <= topB)
			return false;
		if(topA >= bottomB)
			return false;
		if(rightA <= leftB)
			return false;
		if(leftA >= rightB)
			return false;

		return true;

	}

}//gameLib
