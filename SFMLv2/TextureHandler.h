#pragma once
#include <SFML/Graphics.hpp>
#include <map>

 
class TextureHandler
{
private:
	
	// Private Constructor
	TextureHandler();
	
	// Stop the compiler generating methods of copy the object
	TextureHandler(TextureHandler const& copy) = delete;            // Not Implemented
	TextureHandler& operator=(TextureHandler const& copy) = delete; // Not Implemented

public:
	
	// returns the ONLY EXISTING object for handling Textures
	// textures_handler field is made public for getting textures
	// e.g texture_handler["texture_name"] returns REFERENCE to the texture!
	static TextureHandler& getInstance();

	std::map<std::string, sf::Texture> texture_handler;
};