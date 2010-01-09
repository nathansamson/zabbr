/* Copyright (c) 2009, Nathan Samson <nathansamson[at]gmail[dot]com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, 
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of the zabbr-community nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
*/

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
		if (font != 0) {
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
		fFont = 0;
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
