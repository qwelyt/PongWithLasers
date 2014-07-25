#ifndef IMAGE_H
#define IMAGE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>

namespace gameLib{
	class Image{
		private:
			int width;
			int height;
			std::string path;
			SDL_Surface *image=NULL;
		public:
			Image();
			Image(const Image &img); // Copy
			Image(std::string file);
			Image(std::string file, bool trans);
			const Image& operator=(const Image &other);
			~Image();
			SDL_Surface* getImage() const;
	};
}//gameLib

#endif
