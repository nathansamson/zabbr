#ifndef INC_COMBOBOX_H
#define INC_COMBOBOX_H

/** \file
 * File for the comboboxwidget.
 *
 * @author Nathan Samson
*/

#include <vector>

#include "widgets/hbox.h"
#include "widgets/button.h"
#include "widgets/label.h"

namespace Zabbr {
	template<typename T>
	class ComboBox: public HBox {
	public:
		/**
		 * Constructor.
		 *
		 * @param window The SDL window.
		*/
		ComboBox(SDLWindow* window): HBox(window, false, 20), fSelectedOption(-1),
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
		void addOption(T option) {
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
		T getSelectedOption() {
			return fOptions[fSelectedOption];
		}
	
		void setSelectedOption(T option) {
			int i = 0;
			typename std::vector<T>::iterator it;
			for(it = fOptions.begin(); it != fOptions.end(); it++, i++) {
				if ((*it) == option) {
					setOption(i);
					return;
				}
			}
		}
	
	private:
		/**
		 * Set the index of the current option.
		 *
		 * @param option The index of the option, this will correctly wrap around.
		*/
		void setOption(int option) {
			if (option >= (int)fOptions.size()) {
				option = 0;
			} else if (option < 0) {
				option = fOptions.size() - 1;
			}
			fSelectedOption = option;
			fLabel->setLabel(static_cast<std::string>(fOptions[option]));
		}
		
		/**
		 * Callback when clicked on the up/down buttons.
		 *
		 * @param button The clicked button.
		*/	
		void onWheelButtonClicked(Button* button) {
			if (button == fUpButton) {
				fSelectedOption++;
			} else {
				fSelectedOption--;
			}
			setOption(fSelectedOption);
		}
	
		/**
		 * A list of options.
		*/
		std::vector<T> fOptions;
		
		/**
		 * The index of the selected options, a negative number is nothing selected.
		*/
		int fSelectedOption;
	
		/**
		 * The label used to print the active option.
		*/
		Label* fLabel;
		
		/**
		 * The up button.
		*/
		Button* fUpButton;
		
		/**
		 * The down button.
		*/
		Button* fDownButton;
	};
}

#endif // INC_COMBOBOX_H
