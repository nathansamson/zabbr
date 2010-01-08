/** \file
 * File for the sdl window.
 *
 * @author Nathan Samson
*/

#include <iostream>
#include <sstream>
#include <algorithm>

#include "SDL.h"

#include "window.h"
#include "misc/fpscounter.h"
#include "misc/audiomanager.h"
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
	Window::Window(std::string title): fCurrentVideoMode(0, 0), fOldPanel(0), fKeepratio(false), fWindowTitle(title) {
	
	}
	
	/**
	 * Open the window.
	 *
	 * @param xres The X resolution.
	 * @param yres The Y resolution.
	 * @param fs True if running in fullscreen, false if not.
	 * @param keepration If the ratio of xres and yres should be kept.
	 * @param ratio The ratio (defaults to xres / tres).
	 *
	 * @throw An SDLInitializationException if initialization fails.
	*/
	void Window::open(int xres, int yres, bool fs, bool keepratio, double ratio) {
		fFullscreen = fs;
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
			throw SDLInitializationException(SDL_GetError());
		}
	
		atexit(SDL_Quit);
	
		openWindow(xres, yres, fs);
		fCurrentVideoMode = VideoMode(xres, yres);
	
		if(TTF_Init() == -1) {
			throw SDLInitializationException(TTF_GetError());
		}
		fKeepratio = keepratio;
		if (ratio <  0.0) {
			fRatio = xres * 1.0 / yres;
			fRatioOffset.x = 0;
			fRatioOffset.y = 0;
		} else {
			fRatio = ratio;
			calculateRatioOffset(xres, yres);
		}
	}
	
	VideoMode::VideoMode(int x, int y): fX(x), fY(y) {
	}
	
	int VideoMode::getX() { return fX; }
	int VideoMode::getY() { return fY; }
	
	bool VideoMode::operator==(const VideoMode& o) {
		return (fX == o.fX && fY == o.fY);
	}
	
	bool operator<(const VideoMode& lhs, const VideoMode& rhs) {
		return lhs.fX < rhs.fX;
	}
	
	VideoMode::operator std::string() {
		std::stringstream res;
		res << fX << "x" << fY;
		std::string s;
		res >> s;
		return s;
	}
	
	/**
	 * Close the window.
	*/
	void Window::close() {
		AudioManager::get().mute(); // Make sure no resources are in use
		ResourceManager::free();
		AudioManager::close();
		TTF_Quit();
	}
	
	/**
	 * Run the mainloop.
	 *
	 * @param panel The first panel to get control of what happens.
	*/
	void Window::run(VSDLPanel* panel) {
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
						if (fPressedKeys[event.key.keysym.sym]) {
							fPressedKeys[event.key.keysym.sym] = false;
						} else {
							fPanel->keyRelease(event.key);
						}
						break;
					case SDL_MOUSEMOTION:
						event.motion.x -= fRatioOffset.x;
						event.motion.y -= fRatioOffset.y;
						fPanel->mouseMotion(event.motion);
						break;
					case SDL_MOUSEBUTTONUP:
						event.button.x -= fRatioOffset.x;
						event.button.y -= fRatioOffset.y;
						fPanel->mouseButton(event.button);
						break;
					case SDL_QUIT:
						fPanel->requestQuit();
						break;
					case SDL_VIDEORESIZE:
						resize(event.resize.w, event.resize.h);
						break;
				}
			}
	
			if (fOldPanel) {
				delete fOldPanel;
				fOldPanel = 0;
			}
	
			if (fRunning) { // it is possible we quit when firing events.
				clearScreen();
				fPanel->draw();
				AudioManager::get().playQueue();
			}
			
			if (fRunning) { // It is possible we stop running in the draw.
				swapBuffers();
				SDL_Delay(1);
			} else {
				freePanel(fPanel);
				fPanel = 0;
				SDL_Quit();
			}
			if (fpsCounter.frame()) {
				std::stringstream ssWMCaption;
				ssWMCaption << fpsCounter.fps();
				std::string WMCaption;
				ssWMCaption >> WMCaption;
				WMCaption = fWindowTitle+ ": " + WMCaption + " FPS";
				SDL_WM_SetCaption(WMCaption.c_str(), fWindowTitle.c_str());
			}
		}
	}
	
	/**
	 * Close the current panel and pass control to the next panel.
	 *
	 * @param next The next panel. If 0 the window closes.
	*/
	void Window::closePanel(VSDLPanel* next) {
		if (next != 0) {
			fOldPanel = fPanel;
			fPanel = next;
			
			setKeystates();
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
	void Window::openParentPanel(VSDLPanel* prev) {
		if (prev != 0) {
			fOldPanel = fPanel;
			fPanel = prev;
			
			setKeystates();
		} else {
			fRunning = false;
		}
	}
	
	/**
	 * Opens a new panel, but keep the current panel active.
	 *
	 * @param c The new active panel.
	*/
	void Window::openPanel(VSDLPanel* c) {
		fPanel = c;
		setKeystates();
	}
	
	void Window::resize(VideoMode mode) {
		resize(mode.getX(), mode.getY());
	}
	
	/**
	 * Get the x-resolution of the window
	 *
	 * @return The X resolution (width) of the window.
	*/
	int Window::getXResolution() {
		return fCurrentVideoMode.getX() - 2 * fRatioOffset.x;
	}

	/**
	 * Get the y-resolution of the window
	 *
	 * @return The Y resolution (height) of the window.
	*/
	int Window::getYResolution() {
		return fCurrentVideoMode.getY() - 2 * fRatioOffset.y;
	}
	
	/**
	 * Connect to hte screen size changed event.
	 *
	 * @param c Your callback.
	 * return The ID of the callback (so you can disconnect).
	*/
	int Window::connectOnScreenSizeChanged(ICallback3<Window*, int, int>* c) {
		return fScreenChanged.connect(c);
	}
	
	/**
	 * Disconnect a callback.
	 *
	 * @param id The the ID of the callback (as returned by connectOnScreenSizeChanged).
	*/
	void Window::disconnectOnScreenSizeChanged(int id) {
		fScreenChanged.disconnect(id);
	}
	
	VideoMode Window::getVideoMode() {
		return fCurrentVideoMode;
	}
	
	std::vector<VideoMode> Window::getAvailableResolutions() {
		SDL_Rect** modes;
		int i;

		modes = SDL_ListModes(NULL, 0);

		/* Check if there are any modes available */
		if (modes == (SDL_Rect**)0) {
			return std::vector<VideoMode>();
		}

	
		std::vector<VideoMode> listedModes;	
		if (modes == (SDL_Rect**)-1) {
			listedModes.push_back(VideoMode(400, 300));
			listedModes.push_back(VideoMode(640, 480));
			listedModes.push_back(VideoMode(800, 600));
			listedModes.push_back(VideoMode(1024, 768));
			listedModes.push_back(VideoMode(1280, 800));
		} else {
			for (i=0; modes[i]; ++i) {
				listedModes.push_back(VideoMode(modes[i]->w, modes[i]->h));
			}
			std::sort(listedModes.begin(), listedModes.end());
		}
		return listedModes;
	}
	
	/**
	 * Free a panel and all of its parent panels.
	 *
	 * @param p The panel to free.
	*/
	void Window::freePanel(VSDLPanel* p) {
		if (p->fParentPanel) {
			freePanel(p->fParentPanel);
		}
		delete p;
	}
	
	/**
	 * Resize the screen.
	 *
	 * @param w The new width
	 * @param h The new height
	*/
	void Window::resize(int w, int h) {
		//fScreen = SDL_SetVideoMode(w, h, 32, getVideoModeFlags());
		openWindow(w, h, fFullscreen);
		fCurrentVideoMode = VideoMode(w, h);
		if (fKeepratio) {
			calculateRatioOffset(w, h);
		}
		fScreenChanged(this, getXResolution(), getYResolution());
	}
	
	/**
	 * Calculate the ratio offset.
	*/
	void Window::calculateRatioOffset(int w, int h) {
		double ratio = w * 1.0 / h;
		if (ratio > fRatio) {
			fRatioOffset.x = (w - h * fRatio) / 2;
			fRatioOffset.y = 0;
		} else {
			fRatioOffset.x = 0;
			fRatioOffset.y = (h - w / fRatio) / 2;
		}
	}
	
	void Window::setKeystates() {
		int keys;
		Uint8* keystate = SDL_GetKeyState(&keys);
		for (int i = 0; i < keys; i++) {
			if (keystate[i]) {
				fPressedKeys[(SDLKey)i] = true;
			}
		}
	}
}
