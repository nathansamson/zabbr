#include <iostream>

#include "misc/fontprefetcher.h"
#include "resources/resourcemanager.h"

namespace Zabbr {
	/**
	 * Constructor.
	 *
	 * @param name The status text of the prefetcher.
	*/
	FontPrefetcher::FontPrefetcher(std::string name):
	                fSizeIndex(0),
	                fFontIndex(0),
	                fName(name) {
	}
	
	/**
	 * Add a font size to the prefetch list.
	 *
	 * @param size The size for the fonts.
	*/
	void FontPrefetcher::addFontSize(int size) {
		fFontSizes.push_back(size);
	}
	
	/**
	 * Add a font to the prefetch list.
	 *
	 * @param font The path to the font ttf file.
	*/
	void FontPrefetcher::addFont(std::string font) {
		fFontNames.push_back(font);
	}
	
	/**
	 * Run a part of the prefetcher.
	 *
	 * @return True if done prefetching, false if not.
	*/
	bool FontPrefetcher::operator()() {
		if (fFontIndex >= fFontNames.size() && fSizeIndex >= fFontSizes.size()) {
			return true;
		}
		
		FontResource* f = ResourceManager::manager().font(fFontNames[fFontIndex], fFontSizes[fSizeIndex]);
		ResourceManager::manager().free(f);
		fSizeIndex++;
		if (fSizeIndex == fFontSizes.size()) {
			fSizeIndex = 0;
			fFontIndex++;
		}
		if (fFontIndex == fFontNames.size()) {
			return true;
		} else {
			return false;
		}
	}
	
	/**
	 * Returns the name of the prefetcher.
	 *
	 * @return The name of the prefetcher.
	*/
	std::string FontPrefetcher::name() {
		return fName;
	}
}
