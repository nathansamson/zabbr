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
	             VSDLPanel(window), fNextPanel(panel) {
		fImage = ResourceManager::manager().image(fileName, window->getXResolution(), window->getYResolution(), true, 0);
		fPrefetcherList.push(new EmptyPrefetcher());
		SDL_Color black = {0, 0, 0};
		fStatusLabel = new Label(fWindow, "", black);
	}
	
	/**
	 * Desctructor.
	*/
	SplashPanel::~SplashPanel() {
		ResourceManager::manager().free(fImage);
		delete fStatusLabel;
	}
	
	/**
	 * Add a prefetcher to the panel.
	 *
	 * @param prefetcher The prefetcher to add.
	*/
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
					fStatusLabel->setLabel(next->name());
				} else {
					fWindow->closePanel(fNextPanel);
					return;
				}
			}
			fWindow->drawSurface(fImage, 0, 0);
			fStatusLabel->draw(20, fWindow->getYResolution() - 20 - fStatusLabel->getHeight());
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
