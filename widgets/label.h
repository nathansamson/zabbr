#ifndef INC_LABEL_H
#define INC_LABEL_H

#include "SDL.h"

#include "widgets/widget.h"
#include "widgets/label.h"
#include "resources/stringfontresource.h"

namespace Zabbr {

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
		int fWidth;
		int fHeight;
		StringFontResource* fLabel;
	};
}

#endif // INC_LABEL_H