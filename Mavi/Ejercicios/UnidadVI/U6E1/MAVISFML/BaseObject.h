#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class BaseObject
{
public:
    // Constructor de la clase BaseObject que recibe el nombre del archivo de imagen como parámetro
    BaseObject(string filename);

    // Destructor de la clase BaseObject
    ~BaseObject();

    // Función para dibujar el objeto en una ventana RenderWindow
    void Draw(RenderWindow* pWnd);

    // Función para actualizar el objeto en función del tiempo transcurrido
    void Update(float dt);

    Vector2u GetTextureSize() { return _tex->getSize(); }

    // Funciones para configurar las propiedades del objeto
    void SetScale(float uniformScale) { _sprite->setScale(uniformScale, uniformScale); }
    void SetPosition(Vector2f pos) { _position = pos; }
    void SetAcceleration(Vector2f acc) { _acceleration = acc; }
    void SetVelocity(Vector2f vel) { _velocity = vel; }

    // Funciones para obtener las propiedades del objeto
    Vector2f GetPosition() { return _position; }
    Vector2f GetAcceleration() { return _acceleration; }
    Vector2f GetVelocity() { return _velocity; }

    // Función para agregar una aceleración al objeto
    void AddAcceleration(Vector2f acc) {
        _acceleration.x += acc.x;
        _acceleration.y += acc.y;
    }

private:
    Sprite* _sprite;
    Texture* _tex;

    Vector2f _position;
    Vector2f _acceleration;
    Vector2f _velocity;
};


