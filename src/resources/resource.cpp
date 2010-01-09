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
 * File for the resource.
 *
 * @author Nathan Samson
*/

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
