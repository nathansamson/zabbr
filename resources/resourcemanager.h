#ifndef INC_RESOURCEMANAGER_H
#define INC_RESOURCEMANAGER_H

#include <map>

#include "resources/resource.h"
#include "resources/imageresource.h"
#include "resources/fontresource.h"
#include "resources/stringfontresource.h"

namespace Zabbr {

	class ResourceManager {
		public:
			static ResourceManager manager();
			
			void free(VResource* res);
			
			ImageResource* image(std::string);
			FontResource* font(std::string, int);
			StringFontResource* string(std::string, FontResource*, SDL_Color);
		private:
			ResourceManager();
			
			bool hasResource(std::string);
			void insertResource(std::string, VResource*);
			VResource* getResource(std::string);
			
			std::map<std::string, VResource*> fResourceList;
			static ResourceManager fgManager;
	};
}

#endif // INC_RESOURCEMANAGER_H
