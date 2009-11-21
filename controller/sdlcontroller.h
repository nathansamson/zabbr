#ifndef INC_SDLCONTROLLER_H
#define INC_SDLCONTROLLER_H

#include "SDL.h"

#include "sdlwindow.h"

namespace Zabbr {

	/**
	 * \defgroup Controllers Controllers
	 *
	 * All the built-in Zabbr controllers.
	 *
	 * @ingroup Zabbr
	*/

	/**
	 * Virtual base class for all controllers.
	 *
	 * @ingroup Controllers
	 *
	 * A controller controls the content of the screen.
	 * Only one controller is active on a given moment in time.
	 * The active controller receives the window events (mouse motions for example.)
	*/
	class VSDLController {
	public:
		VSDLController(SDLWindow* window);
		virtual ~VSDLController();

		virtual void draw();
		virtual void keyDown(SDL_KeyboardEvent);
		virtual void mouseMotion(SDL_MouseMotionEvent);
		virtual void mouseButton(SDL_MouseButtonEvent);
		virtual void quit();
		void openParentController();
		void openController(VSDLController*);

		void background();
		void foreground();

		friend class SDLWindow;
	protected:
		/**
		 * The parent controller. The parent controller is the controller that 
		 * caused this controller to open. This can be NULL of this is a root controller.
		*/
		VSDLController* fParentController;
		
		/**
		 * The window of the controller. When a controller draws itself it should do this on this window.
		*/
		SDLWindow* fWindow;
		
		/**
		 * A flag to see if the background is in the background.
		*/
		bool fIsBackground;
};
}

#endif // INC_SDLCONTROLLER_H
