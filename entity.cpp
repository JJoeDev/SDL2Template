#include <SDL_image.h>

#include "Entity.h"

// Entity constructor for setting position, rotation, texture, and current frame
Entity::Entity(Vector2f position, float rotation, SDL_Texture* texture) : pos(position), tex(texture), angle(rotation) {
    currentFrame.x = 0;
    currentFrame.y = 0;

    SDL_QueryTexture(texture, nullptr, nullptr, &currentFrame.w, &currentFrame.h);
}

// Function to set a new position
void Entity::setPos(Vector2f newPosition) {
    pos = newPosition;
}

// Function to set new angle / rotation
void Entity::setAngle(float Angle) {
    angle = Angle;
}

// Function to set new scale
void Entity::setScale(Vector2f newScale) {
    scale = newScale;
}

// Function to get texture
SDL_Texture* Entity::getTexture() {
    return tex;
}

// Function to get current frame
SDL_Rect Entity::getCurrentFrame() {
    return currentFrame;
}