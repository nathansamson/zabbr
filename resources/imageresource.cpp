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
		if (temp == 0) {
			throw ResourceNotLoadedException(name, IMG_GetError());
		}
		
		image = SDL_DisplayFormatAlpha(temp);
		SDL_FreeSurface(temp);
		return new ImageResource(createID(name), image);
	}
	
	/**
	 * Scale and rotate the image.
	 *
	 * @param w The maximum width of the new image.
	 * @param h The maximul height of the new image.
	 * @param keepRatio True if the result shoul be the same ratio as the original.
	 * @param angle The angle of the rotation (in degrees).
	*/
	ImageResource* ImageResource::scaleAndRotate(int w, int h, bool keepRatio, int angle) {
		SDL_Surface* surf;
		if (keepRatio) {
			surf = rotozoomSurface(fSurface, angle, std::min(w*1.0/fSurface->w, h*1.0/fSurface->h), SMOOTHING_ON);
		} else {
			SDL_Surface* t;
			t = zoomSurface(fSurface, w*1.0/fSurface->w, h*1.0/fSurface->h, SMOOTHING_ON);
			surf = rotozoomSurface(t, angle, 1, SMOOTHING_ON);
			SDL_FreeSurface(t);
			
		}
		return new ImageResource(createID(getName(), w, h, keepRatio, angle), surf);
	}
	
	/**
	 * Generates an ID for an Image resource.
	 *
	 * @param name The file name of the image.
	*/
	std::string ImageResource::createID(std::string name) {
		return name;
	}
	
	/**
	 * Generates an ID for an Image resource.
	 *
	 * @param name The ID of the original image
	 * @param w The width of the image.
	 * @param h The height of the image
	 * @param keepRatio value to keep the ratio.
	 * @param angle The angle of the rotation
	*/
	std::string ImageResource::createID(std::string name, int w, int h, bool keepRatio, int angle) {
		std::stringstream ssID;
		ssID  << "_" << w << "_"<< h;
		if (keepRatio) {
			ssID << "_KR";
		}
		ssID << "_" << angle;
		std::string id;
		ssID >> id;
		return name + id;
	}
}
