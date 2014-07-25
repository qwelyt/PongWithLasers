#ifndef LABEL_H
#define LABEL_H

#include "Object.h"
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

namespace gameLib{
	class Label : public Object {
		private:
			std::string txt;
			SDL_Color fg;
			TTF_Font *font;
			SDL_Surface *box;
			int size;

			Label(int x, int y, int w, int h, std::string t, std::string f, int s, int r, int g, int b);
		public:
			static Label* create(int x, int y, int w, int h, std::string t, std::string f, int s, int r, int g, int b);

			~Label();

			void setBackground(int r, int g, int b);
			bool collision(std::vector<Object*> objects);

			void setText(std::string nTxt);

	};
}

#endif
