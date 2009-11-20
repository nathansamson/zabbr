#ifndef INC_SDLCONTROLLER_H
#define INC_SDLCONTROLLER_H

#include "SDL.h"

#include "sdlwindow.h"

namespace Zabbr {

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
		VSDLController* fParentController;
		SDLWindow* fWindow;
		bool fIsBackground;
};
}

#endif // INC_SDLCONTROLLER_H
