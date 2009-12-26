/** \file
 * File for the font.
 *
 * @author Nathan Samson
*/

#include <sstream>
#include "SDL_ttf.h"

#include "resources/resourcemanager.h"
#include "resources/fontresource.h"

namespace Zabbr {
	/**
	 * Open a font resource.
	 *
	 * @param fontName The name of the font.
	 * @param size The size of the font.
	 *
	 * @return The loaded font.
	 * @throw ResourceNotLoadedException
	*/
	FontResource* FontResource::open(std::string fontName, int size) {
		TTF_Font* font = TTF_OpenFont((ResourceManager::fgDataPath+fontName).c_str(), size);
		if (font != NULL) {
			return new FontResource(font, getID(fontName, size));
		}
		throw ResourceNotLoadedException(getID(fontName, size), TTF_GetError());
	}

	/**
	 * Private constructor.
	 *
	 * @param font The TTF_Font. The TTF_Font will be freed when the FontResource is desctructed.
	 * @param name The name (ID) of the font.
	*/
	FontResource::FontResource(TTF_Font* font, std::string name)
	             : VResource(name), fFont(font) {
	}

	/**
	 * Destructor.
	*/
	FontResource::~FontResource() {
		TTF_CloseFont(fFont);
		fFont = NULL;
	}

	/**
	 * Generates a surface with a string in the current font.
	 *
	 * @param text The text.
	 * @param c The color.
	 *
	 * @return The Surface with a string.
	*/
	SDL_Surface* FontResource::string(std::string text, SDL_Color c) {
		return TTF_RenderText_Blended(fFont, text.c_str(), c);
	}

	/**
	 * Creates an ID for the resource.
	 *
	 * @param fontName The name of the font
	 * @param ptSize The size of the font.
	 *
	 * @return An ID for the FontResource.
	*/
	std::string FontResource::getID(std::string fontName, int ptSize) {
		std::stringstream ssFontID;
		ssFontID << fontName << "_" << ptSize;
		std::string fontID;
		ssFontID >> fontID;
		return fontID;
	}
}
