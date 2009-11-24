
#include "resources/resourcemanager.h"
#include <iostream>
namespace Zabbr {

	ResourceManager::ResourceManager() {
	}

	ResourceManager& ResourceManager::manager() {
		if (ResourceManager::fgManager == 0)
			ResourceManager::fgManager = new ResourceManager();
		return *ResourceManager::fgManager;
	}
	
	void ResourceManager::free(VResource* res) {
		res->fRefCount--;
		
		if (res->fRefCount == 0) {
			fResourceList.erase(res->getName());
			delete res;
			res = NULL;
		}
	}
	
	ImageResource* ResourceManager::image(std::string fileName) {
		if (!hasResource(fileName)) {
			ImageResource* res = ImageResource::open(fileName);
			insertResource(fileName, res);
			
			return res;
		} else {
			return static_cast<ImageResource*>(getResource(fileName));
		}
	}

	FontResource* ResourceManager::font(std::string name, int ptSize) {
		std::string fontID = FontResource::getID(name, ptSize);
		if (!hasResource(fontID)) {
			FontResource* font = FontResource::open(name, ptSize);
			insertResource(fontID, font);
			
			return font;
		} else {
			return static_cast<FontResource*>(getResource(fontID));
		}
	}

	StringFontResource* ResourceManager::string(std::string text, FontResource* font, SDL_Color c) {
		std::string stringFontID = StringFontResource::getID(text, font, c);
		if (!hasResource(stringFontID)) {
			StringFontResource* stringFont = new StringFontResource(font->string(text, c), stringFontID);
			insertResource(stringFontID, stringFont);

			return stringFont;
		} else {
			return static_cast<StringFontResource*>(getResource(stringFontID));
		}
	}

	bool ResourceManager::hasResource(std::string id) {
		return fResourceList.find(id) != fResourceList.end();
	}
	
	void ResourceManager::insertResource(std::string id, VResource* res) {
		fResourceList[id] = res;
	}
	
	VResource* ResourceManager::getResource(std::string id) {
		VResource* res = fResourceList[id];
		res->fRefCount++;
		return res;
	}
	
	ResourceManager* ResourceManager::fgManager = 0;
}
