#ifndef INC_RESOURCE_H
#define INC_RESOURCE_H

#include <string>

namespace Zabbr {

	class ResourceNotLoadedException {
	public:
		ResourceNotLoadedException(std::string, std::string);
		std::string getResourceID();
		std::string getError();
	private:
		std::string fResourceID;
		std::string fError;
	};

	class VResource {
	public:
		VResource(std::string);
		virtual ~VResource();

		friend class ResourceManager;

		std::string getName();
	private:
		VResource();

		std::string fName;
		int fRefCount;
	};
}

#endif // INC_RESOURE_H
