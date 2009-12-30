#include "widgets/combobox.h"
#include "widgets/vbox.h"

namespace Zabbr {
	/**
	 * Constructor.
	 *
	 * @param window The SDL window.
	*/
	ComboBox::ComboBox(SDLWindow* window): HBox(window, false, 20), fSelectedOption(-1),
	          fUpButton(new Button(fWindow, "+")), fDownButton(new Button(fWindow, "-")) {

		SDL_Color white = {255, 255, 255};
		fLabel = new Label(fWindow, "", white);
		appendWidget(fLabel);
		VBox* buttonVBox = new VBox(fWindow, true, 0);
		buttonVBox->appendWidget(fUpButton);
		buttonVBox->appendWidget(fDownButton);
		appendWidget(buttonVBox);
		
		fUpButton->connectOnClicked(new ClassCallback1<ComboBox, Button*>(this, &ComboBox::onWheelButtonClicked));
		fDownButton->connectOnClicked(new ClassCallback1<ComboBox, Button*>(this, &ComboBox::onWheelButtonClicked));
	}
	
	/**
	 * Add an option to the comboxbox.
	 *
	 * @param option The option.
	*/
	void ComboBox::addOption(std::string option) {
		fOptions.push_back(option);
		if (fSelectedOption < 0) {
			setOption(0);
		}
	}
	
	/**
	 * The current selected option.
	 *
	 * @return The selection option.
	*/
	std::string ComboBox::getSelectedOption() {
		return fOptions[fSelectedOption];
	}
	
	/**
	 * Set the index of the current option.
	 *
	 * @param option The index of the option, this will correctly wrap around.
	*/
	void ComboBox::setOption(int option) {
		if (option >= (int)fOptions.size()) {
			option = 0;
		} else if (option < 0) {
			option = fOptions.size() - 1;
		}
		fSelectedOption = option;
		fLabel->setLabel(fOptions[option]);
	}

	/**
	 * Callback when clicked on the up/down buttons.
	 *
	 * @param button The clicked button.
	*/	
	void ComboBox::onWheelButtonClicked(Button* button) {
		if (button == fUpButton) {
			fSelectedOption++;
		} else {
			fSelectedOption--;
		}
		setOption(fSelectedOption);
	}
}
