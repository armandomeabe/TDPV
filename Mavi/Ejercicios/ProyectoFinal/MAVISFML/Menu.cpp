#include "Menu.h"

Menu::Menu(float width, float height)
    : selectedItemIndex(0) {
    if (!font.loadFromFile("../../res/OpenSans-Regular.ttf")) {
        // Manejar error
    }

    initializeMenu(width, height);
}

void Menu::initializeMenu(float width, float height) {
    std::vector<std::string> items = { "Empezar", "Salir" };
    float yOffset = height / (items.size() + 1);

    for (size_t i = 0; i < items.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setFillColor(i == selectedItemIndex ? sf::Color::Red : sf::Color::White);
        text.setString(items[i]);
        text.setPosition(sf::Vector2f(width / 2 - text.getGlobalBounds().width / 2, (i + 1) * yOffset));
        menuItems.push_back(text);
    }
}

void Menu::draw(sf::RenderWindow& window) {
    for (const auto& item : menuItems) {
        window.draw(item);
    }
}

void Menu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown() {
    if (selectedItemIndex + 1 < menuItems.size()) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

int Menu::getSelectedItemIndex() const {
    return selectedItemIndex;
}