#include "BaseObject.h"
#include <iostream>

// Constructor de la clase BaseObject que recibe el nombre del archivo de imagen
BaseObject::BaseObject(string filename)
{
    // Se crea una nueva instancia de Texture (_tex) y se trata de cargar la imagen desde el archivo
    _tex = new Texture();
    if (!_tex->loadFromFile(filename)) {
        cout << "No se pudo cargar la imagen" << endl;
    }

    // Se crea una nueva instancia de Sprite (_sprite) y se establece su textura
    _sprite = new Sprite();
    _sprite->setTexture(*_tex);

    // Iniciar variables de posici�n, aceleraci�n y velocidad en 0
    _position.x = 0.0f;
    _position.y = 0.0f;
    _acceleration.x = 0.0f;
    _acceleration.y = 0.0f;
    _velocity.x = 0.0f;
    _velocity.y = 0.0f;
}

// Destructor de la clase BaseObject
BaseObject::~BaseObject()
{
    // Se liberan las memorias asignadas din�micamente para el Sprite y la Texture, porque se uso "new" por lo que se reservo memoria del heap y no se limpia sola
    delete _sprite;
    delete _tex;
}

// Funci�n para dibujar el objeto en una ventana RenderWindow
void BaseObject::Draw(RenderWindow* pWnd)
{
    pWnd->draw(*_sprite);
}

// Funci�n para actualizar el objeto en funci�n del tiempo transcurrido (dt)
void BaseObject::Update(float dt)
{
    // Actualizaci�n de la velocidad en funci�n de la aceleraci�n y el tiempo
    _velocity.x += _acceleration.x * dt;
    _velocity.y += _acceleration.y * dt;

    // Actualizaci�n de la posici�n en funci�n de la velocidad y el tiempo
    _position.x += _velocity.x * dt;
    _position.y += _velocity.y * dt;

    // Se actualiza la posici�n del Sprite con la nueva posici�n calculada
    _sprite->setPosition(_position);

    // Reinicio de las aceleraciones a 0 despu�s de la actualizaci�n
    _acceleration.x = 0.0f;
    _acceleration.y = 0.0f;
}
