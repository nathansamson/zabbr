#ifndef INC_TEXTINPUT_H
#define INC_TEXTINPUT_H

#include <string>
#include "widgets/widget.h"
#include "resources/resourcemanager.h"

namespace Zabbr {
	class TextInputWidget: public VWidget {
	public:
		TextInputWidget(SDLWindow*, std::string);
		virtual ~TextInputWidget();
		
		virtual void draw(int, int);
		virtual int getWidth();
		virtual void setWidth(int);
		virtual int getHeight();
		virtual void setHeight(int);
		
		virtual void keyRelease(SDL_KeyboardEvent);
	private:
		FontResource* fFont;
		StringFontResource* fStringResource;
		std::string fText;
		
		int fWidth;
		int fHeight;
		
		bool fTextUpdated;
	};
}

#endif // INC_TEXTINPUT_H
