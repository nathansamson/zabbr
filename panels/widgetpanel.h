#ifndef INC_WIDGETPANEL_H
#define INC_WIDGETPANEL_H

/** \file
 * File for the widget panel.
 *
 * @author Nathan Samson
*/

#include <list>
#include "SDL.h"

#include "panels/sdlpanel.h"
#include "widgets/widget.h"

namespace Zabbr {

	/**
	 * A panel to show a toplevel widget.
	 *
	 * @ingroup Panels
	*/
	class WidgetPanel: public VSDLPanel {
	public:
		WidgetPanel(SDLWindow*, VWidget*);
		virtual ~WidgetPanel();

		virtual void draw();
		virtual void keyPress(SDL_KeyboardEvent);
		virtual void keyRelease(SDL_KeyboardEvent);
		virtual void mouseMotion(SDL_MouseMotionEvent);
		virtual void mouseButton(SDL_MouseButtonEvent);
		virtual void quit();
	protected:
		/**
		 * The top level widget.
		*/
		VWidget* fTopLevel;
	};

}

#endif // INC_WIDGETPANEL_H
