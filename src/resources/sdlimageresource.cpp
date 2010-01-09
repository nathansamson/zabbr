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
 * File for the image resource.
 *
 * @author Nathan Samson
*/

#include <algorithm>
#include <sstream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_rotozoom.h" 

#include "resources/resourcemanager.h"
#include "resources/sdlimageresource.h"
#include "sdlwindow.h"

namespace Zabbr {

	/**
	 * Constructor.
	 *
	 * @param name The name of the image.
	 * @param surface The surface of the image.
	*/
	SDLImageResource::SDLImageResource(std::string name, SDLWindow* window, SDL_Surface* surface)
	              : IImageResource(name), fWindow(window), fSurface(surface) {
	}
	
	/**
	 * Destructor.
	*/
	SDLImageResource::~SDLImageResource() {
		SDL_FreeSurface(fSurface);
	}

	int SDLImageResource::getWidth() {
		return fSurface->w;
	}
	
	int SDLImageResource::getHeight() {
		return fSurface->h;
	}
	
	void SDLImageResource::draw(int x, int y) {
		fWindow->drawSurface(fSurface, x, y);
	}

	/**
	 * Opens an image.
	 *
	 * @param name the filename of the image.
	 *
	 * @throw ResourceNotLoadedException.
	*/
	SDLImageResource* SDLImageResource::open(SDLWindow* window, std::string name) {
		SDL_Surface* temp;
		SDL_Surface* image;
		
		temp = IMG_Load((ResourceManager::fgDataPath+name).c_str());
		if (temp == 0) {
			throw ResourceNotLoadedException(name, IMG_GetError());
		}
		
		image = SDL_DisplayFormatAlpha(temp);
		SDL_FreeSurface(temp);
		return new SDLImageResource(IImageResource::createID(name), window, image);
	}
	
	/**
	 * Scale and rotate the image.
	 *
	 * @param w The maximum width of the new image.
	 * @param h The maximul height of the new image.
	 * @param keepRatio True if the result shoul be the same ratio as the original.
	 * @param angle The angle of the rotation (in degrees).
	*/
	SDLImageResource* SDLImageResource::scaleAndRotate(int w, int h, bool keepRatio, int angle) {
		SDL_Surface* surf;
		if (keepRatio) {
			surf = rotozoomSurface(fSurface, angle, std::min(w*1.0/fSurface->w, h*1.0/fSurface->h), SMOOTHING_ON);
		} else {
			SDL_Surface* t;
			t = zoomSurface(fSurface, w*1.0/fSurface->w, h*1.0/fSurface->h, SMOOTHING_ON);
			surf = rotozoomSurface(t, angle, 1, SMOOTHING_ON);
			SDL_FreeSurface(t);
			
		}
		return new SDLImageResource(IImageResource::createID(getName(), w, h, keepRatio, angle), fWindow, surf);
	}
}
