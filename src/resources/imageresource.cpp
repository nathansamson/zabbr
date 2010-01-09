/** \file
 * File for the image resource.
 *
 * @author Nathan Samson
*/

#include <sstream>

#include "resources/resourcemanager.h"
#include "resources/imageresource.h"

namespace Zabbr {

	IImageResource::IImageResource(std::string id): VResource(id) {
	}

	/**
	 * Generates an ID for an Image resource.
	 *
	 * @param name The file name of the image.
	*/
	std::string IImageResource::createID(std::string name) {
		return name;
	}
	
	/**
	 * Generates an ID for an Image resource.
	 *
	 * @param name The ID of the original image
	 * @param w The width of the image.
	 * @param h The height of the image
	 * @param keepRatio value to keep the ratio.
	 * @param angle The angle of the rotation
	*/
	std::string IImageResource::createID(std::string name, int w, int h, bool keepRatio, int angle) {
		std::stringstream ssID;
		ssID  << "_" << w << "_"<< h;
		if (keepRatio) {
			ssID << "_KR";
		}
		ssID << "_" << angle;
		std::string id;
		ssID >> id;
		return name + id;
	}
}
