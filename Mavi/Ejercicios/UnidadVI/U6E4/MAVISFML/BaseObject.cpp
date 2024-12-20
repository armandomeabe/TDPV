#include "BaseObject.h"
#include <iostream>

sf::Vector2u BaseObject::GetTextureSize() const {
    return _texture->getSize();  // Tamaño de la textura
}

float BaseObject::GetScale() const {
    return _sprite->getScale().x;  // Suponiendo que la escala es la misma en y
}

BaseObject::BaseObject(const std::string& filename)
    : _sprite(nullptr), _texture(nullptr), _position(0.0f, 0.0f), _velocity(0.0f, 0.0f), _acceleration(0.0f, 0.0f)
{
    _texture = new sf::Texture();
    if (!_texture->loadFromFile(filename)) {
        std::cout << "Error: No se pudo cargar la textura desde el archivo " << filename << std::endl;
    }

    _sprite = new sf::Sprite();
    _sprite->setTexture(*_texture);
}

BaseObject::~BaseObject() {
    delete _sprite;
    delete _texture;
}

void BaseObject::Draw(sf::RenderWindow* pWnd) {
    pWnd->draw(*_sprite);
}

sf::FloatRect BaseObject::getGlobalBounds() const {
    return _sprite->getGlobalBounds();  // Delegamos a getGlobalBounds() del sprite
}

void BaseObject::Update(float dt) {
    // Actualizar velocidad y posición con aceleración
    _velocity += _acceleration * dt;

    // Aleatorizar un poco para darle emocion
    //_velocity.x += _velocity.x + 1;

    _position += _velocity * dt; // Como en algebra, a la posicion le sumo el vector direccion afectado por su magnitud en funcion del tiempo

    // Actualizar la posición del sprite
    _sprite->setPosition(_position);

    // Resetear la aceleración después de cada actualización
    // El 100 es porque las cosas se van acelerando conforme se alejan, se hace mas divertido
    // _acceleration = sf::Vector2f(100.0f, 100.0f);
}

void BaseObject::SetScale(float uniformScale) {
    _sprite->setScale(uniformScale, uniformScale);
}

void BaseObject::SetPosition(sf::Vector2f pos) {
    _position = pos;
}

void BaseObject::SetVelocity(sf::Vector2f vel) {
    _velocity = vel;
}

void BaseObject::SetAcceleration(sf::Vector2f acc) {
    _acceleration = acc;
}

sf::Vector2f BaseObject::GetPosition() const {
    return _position;
}

sf::Vector2f BaseObject::GetVelocity() const {
    return _velocity;
}

sf::Vector2f BaseObject::GetAcceleration() const {
    return _acceleration;
}
