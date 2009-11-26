#include "resources/sdlsurfaceresource.h"

namespace Zabbr {
	/**
	 * Constructor.
	 *
	 * @param id The ID of the resource.
	 * @param surf The surface.
	*/
	SDLSurfaceResource::SDLSurfaceResource(std::string id, SDL_Surface* surf): 
	                    VResource(id), fSurface(surf) {
	}
	
	/**
	 * Destructor.
	*/
	SDLSurfaceResource::~SDLSurfaceResource() {
		SDL_FreeSurface(fSurface);
	}

	/**
	 * Returns the width of the surface.
	 *
	 * @return The width of the surface.
	*/
	int SDLSurfaceResource::getWidth() {
		return fSurface->w;
	}
	
	/**
	 * Returns the height of the surface.
	 *
	 * @return The height of the surface.
	*/
	int SDLSurfaceResource::getHeight() {
		return fSurface->h;
	}
	
	/**
	 * Returns the surface.
	 *
	 * @return The surface.
	*/
	SDL_Surface* SDLSurfaceResource::getSurface() {
		return fSurface;
	}
}
