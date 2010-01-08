/** \file
 * File for the image resource.
 *
 * @author Nathan Samson
*/

#include <algorithm>
#include <sstream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_rotozoom.h" 

#include "resources/resourcemanager.h"
#include "resources/sdlimageresource.h"
#include "sdlwindow.h"

namespace Zabbr {

	/**
	 * Constructor.
	 *
	 * @param name The name of the image.
	 * @param surface The surface of the image.
	*/
	SDLImageResource::SDLImageResource(std::string name, SDLWindow* window, SDL_Surface* surface)
	              : IImageResource(name), fWindow(window), fSurface(surface) {
	}
	
	/**
	 * Destructor.
	*/
	SDLImageResource::~SDLImageResource() {
		SDL_FreeSurface(fSurface);
	}

	int SDLImageResource::getWidth() {
		return fSurface->w;
	}
	
	int SDLImageResource::getHeight() {
		return fSurface->h;
	}
	
	void SDLImageResource::draw(int x, int y) {
		fWindow->drawSurface(fSurface, x, y);
	}

	/**
	 * Opens an image.
	 *
	 * @param name the filename of the image.
	 *
	 * @throw ResourceNotLoadedException.
	*/
	SDLImageResource* SDLImageResource::open(SDLWindow* window, std::string name) {
		SDL_Surface* temp;
		SDL_Surface* image;
		
		temp = IMG_Load((ResourceManager::fgDataPath+name).c_str());
		if (temp == 0) {
			throw ResourceNotLoadedException(name, IMG_GetError());
		}
		
		image = SDL_DisplayFormatAlpha(temp);
		SDL_FreeSurface(temp);
		return new SDLImageResource(IImageResource::createID(name), window, image);
	}
	
	/**
	 * Scale and rotate the image.
	 *
	 * @param w The maximum width of the new image.
	 * @param h The maximul height of the new image.
	 * @param keepRatio True if the result shoul be the same ratio as the original.
	 * @param angle The angle of the rotation (in degrees).
	*/
	SDLImageResource* SDLImageResource::scaleAndRotate(int w, int h, bool keepRatio, int angle) {
		SDL_Surface* surf;
		if (keepRatio) {
			surf = rotozoomSurface(fSurface, angle, std::min(w*1.0/fSurface->w, h*1.0/fSurface->h), SMOOTHING_ON);
		} else {
			SDL_Surface* t;
			t = zoomSurface(fSurface, w*1.0/fSurface->w, h*1.0/fSurface->h, SMOOTHING_ON);
			surf = rotozoomSurface(t, angle, 1, SMOOTHING_ON);
			SDL_FreeSurface(t);
			
		}
		return new SDLImageResource(IImageResource::createID(getName(), w, h, keepRatio, angle), fWindow, surf);
	}
}
