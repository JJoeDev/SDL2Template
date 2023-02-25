#pragma once
#include <SDL.h>

#include "vector.h"

class Entity
{
public:
	// Entity constructor, takes a Vector 2 position, a float rotation and a texture
	Entity(Vector2f position, float rotation, SDL_Texture* texture);

	// Functions to get the position, scale, and angle / rotation
	Vector2f& getPos() { return pos; }
	float& getAngle() { return angle; }
	Vector2f& getScale() { return scale; }

	// Functions to set position, scale, and angle / rotation
	void setPos(Vector2f newPos);
	void setScale(Vector2f newScale);
	void setAngle(float newAngle);

	// A function to make the entity render itself
	void renderEntity();

	// Functions to get the current frame and texture
	SDL_Texture* getTexture();
	SDL_Rect getCurrentFrame();

private:
	// Private variables for position, angle, scale, current frame, and texture
	Vector2f pos{ 0.0, 0.0 };
	float angle{ 0 };
	Vector2f scale{ 1, 1 };
	SDL_Rect currentFrame{ 0, 0, 0, 0 };
	SDL_Texture* tex{ nullptr };
};