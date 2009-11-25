#ifndef INC_STRINGFONTRESOURCE_H
#define INC_STRINGFONTRESOURCE_H

#include "SDL.h"

#include "resources/resource.h"

namespace Zabbr {

	class FontResource;

	/**
	 * A resource representing a string in a specified font.
	*/
	class StringFontResource : public VResource {
	public:

		StringFontResource(SDL_Surface*, std::string);
		virtual ~StringFontResource();

		int getWidth();
		int getHeight();
		
		SDL_Surface* getSurface();

		static std::string getID(std::string text, FontResource* font, SDL_Color c);
	private:
		/**
		 * The SDL_Surface of the resource.
		*/
		SDL_Surface* fSurface;
	};
}

#endif // INC_STRINGFONTRESOURCE_H
