#ifndef INC_FONTPREFETCHER_H
#define INC_FONTPREFETCHER_H

/** \file
 * File for the font prefetcher.
 *
 * @author Nathan Samson
*/

#include <vector>

#include "misc/prefetcher.h"

namespace Zabbr {
	/**
	 * A prefetcher for fonts.
	*/
	class FontPrefetcher: public IPrefetcher {
	public:
		FontPrefetcher(std::string);
		void addFontSize(int);
		void addFont(std::string);
		
		virtual bool operator()();
		virtual std::string name();
	private:
		/**
		 * A list of all font sizes.
		*/
		std::vector<int> fFontSizes;
		
		/**
		 * The index of the current size.
		*/
		unsigned int fSizeIndex;
		
		/**
		 * A list of all fotn names.
		*/
		std::vector<std::string> fFontNames;
		
		/**
		 * The index of the current font.
		*/
		unsigned int fFontIndex;
		
		/**
		 * The name of the prefetcher.
		*/
		std::string fName;
	};
}

#endif // INC_FONTPREFETCHER_H
