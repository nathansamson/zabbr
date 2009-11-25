#ifndef INC_FONTRESOURCE_H
#define INC_FONTRESOURCE_H

#include "SDL_ttf.h"

#include "resources/resource.h"

namespace Zabbr {

	/**
	 * A font resource.
	*/
	class FontResource : public VResource {
	public:
		virtual ~FontResource();

		static FontResource* open(std::string, int);
		SDL_Surface* string(std::string, SDL_Color);

		static std::string getID(std::string, int);
	private:
		/**
		 * The TTF_Font.
		*/
		TTF_Font* fFont;
		FontResource(TTF_Font*, std::string);
	};
}

#endif // INC_FONTRESOURCE_H
