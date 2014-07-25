#include "Screen.h"
#include "Object.h"
#include "Rectangle.h"
#include "Label.h"
#include <SDL/SDL.h>
#include <iostream>
#include <time.h>
#include <sstream>
#include <string>
#include <vector>
#include <queue>

std::string intToString(int i){
	std::stringstream ss;
	ss << i;
	return ss.str();
}

const int WIDTH = 800, HEIGHT=600, BPP =32;
int fps = 40;
gameLib::Screen* myScreen = gameLib::Screen::create(WIDTH, HEIGHT, fps);

const int BW=10, BH=10, BXM=(WIDTH/2)-(BW/2), BYM=(HEIGHT/2)-(BH/2);
int BS=2;
gameLib::Rectangle *ball = gameLib::Rectangle::create((WIDTH/2)-(BW/2),(HEIGHT/2)-(BH/2), BW, BH);

const int PHEIGHT=10, PWIDTH=10, PSPEED=2, PMARGIN=10;
gameLib::Rectangle *p1Base = gameLib::Rectangle::create(PMARGIN, (HEIGHT/2)-(PHEIGHT*2), PWIDTH, PHEIGHT*5);

gameLib::Rectangle *p2Base = gameLib::Rectangle::create(WIDTH-PMARGIN*2, (HEIGHT/2)-(PHEIGHT*2), PWIDTH, PHEIGHT*5);

int p1score=0, p2score=0;
std::string s1 = intToString(p1score);
std::string s2 = intToString(p2score);
//std::string font = "/usr/share/fonts/TTF/DroidSans.ttf"; // Depends on the font you like.
std::string font = "visitor1.ttf";

gameLib::Label *lab1 = gameLib::Label::create(WIDTH/4,40,0,0, s2 , font , 46, 200,0,0);
gameLib::Label *lab2 = gameLib::Label::create(WIDTH/1.5,40,0,0, s2 , font, 46, 200,0,0);


const int LW=7, LH=5, LS=BS*2;
gameLib::Rectangle *laser;

void quit(){
	myScreen->quit();
}


void up(gameLib::Object *obj){
	obj->setYVel(-PSPEED);
}
void down(gameLib::Object *obj){
	obj->setYVel(PSPEED);
}
void stopY(gameLib::Object *obj){
	obj->setYVel(0);
}
void checkBounderies(gameLib::Object *obj){
	if(obj->getY() < 0){
		stopY(obj);
		obj->setY(0);
	}
	if(obj->getY() > HEIGHT){
		stopY(obj);
		obj->setY(HEIGHT);
	}
}

void p1Bounds(){
	if(p1Base->getY() < 0){
		stopY(p1Base);
		p1Base->setY(p1Base->getY()+1);
		
	}
	if(p1Base->getY()+p1Base->getH() > HEIGHT){
		stopY(p1Base);
		p1Base->setY(p1Base->getY()-1);
	}

}
void p1Up(){
	up(p1Base);
}
void p1Down(){
	down(p1Base);
}
void p1YStop(){
	stopY(p1Base);
}

void p2Bounds(){
	if(p2Base->getY() < 0){
		stopY(p2Base);
		p2Base->setY(p2Base->getY()+1);
		
	}
	if(p2Base->getY()+p2Base->getH() > HEIGHT){
		stopY(p2Base);
		p2Base->setY(p2Base->getY()-1);
	}

}
void p2Up(){
	up(p2Base);
}
void p2Down(){
	down(p2Base);
}
void p2YStop(){
	stopY(p2Base);
}

void chTxt(){
	std::string s1 = intToString(p1score);
	std::string s2 = intToString(p2score);
	lab1->setText(s1);
	lab2->setText(s2);
}

void ballMove(){
	if(ball->getY() < 1)
		ball->setYVel(BS);
	if(ball->getY() > HEIGHT-(BH+1))
		ball->setYVel(-BS);


	
	if(ball->getXVel() < 0 && ball->hasCollided())
		ball->setXVel(BS);
	else if(ball->getXVel() > 0 && ball->hasCollided())
		ball->setXVel(-BS);

	if(ball->getX() < 1){
		p2score+=10;
		chTxt();
		ball->setX(BXM);
		ball->setY(BYM);
	}

	if(ball->getX() > WIDTH-(BH+1)){
		p1score+=10;
		chTxt();
		ball->setX(BXM);
		ball->setY(BYM);
	}

}

std::queue<gameLib::Rectangle*> lasers;
std::queue<gameLib::Rectangle*> p1L;
std::queue<gameLib::Rectangle*> p2L;
void remove(){
	if(!lasers.empty()){
		gameLib::Rectangle *tmp = lasers.front();
		if(tmp->getX() < 0 || tmp->getX() > WIDTH){
			lasers.pop();
			myScreen->deleteObject(tmp); 
		}
		tmp = NULL;
	}
}

void fire(gameLib::Object *obj){
	laser = NULL;
	if(obj == p1Base){
		laser = gameLib::Rectangle::create(p1Base->getX()+p1Base->getW(), p1Base->getY()+(p1Base->getH()/5*2), LW, LH);
		laser->setXVel(LS);
		p1L.push(laser);
	}
	else if(obj == p2Base){
		laser = gameLib::Rectangle::create(p2Base->getX()-p2Base->getW(), p2Base->getY()+(p2Base->getH()/5*2), LW, LH);
		laser->setXVel(-LS);
		p2L.push(laser);
	}

	lasers.push(laser);
	laser->fillColour(0,255,0);
	laser->collidable(true);
	laser->addTickMove(remove);
	myScreen->addObject(laser);
}

void p1Fire(){
	fire(p1Base);
}
void p2Fire(){
	fire(p2Base);
}
void p1Hit(){
	if(!p2L.empty()){
		if(p1Base->hasCollided() && p2L.front()->hasCollided()){
			p2score++;
			p2L.pop();
			chTxt();
		}
		else if(p2L.front()->getX() < 0){
			gameLib::Rectangle *tmp = p2L.front();
			p2L.pop();
		}
	}
}

void p2Hit(){
	if(!p1L.empty()){
		if(p2Base->hasCollided() && p1L.front()->hasCollided()){
			p1score++;
			p1L.pop();
			chTxt();
		}
		
		else if(p1L.front()->getX() > WIDTH){
			gameLib::Rectangle *tmp = p1L.front();
			p1L.pop();
		}
	}
}

void win(){
	if(p1score > 99 && p2score > 99){
		std::string draw = "Impossiburu! You both win!";
		gameLib::Label *l = gameLib::Label::create(0,HEIGHT/2,0,0, draw , font , 46, 200,0,0);
		myScreen->addObject(l);
		myScreen->pause();
	}
	else if(p1score >99){
		std::string p1win = "Player 1 has won!";
		gameLib::Label *l = gameLib::Label::create(0,HEIGHT/2,0,0, p1win , font , 46, 200,0,0);
		myScreen->addObject(l);
		myScreen->pause();
	}
	else if(p2score > 99){
		std::string p2win = "Player 2 has won!";
		gameLib::Label *l = gameLib::Label::create(0,HEIGHT/2,0,0, p2win , font , 46, 200,0,0);
		myScreen->addObject(l);
		myScreen->pause();
	}
}


int main(int argc, char* args[]){
	myScreen->setTitle("PONG, and lasers!");
	
	myScreen->addKeyDownAction(SDLK_ESCAPE, quit);
	myScreen->addTickAction(win);


	ball->fillColour(255,255,255);
	ball->setYVel(-BS);
	ball->setXVel(-BS);
	ball->addTickMove(ballMove);

	gameLib::Rectangle *mid = gameLib::Rectangle::create((WIDTH/2)-3, HEIGHT/5, 6, HEIGHT/1.5);
	mid->collidable(false);
	mid->fillColour(100,100,100);
	myScreen->addObject(mid);


	myScreen->addObject(lab1);
	myScreen->addObject(lab2);

	myScreen->addObject(ball);

	// Player 1
	p1Base->fillColour(255,255,255);
	p1Base->addKeyDownAction(SDLK_UP, p1Up);
	p1Base->addKeyDownAction(SDLK_DOWN, p1Down);
	p1Base->addKeyUpAction(SDLK_UP, p1YStop);
	p1Base->addKeyUpAction(SDLK_DOWN, p1YStop);

	p1Base->addKeyDownAction(SDLK_RIGHT, p1Fire);
	p1Base->addTickMove(p1Bounds);
	p1Base->addTickMove(p1Hit);


	// Player 2
	p2Base->fillColour(255,255,255);
	p2Base->addKeyDownAction(SDLK_k, p2Up);
	p2Base->addKeyDownAction(SDLK_j, p2Down);
	p2Base->addKeyUpAction(SDLK_k, p2YStop);
	p2Base->addKeyUpAction(SDLK_j, p2YStop);
	
	p2Base->addKeyDownAction(SDLK_q,p2Fire);
	p2Base->addTickMove(p2Bounds);
	p2Base->addTickMove(p2Hit);


	myScreen->addObject(p1Base);
	myScreen->addObject(p2Base);
	



	myScreen->run();

	return 0;
}
