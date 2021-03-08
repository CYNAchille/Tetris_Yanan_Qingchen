#ifndef BLOCK_HPP
#define BLOCK_HPP
#include<iostream>


class Block
{
private:
    int block[4];
    int type;
    int type_next;
    int blocks[7][4] =
    {
        0,2,4,6, // I
        0,2,3,5, // S
        1,3,2,4, // S
        0,2,3,4, // T
        0,2,4,5, // L
        1,3,5,4, // J
        0,1,2,3, // O
    };
    
    
public:
    struct Point {int x,y;} a[4], b[4];
    Block();
    int block_next[4];
    int getRandom(int n);
    void setBlock();
    void setBlockNext();
    int  getType();
    int  getNextType();
    void toNext();
    void rotationRight();
    void rotationLeft();
    void moveLeft();
    void moveRight();
    void moveDown();
    void bCopya();
    void aCopyb();
    
    
    

};






#endif // BLOCK_HPP
