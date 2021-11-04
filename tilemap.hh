#ifndef DEF_TILEMAP
#define DEF_TILEMAP
#include <iostream>
#include <SFML/Graphics.hpp>


class TileMap : public sf::Drawable, public sf::Transformable
{
private:
    sf::VertexArray** m_vertices;  // tableau de cases (ensemble de quatre points)
    static int* m_grid1;
    static int* m_grid2;
    sf::Texture m_tileset; // l'image du tileset
    int m_tileSize; // taille d'un tile (d'une case) en pixels
    int m_xTiles; // largeur du tileset en tiles (en cases)
    int m_yTiles; // hauteur du tileset en tiles (en cases)
    int m_xPixels; // largeur du tileset en pixels
    int m_yPixels; // hauteur du tileset en pixels

    //dessine, affiche la map sur l'ecran 
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
public:
    TileMap(int p_xTiles, int p_yTiles, int p_xPixels, int p_yPixels, int p_tileSize):
        m_tileSize(p_tileSize),m_xTiles(p_xTiles),m_yTiles(p_yTiles),m_xPixels(p_xPixels),m_yPixels(p_yPixels){
            m_vertices = new sf::VertexArray*[m_xTiles];
            for(int i = 0;i < m_xTiles;i++){
                m_vertices[i] = new sf::VertexArray[m_yTiles];
            }
            m_grid1 = new int[m_xTiles*m_yTiles]{
                3, 3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3, 3,
                3,  3,  3,  3, 3,  3,  3,  24,  3,  3,  3,  24,  3,  3, 3,  3,  3,  3, 3,
                3,  3,  3,  3,  3, 24, 24, 24,  24, 24, 24, 24, 24, 24, 3,  3,  3, 3, 3,
                3, 3, 24, 24, 24, 24, 24, 24, 24,  56, 57, 58, 24, 24, 24, 24, 24, 3, 10,
                24, 3, 24, 24, 24, 24, 24, 24,  24, 64, 65, 66, 24, 24, 24, 24, 24, 24, 10,
                24, 24, 24, 24, 24, 24, 24, 24, 24, 72, 73, 74, 24, 24, 24, 24, 24, 24, 10,
                24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 18,
                24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
                3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
                3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
                3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
                3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 3,
                3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 3,
                3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 3,
                3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 3, 3,
                3, 3, 3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 3, 3,
                3, 3, 3, 3, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 3, 3, 3,
                 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                
            };
            m_grid2 = new int[m_xTiles*m_yTiles]{
                3, 3,  3,  3,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  3,  3,  3, 3,
                3,  0,  1,  1, 16,  9,  9,  9,  9,  9,  9,  9,  9,  9, 18,  1,  1,  2, 3,
                3,  8,  9,  9,  9, 3, 3, 3,  4, 3, 3, 3, 4, 3, 9,  9,  9, 18, 2,
                1, 16, 3, 3, 3, 3, 3, 3, 12, 3, 3, 3, 12, 3, 3, 3, 3, 9, 10,
                9, 9, 3, 3, 3, 3, 3, 3,  20, 3, 3, 3, 20, 3, 3, 3, 3, 3, 10,
                23, 3, 3, 3, 3, 3, 3, 3, 23, 3, 3, 3, 23, 3, 3, 3, 3, 3, 10,
                23, 3, 3, 3, 23, 3, 23, 23, 23, 3, 3, 23, 23, 3, 3, 3, 3, 3, 18,
                23, 3, 3, 3, 3, 23, 3, 3, 3, 3, 3, 3, 23, 3, 3, 3, 3, 23, 9,
                3, 3, 3, 3, 23, 23, 23, 3, 3, 3, 3, 23, 23, 3, 3, 23, 23, 23, 3,
                3, 3, 3, 3, 3, 23, 3, 3, 3, 3, 3, 3, 3, 23, 3, 3, 23, 23, 3,
                3, 3, 3, 3, 3, 23, 3, 3, 3, 3, 3, 3, 23, 23, 23, 23, 23, 23, 23,
                3, 23, 3, 3, 3, 23, 23, 23, 23, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                3, 23, 3, 3, 3, 3, 23, 3, 23, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                3, 23, 3, 3, 3, 3, 3, 3, 23, 23, 23, 23, 23, 3, 3, 3, 3, 3, 3,
                3, 23, 3, 3, 3, 3, 3, 3, 3, 3, 23, 23, 23, 23, 3, 3, 3, 3, 3,
                3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
            };
            
    }

    sf::VertexArray** get_vertices() const{return(m_vertices);}
    static int* get_grid1(){return(m_grid1);}
    static int* get_grid2(){return(m_grid2);}
    int get_tileSize() const{return(m_tileSize);}
    int get_xTiles() const{return(m_xTiles);}

    ~TileMap(){
        for(int i = 0;i<m_xTiles;i++){
            delete[] m_vertices[i];
        }
        delete[] m_vertices;
        delete[] m_grid1;
        delete[] m_grid2;
        std::cout << "TileMap a ete detruit.\n";
    }

    //importe l'image du tileset
    //- tileset : nom du fichier a importer
    //- tiles : tableau avec des int representant la map
    bool load(const std::string& tileset, const int* tiles)
    {
        // on charge la texture du tileset
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // on remplit le tableau de vertex, avec un quad par case
        for(int j = 0; j < m_yTiles; ++j) //m_yTiles = 18
            for(int i = 0; i < m_xTiles; ++i) //m_xTiles = 19
            {
                m_vertices[i][j].setPrimitiveType(sf::Quads);
                m_vertices[i][j].resize(4);

                // on récupère le numéro de la case (ce sont les numeros affichees dans la grille Tilemap map)
                int tileNumber = tiles[i + j * m_xTiles]; //tiles[abscisses(0:19) + ordonnees*largeur(0:18)]

                // on en déduit sa position dans l'image du tileset
                int tu = tileNumber % (m_tileset.getSize().x / m_tileSize);
                int tv = tileNumber / (m_tileset.getSize().x / m_tileSize);

                // on définit les coordonnées de ses quatre points sur la map (l'image affiche dans le jeu)
                m_vertices[i][j][0].position = sf::Vector2f(i * m_tileSize, j * m_tileSize); 
                m_vertices[i][j][1].position = sf::Vector2f((i + 1) * m_tileSize, j * m_tileSize);
                m_vertices[i][j][2].position = sf::Vector2f((i + 1) * m_tileSize, (j + 1) * m_tileSize);
                m_vertices[i][j][3].position = sf::Vector2f(i * m_tileSize, (j + 1) * m_tileSize);

                // on définit les coordonnées de ses quatre points dans l'image du tileset
                m_vertices[i][j][0].texCoords = sf::Vector2f(tu * m_tileSize, tv * m_tileSize);
                m_vertices[i][j][1].texCoords = sf::Vector2f((tu + 1) * m_tileSize, tv * m_tileSize);
                m_vertices[i][j][2].texCoords = sf::Vector2f((tu + 1) * m_tileSize, (tv + 1) * m_tileSize);
                m_vertices[i][j][3].texCoords = sf::Vector2f(tu * m_tileSize, (tv + 1) * m_tileSize);
            }
        return true;
    }

    // affiche pour chaque case (Vertex) son point en haut a gauche
    void print_coordinates_vertices(){
        for(int j = 0; j < m_yTiles; ++j){
            for(int i = 0; i < m_xTiles; ++i){
                std::cout << "x = " << m_vertices[i][j][0].position.x << ", y = " << m_vertices[i][j][0].position.y << std::endl;
            }
        }
    }
};

#endif
