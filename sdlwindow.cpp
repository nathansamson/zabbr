/** \file
 * File for the sdl window.
 *
 * @author Nathan Samson
*/

#include <iostream>
#include <sstream>
#include <algorithm>

#include "SDL.h"
#include "SDL_gfxPrimitives.h"
#include "SDL_ttf.h"

#include "sdlwindow.h"
#include "misc/fpscounter.h"
#include "misc/audiomanager.h"
#include "panels/sdlpanel.h"
#include "resources/resourcemanager.h"

namespace Zabbr {

	SDLImageFactory::SDLImageFactory(SDLWindow* window): fWindow(window) {
	}
	
	SDLImageResource* SDLImageFactory::operator()(std::string name) {
		return SDLImageResource::open(fWindow, name);
	}
	
	/**
	 * Public constructor.
	*/
	SDLWindow::SDLWindow(std::string title): Window(title) {
		ResourceManager::manager().setImageFactory(new SDLImageFactory(this));
	}

	void SDLWindow::openWindow(int x, int y, bool fs) {
		if (!fs) {
			fScreen = SDL_SetVideoMode(x, y, 32, SDL_RESIZABLE);
		} else {
			fScreen = SDL_SetVideoMode(x, y, 32, SDL_FULLSCREEN | SDL_DOUBLEBUF | SDL_HWSURFACE);
		}
		if (fScreen == 0) {
			throw SDLInitializationException(SDL_GetError());
		}
	}

	void SDLWindow::clearScreen() {
		SDL_FillRect(fScreen, 0, SDL_MapRGB(fScreen->format, 0, 0, 0));
	}
	
	/**
	 * Updates the physical screen so it contains the same information as the screen buffer.
	*/
	void SDLWindow::swapBuffers() {
		SDL_Flip(fScreen);
	}
	
	
	/**
	 * Draws a raw SDL Surface on the window.
	 *
	 * @param surface The SDL Surface.
	 * @param x The x coordinate on the screen.
	 * @param y The y coordinate on the screen.
	*/
	void SDLWindow::drawSurface(SDL_Surface* surface, int x, int y) {
		SDL_Rect dest;
		dest.x = x + fRatioOffset.x;
		dest.y = y + fRatioOffset.y;
	
		SDL_BlitSurface(surface, 0, fScreen, &dest);
	}
	
	/**
	 * Draws a part of the surface.
	 *
	 * @param surface The surface to draw.
	 * @param x The x coordinate on the screen.
	 * @param y The y coordinate on the screen.
	 * @param src the rectangle of the part of the surface that should be drawn.
	*/
	void SDLWindow::drawPartOfSurface(SDL_Surface* surface, int x, int y, SDL_Rect src) {
		SDL_Rect dest;
	
		dest.x = x + fRatioOffset.x;
		dest.y = y + fRatioOffset.y;
		dest.w = src.w;
		dest.h = src.h;
	
		SDL_BlitSurface(surface, &src, fScreen, &dest);
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
	void SDLWindow::drawRectangle(int x, int y, int w, int h, int r, int g, int b) {
		SDL_Rect dest;
		dest.x = x + fRatioOffset.x;
		dest.y = y + fRatioOffset.y;
		dest.w = w;
		dest.h = h;
		
		SDL_FillRect(fScreen, &dest, SDL_MapRGB(fScreen->format, r, g, b));
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
	void SDLWindow::drawRectangle(int x, int y, int w, int h, int r, int g, int b, double a) {
		boxRGBA(fScreen, x + fRatioOffset.x,
		        y + fRatioOffset.y,
		        x + fRatioOffset.x + w, 
		        y + fRatioOffset.y + h, r, g, b, a*255);
	}
}
