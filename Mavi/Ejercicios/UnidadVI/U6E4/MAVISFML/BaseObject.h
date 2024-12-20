#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class BaseObject {
public:
    BaseObject(const std::string& filename);
    ~BaseObject();

    void Draw(sf::RenderWindow* pWnd);
    virtual void Update(float dt);

    void SetScale(float uniformScale);
    void SetPosition(sf::Vector2f pos);
    void SetVelocity(sf::Vector2f vel);
    void SetAcceleration(sf::Vector2f acc);

    sf::Vector2f GetPosition() const;
    sf::Vector2f GetVelocity() const;
    sf::Vector2f GetAcceleration() const;

    sf::Vector2u GetTextureSize() const;
    float GetScale() const;

    sf::FloatRect getGlobalBounds() const;

private:
    sf::Sprite* _sprite = nullptr;
    sf::Texture* _texture = nullptr;

    sf::Vector2f _position;
    sf::Vector2f _velocity;
    sf::Vector2f _acceleration;
};
