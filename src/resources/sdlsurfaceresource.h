#ifndef INC_SDLSURFACERESOURCE_H
#define INC_SDLSURFACERESOURCE_H

/** \file
 * File for the sdl surfaces.
 *
 * @author Nathan Samson
*/

#include "SDL.h"

#include "resources/resource.h"

namespace Zabbr {

	/**
	 * An image resource.
	*/
	class SDLSurfaceResource : public VResource {
	public:
		virtual ~SDLSurfaceResource();
	
		int getWidth();
		int getHeight();
		
		SDL_Surface* getSurface();
	protected:
		SDLSurfaceResource(std::string, SDL_Surface*);
		/**
		 * The SDL Surface.
		*/
		SDL_Surface* fSurface;
	};
}

#endif // INC_SDLSURFACERESOURCE_H
