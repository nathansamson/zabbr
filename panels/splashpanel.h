#ifndef INC_SPLASHPANEL_H
#define INC_SPLASHPANEL_H

#include <string>

#include "panels/sdlpanel.h"
#include "resources/imageresource.h"

namespace Zabbr {

	/**
	 * A Splash panel.
	 *
	 * @ingroup panels
	 *
	 * This will display a splash image and messages.
	*/
	class SplashPanel: public VSDLPanel {
	public:
		SplashPanel(SDLWindow*, std::string, VSDLPanel*);
		virtual ~SplashPanel();

		virtual void draw();
	private:
		/**
		 * The splash image.
		*/
		ImageResource* fImage;
		
		/**
		 * The panel that should be loaded after loading is done.
		*/
		VSDLPanel* fNextPanel;
	};
}

#endif // INC_SPLASHPANEL_H
