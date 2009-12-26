#ifndef INC_RESOURCEMANAGER_H
#define INC_RESOURCEMANAGER_H

/** \file
 * File for the resource manager.
 *
 * @author Nathan Samson
*/

#include <map>

#include "resources/resource.h"
#include "resources/imageresource.h"
#include "resources/fontresource.h"
#include "resources/stringfontresource.h"

namespace Zabbr {

	/**
	 * ResourceManager.
	*/
	class ResourceManager {
		public:
			static ResourceManager& manager();
			
			void free(VResource* res);
				
			ImageResource* image(std::string);
			ImageResource* image(std::string, int, int, bool, int);
			FontResource* font(std::string, int);
			StringFontResource* string(std::string, FontResource*, SDL_Color);
			
			/**
			 * The datapath.
			*/
			static std::string fgDataPath;
		private:
			ResourceManager();
			
			bool hasResource(std::string);
			void insertResource(std::string, VResource*);
			VResource* getResource(std::string);
			
			/**
			 * A map of all resources.
			*/
			std::map<std::string, VResource*> fResourceList;
			
			/**
			 * The singleton ResourceManager.
			*/
			static ResourceManager* fgManager;
	};
}

#endif // INC_RESOURCEMANAGER_H
