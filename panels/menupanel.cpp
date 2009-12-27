/** \file
 * File for the menu panel.
 *
 * @author Nathan Samson
*/

#include "panels/menupanel.h"
#include "widgets/label.h"
#include "widgets/hbox.h"

namespace Zabbr {
	/**
	 * Public constructor.
	 *
	 * @param window The SDLWindow
	 * @param title The title of the menu.
	*/
	MenuPanel::MenuPanel(SDLWindow* window, std::string title):
	               WidgetPanel(window, new VBox(window, false, 10)) {
		fButtonBox = new VBox(fWindow, true, 7);
		SDL_Color white = {255, 255, 255};
		dynamic_cast<VBox*>(fTopLevel)->appendWidget(new Label(fWindow, title, white, "DejaVuSans-Bold.ttf", 48));
		dynamic_cast<VBox*>(fTopLevel)->appendWidget(fButtonBox);
	}
	
	/**
	 * Public constructor.
	 *
	 * @param window The SDLWindow.
	 * @param title The Title of the menu
	 * @param color The color of the title.
	 * @param font The font of the title.
	 * @param size The font size.
	*/
	MenuPanel::MenuPanel(SDLWindow* window, std::string title,
	                     SDL_Color color, std::string font, int size):
	               WidgetPanel(window, new VBox(window, false, 10)) {
		fButtonBox = new VBox(fWindow, true, 7);
		dynamic_cast<VBox*>(fTopLevel)->appendWidget(new Label(fWindow, title, color, font, size));
		dynamic_cast<VBox*>(fTopLevel)->appendWidget(fButtonBox);
	}
	
	/**
	 * Adds a button to the menu.
	 *
	 * @param b The button.
	*/
	void MenuPanel::addButton(Button* b) {
		fButtonBox->appendWidget(b);
	}
}
