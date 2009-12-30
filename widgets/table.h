#ifndef INC_TABLE_H
#define INC_TABLE_H

/** \file
 * File for the Table widget.
 *
 * @author Nathan Samson
*/

#include <vector>

#include "widgets/widget.h"

namespace Zabbr {

	/**
	 * A table is a widget that can store widgets in a tabular/matrix layout.
	*/
	class Table: public VWidget {
	public:
		Table(SDLWindow*, int, int, int, int);
		virtual ~Table();
		
		void setWidget(VWidget*, int, int);
		
		virtual void draw(int, int);
		
		virtual int getWidth();
		virtual void setWidth(int);
		virtual int getHeight();
		virtual void setHeight(int);
		
		virtual void mouseMotion(SDL_MouseMotionEvent);
		virtual void mouseButton(SDL_MouseButtonEvent);
		virtual void keyPress(SDL_KeyboardEvent);
		virtual void keyRelease(SDL_KeyboardEvent);
	
	private:
		typedef std::vector<VWidget*> WidgetRow;
		typedef std::vector<WidgetRow> WidgetTable;
	
		/**
		 * A matrix of widgets
		*/
		WidgetTable fWidgets;
		
		/**
		 * A dimension struct.
		*/
		struct Dimension {
			/**
			 * Width
			*/
			int width;
			
			/**
			 * Height 
			*/
			int height;
		} fDimension;
	
		int requestedWidth();
		int requestedHeight();
		
		int getRowHeight(int);
		int getColumnWidth(int);
		
		/**
		 * The spacing between cells in one row.
		*/
		int fXSpacing;
		
		/**
		 * The spacing between cells in one column.
		*/
		int fYSpacing;
	};
}

#endif // INC_TABLE_H
