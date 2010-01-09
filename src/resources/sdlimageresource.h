#ifndef INC_SDLIMAGERESOURCE_H
#define INC_SDLIMAGERESOURCE_H

/** \file
 * File for SDL images.
 *
 * @author Nathan Samson
*/

#include "SDL.h"

#include "resources/imageresource.h"

namespace Zabbr {
	class SDLWindow;

	/**
	 * An image resource.
	*/
	class SDLImageResource : public IImageResource {
	public:
		virtual ~SDLImageResource();
		
		static SDLImageResource* open(SDLWindow*, std::string);
		
		virtual int getWidth();
		virtual int getHeight();
		virtual void draw(int, int);
		virtual SDLImageResource* scaleAndRotate(int, int, bool, int);
	private:
		SDLWindow* fWindow;
		SDL_Surface* fSurface;
	
		SDLImageResource(std::string, SDLWindow*, SDL_Surface*);
	};
}

#endif // INC_SDLIMAGERESOURCE_H
