#ifndef INC_DIALOGPANEL_H
#define INC_DIALOGPANEL_H

/** \file
 * File for the dialog panel.
 *
 * @author Nathan Samson
*/

#include <map>
#include <vector>

#include "panels/widgetpanel.h"
#include "events/callbacks.h"
#include "events/event.h"
#include "widgets/label.h"
#include "widgets/button.h"

namespace Zabbr {
	/**
	 * Panel that shows a text, and buttons.
	*/
	class DialogPanel: public WidgetPanel {
	public:
		static const int Quit = -1;
		static const int Cancel = -2;
	
		DialogPanel(SDLWindow*, std::string, std::vector<std::pair<int, std::string> >);
		
		virtual void keyRelease(SDL_KeyboardEvent);
		void connectOnResponse(ICallback1<int>*);
	private:
		/**
		 * The question label
		*/
		Label* fQuestionLabel;
	
		/**
		 * A map of buttons with their response ID's as value.
		*/
		std::map<Button*, int> fButtonResponseMap;
		
		/**
		 * Response event
		*/
		Event1<int> fResponseEvent;
		
		void onButtonClick(Button*);
		void onRequestQuit();
	};
}

#endif // INC_DIALOGPANEL_H
