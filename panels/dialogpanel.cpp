#include "panels/dialogpanel.h"

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
	             MenuPanel(w) {
		SDL_Color white = {255, 255, 255};
		fQuestionLabel = new Label(fWindow, question, white, "DejaVuSans-Bold.ttf", 24);
		addWidget(fQuestionLabel);
		
		for(std::vector<std::pair<int, std::string> >::iterator it = responseIDMap.begin(); it != responseIDMap.end(); it++) {
			Button* b = new Button(fWindow, (*it).second);
			fButtonResponseMap[b] = (*it).first;
			fButtons.push_back(b);
			addWidget(b);
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
	 * Draw the panel
	*/
	void DialogPanel::draw() {
		if (fParentPanel) {
			fParentPanel->draw();
		}
		
		fQuestionLabel->draw(fWindow->getXResolution() / 2 - fQuestionLabel->getWidth(),
		                     fWindow->getYResolution() / 2 - fQuestionLabel->getHeight() - 5);
		
		
		int totalWidth = -10;
		for(std::vector<Button*>::iterator it = fButtons.begin(); it != fButtons.end(); it++) {
			totalWidth += (*it)->getWidth() + 10;
		}
		
		int x = (fWindow->getXResolution() - totalWidth) / 2;
		for(std::vector<Button*>::iterator it = fButtons.begin(); it != fButtons.end(); it++) {
			(*it)->draw(x, fWindow->getYResolution() / 2 + 5);
			x += (*it)->getWidth() + 10;
		}
	}
	
	/**
	 * Callback when one of the buttons is clicked.
	*/
	void DialogPanel::onButtonClick(Button* b) {
		fResponseEvent(fButtonResponseMap[b]);
	}
}
