/** \file
 * File for the dialog panel.
 *
 * @author Nathan Samson
*/

#include "panels/dialogpanel.h"
#include "widgets/vbox.h"
#include "widgets/hbox.h"

namespace Zabbr {

	/**
	 * Constructor.
	 *
	 * @param w The window of the panel.
	 * @param question The question to print.
	 * @param responseIDMap A map of response ID's (should be positive).
	*/
	DialogPanel::DialogPanel(SDLWindow* w, std::string question,
	                         std::vector<std::pair<int, std::string> > responseIDMap):
	             WidgetPanel(w, new VBox(w, false, 10, YALIGN_CENTER)) {
		SDL_Color white = {255, 255, 255};
		fQuestionLabel = new Label(fWindow, question, white, "DejaVuSans-Bold.ttf", 24);
		dynamic_cast<VBox*>(fTopLevel)->appendWidget(fQuestionLabel);
		
		HBox* buttonBox = new HBox(fWindow, true, 10);
		dynamic_cast<VBox*>(fTopLevel)->appendWidget(buttonBox);
		
		for(std::vector<std::pair<int, std::string> >::iterator it = responseIDMap.begin(); it != responseIDMap.end(); it++) {
			Button* b = new Button(fWindow, (*it).second);
			fButtonResponseMap[b] = (*it).first;
			buttonBox->appendWidget(b);
			b->connectOnClicked(new ClassCallback1<DialogPanel, Button*>(this, &DialogPanel::onButtonClick));
		}
	}
	
	/**
	 * Connect to the response event.
	 *
	 * @param c The callback.
	*/
	void DialogPanel::connectOnResponse(ICallback1<int>* c) {
		fResponseEvent.connect(c);
	}
	
	/**
	 * Callback when one of the buttons is clicked.
	*/
	void DialogPanel::onButtonClick(Button* b) {
		fResponseEvent(fButtonResponseMap[b]);
	}
}
