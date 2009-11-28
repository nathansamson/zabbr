#include <iostream>
#include <sstream>

#include "SDL.h"
#include "SDL_gfxPrimitives.h"
#include "SDL_ttf.h"

#include "sdlwindow.h"
#include "misc/fpscounter.h"
#include "controller/sdlcontroller.h"
#include "resources/imageresource.h"
#include "resources/stringfontresource.h"

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
	SDLWindow::SDLWindow() {
	
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
	
		screen = SDL_SetVideoMode(xres, yres, 32, SDL_DOUBLEBUF);
		if (screen == NULL) {
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
		if (screen)
			SDL_FreeSurface(screen);
		TTF_Quit();
	}
	
	/**
	 * Run the mainloop.
	 *
	 * @param controller The first controller to get control of what happens.
	*/
	void SDLWindow::run(VSDLController* controller) {
		FPSCounter fpsCounter(500);
		fController = controller;
		SDL_Event event;
		fRunning = true;
	
		while (fRunning) {
			while (fRunning && SDL_PollEvent(&event)) {
				switch (event.type) {
					case SDL_KEYDOWN:
						fController->keyDown(event.key);
						break;
					case SDL_MOUSEMOTION:
						fController->mouseMotion(event.motion);
						break;
					case SDL_MOUSEBUTTONUP:
						fController->mouseButton(event.button);
						break;
					case SDL_QUIT:
						fController->quit();
						break;
				}
			}
	
			if (fOldController) {
				delete fOldController;
				fOldController = NULL;
			}
	
			if (fRunning) { // it is possible we quit when firing events.
				drawRectangle(0, 0, screen->w, screen->h, 0, 0, 0);
				fController->draw();
				draw();
				//SDL_Delay(1);
			} else {
				freeController(fController);
				fController = NULL;
				screen = NULL;
			}
			if (fpsCounter.frame()) {
				std::stringstream ssWMCaption;
				ssWMCaption << fpsCounter.fps();
				std::string WMCaption;
				ssWMCaption >> WMCaption;
				WMCaption = "Space-Invadors   " + WMCaption + " FPS";
				SDL_WM_SetCaption(WMCaption.c_str(), "Icon Title");
			}
			SDL_Delay(1);
		}
	}
	
	/**
	 * Updates the physical screen so it contains the same information as the screen buffer.
	*/
	void SDLWindow::draw() {
		SDL_Flip(screen);
	}
	
	/**
	 * Close the current controller and pass control to the next controller.
	 *
	 * @param next The next controller. If 0 the window closes.
	*/
	void SDLWindow::closeController(VSDLController* next) {
		if (next != NULL) {
			fOldController = fController;
			fController = next;
		} else {
			// We keep the old controller.
			fRunning = false;
			SDL_Quit();
		}
	}
	
	/**
	 * Gives control back to the parent controller, and close the current controller.
	 *
	 * @param prev The parent controller.
	*/
	void SDLWindow::openParentController(VSDLController* prev) {
		fOldController = fController;
		fController = prev;
	}
	
	/**
	 * Opens a new controller, but keep the current controller active.
	 *
	 * @param c The new active controller.
	*/
	void SDLWindow::openController(VSDLController* c) {
		fController = c;
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
		
		SDL_BlitSurface(surface->getSurface(), &src, screen, &dest);
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
		
		SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, r, g, b));
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
		boxRGBA(screen, x, y, x + w, y + h, r, g, b, a*255);
	}
	
	/**
	 * Free a controller and all of its parent controllers.
	 *
	 * @param c The controller to free.
	*/
	void SDLWindow::freeController(VSDLController* c) {
		if (c->fParentController) {
			freeController(c->fParentController);
		}
		delete c;
	}

}
