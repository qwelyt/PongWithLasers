#include "Image.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <stdexcept>

namespace gameLib{
	Image::Image(){
		//empty
		image = NULL;
	}

	Image::Image(std::string file){
		Image(file, false);
	}

	Image::Image(std::string file, bool trans){
		path = file;
		SDL_Surface *tmp = NULL;
		SDL_Surface *used = NULL;

		tmp = IMG_Load(file.c_str());
		if(tmp == NULL)
			throw std::runtime_error("Image could not be found: "+file);
		else{
			used = SDL_DisplayFormat(tmp);
			SDL_FreeSurface(tmp);

			width = used->w;
			height = used->h;

			if(trans){
				Uint32 bg = *(Uint32*)used->pixels;
				SDL_SetColorKey(used, SDL_SRCCOLORKEY | SDL_RLEACCEL, bg);
			}

			image = used;
		}
	}

	// Copy
	Image::Image(const Image &img){
		image = img.image;
		image->refcount++;
	}

	SDL_Surface* Image::getImage() const{
		return image;
	}

	const Image& Image::operator=(const Image &other){
		if(image != other.image){
			if(image)
				SDL_FreeSurface(image);
			image = other.getImage();
			image->refcount++;
		}
		return *this;
	}

	Image::~Image(){
		SDL_FreeSurface(image);
	}
}//gameLib
