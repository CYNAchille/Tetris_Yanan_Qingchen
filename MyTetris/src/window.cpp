#include "../include/window.hpp"
#include "../include/block.hpp"
#include "../include/Network.hpp"
#include <string>
#include<iostream>
using namespace sf;
#define FPS 2

Game::Game() : _window(sf::VideoMode(530, 480),"TETRIS"),block(){
    
    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/v.png");
    //t2.loadFromFile("images/background.png");
    //t3.loadFromFile("images/b.png");
    font.loadFromFile("images/arial.ttf");
    text.setFont(font);
    GetTexture();
    for(int i=0;i<20;i++) for (int j=0;j<10;j++) {field[i][j]=0;field_enemy[i][j]=0;}
    start=0;
    end=0;
    level=0;
    multi=0;
}



bool Game::detectCollision()
{
   for (int i=0;i<4;i++)
      if (block.a[i].x<0 || block.a[i].x>=10 || block.a[i].y>=20) return true;
      else if (field[block.a[i].y][block.a[i].x]) return true;
   return false;
};

void Game::GetTexture() {
    sprite=Sprite(t1);
    bkground=Sprite(t2);
    bkground_enemy=Sprite(t2);
    sprite_next=Sprite(t1);
    sprite_enemy=Sprite(t1);
}
void Game::toStart(){

        if(!start && !end) {
            _window.clear(Color::White);
            text.setString("  Enter a number from 0 to 9\n        to choose a level\n\n      Enter C to create a room\n\n       Enter J to join a room.");
            text.setCharacterSize(20); 
            text.setFillColor(sf::Color::Blue); 
            text.setPosition(20,150);
            _window.draw(text);
            _window.display();
        }
}

void Game::toEnd(){
        if(!start && end) {
            _window.clear(Color::White);
            text.setString("      GAME OVER!\nPress ENTER to restart");
            text.setCharacterSize(20); 
            text.setFillColor(sf::Color::Blue); 
            text.setPosition(70,200);
            _window.draw(text);
            _window.display();
        }
}

void Game::Waiting(){

            _window.clear(Color::White);
            text.setString("    Waiting for others to join in");
            text.setCharacterSize(20); 
            text.setFillColor(sf::Color::Blue); 
            text.setPosition(70,200);
            _window.draw(text);
            _window.display();

}

void Game::run() {
    sf::Clock clock;
    sf::Time time = sf::Time::Zero;
    sf::Time SPF = sf::seconds(1.f/FPS*2/(level+2));
    int isCreate=0;
    while (_window.isOpen() ) {
        if (multi==1 && join==0 && isCreate!=1){
            int i = net.CreateRoom();
            isCreate=1;
            Waiting();
        }
        else if (multi==1 && join==1 && isCreate!=1){
            int i = net.EnterRoom();
            isCreate=1;
            Waiting();
        }

        SPF = sf::seconds(1.f/FPS*2/(level+2));
        processEvents();
        toStart();
        if(!end  && start){
        bool repaint = false;
        time += clock.restart();
        if (Keyboard::isKeyPressed(Keyboard::Down)) SPF = sf::seconds(0.3/FPS*2/(level+2));
        while (time > SPF) {
            time = time%SPF;
            repaint = true;
            block.bCopya();
            update();
            if (detectCollision()){
                block.aCopyb();
                for (int i =0;i<4;i++){
                    field[block.a[i].y][block.a[i].x]=block.getType()+1;
                }
                checkLine();
                block.toNext();
                for(int i=0;i<4;i++)
                    if (field[block.a[i].y][block.a[i].x]){
			 end=1;
			 start=0;
			}
            }
        }
        if(repaint) {
           
            if(multi==1 && join==0 && isCreate==1){
            	 std::vector<int> field_vector(200);
            	 std::vector<int> field_Evector(200);
            	 for(int i=0;i<20;i++)
            	     for(int j=0;j<10;j++){
            	         field_vector[i*10+j]=field[i][j];
            	     }
                net.sendField(field_vector, net.getplayer2Ip(), net.getplayer2Port());
                net.receiveField(field_Evector, net.getplayer2Ip(), net.getplayer2Port());
                for(int i=0;i<20;i++)
            	     for(int j=0;j<10;j++){
            	         field_enemy[i][j]=field_Evector[i*10+j];
            	     }
            }
            if(multi==1 && join==1 && isCreate==1){
 		std::vector<int> field_vector(200);
 		std::vector<int> field_Evector(200);
            	 for(int i=0;i<20;i++)
            	     for(int j=0;j<10;j++){
            	         field_vector[i*10+j]=field[i][j];
            	     }
                net.sendField(field_vector, net.getplayer1Ip(), net.getplayer1Port());
 
                net.receiveField(field_Evector, net.getplayer1Ip(), net.getplayer1Port());
                for(int i=0;i<20;i++)
            	     for(int j=0;j<10;j++){
            	         field_enemy[i][j]=field_Evector[i*10+j];
            	     }
            }
           render();
        }
                
        
        
        
        
        }
        toEnd();
        
    }
}


void Game::checkLine(){
    int k=20-1;
    int n_lines=0;
    for (int i=20-1;i>0;i--)
    {
        int count=0;
        for (int j=0;j<10;j++)
        {
            if (field[i][j]) count++;
            field[k][j]=field[i][j];
        }
        if (count<10) k--;
        if (count==10) n_lines++;
    }
    score+=(level+1)*addScore(n_lines);

}

int Game::addScore(int n_lines){
    if (n_lines==0) return 0;
    else if(n_lines==1) return 40;
    else if(n_lines==2) return 100;
    else if(n_lines==3) return 300;
    else return 1200;
}

void Game::draw(){

    _window.draw(bkground);
    //_window.draw(fr);
    std::string sc=std::to_string(score) ;
    text.setString(sc);
    text.setCharacterSize(18); 
    text.setFillColor(sf::Color::Black); 
    text.setPosition(240,180);
    _window.draw(text);
    for (int i=0;i<20;i++)
         for (int j=0;j<10;j++)
           {
             if (field[i][j]==0) continue;
             sprite.setTextureRect(IntRect(field[i][j]*18,0,18,18));
             sprite.setPosition(j*18,i*18);
             sprite.move(22,22); //offset
             _window.draw(sprite);
           }
    for (int i =0;i<4;i++)
    {
    	sprite.setTextureRect(IntRect(block.getType()*18+18,0,18,18));
        sprite.setPosition(block.a[i].x*18,block.a[i].y*18);
        sprite.move(22,22);
        _window.draw(sprite);
        sprite_next.setTextureRect(IntRect(block.getNextType()*18+18,0,18,18));
        sprite_next.setPosition(block.block_next[i]%2*18,block.block_next[i]/2*18);
        sprite_next.move(262,40);
        _window.draw(sprite_next);
        
    }
    
   if (multi){
        bkground_enemy.setPosition(320,0);
        _window.draw(bkground_enemy);
            for (int i=0;i<20;i++)
         for (int j=0;j<10;j++)
           {
             if (field_enemy[i][j]==0) continue;
             sprite_enemy.setTextureRect(IntRect(field_enemy[i][j]*18,0,18,18));
             sprite_enemy.setPosition(j*18,i*18);
             sprite_enemy.move(342,22); //offset
             _window.draw(sprite_enemy);
           }

    }
    
}



void Game::processEvents() {
    sf::Event event;
    while (_window.pollEvent(event)) {
        if ((event.type == sf::Event::Closed)
          || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) {
            _window.close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            block.bCopya();
            
            if (event.key.code==Keyboard::Z && !end && start) block.rotationLeft();
             else if (event.key.code==Keyboard::Num0 && !start && !end) {start=1; end=0;level=0;}
            else if (event.key.code==Keyboard::Num1 && !start && !end) {start=1; end=0;level=1;}
            else if (event.key.code==Keyboard::Num2 && !start && !end) {start=1; end=0;level=2;}
            else if (event.key.code==Keyboard::Num3 && !start && !end) {start=1; end=0;level=3;}
            else if (event.key.code==Keyboard::Num4 && !start && !end) {start=1; end=0;level=4;}
            else if (event.key.code==Keyboard::Num5 && !start && !end) {start=1; end=0;level=5;}
            else if (event.key.code==Keyboard::Num6 && !start && !end) {start=1; end=0;level=6;}
            else if (event.key.code==Keyboard::Num7 && !start && !end) {start=1; end=0;level=7;}
            else if (event.key.code==Keyboard::Num8 && !start && !end) {start=1; end=0;level=8;}
            else if (event.key.code==Keyboard::Num9 && !start && !end) {start=1; end=0;level=9;}
            else if (event.key.code==Keyboard::C && !start && !end) {start=1; end=0;multi=1;join=0;}
            else if (event.key.code==Keyboard::J && !start && !end) {start=1; end=0;multi=1;join=1;}
            else if (event.key.code==Keyboard::Enter && !start) {reStart();}
            else if (event.key.code==Keyboard::Enter && end) {reStart();}
            else if (event.key.code==Keyboard::X && !end && start) block.rotationRight();
            else if (event.key.code==Keyboard::Left && !end && start) block.moveLeft();
            else if (event.key.code==Keyboard::Right && !end && start) block.moveRight();
            
            if (detectCollision()) block.aCopyb();
            else if (start ) render();
        }
    }
}

void Game::reStart(){
    GetTexture();
    for(int i=0;i<20;i++) for (int j=0;j<10;j++) field[i][j]=0;
    start=1;
    end=0;

}
void Game::update() {
    if(start)block.moveDown();
    
}

void Game::render() {
    _window.clear(Color::White);
    draw();
    _window.display();
}
