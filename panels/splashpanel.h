#ifndef INC_SPLASHCONTROLLER_H
#define INC_SPLASHCONTROLLER_H

#include <string>

#include "controller/sdlcontroller.h"
#include "resources/imageresource.h"

namespace Zabbr {

	/**
	 * A Splash controller.
	 *
	 * @ingroup Controllers
	 *
	 * This will display a splash image and messages.
	*/
	class SplashController : public VSDLController {
	public:
		SplashController(SDLWindow*, std::string, VSDLController*);
		virtual ~SplashController();

		virtual void draw();
	private:
		/**
		 * The splash image.
		*/
		ImageResource* fImage;
		
		/**
		 * The controller that should be loaded after loading is done.
		*/
		VSDLController* fNextController;
	};
}

#endif // INC_SPLASHCONTROLLER_H
