#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "Network.hpp"
#include "block.hpp"


#include <SFML/Graphics.hpp>
#include <time.h>
#define FPS 2
using namespace sf;
   
class Game {
private:
    sf::RenderWindow _window;
    Sprite sprite,sprite_next,sprite_enemy,bkground,bkground_enemy;
    Texture t1,t2,t3;
    Font font;
    Text text;
    int field[20][10];
    int field_enemy[20][10];
    bool start,end;
    int score;
    int level;
    bool multi;
    bool join;
    Network net;
    Block block;
    void Waiting();
    bool detectCollision();
    void GetTexture();
    void draw();
    void toStart();
    void toEnd();
    int addScore(int n_lines);
    void processEvents();
    void update();
    void render();
    void reStart();
    void checkLine();
public:
    Game();
    void run();
};


#endif // WINDOW_HPP
