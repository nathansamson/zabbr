#ifndef INC_MENUPANEL_H
#define INC_MENUPANEL_H

/** \file
 * File for the menu panel.
 *
 * @author Nathan Samson
*/

#include <list>
#include "SDL.h"

#include "panels/sdlpanel.h"
#include "widgets/widget.h"

namespace Zabbr {

	/**
	 * A panel to show a menu.
	 *
	 * @ingroup Panels
	 *
	 * Actually it shows a list of widgets.
	*/
	class MenuPanel: public VSDLPanel {
	public:
		MenuPanel(SDLWindow*);
		virtual ~MenuPanel();

		void addWidget(VWidget*);

		virtual void draw();
		virtual void keyPress(SDL_KeyboardEvent);
		virtual void keyRelease(SDL_KeyboardEvent);
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

#endif // INC_MENUPANEL_H
