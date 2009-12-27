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
	class DialogPanel: public WidgetPanel {
	public:
		static const int Quit = -1;
		static const int Cancel = -2;
	
		DialogPanel(SDLWindow*, std::string, std::vector<std::pair<int, std::string> >);
		
		void connectOnResponse(ICallback1<int>*);
		
		void onButtonClick(Button*);
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
	};
}

#endif // INC_DIALOGPANEL_H
