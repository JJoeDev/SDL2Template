#include <SDL_image.h>
#include <SDL.h>
#include "Entity.h"
#include "game.h"

// Entity constructor for setting position, rotation, texture, and current frame
Entity::Entity(Vector2f position, float rotation, SDL_Texture* texture) : pos(position), tex(texture), angle(rotation) {
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

// Function to make the entity render itself
void Entity::renderEntity() {
    SDL_Rect dst;

    dst.x = getPos().x - currentFrame.w * getScale().x / 2;
    dst.y = getPos().y - currentFrame.h * getScale().y / 2;
    dst.w = currentFrame.w * getScale().x;
    dst.h = currentFrame.h * getScale().y;

    SDL_RenderCopyEx(Game::renderer, tex, &currentFrame, &dst, angle, nullptr, SDL_FLIP_NONE);
}

// Function to get texture
SDL_Texture* Entity::getTexture() {
    return tex;
}

// Function to get current frame
SDL_Rect Entity::getCurrentFrame() {
    return currentFrame;
}