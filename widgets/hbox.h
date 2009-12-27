#ifndef INC_HBOX_H
#define INC_HBOX_H

#include "widgets/box.h"

namespace Zabbr {
	/**
	 * A Horizontal box. It places all widgets in one row.
	*/
	class HBox: public Box {
	public:
		HBox(SDLWindow*, bool, int);
		HBox(SDLWindow*, bool, int, XAlignment);
		virtual ~HBox();
	
		virtual void draw(int, int);
	protected:
		virtual int requestedWidth();
		virtual int requestedHeight();
	};
}

#endif // INC_HBOX_H
