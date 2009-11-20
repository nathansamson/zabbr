#include "SDL.h"

#include "resources/imageresource.h"

namespace Zabbr {

	ImageResource::ImageResource(std::string name, SDL_Surface* surface)
	              : VResource(name), fImageSurface(surface) {
	}
	
	ImageResource::~ImageResource() {
		SDL_FreeSurface(fImageSurface);
	}

	ImageResource* ImageResource::open(std::string name) {
		SDL_Surface* temp;
		SDL_Surface* image;
		
		temp = SDL_LoadBMP(("../data/"+name).c_str());
		if (temp == NULL) {
			throw ResourceNotLoadedException(name, SDL_GetError());
		}
		
		image = SDL_DisplayFormat(temp);
		SDL_FreeSurface(temp);
		return new ImageResource(name, image);
	}
	
	int ImageResource::getWidth() {
		return fImageSurface->w;
	}
	
	int ImageResource::getHeight() {
		return fImageSurface->h;
	}
	
	SDL_Surface* ImageResource::getSurface() {
		return fImageSurface;
	}

}
