#include "SDL.h"
#include "SDL_image.h" 

#include "resources/resourcemanager.h"
#include "resources/imageresource.h"

namespace Zabbr {

	/**
	 * Constructor.
	 *
	 * @param name The name of the image.
	 * @param surface The surface of the image.
	*/
	ImageResource::ImageResource(std::string name, SDL_Surface* surface)
	              : SDLSurfaceResource(name, surface) {
	}
	
	/**
	 * Destructor.
	*/
	ImageResource::~ImageResource() {
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
		
		temp = IMG_Load((ResourceManager::fgDataPath+name).c_str());
		if (temp == NULL) {
			throw ResourceNotLoadedException(name, IMG_GetError());
		}
		
		image = SDL_DisplayFormatAlpha(temp);
		SDL_FreeSurface(temp);
		return new ImageResource(name, image);
	}
}
