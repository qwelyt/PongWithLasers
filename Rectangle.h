#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Image.h"
#include "Object.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <vector>

namespace gameLib{
	class Rectangle : public Object {
		private:
			bool collis(Object* other);

			Rectangle(int x, int y, int w, int h);
			Rectangle(int x, int y, std::string img);
			Rectangle(int x, int y, std::string img, bool trans);
		public:
			static Rectangle* create(int x, int y, int w, int h);
			static Rectangle* create(int x, int y, std::string img);
			static Rectangle* create(int x, int y, std::string img, bool trans);
			
			bool collision(std::vector<Object*> objects);
	};
}
#endif
