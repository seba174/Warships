#include "stdafx.h"
#include "TextureHandler.h"


using std::make_pair;


void TextureHandler::addElement(const std::string & textureName, const std::string & texturePath, TextureHandler& instance)
{
	const std::string error_message("Failed to load textures!");
	sf::Texture tmp;

	if (!tmp.loadFromFile(texturePath))
		std::cerr << error_message << std::endl;
	else
	{
		instance.texture_handler.emplace(textureName, tmp);
	}
}

TextureHandler & TextureHandler::getInstance()
{
	// The only instance
	// Guaranteed to be lazy initialized
	// Guaranteed that it will be destroyed correctly
	static TextureHandler instance;

	static bool initialize = true;

	if (initialize)
	{
		instance.initializationInfo.emplace("menuTexture0", "Textures/warshipsMenuSG10.jpg");
		instance.initializationInfo.emplace("menuTexture1", "Textures/warshipsMenuSG5.png");
		instance.initializationInfo.emplace("menuTexture2", "Textures/warshipsMenuSG8.png");
		instance.initializationInfo.emplace("mapTexture8x8", "Textures/mapTexture8x8C.png");
		instance.initializationInfo.emplace("mapTexture10x10", "Textures/mapTexture10x10C.png");
		instance.initializationInfo.emplace("mapTexture12x12", "Textures/mapTexture12x12C.png");

		addElement("big_body_final", "Textures/big_body_finalC.png", instance);
		addElement("big_body_final_destroyed", "Textures/big_body_final_destroyedC.png", instance);
		addElement("irregular2", "Textures/irregular2NewFinalC.png", instance);
		addElement("irregular3", "Textures/irregular3_final_v2C.png", instance);
		addElement("irregular3_destroyed", "Textures/irregular3FinalDestroyedC.png", instance);
		addElement("buttonFrame", "Textures/buttonFrameC.png", instance);
		addElement("rightarrow", "Textures/rightArrowOutlinedC.png", instance);
		addElement("leftarrow", "Textures/leftArrowOutlinedC.png", instance);
		addElement("big_body_no_waves", "Textures/big_body_no_wavesC.png", instance);
		addElement("irregular3_no_waves", "Textures/irregular3_no_wavesC.png", instance);
		addElement("irregular2_no_waves", "Textures/irregular2NewNoWavesC.png", instance);
		addElement("irregular2_destroyed", "Textures/irregular2NewDestroyedFinalC.png", instance);
		addElement("X", "Textures/X.png", instance);
		addElement("fire5", "Textures/fire5C.png", instance);
		addElement("buttonInterior", "Textures/buttonInteriorC.png", instance);
		addElement("logo", "Textures/logoSGC.png", instance);
		addElement("cup", "Textures/trophyGold.png", instance);
		addElement("star", "Textures/star2.png", instance);
		addElement("crosshair", "Textures/crosshair2.png", instance);
		addElement("helpButton", "Textures/helpButton.png", instance);

		initialize = false;
	}
	return instance;
}

void TextureHandler::setSmooth(bool shouldSet)
{
	for (auto& el : TextureHandler::getInstance().texture_handler)
	{
		el.second.setSmooth(shouldSet);
	}
}

sf::Texture& TextureHandler::getTextureWithInitialization(const std::string& textureName)
{
	TextureHandler& handler = getInstance();
	// quit if texture is already present
	if (handler.texture_handler.find(textureName) != handler.texture_handler.end())
		return handler.texture_handler[textureName];

	std::string texturePath{ handler.initializationInfo[textureName] };
	addElement(textureName, texturePath, handler);

	return handler.texture_handler[textureName];
}


