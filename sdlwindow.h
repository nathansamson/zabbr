#ifndef INC_SDLWINDOW_H
#define INC_SDLWINDOW_H

/** \file
 * File for the SDL window.
 *
 * @author Nathan Samson
*/

#include <string>
#include <vector>
#include "SDL.h"

#include "resources/sdlsurfaceresource.h"
#include "events/callbacks.h"
#include "events/event.h"

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
	 * A video mode class.
	*/
	class VideoMode {
	public:
		VideoMode(int, int);
		
		int getX();
		int getY();
		
		bool operator==(const VideoMode&);
		operator std::string();
		friend bool operator<(const VideoMode&, const VideoMode&);
	private:
		/**
		 * Y value of the resolution.
		*/
		int fX;
		
		/**
		 * X Value of the resolution.
		*/
		int fY;
	};
	
	bool operator<(const VideoMode&, const VideoMode&);
	
	/**
	 * A Window.
	*/
	class SDLWindow {
	public:
		SDLWindow(std::string);
		
		void draw();
		
		void open(int, int, bool, bool = false, double = -1.0);
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
		void resize(VideoMode);
		
		int getXResolution();
		int getYResolution();
		
		int connectOnScreenSizeChanged(ICallback3<SDLWindow*, int, int>*);
		void disconnectOnScreenSizeChanged(int);
		VideoMode getVideoMode();
		std::vector<VideoMode> getAvailableResolutions();

	protected:
		/**
		 * The current active panel.
		*/
		VSDLPanel* fPanel;
	private:
		void freePanel(VSDLPanel*);
		void resize(int, int);
		void calculateRatioOffset(int, int);
		int getVideoModeFlags();

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
		
		/**
		 * Flag to see if we have to keep ratio
		*/
		bool fKeepratio;
		
		/**
		 * The ratio of the screen
		*/
		double fRatio;
		
		/**
		 * The window title.
		*/
		std::string fWindowTitle;
		
		/**
		 * The offset to the physical screen we can draw.
		*/
		struct Offset {
			int x;
			int y;
		} fRatioOffset;
		
		/**
		 * The screen size changed signal
		*/
		Event3<SDLWindow*, int, int> fScreenChanged;
		
		/**
		 * Flag to see if we are fullscreen.
		*/
		bool fFullscreen;
	};

}

#endif // INC_SDLWINDOW_H
