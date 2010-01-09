/* Copyright (c) 2009, Nathan Samson <nathansamson[at]gmail[dot]com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, 
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of the zabbr-community nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
*/

/** \file
 * File for the Table widget
 *
 * @author Nathan Samson
*/

#include "widgets/table.h"

namespace Zabbr {
	/**
	 * Constructor.
	 *
	 * @param w The Window.
	 * @param xSpacing The spacing between cells on one row.
	 * @param ySpacing The spacing betwene cells in one column.
	 * @param rows The number of rows.
	 * @param columns The number of columns.
	*/
	Table::Table(Window* w, int xSpacing, int ySpacing,
	             int rows, int columns): VWidget(w), fXSpacing(xSpacing), fYSpacing(ySpacing) {
		fDimension.width = 0;
		fDimension.height = 0;
		for (int row = 0; row < rows; row++) {
			WidgetRow widgets;
			for (int column = 0; column < columns; column++) {
				widgets.push_back(0);
			}
			fWidgets.push_back(widgets);
		}
	}
	
	Table::~Table() {
		for(WidgetTable::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			for(WidgetRow::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++) {
				if ((*it2) != 0) delete (*it2);
			}
		}
	}
	
	/**
	 * Draws the widget.
	 *
	 * @param x The X coordinate
	 * @param y The Y coordinate.
	*/
	void Table::draw(int x, int y) {
		int row = 0;
		for(WidgetTable::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			int rowX = x;
			int column = 0;
			for(WidgetRow::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++) {
				if ((*it2) != 0) {
					(*it2)->draw(rowX, y);
				}
				rowX += getColumnWidth(column) + fXSpacing;
				column++;
			}
			y += getRowHeight(row) + fYSpacing;
			row++;
		}
	}
	
	/**
	 * Adds a widget to a specified location in the table.
	 *
	 * @param widget The widget to add.
	 * @param row The row of the widget.
	 * @param column The column of the widget.
	*/
	void Table::setWidget(VWidget* widget, int row, int column) {
		fWidgets[row][column] = widget;
	}
	
	/**
	 * Returns the width of the table.
	 *
	 * @return The width of the table.
	*/
	int Table::getWidth() {
		if (fDimension.width == 0) {
			return requestedWidth();
		} else {
			return fDimension.width;
		}
	}
	
	/**
	 * Sets the width of the table.
	 *
	 * @param width The new width of the table.
	*/
	void Table::setWidth(int width) {
		fDimension.width = width;
	}
	
	/**
	 * Returns the height of the table.
	 *
	 * @return the height of the table.
	*/
	int Table::getHeight() {
		if (fDimension.height == 0) {
			return requestedHeight();
		} else {
			return fDimension.height;
		}
	}
	
	/**
	 * Set the height of the table.
	 *
	 * @param height The new height of the table.
	*/
	void Table::setHeight(int height) {
		fDimension.height = height;
	}
	
	/**
	 * Function called when a key is pressed.
	 *
	 * @param event The SDL Keyboard event.
	*/
	void Table::keyPress(SDL_KeyboardEvent event) {
		for(WidgetTable::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			for(WidgetRow::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++) {
				if ((*it2) != 0) (*it2)->keyPress(event);
			}
		}
	}
	
	/**
	 * Function called when a key is release.
	 *
	 * @param event The SDL Keyboard event.
	*/
	void Table::keyRelease(SDL_KeyboardEvent event) {
		for(WidgetTable::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			for(WidgetRow::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++) {
				if ((*it2) != 0) (*it2)->keyRelease(event);
			}
		}
	}

	/**
	 * Function called when the mouse moves.
	 *
	 * @param event The SDL Mouse Motion event.
	*/
	void Table::mouseMotion(SDL_MouseMotionEvent event) {
		for(WidgetTable::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			for(WidgetRow::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++) {
				if ((*it2) != 0) (*it2)->mouseMotion(event);
			}
		}
	}

	/**
	 * Function called when a mouse button event is generated.
	 *
	 * @param event The SDL Mouse Button event.
	*/
	void Table::mouseButton(SDL_MouseButtonEvent event) {
		for(WidgetTable::iterator it = fWidgets.begin(); it != fWidgets.end(); it++) {
			for(WidgetRow::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++) {
				if ((*it2) != 0) (*it2)->mouseButton(event);
			}
		}
	}
	
	/**
	 * The requested width of the table.
	 *
	 * @return the requested width of the table.
	*/
	int Table::requestedWidth() {
		int width = 0;
		for (unsigned int i = 0; i < fWidgets[0].size(); i++) {
			width += getColumnWidth(i);
		}
		return width + fWidgets[0].size() * fXSpacing;
	}
	
	/**
	 * The requested height of the table.
	 *
	 * @return the requested height of the table.
	*/
	int Table::requestedHeight() {
		int height = 0;
		for (unsigned int i = 0; i < fWidgets.size(); i++) {
			height += getRowHeight(i);
		}
		return height + fWidgets.size() * fYSpacing;;
	}
	
	/**
	 * The requested height of one row.
	 *
	 * @param row The index of the row.
	 *
	 * @return the requested height of the row.
	*/
	int Table::getRowHeight(int row) {
		int height = 0;
		for (unsigned int i = 0; i < fWidgets[row].size(); i++) {
			height = std::max(height, fWidgets[row][i]->getHeight());
		}
		return height;
	}
	
	/**
	 * The requested width of one column.
	 *
	 * @param row The index of the column.
	 *
	 * @return the requested width of the column.
	*/
	int Table::getColumnWidth(int column) {
		int width = 0;
		for(unsigned int i = 0; i < fWidgets.size(); i++) {
			if (fWidgets[i][column] != 0) {
				width = std::max(width, fWidgets[i][column]->getWidth());
			}
		}
		return width;
	}
}
