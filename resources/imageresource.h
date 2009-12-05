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
		
		ImageResource* scale(int, int, bool);
		SDL_Surface* getSurface();
		
		static std::string createID(std::string);
		static std::string createID(std::string, int, int, bool);
	private:
		ImageResource(std::string, SDL_Surface*);
		virtual ~ImageResource();
	};
}

#endif // INC_IMAGERESOURCE_H
