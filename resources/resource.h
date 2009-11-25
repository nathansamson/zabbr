#ifndef INC_RESOURCE_H
#define INC_RESOURCE_H

#include <string>

namespace Zabbr {

	/**
	 * Exception for load errors of resources.
	*/
	class ResourceNotLoadedException {
	public:
		ResourceNotLoadedException(std::string, std::string);
		std::string getResourceID();
		std::string getError();
	private:
		/**
		 * The ID of the resource that was not loaded.
		*/
		std::string fResourceID;
		
		/**
		 * The reason why the resource could not load.
		*/
		std::string fError;
	};

	/**
	 * Base class for all resources.
	*/
	class VResource {
	public:
		VResource(std::string);
		virtual ~VResource();

		friend class ResourceManager;

		std::string getName();
	private:
		VResource();

		/**
		 * The name/ID of the resource.
		*/
		std::string fName;
		
		/**
		 * The number of users that uses this resource.
		*/
		int fRefCount;
	};
}

#endif // INC_RESOURE_H
