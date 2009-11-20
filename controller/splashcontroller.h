#ifndef INC_SPLASHCONTROLLER_H
#define INC_SPLASHCONTROLLER_H

#include <string>

#include "controller/sdlcontroller.h"
#include "resources/imageresource.h"

namespace Zabbr {

	class SplashController : public VSDLController {
	public:
		SplashController(SDLWindow*, std::string, VSDLController*);
		SplashController(const SplashController&);
		virtual ~SplashController();

		virtual void draw();
	private:
		ImageResource* fImage;
		VSDLController* fNextController;
		int i;
	};
}

#endif // INC_SPLASHCONTROLLER_H
