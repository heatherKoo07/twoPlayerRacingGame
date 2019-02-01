//
// Created by Heather Hyunkyung Koo on 1/13/19.
//

#ifndef SFML_JUMPING_PLAYER_H
#define SFML_JUMPING_PLAYER_H

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"

class Player {
public:
    Player(sf::Texture *texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);

    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);
    void onCollision(sf::Vector2f direction);

    sf::Vector2f GetPosition() {return body.getPosition();}
    Collider GetCollider() { return Collider(body); }

private:
    sf::RectangleShape body;
    Animation animation;
    unsigned int row;
    float speed;
    bool faceRight;

    sf::Vector2f velocity;
    bool canJump;
    float jumpHeight;
};

Player::Player(sf::Texture *texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
        animation(texture, imageCount, switchTime)
{
    this->speed = speed;
    this->jumpHeight = jumpHeight;
    row = 0;
    faceRight = true;

    body.setSize(sf::Vector2f(100.0f, 150.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(206.0f, 206.0f);
    body.setTexture(texture);
}

void Player::Update(float deltaTime) {
    velocity.x *= 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        velocity.x -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        velocity.x += speed * deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump) {
        canJump = false;
        velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
    }

    velocity.y += 981.0f * deltaTime;

    if (velocity.x == 0.0f)
        row = 0;
    else {
        row = 1;
        if (velocity.x > 0.0f)
            faceRight = true;
        else
            faceRight = false;
    }
    animation.Update(row, deltaTime, faceRight);
    body.setTextureRect(animation.uvRect);
    body.move(velocity * deltaTime);
}


void Player::Draw(sf::RenderWindow& window) {
    window.draw(body);
}

void Player::onCollision(sf::Vector2f direction) {
    if (direction.x < 0.0f) {
        //Collision on the left
        velocity.x = 0.0f;
    } else if (direction.x > 0.0f) {
        //Collision on the right
        velocity.x = 0.0f;
    }
    if (direction.y < 0.0f) {
        //Collision on the bottom
        velocity.y = 0.0f;
        canJump = true;
    } else if (direction.y > 0.0f) {
        //Collision on the top
        velocity.y = 0.0f;
    }
}

#endif //SFML_JUMPING_PLAYER_H
