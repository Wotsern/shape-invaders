#include "Settings.h"
#include "TextureHandler.h"
#include <SFML/System/String.hpp>

TextureHandler::TextureHandler()
{
	
}

TextureHandler::~TextureHandler()
{
	// Safe delete all texture pointers.
	for (auto texturePointer : m_Texture)
	{
		delete texturePointer.second;
		texturePointer.second = nullptr;
	}
}

// Function called to load the textures stored within the projects assets folder.
void TextureHandler::loadTexture(TextureType textureName, const sf::String& textureFile)
{
	m_Texture[textureName] = new sf::Texture();
	m_Texture[textureName]->loadFromFile(textureFile);
}

// Load all the textures ready to be accessed throughout the game.
void TextureHandler::initialise()
{	
	loadTexture(TextureType::Player,					SpritePaths::c_playerSprite);
	loadTexture(TextureType::PlayerProjectile,			SpritePaths::c_projectilePlayer);
	loadTexture(TextureType::PlayerParticle,			SpritePaths::c_playerParticle);
	loadTexture(TextureType::CircleProjectile,			SpritePaths::c_projectileCircle);
	loadTexture(TextureType::TriangleProjectile,		SpritePaths::c_projectileTriangle);
	loadTexture(TextureType::SquareProjectile,			SpritePaths::c_projectileSquare);
	loadTexture(TextureType::PentagonProjectile,		SpritePaths::c_projectilePentagon);
	loadTexture(TextureType::CircleEnemy,				SpritePaths::c_circleEnemy);
	loadTexture(TextureType::TriangleEnemy,				SpritePaths::c_triangleEnemy);
	loadTexture(TextureType::SquareEnemy,				SpritePaths::c_squareEnemy);
	loadTexture(TextureType::PentagonEnemy,				SpritePaths::c_pentagonEnemy);
	loadTexture(TextureType::MineObstacle,				SpritePaths::c_mineObstacle);
	loadTexture(TextureType::RockExplode,				SpritePaths::c_rockExploding);
	loadTexture(TextureType::CircleBGD,					SpritePaths::c_bgdCircle);
	loadTexture(TextureType::TriangleBGD,				SpritePaths::c_bgdTriangle);
	loadTexture(TextureType::SquareBGD,					SpritePaths::c_bgdSquare);
	loadTexture(TextureType::PentagonBGD,				SpritePaths::c_bgdPentagon);
	loadTexture(TextureType::ShopBGD,					SpritePaths::c_bgdShop);
	loadTexture(TextureType::ShopSelection,				SpritePaths::c_shopSelection);
	loadTexture(TextureType::ShopSelectionPurchased,	SpritePaths::c_shopPurchased);
	loadTexture(TextureType::ShopSelectionFailed,		SpritePaths::c_shopFailed);
	loadTexture(TextureType::Portal,					SpritePaths::c_portal);
	loadTexture(TextureType::Explosion,					SpritePaths::c_explosion);
	loadTexture(TextureType::Health100,					SpritePaths::c_health100);
	loadTexture(TextureType::Health80,					SpritePaths::c_health80);
	loadTexture(TextureType::Health60,					SpritePaths::c_health60);
	loadTexture(TextureType::Health40,					SpritePaths::c_health40);
	loadTexture(TextureType::Health20,					SpritePaths::c_health20);
	loadTexture(TextureType::Health0,					SpritePaths::c_health0);
	loadTexture(TextureType::Heart,						SpritePaths::c_heart);
	loadTexture(TextureType::Cursor,					SpritePaths::c_cursor);
	loadTexture(TextureType::HowToPlay,					SpritePaths::c_howToPlay);
	loadTexture(TextureType::Mascot,					SpritePaths::c_mascot);
}

// Return the desired texture based on the texture name.
const sf::Texture& TextureHandler::getTexture(TextureType textureName)
{
	auto textureLookup = m_Texture.find(textureName);
	return *textureLookup->second;
}






