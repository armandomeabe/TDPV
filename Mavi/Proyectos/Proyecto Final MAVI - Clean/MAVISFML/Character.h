#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>

class Character : public sf::Drawable {
public:
    // Constructor que recibe la textura
    Character(const sf::Texture& texture, float lifeTime);

    // Establecer la posición
    void setPosition(float x, float y);

    // Obtener la posición del personaje
    sf::Vector2f getPosition() const;

    // Obtener los límites del sprite para la colisión
    sf::FloatRect getGlobalBounds() const;

    // Método para obtener el sprite por referencia (no copia)
    sf::Sprite& getSprite();  // Cambiar a referencia

    // Para registrar el paso del tiempo
    void Update(float deltaTime);

    // Para saber si ya caducó el personaje
    bool IsExpired() const;

protected:
    // Método para dibujar el sprite
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Sprite sprite;  // El sprite del personaje
    float elapsedTime;
    float lifeTime;
};

#endif // CHARACTER_H
