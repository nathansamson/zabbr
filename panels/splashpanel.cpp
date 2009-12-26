/** \file
 * File for the splash panel.
 *
 * @author Nathan Samson
*/

#include <iostream>
#include "SDL.h"

#include "panels/splashpanel.h"
#include "resources/resourcemanager.h"

namespace Zabbr {

	/**
	 * Constructor.
	 *
	 * @param window The SDLWindow.
	 * @param fileName The file name of the splash image.
	 * @param panel The controller that should be activated after loading is done.
	*/
	SplashPanel::SplashPanel(SDLWindow* window, std::string fileName,
	                         VSDLPanel* panel):
	             VSDLPanel(window), fNextPanel(panel), fStatusText(0) {
		fImage = ResourceManager::manager().image(fileName, window->getXResolution(), window->getYResolution(), true, 0);
		fPrefetcherList.push(new EmptyPrefetcher());
		fFont = ResourceManager::manager().font("DejaVuSans-Bold.ttf", 18);
	}
	
	/**
	 * Desctructor.
	*/
	SplashPanel::~SplashPanel() {
		ResourceManager::manager().free(fImage);
		if (fStatusText) ResourceManager::manager().free(fStatusText);
		ResourceManager::manager().free(fFont);
	}
	
	void SplashPanel::addPrefetcher(IPrefetcher* prefetcher) {
		fPrefetcherList.push(prefetcher);
	}
	
	/**
	 * Draws the splash screen.
	*/
	void SplashPanel::draw() {
		if (!fPrefetcherList.empty()) {
			IPrefetcher* prefetcher = fPrefetcherList.front();
			fTimer.reset();
			bool done = (*prefetcher)();
			while (fTimer.time() < 0.01 && !done) {
				SDL_Delay(200); // Just for fun, to show the cool splash
				done = (*prefetcher)();
			}
			if (done) {
				delete prefetcher;
				fPrefetcherList.pop();
				if (! fPrefetcherList.empty()) {
					IPrefetcher* next = fPrefetcherList.front();
					SDL_Color black = {0, 0, 0};
					if (fStatusText) ResourceManager::manager().free(fStatusText);
					fStatusText = ResourceManager::manager().string(next->name(), fFont, black);
				} else {
					fWindow->closePanel(fNextPanel);
					return;
				}
			}
			fWindow->drawSurface(fImage, 0, 0);
			fWindow->drawSurface(fStatusText, 20, fWindow->getYResolution() - 20 - fStatusText->getHeight());
		} else {
			fWindow->closePanel(fNextPanel);
		}
	}
	
	/**
	 * Destructor.
	*/
	SplashPanel::EmptyPrefetcher::~EmptyPrefetcher() {
	}
	
	/**
	 * Run the empty prefetcher.
	 *
	 * @return True (it is always done).
	*/
	bool SplashPanel::EmptyPrefetcher::operator()() {
		return true;
	}
	
	/**
	 * Return the name of the prefetcher.
	 *
	 * @return The name of the prefetcher.
	*/
	std::string SplashPanel::EmptyPrefetcher::name() {
		return "";
	}
}
