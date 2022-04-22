#include <cmath>
#include "Helpers.h"

bool screenShake;

// This functions handles collision detection and returns true if the criteria passed through the parameters are met.
bool checkDistance(sf::Vector2f firstPos, sf::Vector2f secondPos, float r)
{
	float distX = firstPos.x - secondPos.x;
	float distY = firstPos.y - secondPos.y;
	float distance = sqrt((distX * distX) + (distY * distY));

	if (distance <= r) 
	{
		return true;
	}
	return false;
}

// Function to handle moving one objects towards another based on parameter values.
void moveTowards(sf::Vector2f firstPos, sf::Vector2f secondPos, Object* object, float deltaTime, float speed, bool rotate)
{
	const float PI = 3.14159265;

	float dx = firstPos.x - secondPos.x;
	float dy = firstPos.y - secondPos.y;

	sf::Vector2f direction = (secondPos - firstPos);
	object->move(direction * deltaTime * speed);

	if (rotate == true) {
		float rotation = (atan2(dy, dx)) * 180 / PI;

		object->setRotation(rotation - 90);
	}
}

// This function allows for a smooth transition from one position to another at a constant speed.
sf::Vector2f vectorLerp(const sf::Vector2f& startingPosition, const sf::Vector2f& endPosition, float time)
{
	return startingPosition + time * (endPosition - startingPosition);
}

// Generate a random float.
float generateRandomFloat(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}