#include "SDL.h"

#include "resources/imageresource.h"

namespace Zabbr {

	/**
	 * Constructor.
	 *
	 * @param name The name of the image.
	 * @param surface The surface of the image.
	*/
	ImageResource::ImageResource(std::string name, SDL_Surface* surface)
	              : VResource(name), fImageSurface(surface) {
	}
	
	/**
	 * Destructor.
	*/
	ImageResource::~ImageResource() {
		SDL_FreeSurface(fImageSurface);
	}

	/**
	 * Opens an image.
	 *
	 * @param name the filename of the image.
	 *
	 * @throw ResourceNotLoadedException.
	*/
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
	
	/**
	 * Returns the width of the image.
	 *
	 * @return The width of the image.
	*/
	int ImageResource::getWidth() {
		return fImageSurface->w;
	}
	
	/**
	 * Returns the height of the image.
	 *
	 * @return The height of the image.
	*/
	int ImageResource::getHeight() {
		return fImageSurface->h;
	}
	
	/**
	 * Returns the surface of the image.
	 *
	 * @return The surface.
	*/
	SDL_Surface* ImageResource::getSurface() {
		return fImageSurface;
	}

}
