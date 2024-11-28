#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>

class Character : public sf::Drawable {
public:
    // Constructor que recibe la textura
    Character(const sf::Texture& texture);

    // Establecer la posici�n
    void setPosition(float x, float y);

    // Obtener la posici�n del personaje
    sf::Vector2f getPosition() const;

    // Obtener los l�mites del sprite para la colisi�n
    sf::FloatRect getGlobalBounds() const;

    // M�todo para obtener el sprite por referencia (no copia)
    sf::Sprite& getSprite();  // Cambiar a referencia

protected:
    // M�todo para dibujar el sprite
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Sprite sprite;  // El sprite del personaje
};

#endif // CHARACTER_H
