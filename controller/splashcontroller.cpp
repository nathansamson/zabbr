#include "SDL.h"

#include "controller/splashcontroller.h"
#include "resources/resourcemanager.h"

namespace Zabbr {

	SplashController::SplashController(
	          SDLWindow* window, std::string fileName,
	          VSDLController* controller)
	                : VSDLController(window),
	                  fNextController(controller) {
		fImage = ResourceManager::manager().image(fileName);
		i = 0;
	}
	
	SplashController::SplashController(const SplashController& orig)
	                 : VSDLController(orig.fWindow)  {
	}
	
	SplashController::~SplashController() {
		ResourceManager::manager().free(fImage);
	}
	
	void SplashController::draw() {
		fWindow->drawImage(fImage, 0, 0);
		SDL_Delay(1000);
		i++;
		if (i > 5) {
			fWindow->closeController(fNextController);
		}
	}
}
