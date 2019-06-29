#include <SFML/Graphics.hpp>
#include "headers/database.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920,1080), "FRC 6908: Infuzed Inventory System");
    
    sf::Font font;
    if (!font.loadFromFile("Resources/abel-regular.ttf")) {
        std::cerr << "Cannot load font." << std::endl;
        return EXIT_FAILURE;
    }

    sf::Event event;

    std::string inputText;
    sf::Text dispText("", font, 50);
    dispText.setPosition(158, 909);
    dispText.setFillColor(sf::Color::White);


    sf::Text outputText("", font, 30);
    outputText.setPosition(sf::Vector2f(1015.0f, 148.0f));
    outputText.setFillColor(sf::Color(31,24,255));

    sf::Texture infuzedLogo;
    if (!infuzedLogo.loadFromFile("Resources/Infuzed.png", sf::IntRect(0, 0, 997, 1014))) {
        std::cerr << "ERROR: CANNOT LOAD IMAGE" << std::endl;
        return EXIT_FAILURE;
    }

    infuzedLogo.setSmooth(true);
    sf::Sprite infuzedLogoS;
    infuzedLogoS.setTexture(infuzedLogo);

    sf::RectangleShape rect; // input box (ish)
    rect.setPosition(sf::Vector2f(158.0f, 918.0f));
    rect.setSize(sf::Vector2f(692.0f, 56.0f));
    rect.setFillColor(sf::Color(31, 24, 255));

    database frc("data/frcTestData.csv");
    frc.init();

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    frc.close();
                    window.close();
                    break;
                case sf::Event::TextEntered:
                    switch (event.text.unicode) {
                        case 13:
                            //std::cout << "BROKE LEL" << std::endl;
                            frc.inputCmd(inputText);
                            inputText.clear();
                            break;
                        case 8:
                            inputText = inputText.substr(0, inputText.size() - 1);
                            break;
                        default:
                            inputText += event.text.unicode;
                    }
                    dispText.setString(inputText);
                    outputText.setString(frc.dbText);
                    std::cout << frc.dbText;
            }
        }
        window.draw(rect);
        window.draw(infuzedLogoS);
        window.draw(dispText);
        window.draw(outputText);
        window.display();
        window.clear(sf::Color::White);
    }
    return 0;
}
