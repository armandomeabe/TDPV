#include "BaseObject.h"
#include <iostream>

BaseObject::BaseObject(string filename) {
    _text = new Texture();
    if (!_text->loadFromFile(filename)) {
        cout << "No se pudo cargar la imagen: " << filename << endl;
    }

    _sprite = new Sprite();
    _sprite->setTexture(*_text);

    _position = Vector2f(0.0f, 0.0f);
    _acceleration = Vector2f(0.0f, 0.0f);
    _velocity = Vector2f(0.0f, 0.0f);
}

BaseObject::~BaseObject() {
    delete _sprite;
    delete _text;
}

void BaseObject::Draw(RenderWindow* pWnd) {
    pWnd->draw(*_sprite);
}

void BaseObject::Update(float dt) {
    _velocity += _acceleration * dt;
    _position += _velocity * dt;
    _sprite->setPosition(_position);
}
