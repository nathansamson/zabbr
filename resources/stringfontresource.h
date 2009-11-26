#ifndef INC_STRINGFONTRESOURCE_H
#define INC_STRINGFONTRESOURCE_H

#include "SDL.h"

#include "resources/sdlsurfaceresource.h"

namespace Zabbr {

	class FontResource;

	/**
	 * A resource representing a string in a specified font.
	*/
	class StringFontResource : public SDLSurfaceResource {
	public:
		StringFontResource(SDL_Surface*, std::string);
		virtual ~StringFontResource();

		static std::string getID(std::string text, FontResource* font, SDL_Color c);
	};
}

#endif // INC_STRINGFONTRESOURCE_H
