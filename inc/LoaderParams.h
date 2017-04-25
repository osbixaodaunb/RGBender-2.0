#ifndef LOADER_PARAMS_H
#define LOADER_PARAMS_H

#include <string>

class LoaderParams{
public:
	LoaderParams(int x, int y, int width, int height, std::string textureID) : m_x(x), m_y(y), m_width(width), m_height(height), m_textureID(textureID), m_numFrames(0){}
	
	LoaderParams(int x, int y, int width, int height, std::string textureID, int numFrames) : m_x(x), m_y(y), m_width(width), m_height(height), m_textureID(textureID), m_numFrames(numFrames) {}


	int getX() const {
		return m_x;
	}

	int getY() const {
		return m_y;
	}

	int getWidth() const {
		return m_width;
	}

	int getHeight() const {
		return m_height;
	}

	std::string getTextureID() const {
		return m_textureID;
	}

	int getNumFrames() const{
		return m_numFrames;
	}

private:
	int m_x;
	int m_y;

	int m_width;
	int m_height;

	int m_numFrames;

	std::string m_textureID;
};

#endif
