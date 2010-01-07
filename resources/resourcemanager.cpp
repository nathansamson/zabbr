/** \file
 * File for the resource manager.
 *
 * @author Nathan Samson
*/

#include "resources/resourcemanager.h"
#include <iostream>
namespace Zabbr {

	/**
	 * Private constructor.
	*/
	ResourceManager::ResourceManager(): fMaxCachedItems(100) {
	}

	ResourceManager::~ResourceManager() {
		for(std::map<std::string, VResource*>::iterator it = fResourceList.begin(); it != fResourceList.end(); it++) {
			if ((*it).second->fRefCount > 0) {
				std::cout << (*it).second->getName() << " Not freed." << std::endl;
			} else {
				delete (*it).second;
			}
		}
	}

	/**
	 * Free the resource manager.
	 * It is recommended that this is done only once, just before quit.
	 *
	*/
	void ResourceManager::free() {
		delete ResourceManager::fgManager;
		ResourceManager::fgManager = 0;
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
			fResourceCache.push_back(res);
			if (fResourceCache.size() > fMaxCachedItems) {
				VResource* deleted = fResourceCache.front();
				fResourceCache.pop_front();
				fResourceList.erase(deleted->getName());
				delete deleted;
			}
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
	
	#ifdef ENABLE_AUDIO
	/**
	 * Opens a small audio file.
	 *
	 * @param name The name of the audio file.
	 *
	 * @return The Audio file.
	*/
	SoundResource* ResourceManager::sound(std::string name) {
		std::string id = "audio_" + name;
		if (!hasResource(id)) {
			SoundResource* sound = SoundResource::open(name);
			insertResource(id, sound);
			
			return sound;
		} else {
			return static_cast<SoundResource*>(getResource(id));
		}
	}
	
	/**
	 * Opens a music file.
	 *
	 * @param name The name of the music file.
	 *
	 * @return The music file.
	*/
	MusicResource* ResourceManager::music(std::string name) {
		std::string id = "music_" + name;
		if (!hasResource(id)) {
			MusicResource* music = MusicResource::open(name);
			insertResource(id, music);
			
			return music;
		} else {
			return static_cast<MusicResource*>(getResource(id));
		}
	}
	#endif

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
		if (res->fRefCount == 0) {
			// Remove it from the cache list.
			for(std::list<VResource*>::iterator it = fResourceCache.begin(); it != fResourceCache.end(); it++) {
				if ((*it) == res) {
					fResourceCache.erase(it);
					break;
				}
			}
		}
		res->fRefCount++;
		return res;
	}
	
	ResourceManager* ResourceManager::fgManager = 0;
	std::string ResourceManager::fgDataPath = "";
}
