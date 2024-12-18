#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class BaseObject {
public:
    BaseObject(string filename);
    ~BaseObject();

    void Draw(RenderWindow* pWnd);
    void Update(float dt);

    void SetScale(float uniformScale) { _sprite->setScale(uniformScale, uniformScale); }
    void SetPosition(Vector2f pos) { _position = pos; }
    void SetAcceleration(Vector2f acc) { _acceleration = acc; }
    void SetVelocity(Vector2f vel) { _velocity = vel; }

    Vector2f GetPosition() const { return _position; }
    Vector2f GetAcceleration() const { return _acceleration; }
    Vector2f GetVelocity() const { return _velocity; }
    sf::Vector2f GetScale() const { return _sprite->getScale(); }
    sf::Vector2u GetTextureSize() const { return _text->getSize(); }

    void AddAcceleration(Vector2f acc) {
        _acceleration.x += acc.x;
        _acceleration.y += acc.y;
    }

private:
    Sprite* _sprite;
    Texture* _text;

    Vector2f _position;
    Vector2f _acceleration;
    Vector2f _velocity;
};
