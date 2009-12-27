#ifndef INC_SDLWINDOW_H
#define INC_SDLWINDOW_H

/** \file
 * File for the SDL window.
 *
 * @author Nathan Samson
*/

#include <string>
#include "SDL.h"

#include "resources/sdlsurfaceresource.h"

namespace Zabbr {

	class VSDLPanel;

	/**
	 * Exception when SDL could not initialize.
	*/
	class SDLInitializationException {
	public:
		SDLInitializationException(std::string);
		std::string getError();
	private:
		/**
		 * The initialization error.
		*/
		std::string fError;
	};

	/**
	 * A Window.
	*/
	class SDLWindow {
	public:
		SDLWindow();
		
		void draw();
		
		void open(int, int, bool);
		void close();
		
	    void run(VSDLPanel*);

		/***** API for panels ******/

		void closePanel(VSDLPanel*);
		void openParentPanel(VSDLPanel*);
		void openPanel(VSDLPanel*);
		
		void drawSurface(SDLSurfaceResource*, int, int);
		void drawSurface(SDL_Surface*, int, int);
		void drawPartOfSurface(SDL_Surface*, int, int, SDL_Rect);
		void drawSurface(SDLSurfaceResource*, int, int, double);
		void drawRectangle(int, int, int, int, int, int, int);
		void drawRectangle(int, int, int, int, int, int, int, double);
		
		int getXResolution();
		int getYResolution();
	protected:
		/**
		 * The current active panel.
		*/
		VSDLPanel* fPanel;
	private:
		void freePanel(VSDLPanel*);

		/**
		 * Keeping the removed panel for a while (rest of the frame) in memory.
		*/
		VSDLPanel* fOldPanel;
		
		/**
		 * The window surface.
		*/
		SDL_Surface* fScreen;
		
		/**
		 * A bool representing of the app is still running.
		*/
		bool fRunning;
	};

}

#endif // INC_SDLWINDOW_H
