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
	
	void ResourceManager::setImageFactory(IImageResourceFactory* imageFactory) {
		fImageFactory = imageFactory;
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
	IImageResource* ResourceManager::image(std::string fileName) {
		std::string id = IImageResource::createID(fileName);
		if (!hasResource(id)) {
			return (*fImageFactory)(fileName);
		} else {
			return static_cast<IImageResource*>(getResource(id));
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
	IImageResource* ResourceManager::image(std::string fileName, int width,
	                                      int height, bool keepRatio, int angle) {
		std::string id = IImageResource::createID(fileName, width, height, keepRatio, angle);
		if (!hasResource(id)) {
			IImageResource* res = image(fileName);
			IImageResource* scaled = res->scaleAndRotate(width, height, keepRatio, angle);
			free(res);
			insertResource(scaled->getName(), scaled);
			
			return scaled;
		} else {
			return static_cast<IImageResource*>(getResource(id));
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
