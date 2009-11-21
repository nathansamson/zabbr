#ifndef INC_LABEL_H
#define INC_LABEL_H

#include "SDL.h"

#include "widgets/widget.h"
#include "widgets/label.h"
#include "resources/stringfontresource.h"

namespace Zabbr {

	/**
	 * A label widget.
	 *
	 * @ingroup Widgets.
	*/
	class Label : public VWidget {
	public:
		Label(SDLWindow*, std::string, SDL_Color);
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
