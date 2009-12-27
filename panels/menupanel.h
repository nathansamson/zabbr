#ifndef INC_MENUPANEL_H
#define INC_MENUPANEL_H

/** \file
 * File for the menu panel.
 *
 * @author Nathan Samson
*/

#include "panels/widgetpanel.h"
#include "widgets/button.h"
#include "widgets/vbox.h"

namespace Zabbr {
	/**
	 * Panel that shows a title + buttons.
	*/
	class MenuPanel: public WidgetPanel {
	public:
		MenuPanel(SDLWindow*, std::string);
		MenuPanel(SDLWindow*, std::string, SDL_Color, std::string, int);
	
		void addButton(Button*);
	private:
		/**
		 * Button box.
		*/
		VBox* fButtonBox;
	};
}

#endif // INC_MENUPANEL_H
