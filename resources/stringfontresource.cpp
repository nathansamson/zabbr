#include <sstream>

#include "resources/stringfontresource.h"
#include "resources/fontresource.h"

namespace Zabbr {

	/**
	 * Constructor.
	 *
	 * @param surface The surface.
	 * @param id The ID of the string fonts.
	*/
	StringFontResource::StringFontResource(SDL_Surface* surface, std::string id)
	                   : VResource(id), fSurface(surface) {
	}

	/**
	 * Destructor.
	*/
	StringFontResource::~StringFontResource() {
		SDL_FreeSurface(fSurface);
	}
	
	/**
	 * Returns the width of the string.
	*/
	int StringFontResource::getWidth() {
		return fSurface->w;
	}
	
	/**
	 * Returns the height of the string.
	*/
	int StringFontResource::getHeight() {
		return fSurface->h;
	}
	
	/**
	 * Returns the surface.
	*/
	SDL_Surface* StringFontResource::getSurface() {
		return fSurface;
	}

	/**
	 * ID Generator.
	 *
	 * @param text The text to print
	 * @param font The font the string should be drawn in.
	 * @param c The color of the string.
	*/
	std::string StringFontResource::getID(std::string text, FontResource* font, SDL_Color c) {
		std::stringstream sID;
		sID << text << font->getName() << c.r << "_" << c.g << "_" << c.b;
		std::string id;
		sID >> id;
		return id;
	}

}
