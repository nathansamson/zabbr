#ifndef INC_RESOURCEMANAGER_H
#define INC_RESOURCEMANAGER_H

/** \file
 * File for the resource manager.
 *
 * @author Nathan Samson
*/

#include <map>
#include <list>

#include "resources/resource.h"
#include "resources/imageresource.h"
#include "resources/fontresource.h"
#ifdef ENABLE_AUDIO
#include "resources/soundresource.h"
#include "resources/musicresource.h"
#endif

namespace Zabbr {

	/**
	 * ResourceManager.
	*/
	class ResourceManager {
		public:
			ResourceManager();
			static void free();
			static ResourceManager& manager();
			~ResourceManager();
			
			void free(VResource* res);
				
			void setImageFactory(IImageResourceFactory*);
			IImageResource* image(std::string);
			IImageResource* image(std::string, int, int, bool, int);
			FontResource* font(std::string, int);
			#ifdef ENABLE_AUDIO
			SoundResource* sound(std::string);
			MusicResource* music(std::string);
			#endif
			
			/**
			 * The datapath.
			*/
			static std::string fgDataPath;
		private:
			bool hasResource(std::string);
			void insertResource(std::string, VResource*);
			VResource* getResource(std::string);
			
			/**
			 * A map of all resources.
			*/
			std::map<std::string, VResource*> fResourceList;
			
			/**
			 * A cache of unused resources, but still in the cache.
			 * This list is ordered on least-recently used first.
			*/
			std::list<VResource*> fResourceCache;
			
			IImageResourceFactory* fImageFactory;
			
			/**
			 * The maximum number of cached items.
			*/
			unsigned int fMaxCachedItems;
			
			/**
			 * The singleton ResourceManager.
			*/
			static ResourceManager* fgManager;
	};
}

#endif // INC_RESOURCEMANAGER_H
