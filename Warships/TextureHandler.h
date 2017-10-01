#pragma once

class TextureHandler
{
private:
	
	// Private Constructor
	TextureHandler() {};
	
	// Stop the compiler generating methods of copy the object
	TextureHandler(TextureHandler const& copy) = delete;            // Not Implemented
	TextureHandler& operator=(TextureHandler const& copy) = delete; // Not Implemented

	static void addElement(const std::string& textureName, const std::string& texturePath, TextureHandler& instance);

	std::map<std::string, std::string> initializationInfo;

public:
	
	// returnsTHE ONLY EXISTING object for handling Textures
	// textures_handler field is made public for getting textures
	// e.g texture_handler["texture_name"] returns reference to the texture!
	static TextureHandler& getInstance();

	std::map<std::string, sf::Texture> texture_handler;

	static void setSmooth(bool shouldSet);

	static sf::Texture& getTextureWithInitialization(const std::string& textureName);
};