
#include "resources/resourcemanager.h"
#include <iostream>
namespace Zabbr {

	/**
	 * Private constructor.
	*/
	ResourceManager::ResourceManager() {
	}

	/**
	 * Returns the single ResourceManager instance.
	 *
	 * @return The unique resource manager.
	*/
	ResourceManager& ResourceManager::manager() {
		if (ResourceManager::fgManager == 0)
			ResourceManager::fgManager = new ResourceManager();
		return *ResourceManager::fgManager;
	}
	
	/**
	 * Free a resource. A resource will not be freed from memory when the
	 * their are still users of the resource.
	 * One can get a resource with the respective methods (image, font, ...) on this class.
	 *
	 * @param res The resource to free.
	*/
	void ResourceManager::free(VResource* res) {
		res->fRefCount--;
		
		if (res->fRefCount == 0) {
			fResourceList.erase(res->getName());
			delete res;
			res = NULL;
		}
	}
	
	/**
	 * Returns an image resource.
	 *
	 * @param fileName The filename of the image.
	 *
	 * @return The image.
	 *
	 * @throw ResourceNotLoadedExcpetion
	*/
	ImageResource* ResourceManager::image(std::string fileName) {
		std::string id = ImageResource::createID(fileName);
		if (!hasResource(id)) {
			ImageResource* res = ImageResource::open(fileName);
			insertResource(res->getName(), res);
			
			return res;
		} else {
			return static_cast<ImageResource*>(getResource(id));
		}
	}
	
	/**
	 * Returns an image resource. The image will be scaled and rotated.
	 *
	 * @param fileName The filename of the image.
	 * @param width The width of the image.
	 * @param height The height of the image.
	 * @param keepRatio True if to keep the aspect ratio of the original image.
	 *        It is possible that the width or height of the image will be less than the given values.
	 * @param angle The angle of the rotation (in degrees).
	 *
	 * @return The image.
	 *
	 * @throw ResourceNotLoadedExcpetion
	*/
	ImageResource* ResourceManager::image(std::string fileName, int width,
	                                      int height, bool keepRatio, int angle) {
		std::string id = ImageResource::createID(fileName, width, height, keepRatio, angle);
		if (!hasResource(id)) {
			ImageResource* res = image(fileName);
			ImageResource* scaled = res->scaleAndRotate(width, height, keepRatio, angle);
			free(res);
			insertResource(scaled->getName(), scaled);
			
			return scaled;
		} else {
			return static_cast<ImageResource*>(getResource(id));
		}
	}

	/**
	 * Opens a font.
	 *
	 * @param name The name of the font.
	 * @param ptSize The size of the font in points.
	 *
	 * @return The Font.
	 *
	 * @throw ResourceNotLoadedExcpetion
	*/
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

	/**
	 * Creates a string.
	 *
	 * @param text The text of the string.
	 * @param font The font.
	 * @param c The color of the font.
	 *
	 * @return The stringfont resource.
	*/
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

	/**
	 * Checks if a resource with a specific ID is still in memory.
	 *
	 * @param id The ID of the resource.
	 *
	 * @return True if the resource exists in memory. False if not.
	*/
	bool ResourceManager::hasResource(std::string id) {
		return fResourceList.find(id) != fResourceList.end();
	}
	
	/**
	 * Insert a resource in the list of resources.
	 *
	 * @param id The ID of the resource.
	 * @param res The resource to insert.
	*/
	void ResourceManager::insertResource(std::string id, VResource* res) {
		fResourceList[id] = res;
	}
	
	/**
	 * Get a resource with a given ID from the internal list of resources.
	 *
	 * @param id The ID of the resource.
	 *
	 * @return The resource.
	*/
	VResource* ResourceManager::getResource(std::string id) {
		VResource* res = fResourceList[id];
		res->fRefCount++;
		return res;
	}
	
	ResourceManager* ResourceManager::fgManager = 0;
	std::string ResourceManager::fgDataPath = "";
}
