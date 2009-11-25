#include "resources/resource.h"

#include <iostream>

namespace Zabbr {

	/**
	 * Constructor.
	 *
	 * @param id The ID of the resource.
	 * @param error The error string.
	*/
	ResourceNotLoadedException::ResourceNotLoadedException(std::string id, std::string error)
                               : fResourceID(id), fError(error)	{
	}

	/**
	 * Returns the ID of the resource.
	 *
	 * @return ID of the resource.
	*/
	std::string ResourceNotLoadedException::getResourceID() {
		return fResourceID;
	}

	/**
	 * Returns the error.
	 *
	 * @return The erorr. 
	*/
	std::string ResourceNotLoadedException::getError() {
		return fError;
	}

	/**
	 * Constructor.
	 *
	 * @param name The ID of the resource.
	*/
	VResource::VResource(std::string name)
	          : fName(name), fRefCount(1) {
	}
	
	/**
	 * Destructor.
	*/
	VResource::~VResource() {
	}

	/**
	 * Return the name of the resource.
	 *
	 * @return The ID of the resouce.
	*/
	std::string VResource::getName() {
		return fName;
	}
}
