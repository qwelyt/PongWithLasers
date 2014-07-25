#include "Object.h"
#include "Screen.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <stdexcept>
#include <iostream>

namespace gameLib{
	Object::Object(int X, int Y, int w, int h): width(w), height(h), x(X), y(Y), image(){
		object = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
		yVel=0;
		xVel=0;
		collided=false;
		Collidable=true;
	}

	Object::Object(int X, int Y, std::string img): x(X), y(Y), xVel(0), yVel(0), image(img, false){
		collided=false;
		Collidable=true;
		width=image.getImage()->w;
		height=image.getImage()->h;
	}

	Object::Object(int X, int Y, std::string img, bool trans): x(X), y(Y), xVel(0), yVel(0), image(img, trans){
		collided=false;
		Collidable=true;
		width=image.getImage()->w;
		height=image.getImage()->h;
	}

	Object::~Object(){
		SDL_FreeSurface(object);
	}

	/*
	 * Getters
	 */
	int Object::getW() const{
		return width;
	}

	int Object::getH() const{
		return height;
	}

	int Object::getX() const{
		return x;
	}

	int Object::getY() const{
		return y;
	}

	int Object::getXVel() const{
		return xVel;
	}

	int Object::getYVel() const{
		return yVel;
	}

	SDL_Surface* Object::getObject() const{
		if(image.getImage())
			return image.getImage();
		else
			return object;
	}

	bool Object::hasCollided() const{
		return collided;
	}

	bool Object::canCollide() const{
		return Collidable;
	}


	/*
	 * Setters
	 */
	void Object::setX(int newX){
		x = newX;
	}

	void Object::setY(int newY){
		y = newY;
	}
	
	void Object::setXVel(int newXvel){
		xVel = newXvel;
	}

	void Object::setYVel(int newYvel){
		yVel = newYvel;
	}

	void Object::setCollided(bool col){
		collided = col;
	}

	void Object::setImage(std::string img){
		setImage(img, false);
	}

	void Object::setImage(std::string img, bool trans){
		image = Image(img, trans);
		width = image.getImage()->w;
		height = image.getImage()->h;
	}

	void Object::setObject(SDL_Surface *box){
		if(box != NULL){
			if(object){
				delete object;
				object = NULL;
			}
			object = box;
			width = box->w;
			height = box->h;
		}
	}

	void Object::collidable(bool colli){
		Collidable = colli;
	}

	void Object::fillColour(int r, int g, int b){
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

		Uint32 color = SDL_MapRGB(getObject()->format, r, g, b);
		SDL_FillRect(getObject(), NULL, color);
	}

	void Object::addKeyDownAction(SDLKey key, Action a){
		if(a == NULL)
			return;
		else
			downActions[key] = a;
	}

	void Object::addKeyUpAction(SDLKey key, Action a){
		if(a == NULL)
			return;
		else
			upActions[key] = a;
	}

	void Object::addTickMove(Action a){
		if(a == NULL)
			return;
		else
			tickMoves.push_back(a);
	}

	/*
	 * Other
	 */
	void Object::draw(SDL_Surface *dest){
		SDL_Rect offset;
		offset.x = getX();
		offset.y = getY();

		SDL_BlitSurface(getObject(), NULL, dest, &offset);
	}

	void Object::move(){
		// Move object without input
		for(int i=0; i<tickMoves.size(); i++)
			tickMoves[i]();

		// If the user has changed the velocity of the object.
		setX(getX()+xVel);
		setY(getY()+yVel);
	}


	void Object::keyDown(SDLKey key){
		it=downActions.find(key);
		if(it != downActions.end()){
			downActions[key]();
		}
	}
	void Object::keyUp(SDLKey key){
		it=upActions.find(key);
		if(it != upActions.end()){
			upActions[key]();
		}
	}
	void Object::mouseDown(int mX, int mY){}
	void Object::mouseUp(int mX, int mY){}
	void Object::mouseMotion(int mX, int mY){}
	
}//gameLib
