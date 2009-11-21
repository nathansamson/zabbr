#ifndef INC_MENUCONTROLLER_H
#define INC_MENUCONTROLLER_H

#include <list>
#include "SDL.h"

#include "controller/sdlcontroller.h"
#include "widgets/widget.h"

namespace Zabbr {

	/**
	 * A controller to show a menu.
	 *
	 * @ingroup Controllers
	 *
	 * Actually it shows a list of widgets.
	*/
	class MenuController : public VSDLController {
	public:
		MenuController(SDLWindow*);
		virtual ~MenuController();

		void addWidget(VWidget*);

		virtual void draw();
		virtual void keyDown(SDL_KeyboardEvent);
		virtual void mouseMotion(SDL_MouseMotionEvent);
		virtual void mouseButton(SDL_MouseButtonEvent);
		virtual void quit();
	private:
		/**
		 * A list of all widgets.
		*/
		std::list<VWidget*> fWidgets;
	};

}

#endif // INC_MENUCONTROLLER_H
