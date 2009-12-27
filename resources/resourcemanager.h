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
				
			ImageResource* image(std::string);
			ImageResource* image(std::string, int, int, bool, int);
			FontResource* font(std::string, int);
			
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
