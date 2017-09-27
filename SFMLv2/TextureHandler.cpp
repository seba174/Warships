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
		instance.texture_handler.insert(make_pair(textureName, tmp));
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
		addElement("mapTexture8x8", "Textures/mapTexture8x8.png", instance);
		addElement("mapTexture10x10", "Textures/mapTexture10x10.png", instance);
		addElement("mapTexture12x12", "Textures/mapTexture12x12.png", instance);
		addElement("big_body_final", "Textures/big_body_final.png", instance);
		addElement("big_body_final_destroyed", "Textures/big_body_final_destroyed.png", instance);
		addElement("irregular2", "Textures/irregular2NewFinal.png", instance);
		addElement("irregular3", "Textures/irregular3_final_v2.png", instance);
		addElement("irregular3_destroyed", "Textures/irregular3FinalDestroyed.png", instance);
		addElement("buttonFrame", "Textures/buttonFrame.png", instance);
		addElement("rightarrow", "Textures/rightArrowOutlined.png", instance);
		addElement("leftarrow", "Textures/leftArrowOutlined.png", instance);
		addElement("big_body_no_waves", "Textures/big_body_no_waves.png", instance);
		addElement("irregular3_no_waves", "Textures/irregular3_no_waves.png", instance);
		addElement("irregular2_no_waves", "Textures/irregular2NewNoWaves.png", instance);
		addElement("irregular2_destroyed", "Textures/irregular2NewDestroyedFinal.png", instance);
		addElement("X", "Textures/X.png", instance);
		addElement("fire5", "Textures/fire5.png", instance);
		//2
		addElement("menuTexture0", "Textures/warshipsMenuSG10.jpg", instance);
		addElement("menuTexture1", "Textures/warshipsMenuSG5.png", instance);
		addElement("menuTexture2", "Textures/warshipsMenuSG8.png", instance);
		addElement("buttonInterior", "Textures/buttonInterior.png", instance);
		addElement("logo", "Textures/logoSG.png", instance);
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


