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
	class ComboBox: public HBox {
	public:
		ComboBox(SDLWindow*);
		
		void addOption(std::string);
		std::string getSelectedOption();
		void setSelectedOption(std::string);
	
	private:
		void setOption(int);
		void onWheelButtonClicked(Button*);
	
		/**
		 * A list of options.
		*/
		std::vector<std::string> fOptions;
		
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
