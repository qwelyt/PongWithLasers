#include "Label.h"
#include <stdexcept>

namespace gameLib{
	Label::Label(int x, int y, int w, int h, std::string t, std::string f, int s, int r, int g, int b):Object(x,y,w,h), size(s), txt(t){
		font = TTF_OpenFont(f.c_str(), s);
		if(font == NULL)
			throw std::runtime_error("The specified font could not be loaded: "+f);

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

		SDL_Color tmp = {r,g,b};
		fg = tmp;

		box = TTF_RenderText_Solid(font, txt.c_str(), fg);
		setObject(box);
		collidable(false);
	}

	Label* Label::create(int x, int y, int w, int h, std::string t, std::string f, int s, int r, int g, int b){
		return new Label(x,y,w,h,t,f,s,r,g,b);
	}

	Label::~Label(){
		TTF_CloseFont(font);
	}
	bool Label::collision(std::vector<Object*> objects){
		return false;
	}

	void Label::setText(std::string nTxt){
		//SDL_Surface *old = getObject();
		txt = nTxt;
		box = TTF_RenderText_Solid(font, txt.c_str(), fg);
		setObject(box);
		//delete old;
	}

}//gameLib
