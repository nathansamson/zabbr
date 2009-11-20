#include "resources/resource.h"

#include <iostream>

namespace Zabbr {

	ResourceNotLoadedException::ResourceNotLoadedException(std::string id, std::string error)
                               : fResourceID(id), fError(error)	{
	}

	std::string ResourceNotLoadedException::getResourceID() {
		return fResourceID;
	}

	std::string ResourceNotLoadedException::getError() {
		return fError;
	}

	VResource::VResource(std::string name)
	          : fName(name), fRefCount(1) {
	}
	
	VResource::~VResource() {
	}

	std::string VResource::getName() {
		return fName;
	}
}
