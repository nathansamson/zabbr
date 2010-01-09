#ifndef INC_IMAGERESOURCE_H
#define INC_IMAGERESOURCE_H

/** \file
 * File for images.
 *
 * @author Nathan Samson
*/

#include "resources/resource.h"

namespace Zabbr {

	/**
	 * An image resource.
	*/
	class IImageResource : public VResource {
	public:	
		IImageResource(std::string);
	
	
		virtual int getWidth() = 0;
		virtual int getHeight() = 0;
		virtual void draw(int, int) = 0;
		virtual IImageResource* scaleAndRotate(int, int, bool, int) = 0;
		
		static std::string createID(std::string);
		static std::string createID(std::string, int, int, bool, int);
	};
	
	class IImageResourceFactory {
	public:
		//virtual ~IImageResourceFactory() {};
		virtual IImageResource* operator()(std::string) = 0;
	};
}

#endif // INC_IMAGERESOURCE_H
