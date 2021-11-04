#ifndef DEF_TEXT	
#define DEF_TEXT
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>



class TextPrinted{
private:
	sf::Text m_text;
	sf::Font m_font;
public:
	TextPrinted(std::string fontName, std::string string, int size, int x, int y){
		if(!m_font.loadFromFile(fontName)){std::cout << "erreur importation font\n";}
		m_text.setFont(m_font); 
		m_text.setString(string);
		m_text.setFillColor(sf::Color::Black);
		m_text.setCharacterSize(size); // exprimée en pixels, pas en points !
		m_text.setPosition(x,y);
	}

	void setString(std::string string){m_text.setString(string);}
	sf::Text getText() const{return(m_text);}
};

#endif