#ifndef INC_SDLWINDOW_H
#define INC_SDLWINDOW_H

#include <string>
#include "SDL.h"

#include "resources/imageresource.h"
#include "resources/stringfontresource.h"

namespace Zabbr {

	class VSDLController;

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
		
	    void run(VSDLController*);

		/***** API for controllers ******/

		void closeController(VSDLController*);
		void openParentController(VSDLController*);
		void openController(VSDLController*);
		
		void drawImage(ImageResource*, int, int);
		void drawImage(ImageResource*, int, int, double);
		void drawString(StringFontResource*, int, int);
		void drawRectangle(int, int, int, int, int, int, int);
		void drawRectangle(int, int, int, int, int, int, int, double);
	protected:
		/**
		 * The current active controller.
		*/
		VSDLController* fController;
	private:
		void freeController(VSDLController*);

		/**
		 * Keeping the removed controller for a while (rest of the frame) in memory.
		*/
		VSDLController* fOldController;
		
		/**
		 * The window surface.
		*/
		SDL_Surface* screen;
		
		/**
		 * A bool representing of the app is still running.
		*/
		bool fRunning;
	};

}

#endif // INC_SDLWINDOW_H
