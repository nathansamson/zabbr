#ifndef INC_IMAGERESOURCE_H
#define INC_IMAGERESOURCE_H

#include "SDL.h"

#include "resources/sdlsurfaceresource.h"

namespace Zabbr {

	/**
	 * An image resource.
	*/
	class ImageResource : public SDLSurfaceResource {
	public:
		static ImageResource* open(std::string);
		
		int getWidth();
		int getHeight();
		
		SDL_Surface* getSurface();
	private:
		ImageResource(std::string, SDL_Surface*);
		virtual ~ImageResource();
	};
}

#endif // INC_IMAGERESOURCE_H
