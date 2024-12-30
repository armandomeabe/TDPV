#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>


/// <summary>
/// Es la clase base para enemigos e inocentes. No deber� ser instanciada (clase abstracta).
/// </summary>
class Character : public sf::Drawable {
public:
    // Constructor que recibe textura
    Character(const sf::Texture& texture, float lifeTime);

    // Establecer la posici�n del personaje
    void setPosition(float x, float y);

    // Obtener la posici�n del personaje
    sf::Vector2f getPosition() const;

    // Obtener los l�mites del sprite para la colisi�n con las balas
    sf::FloatRect getGlobalBounds() const;

    // Obtener el sprite por referencia (no copia)
    sf::Sprite& getSprite();

    // Para registrar el paso del tiempo
    void Update(float deltaTime);

    // Para saber si ya caduc� el personaje
    bool IsExpired() const;

protected:
    // M�todo para dibujar el sprite
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Sprite sprite;
    float elapsedTime;
    float lifeTime;
};

#endif // CHARACTER_H
