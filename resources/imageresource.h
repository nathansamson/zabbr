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
		
		ImageResource* scaleAndRotate(int, int, bool, int);
		SDL_Surface* getSurface();
		
		static std::string createID(std::string);
		static std::string createID(std::string, int, int, bool, int);
	private:
		ImageResource(std::string, SDL_Surface*);
		virtual ~ImageResource();
	};
}

#endif // INC_IMAGERESOURCE_H
