#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(512, 512), "demo", sf::Style::Close | sf::Style::Resize);
    //sf::RectangleShape player(sf::Vector2f(150.0f, 150.0f));
    //player.setPosition(206.0f, 206.0f);
    sf::Texture playerTexture;
    playerTexture.loadFromFile("blues.png");
    //player.setTexture(&playerTexture);

    //Animation animation(&playerTexture, sf::Vector2u(6, 1), 0.1f);
    Player player(&playerTexture, sf::Vector2u(6, 1), 0.1f, 100.0f);

    float deltaTime = 0.0f;
    sf::Clock clock;

    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();

        sf::Event evnt;
        while (window.pollEvent(evnt)) {
            switch (evnt.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
        player.Update(deltaTime);
        //animation.Update(0, deltaTime, false);
        //player.setTextureRect(animation.uvRect);

        window.clear(sf::Color(150, 150, 150));
        //window.draw(player);
        player.Draw(window);
        window.display();
    }


    return 0;
}
