#ifndef INC_WINDOW_H
#define INC_WINDOW_H

#include <string>
#include <vector>
#include <map>
#include "SDL.h"

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
	class Window {
	public:
		Window(std::string);
		
		void draw();
		
		void open(int, int, bool, bool = false, double = -1.0);
		void close();
		
	    void run(VSDLPanel*);

		/***** API for panels ******/

		void closePanel(VSDLPanel*);
		void openParentPanel(VSDLPanel*);
		void openPanel(VSDLPanel*);
		void resize(VideoMode);
		
		int getXResolution();
		int getYResolution();
		
		int connectOnScreenSizeChanged(ICallback3<Window*, int, int>*);
		void disconnectOnScreenSizeChanged(int);
		VideoMode getVideoMode();
		std::vector<VideoMode> getAvailableResolutions();
		
		virtual void drawRectangle(int, int, int, int, int, int, int) = 0;
		virtual void drawRectangle(int, int, int, int, int, int, int, double) = 0;

	protected:		
		virtual void clearScreen() = 0;
		virtual void swapBuffers() = 0;
		virtual void openWindow(int, int, bool) = 0;
		
		/**
		 * The current active panel.
		*/
		VSDLPanel* fPanel;
		
		/**
		 * The offset to the physical screen we can draw.
		*/
		struct Offset {
			int x;
			int y;
		} fRatioOffset;
	private:
		void freePanel(VSDLPanel*);
		void resize(int, int);
		void calculateRatioOffset(int, int);
		void setKeystates();
		
		VideoMode fCurrentVideoMode;

		/**
		 * Keeping the removed panel for a while (rest of the frame) in memory.
		*/
		VSDLPanel* fOldPanel;
		
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
		 * The screen size changed signal
		*/
		Event3<Window*, int, int> fScreenChanged;
		
		/**
		 * Flag to see if we are fullscreen.
		*/
		bool fFullscreen;
		
		/**
		 * A list of keystates. When a specific
		 * key is pressed when a panel closes, the state will be true in this list.
		 * When the key is released it will turn back to false.
		*/
		std::map<SDLKey, bool> fPressedKeys;
	};
}

#endif // INC_WINDOW_H
