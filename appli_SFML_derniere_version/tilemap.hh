#ifndef DEF_TILEMAP
#define DEF_TILEMAP
#include <iostream>
#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    TileMap(int p_xTiles, int p_yTiles, int p_xPixels, int p_yPixels, int p_tileSize):
        m_tileSize(p_tileSize),m_xTiles(p_xTiles),m_yTiles(p_yTiles),m_xPixels(p_xPixels),m_yPixels(p_yPixels){
            m_vertices = new sf::VertexArray*[m_xTiles];
            for(int i = 0;i < m_xTiles;i++){
                m_vertices[i] = new sf::VertexArray[m_yTiles];
            }
    }

    sf::VertexArray** get_vertices() const{return(m_vertices);}
    int get_tileSize() const{return(m_tileSize);}
    int get_xTiles() const{return(m_xTiles);}

    ~TileMap(){
        for(int i = 0;i<m_xTiles;i++){
            delete[] m_vertices[i];
        }
        delete[] m_vertices;
        std::cout << "TileMap a ete detruit.\n";
    }

    //tileset : nom du fichier a importer
    //tiles : tableau avec des int representant la map
    bool load(const std::string& tileset, const int* tiles)
    {
        // on charge la texture du tileset
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // on remplit le tableau de vertex, avec un quad par tuile
        for(int j = 0; j < m_yTiles; ++j)
            for(int i = 0; i < m_xTiles; ++i)
            {
                m_vertices[i][j].setPrimitiveType(sf::Quads);
                m_vertices[i][j].resize(4);

                // on récupère le numéro de tuile courant
                int tileNumber = tiles[i + j * m_xTiles];

                // on en déduit sa position dans la texture du tileset
                int tu = tileNumber % (m_tileset.getSize().x / m_tileSize);
                int tv = tileNumber / (m_tileset.getSize().x / m_tileSize);

                // on définit ses quatre coins
                m_vertices[i][j][0].position = sf::Vector2f(i * m_tileSize, j * m_tileSize); 
                m_vertices[i][j][1].position = sf::Vector2f((i + 1) * m_tileSize, j * m_tileSize);
                m_vertices[i][j][2].position = sf::Vector2f((i + 1) * m_tileSize, (j + 1) * m_tileSize);
                m_vertices[i][j][3].position = sf::Vector2f(i * m_tileSize, (j + 1) * m_tileSize);

                // if(i == 0 and j < 4){
                // std::cout << "i = " << i << ", j = " << j << m_xTiles << std::endl;
                // std::cout << "x = " << m_vertices[i][j][0].position.x << ", y0 = " << m_vertices[i][j][0].position.y << std::endl;
                // std::cout << "x = " << m_vertices[i][j][1].position.x << ", y0 = " << m_vertices[i][j][1].position.y << std::endl;
                // std::cout << "x = " << m_vertices[i][j][2].position.x << ", y0 = " << m_vertices[i][j][2].position.y << std::endl;
                // std::cout << "x = " << m_vertices[i][j][3].position.x << ", y0 = " << m_vertices[i][j][3].position.y << std::endl;
                // }
                // std::cout << "i = " << i << ", j = " << j << "= " << (i + j * width) * 4 << std::endl;


                // on définit ses quatre coordonnées de texture
                m_vertices[i][j][0].texCoords = sf::Vector2f(tu * m_tileSize, tv * m_tileSize);
                m_vertices[i][j][1].texCoords = sf::Vector2f((tu + 1) * m_tileSize, tv * m_tileSize);
                m_vertices[i][j][2].texCoords = sf::Vector2f((tu + 1) * m_tileSize, (tv + 1) * m_tileSize);
                m_vertices[i][j][3].texCoords = sf::Vector2f(tu * m_tileSize, (tv + 1) * m_tileSize);
            }

        return true;
    }

    void print_coordinates_vertices(){
        for(int j = 0; j < m_yTiles; ++j){
            for(int i = 0; i < m_xTiles; ++i){
                std::cout << "x = " << m_vertices[i][j][0].position.x << ", y = " << m_vertices[i][j][0].position.y << std::endl;
            }
        }
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // on applique la transformation
        states.transform *= getTransform();

        // on applique la texture du tileset
        states.texture = &m_tileset;

        // et on dessine enfin le tableau de vertex
        for(int j = 0; j < m_yTiles; ++j){  
            for(int i = 0; i < m_xTiles; ++i)
            {
                target.draw(m_vertices[i][j], states);
            }
        }
    }

    sf::VertexArray** m_vertices;
    sf::Texture m_tileset;
    int m_tileSize; //taille d'un tile en pixels
    int m_xTiles;
    int m_yTiles;  
    int m_xPixels;
    int m_yPixels;
};

#endif
