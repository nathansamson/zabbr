#ifndef INC_TEXTINPUT_H
#define INC_TEXTINPUT_H

/** \file
 * File for the text input widget.
 *
 * @author Nathan Samson
*/

#include <string>
#include "widgets/widget.h"
#include "resources/resourcemanager.h"

namespace Zabbr {
	/**
	 * Text input widget.
	 *
	 * @ingroup Widgets
	*/
	class TextInputWidget: public VWidget {
	public:
		TextInputWidget(SDLWindow*, std::string);
		virtual ~TextInputWidget();
		
		virtual void draw(int, int);
		virtual int getWidth();
		virtual void setWidth(int);
		virtual int getHeight();
		virtual void setHeight(int);
		std::string getValue();
		
		virtual void keyRelease(SDL_KeyboardEvent);
	private:
		/**
		 * The font of the text.
		*/
		FontResource* fFont;
		
		/**
		 * The current string resource.
		*/
		StringFontResource* fStringResource;
		
		/**
		 * The current text value.
		*/
		std::string fText;
		
		/**
		 * The width of the widget.
		*/
		int fWidth;
		
		/**
		 * The height of the widget.
		*/
		int fHeight;
		
		/**
		 * Boolean to keep state if the text is updated between 2 draws.
		*/
		bool fTextUpdated;
	};
}

#endif // INC_TEXTINPUT_H
