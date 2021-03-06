#ifndef INC_HBOX_H
#define INC_HBOX_H

/** \file
 * File for the hbox widget.
 *
 * @author Nathan Samson
*/

#include "widgets/box.h"

namespace Zabbr {
	/**
	 * A Horizontal box. It places all widgets in one row.
	*/
	class HBox: public Box {
	public:
		HBox(Window*, bool, int);
		HBox(Window*, bool, int, XAlignment);
		virtual ~HBox();
	
		virtual void draw(int, int);
	protected:
		virtual int requestedWidth();
		virtual int requestedHeight();
	};
}

#endif // INC_HBOX_H
