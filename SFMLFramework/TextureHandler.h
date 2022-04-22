#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H

#include <SFML\Graphics\Texture.hpp>
#include <map>
#include <SFML/System/String.hpp>

enum class TextureType { // Types of textures.
	Player,
	PlayerParticle,
	PlayerProjectile,
	CircleProjectile,
	TriangleProjectile,
	SquareProjectile,
	PentagonProjectile,
	CircleEnemy,
	TriangleEnemy,
	SquareEnemy,
	PentagonEnemy,
	HexagonEnemy,
	HeptagonEnemy,
	OctagonEnemy,
	NonagonEnemy,
	DecagonEnemy,
	MineObstacle,
	RockExplode,
	Seamless,
	CircleBGD,
	TriangleBGD,
	SquareBGD,
	PentagonBGD,
	ShopBGD,
	ShopSelection,
	ShopSelectionPurchased,
	ShopSelectionFailed,
	Portal,
	Explosion,
	Health100,
	Health80,
	Health60,
	Health40,
	Health20,
	Health0,
	Heart,
	Cursor,
	HowToPlay,
	Mascot
};

class TextureHandler
{
private:
	std::map<TextureType, sf::Texture*>   m_Texture; // This stores the texture and its name path to retrieve it throughout the entire project.

public:
	TextureHandler();	// Constructor.
	~TextureHandler();	// Deconstructor.

	void initialise();	// Initialiser.

	void loadTexture(TextureType textureName, const sf::String& textureFile);	

	const sf::Texture& getTexture(TextureType textureID);						// Get the texture to load.
};

#endif //!TEXTUREHANDLER_H