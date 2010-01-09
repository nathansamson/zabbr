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

#include <iostream>
#include <algorithm>
#include <sstream>

#include "SDL_image.h"

#include "resources/resourcemanager.h"
#include "resources/glimageresource.h"

namespace Zabbr {

	/**
	 * Constructor.
	 *
	 * @param name The name of the image.
	 * @param surface The surface of the image.
	*/
	GLImageResource::GLImageResource(std::string name, GLuint texture, int w, int h, int rotation)
	              : IImageResource(name), fTexture(texture), fWidth(w), fHeight(h), fRotation(rotation) {
	}
	
	/**
	 * Destructor.
	*/
	GLImageResource::~GLImageResource() {
	}

	int GLImageResource::getWidth() {
		return fWidth;
	}
	
	int GLImageResource::getHeight() {
		return fHeight;
	}
	
	void GLImageResource::draw(int x, int y) {
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		// Bind the texture object
		glBindTexture(GL_TEXTURE_2D, fTexture);
		
		glBegin(GL_QUADS);
		if (fRotation == 0) {
			//Top-left vertex (corner)
			glTexCoord2i(0, 0);
			glVertex3f(x, y, 0.0f);

			//Bottom-left vertex (corner)
			glTexCoord2i(1, 0);
			glVertex3f(x+fWidth, y, 0);

			//Bottom-right vertex (corner)
			glTexCoord2i(1, 1);
			glVertex3f(x+fWidth, y + fHeight, 0);

			//Top-right vertex (corner)
			glTexCoord2i(0, 1);
			glVertex3f(x, y + fHeight, 0);
		} else {
			//Top-left vertex (corner)
			glTexCoord2i(0, 0);
			glVertex3f(x + fWidth, y + fHeight, 0.0f);

			//Bottom-left vertex (corner)
			glTexCoord2i(1, 0);
			glVertex3f(x, y + fHeight, 0);

			//Bottom-right vertex (corner)
			glTexCoord2i(1, 1);
			glVertex3f(x, y, 0);

			//Top-right vertex (corner)
			glTexCoord2i(0, 1);
			glVertex3f(x + fWidth, y, 0);
		}
		glEnd();
		glDisable(GL_BLEND);
	}

	/**
	 * Opens an image.
	 *
	 * @param name the filename of the image.
	 *
	 * @throw ResourceNotLoadedException.
	*/
	GLImageResource* GLImageResource::open(std::string name) {
		SDL_Surface* temp;
		SDL_Surface* surface;
		
		temp = IMG_Load((ResourceManager::fgDataPath+name).c_str());
		if (temp == 0) {
			throw ResourceNotLoadedException(name, IMG_GetError());
		}
		
		surface = SDL_DisplayFormatAlpha(temp);
		SDL_FreeSurface(temp);
		
		GLuint texture;
		GLenum texture_format;
		GLint  nOfColors;

		nOfColors = surface->format->BytesPerPixel;
		if (nOfColors == 4) {
			if (surface->format->Rmask == 0x000000ff) {
				texture_format = GL_RGBA;
			} else {
				texture_format = GL_BGRA;
			}
		} else if (nOfColors == 3) {
			if (surface->format->Rmask == 0x000000ff) {
				texture_format = GL_RGB;
			} else {
				texture_format = GL_BGR;
			}
		} else {
			throw ResourceNotLoadedException(name, "Wrong color format");
		}
		
		// Have OpenGL generate a texture object handle for us
		glGenTextures(1, &texture);

		glBindTexture(GL_TEXTURE_2D, texture); 
		// Set the texture's stretching properties
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Edit the texture object's image data using the information SDL_Surface gives us
		glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
		              texture_format, GL_UNSIGNED_BYTE, surface->pixels);
		GLImageResource* res = new GLImageResource(IImageResource::createID(name), texture, surface->w, surface->h, 0);
		SDL_FreeSurface(surface);
		return res;
	}
	
	/**
	 * Scale and rotate the image.
	 *
	 * @param w The maximum width of the new image.
	 * @param h The maximul height of the new image.
	 * @param keepRatio True if the result shoul be the same ratio as the original.
	 * @param angle The angle of the rotation (in degrees).
	*/
	GLImageResource* GLImageResource::scaleAndRotate(int w, int h, bool keepRatio, int angle) {
		return new GLImageResource(IImageResource::createID(getName(), w, h, keepRatio, angle), fTexture, w, h, angle);
	}
}
