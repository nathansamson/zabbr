#ifndef INC_DIALOGPANEL_H
#define INC_DIALOGPANEL_H

#include <map>
#include <vector>

#include "panels/menupanel.h"
#include "events/callbacks.h"
#include "events/event.h"
#include "widgets/label.h"
#include "widgets/button.h"

namespace Zabbr {
	class DialogPanel: public MenuPanel {
	public:
		static const int Quit = -1;
		static const int Cancel = -2;
	
		DialogPanel(SDLWindow*, std::string, std::vector<std::pair<int, std::string> >);
		
		void connectOnResponse(ICallback1<int>*);
		virtual void draw();
		
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
		 * A list of all butons.
		*/
		std::vector<Button*> fButtons;
		
		/**
		 * Response event
		*/
		Event1<int> fResponseEvent;
	};
}

#endif // INC_DIALOGPANEL_H
