/** \file
 * File for the sdl window.
 *
 * @author Nathan Samson
*/

#include <iostream>
#include <sstream>

#include "SDL.h"
#include "SDL_gfxPrimitives.h"
#include "SDL_ttf.h"

#include "sdlwindow.h"
#include "misc/fpscounter.h"
#include "panels/sdlpanel.h"
#include "resources/imageresource.h"
#include "resources/resourcemanager.h"

namespace Zabbr {

	/**
	 * Public constructor for the SDL initialization exception.
	 *
	 * @param s The initialization error.
	*/
	SDLInitializationException::SDLInitializationException(std::string s)
	                           : fError(s) {
	}
	
	/**
	 * Returns the error of the exception.
	 *
	 * @return The error of the exception.
	*/
	std::string SDLInitializationException::getError() {
		return fError;
	}
	
	/**
	 * Public constructor.
	*/
	SDLWindow::SDLWindow(): fOldPanel(0) {
	
	}
	
	/**
	 * Open the window.
	 *
	 * @param xres The X resolution.
	 * @param yres The Y resolution.
	 * @param fs True if running in fullscreen, false if not.
	 *
	 * @throw An SDLInitializationException if initialization fails.
	*/
	void SDLWindow::open(int xres, int yres, bool fs) {
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			throw SDLInitializationException(SDL_GetError());
		}
	
		atexit(SDL_Quit);
	
		fScreen = SDL_SetVideoMode(xres, yres, 32, SDL_RESIZABLE);
		if (fScreen == NULL) {
			throw SDLInitializationException(SDL_GetError());
		}
	
		if(TTF_Init() == -1) {
			throw SDLInitializationException(TTF_GetError());
		}
	
	}
	
	/**
	 * Close the window.
	*/
	void SDLWindow::close() {
		if (fScreen)
			SDL_FreeSurface(fScreen);
		TTF_Quit();
		ResourceManager::free();
	}
	
	/**
	 * Run the mainloop.
	 *
	 * @param panel The first panel to get control of what happens.
	*/
	void SDLWindow::run(VSDLPanel* panel) {
		FPSCounter fpsCounter(500);
		fPanel = panel;
		SDL_Event event;
		fRunning = true;
	
		while (fRunning) {
			while (fRunning && SDL_PollEvent(&event)) {
				switch (event.type) {
					case SDL_KEYDOWN:
						fPanel->keyPress(event.key);
						break;
					case SDL_KEYUP:
						fPanel->keyRelease(event.key);
						break;
					case SDL_MOUSEMOTION:
						fPanel->mouseMotion(event.motion);
						break;
					case SDL_MOUSEBUTTONUP:
						fPanel->mouseButton(event.button);
						break;
					case SDL_QUIT:
						fPanel->requestQuit();
						break;
					case SDL_VIDEORESIZE:
						fScreen = SDL_SetVideoMode(event.resize.w, event.resize.h, 32, SDL_RESIZABLE);
						break;
				}
			}
	
			if (fOldPanel) {
				delete fOldPanel;
				fOldPanel = NULL;
			}
	
			if (fRunning) { // it is possible we quit when firing events.
				SDL_FillRect(fScreen, NULL, 0);
				//drawRectangle(0, 0, fScreen->w, fScreen->h, 0, 0, 0);
				fPanel->draw();
			}
			
			if (fRunning) { // It is possible we stop running in the draw.
				draw();
				SDL_Delay(1);
			} else {
				freePanel(fPanel);
				fPanel = NULL;
				fScreen = NULL;
				SDL_Quit();
			}
			if (fpsCounter.frame()) {
				std::stringstream ssWMCaption;
				ssWMCaption << fpsCounter.fps();
				std::string WMCaption;
				ssWMCaption >> WMCaption;
				WMCaption = "Space-Invadors   " + WMCaption + " FPS";
				SDL_WM_SetCaption(WMCaption.c_str(), "Icon Title");
			}
		}
	}
	
	/**
	 * Updates the physical screen so it contains the same information as the screen buffer.
	*/
	void SDLWindow::draw() {
		SDL_Flip(fScreen);
	}
	
	/**
	 * Close the current panel and pass control to the next panel.
	 *
	 * @param next The next panel. If 0 the window closes.
	*/
	void SDLWindow::closePanel(VSDLPanel* next) {
		if (next != NULL) {
			fOldPanel = fPanel;
			fPanel = next;
		} else {
			// We keep the old panel.
			fRunning = false;
		}
	}
	
	/**
	 * Gives control back to the parent panel, and close the current panel.
	 *
	 * @param prev The parent panel.
	*/
	void SDLWindow::openParentPanel(VSDLPanel* prev) {
		if (prev != NULL) {
			fOldPanel = fPanel;
			fPanel = prev;
		} else {
			fRunning = false;
		}
	}
	
	/**
	 * Opens a new panel, but keep the current panel active.
	 *
	 * @param c The new active panel.
	*/
	void SDLWindow::openPanel(VSDLPanel* c) {
		fPanel = c;
	}
	
	/**
	 * Draws a surface on the window.
	 *
	 * @param surface The surface to draw.
	 * @param x The x coordinate on the screen.
	 * @param y The y coordinate on the screen.
	*/
	void SDLWindow::drawSurface(SDLSurfaceResource* surface, int x, int y) {
		drawSurface(surface, x, y, 1.0);
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
		dest.x = x;
		dest.y = y;
	
		SDL_BlitSurface(surface, 0, fScreen, &dest);
	}
	
	/**
	 * Draws a surface on the window.
	 *
	 * @param surface The surface to draw.
	 * @param x The x coordinate on the screen.
	 * @param y The y coordinate on the screen.
	 * @param scale Scale factor of the surface. Not yet implemented.
	*/
	void SDLWindow::drawSurface(SDLSurfaceResource* surface, int x, int y, double scale) {
		SDL_Rect src, dest;
	
		src.x = 0;
		src.y = 0;
		src.w = surface->getWidth();
		src.h = surface->getHeight();
		
		dest.x = x;
		dest.y = y;
		dest.w = surface->getWidth() * scale;
		dest.h = surface->getHeight() * scale;
		
		SDL_BlitSurface(surface->getSurface(), &src, fScreen, &dest);
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
	
		dest.x = x;
		dest.y = y;
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
		dest.x = x;
		dest.y = y;
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
		boxRGBA(fScreen, x, y, x + w, y + h, r, g, b, a*255);
	}
	
	/**
	 * Get the x-resolution of the window
	 *
	 * @return The X resolution (width) of the window.
	*/
	int SDLWindow::getXResolution() {
		return fScreen->w;
	}

	/**
	 * Get the y-resolution of the window
	 *
	 * @return The Y resolution (height) of the window.
	*/
	int SDLWindow::getYResolution() {
		return fScreen->h;
	}
	
	/**
	 * Free a panel and all of its parent panels.
	 *
	 * @param p The panel to free.
	*/
	void SDLWindow::freePanel(VSDLPanel* p) {
		if (p->fParentPanel) {
			freePanel(p->fParentPanel);
		}
		delete p;
	}

}
