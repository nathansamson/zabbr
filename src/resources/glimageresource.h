#ifndef INC_GLIMAGERESOURCE_H
#define INC_GLIMAGERESOURCE_H

/** \file
 * File for opengl texture.
 *
 * @author Nathan Samson
*/
#include <GL/gl.h>

#include "SDL.h"

#include "resources/imageresource.h"

namespace Zabbr {
	/**
	 * An image resource.
	*/
	class GLImageResource : public IImageResource {
	public:
		virtual ~GLImageResource();
		
		static GLImageResource* open(std::string);
		
		virtual int getWidth();
		virtual int getHeight();
		virtual void draw(int, int);
		virtual GLImageResource* scaleAndRotate(int, int, bool, int);
	private:
		GLuint fTexture;
		int fWidth;
		int fHeight;
		int fRotation;
	
		GLImageResource(std::string, GLuint, int, int, int);
	};
}

#endif // INC_GLIMAGERESOURCE_H
