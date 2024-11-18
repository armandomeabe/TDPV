#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
public:
    Menu(float width, float height);
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedItemIndex() const;

private:
    int selectedItemIndex;
    sf::Font font;
    std::vector<sf::Text> menuItems;

    void initializeMenu(float width, float height);
};

#endif