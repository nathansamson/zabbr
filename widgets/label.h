#ifndef INC_LABEL_H
#define INC_LABEL_H

/** \file
 * File for the label widget.
 *
 * @author Nathan Samson
*/

#include "SDL.h"

#include "widgets/widget.h"
#include "resources/stringfontresource.h"

namespace Zabbr {

	/**
	 * A Label widget.
	 *
	 * @ingroup Widgets
	*/
	class Label : public VWidget {
	public:
		Label(SDLWindow*, std::string, SDL_Color);
		Label(SDLWindow*, std::string, SDL_Color, std::string, int);
		virtual ~Label();

		virtual void draw(int, int);
		virtual int getWidth();
		virtual void setWidth(int);
		virtual int getHeight();
		virtual void setHeight(int);
	private:
		/**
		 * The allocated width. If 0 it is the default width of the label.
		*/
		int fWidth;
		
		/**
		 * The allocated height. If 0 it is the default height of the label.
		*/
		int fHeight;
		
		/**
		 * The internal label resource.
		*/
		StringFontResource* fLabel;
	};
}

#endif // INC_LABEL_H
