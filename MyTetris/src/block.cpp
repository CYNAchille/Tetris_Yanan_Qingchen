#include "../include/block.hpp"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <chrono>
#include <ctime>

using namespace std;

Block::Block(){
    setBlock();
    setBlockNext();
    for (int i=0;i<4;i++)
    {
        a[i].x = block[i] % 2;
        a[i].y = block[i] / 2;
        b[i].x = a[i].x;
        b[i].y = a[i].y;
    }
    
}


int Block::getRandom(int n){
    srand(time(0)+n);
    return rand()%7;
}
                                 

void Block::setBlock()
{

    int random = getRandom(0);
    for (int i =0;i<4;i++)
    	block[i]=blocks[random][i];
    type = random;
    
}

void Block::setBlockNext()
{
    int random = getRandom(1000);
    for (int i =0;i<4;i++)
        block_next[i]=blocks[random][i];
    type_next = random;
    
}

void Block::toNext(){
    for (int i =0;i<4;i++)
        block[i]=block_next[i];
    for (int i=0;i<4;i++)
    {
        a[i].x = block_next[i] % 2;
        a[i].y = block_next[i] / 2;
        b[i].x = a[i].x;
        b[i].y = a[i].y;
    }
    type = type_next;
    setBlockNext();
}



int Block::getType(){
    return type;
}

int Block::getNextType(){
    return type_next;
}

void Block::rotationRight()
{
    Point center = a[1]; //center of rotation
    if (type==6) return;
    for (int i=0;i<4;i++)
      {
        int x = a[i].y-center.y;
        int y = a[i].x-center.x;
        a[i].x = center.x - x;
        a[i].y = center.y + y;
       }
    int OutOfLeftRange = 0;
    int OutOfRightRange = 10-1;
    for (int i=0;i<4;i++)
    {
        if (a[i].x<OutOfLeftRange) OutOfLeftRange = a[i].x;
        else if (a[i].x>OutOfRightRange) OutOfRightRange = a[i].x;
    }
  
    if (OutOfLeftRange<0) for (int i=0;i<4;i++) a[i].x = a[i].x - OutOfLeftRange;
    else if(OutOfRightRange>10-1) for (int i=0;i<4;i++) a[i].x = a[i].x - (OutOfLeftRange - (10-1));
}


void Block::rotationLeft()
{
    Point center = a[1]; //center of rotation
    if (type==6) return;
    for (int i=0;i<4;i++)
      {
        int x = a[i].y-center.y;
        int y = a[i].x-center.x;
        a[i].x = center.x + x;
        a[i].y = center.y - y;
       }
    int OutOfLeftRange = 0;
    int OutOfRightRange = 10-1;
    for (int i=0;i<4;i++)
    {
        if (a[i].x<OutOfLeftRange) OutOfLeftRange = a[i].x;
        else if (a[i].x>OutOfRightRange) OutOfRightRange = a[i].x;
    }
  
    if (OutOfLeftRange<0) for (int i=0;i<4;i++) a[i].x = a[i].x - OutOfLeftRange;
    else if(OutOfRightRange>10-1) for (int i=0;i<4;i++) a[i].x = a[i].x - (OutOfLeftRange - (10-1));
}


void Block::moveLeft(){
    for (int i=0;i<4;i++) a[i].x--;
}
void Block::moveRight(){
    for (int i=0;i<4;i++) a[i].x++;
}

void Block::moveDown(){
    for (int i=0;i<4;i++) a[i].y++;
}

void Block::aCopyb(){
    for (int i=0;i<4;i++){
        a[i].x = b[i].x;
        a[i].y = b[i].y;
    }
}
void Block::bCopya(){
    for (int i=0;i<4;i++){
        b[i].x = a[i].x;
        b[i].y = a[i].y;
    }
}
