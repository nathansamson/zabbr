#ifndef INC_VBOX_H
#define INC_VBOX_H

/** \file
 * File for the vbox widget.
 *
 * @author Nathan Samson
*/

#include "widgets/box.h"

namespace Zabbr {
	/**
	 * A Vertical box. It places all widgets in one column.
	*/
	class VBox: public Box {
	public:
		VBox(SDLWindow*, bool, int);
		VBox(SDLWindow*, bool, int, YAlignment);
		VBox(SDLWindow*, bool, int, XAlignment, YAlignment);
		virtual ~VBox();
	
		virtual void draw(int, int);
	protected:
		virtual int requestedWidth();
		virtual int requestedHeight();
	};
}

#endif // INC_VBOX_H
