#ifndef INC_LABEL_H
#define INC_LABEL_H

/** \file
 * File for the label widget.
 *
 * @author Nathan Samson
*/

#include "SDL.h"

#include "widgets/widget.h"
#include "resources/fontresource.h"

namespace Zabbr {

	const int FONTSIZE_BIG = 32;
	const int FONTSIZE_MEDIUM = 24;
	const int FONTSIZE_NORMAL = 20;
	const int FONTSIZE_SMALL = 16;

	/**
	 * A Label widget.
	 *
	 * @ingroup Widgets
	*/
	class Label : public VWidget {
	public:
		Label(SDLWindow*, std::string, SDL_Color, int = FONTSIZE_NORMAL, std::string = "DejaVuSans-Bold.ttf");
		virtual ~Label();
		
		void setLabel(std::string);
		void setColor(SDL_Color);

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
		 * The internal label surface.
		*/
		SDL_Surface* fLabel;
		
		/**
		 * The text of the label.
		*/
		std::string fLabelString;
		
		/**
		 * The color of the label.
		*/
		SDL_Color fColor;
		
		/**
		 * The font of the label.
		*/
		FontResource* fFont;
	};
}

#endif // INC_LABEL_H
