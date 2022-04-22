#ifndef HELPERS_H
#define HELPERS_H

#include <SFML\System\Vector2.hpp>

#include "Object.h"

extern bool screenShake; // Global bool to shake the screen.

bool checkDistance(sf::Vector2f firstPos, sf::Vector2f secondPos, float r); // Function to check distance between two declared objects.

void moveTowards(sf::Vector2f firstPos, sf::Vector2f secondPos, Object* object, float deltaTime, float speed, bool rotate); // Function to move one object towards another.

sf::Vector2f vectorLerp(const sf::Vector2f& startingPosition, const sf::Vector2f& endPosition, float time); // Function to handle smooth movement between two set points.

template <typename T> void safeDeletePointer(T*& pointer) // Safe delete pointer template.
{
    delete pointer;
    pointer = nullptr;
}

template <typename T> void safeDeletePointerArray(T*& pointerArray) // Safe delete pointer array template.
{
    delete[] pointerArray;
    pointerArray = nullptr;
}

float generateRandomFloat(float a, float b);
#endif // !HELPERS_H