/** \file
 * File for the splash panel.
 *
 * @author Nathan Samson
*/

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
	}
	
	/**
	 * Desctructor.
	*/
	SplashPanel::~SplashPanel() {
		ResourceManager::manager().free(fImage);
	}
	
	/**
	 * Draws the splash screen.
	*/
	void SplashPanel::draw() {
		static int i = 0;
		fWindow->drawSurface(fImage, 0, 0);
		SDL_Delay(100);
		i++;
		if (i > 30) {
			fWindow->closePanel(fNextPanel);
		}
	}
}
