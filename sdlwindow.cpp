#include <iostream>

#include "SDL.h"
#include "SDL_gfxPrimitives.h"
#include "SDL_ttf.h"

#include "sdlwindow.h"
#include "controller/sdlcontroller.h"
#include "resources/imageresource.h"
#include "resources/stringfontresource.h"

namespace Zabbr {

	SDLInitializationException::SDLInitializationException(std::string s)
	                           : fError(s) {
	}
	
	std::string SDLInitializationException::getError() {
		return fError;
	}
	
	SDLWindow::SDLWindow() {
	
	}
	
	SDLWindow::SDLWindow(const SDLWindow&) {
	
	}
	
	SDLWindow& SDLWindow::operator=(const SDLWindow& rhs) {
		screen = rhs.screen;
		return *this;
	}
	
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
	
	void SDLWindow::close() {
		if (screen)
			SDL_FreeSurface(screen);
		TTF_Quit();
	}
	
	void SDLWindow::run(VSDLController* controller) {
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
				SDL_Delay(1);
			} else {
				freeController(fController);
				fController = NULL;
				screen = NULL;
			}
		}
	}
	
	void SDLWindow::draw() {
		SDL_Flip(screen);
	}
	
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
	
	void SDLWindow::openParentController(VSDLController* prev) {
		fOldController = fController;
		fController = prev;
	}
	
	void SDLWindow::openController(VSDLController* c) {
		fController = c;
	}
	
	void SDLWindow::drawImage(ImageResource* img, int x, int y) {
		drawImage(img, x, y, 1.0);
	}
	
	void SDLWindow::drawImage(ImageResource* img, int x, int y, double scale) {
		SDL_Rect src, dest;
	
		src.x = 0;
		src.y = 0;
		src.w = img->getWidth();
		src.h = img->getHeight();
		
		dest.x = x;
		dest.y = y;
		dest.w = img->getWidth() * scale;
		dest.h = img->getHeight() * scale;
		
		SDL_BlitSurface(img->getSurface(), &src, screen, &dest);
	}
	
	void SDLWindow::drawString(StringFontResource* string, int x, int y) {
		SDL_Rect src, dest;
		
		src.x = 0;
		src.y = 0;
		src.w = string->getWidth();
		src.h = string->getHeight();
		
		dest.x = x;
		dest.y = y;
		dest.w = string->getWidth();
		dest.h = string->getHeight();
		
		SDL_BlitSurface(string->getSurface(), &src, screen, &dest);
	}
	
	void SDLWindow::drawRectangle(int x, int y, int w, int h, int r, int g, int b) {
		SDL_Rect dest;
		dest.x = x;
		dest.y = y;
		dest.w = w;
		dest.h = h;
	
	
		SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, r, g, b));
	}
	
	void SDLWindow::drawRectangle(int x, int y, int w, int h, int r, int g, int b, double op) {
		boxRGBA(screen, x, y, x + w, y + h, r, g, b, op*255);
	}
	
	void SDLWindow::freeController(VSDLController* c) {
		if (c->fParentController) {
			freeController(c->fParentController);
		}
		delete c;
	}

}
