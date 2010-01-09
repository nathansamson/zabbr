#ifndef INC_SDLWINDOW_H
#define INC_SDLWINDOW_H

/** \file
 * File for the SDL window.
 *
 * @author Nathan Samson
*/

#include "resources/sdlimageresource.h"
#include "window.h"

namespace Zabbr {
	/**
	 * A Window.
	*/
	class SDLWindow: public Window {
	public:
		SDLWindow(std::string);

		
		void drawSurface(SDL_Surface*, int, int);
		void drawPartOfSurface(SDL_Surface*, int, int, SDL_Rect);
		virtual void drawRectangle(int, int, int, int, int, int, int);
		virtual void drawRectangle(int, int, int, int, int, int, int, double);

	protected:
		virtual void clearScreen();
		virtual void swapBuffers();
		virtual void openWindow(int, int, bool);
	private:
		/**
		 * The window surface.
		*/
		SDL_Surface* fScreen;
	};

	class SDLImageFactory: public IImageResourceFactory {
	public:
		SDLImageFactory(SDLWindow*);
		
		virtual SDLImageResource* operator()(std::string);
	private:
		SDLWindow* fWindow;
	};
}

#endif // INC_SDLWINDOW_H
