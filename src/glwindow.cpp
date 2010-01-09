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
 * File for the sdl window.
 *
 * @author Nathan Samson
*/

#include <iostream>
#include <sstream>
#include <algorithm>

#include <GL/gl.h>
#include "SDL.h"

#include "glwindow.h"
#include "resources/resourcemanager.h"

namespace Zabbr {
	
	GLImageResource* GLImageFactory::operator()(std::string name) {
		return GLImageResource::open(name);
	}
	
	/**
	 * Public constructor.
	*/
	GLWindow::GLWindow(std::string title): Window(title) {
		ResourceManager::manager().setImageFactory(new GLImageFactory());
	}

	void GLWindow::openWindow(int x, int y, bool fs) {
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_Surface* screen = 0;
		if (! fs) {
			screen = SDL_SetVideoMode(x, y, 32, SDL_RESIZABLE | SDL_OPENGL);
		} else {
			screen = SDL_SetVideoMode(x, y, 32, SDL_FULLSCREEN | SDL_OPENGL);
		}
		if (screen == 0) {
			throw SDLInitializationException(SDL_GetError());
		}
		glClearColor(0.0, 0.0, 0.0, 0);
		glEnable(GL_TEXTURE_2D);

		/*
		 * Change to the projection matrix and set
		 * our viewing volume.
		 */
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0f, x, y, 0.0f, -1.0f, 1.0f);
	}

	void GLWindow::clearScreen() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	/**
	 * Updates the physical screen so it contains the same information as the screen buffer.
	*/
	void GLWindow::swapBuffers() {
		SDL_GL_SwapBuffers();
	}
	
	/**
	 * Draws a rectangle on the screen.
	 *
	 * @param x The x coordinate of the rectangle on the screen.
	 * @param y The y coordinate of the rectangle on the screen.
	 * @param w The width of the rectangle.
	 * @param h The height of the rectangle.
	 * @param r The red component of the color of the rectangle.
	 * @param g The green component of the color of the rectangle.
	 * @param b The blue component of the color of the rectangle.
	*/
	void GLWindow::drawRectangle(int x, int y, int w, int h, int r, int g, int b) {
		glColor3ub(r, g, b);
		glRectf(x+fRatioOffset.x,y+fRatioOffset.y, x+fRatioOffset.x+w,y+fRatioOffset.y+h);
		glColor3f(1.0, 1.0, 1.0);
	}
	
	/**
	 * Draws a transparant rectangle on the screen.
	 *
	 * @param x The x coordinate of the rectangle on the screen.
	 * @param y The y coordinate of the rectangle on the screen.
	 * @param w The width of the rectangle.
	 * @param h The height of the rectangle.
	 * @param r The red component of the color of the rectangle.
	 * @param g The green component of the color of the rectangle.
	 * @param b The blue component of the color of the rectangle.
	 * @param a The alpha-channel of the rectangle, 0.0 for completely transparant, 1.0 for opaque.
	*/
	void GLWindow::drawRectangle(int x, int y, int w, int h, int r, int g, int b, double a) {
	}
}
