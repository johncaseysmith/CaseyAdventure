#ifndef BLOCK_H
#define BLOCK_H

class Block
{
    public:
        Block(int _x, int _y) : x(_x), y(_y), asciiChar(), attributes(), deleted(false) {}
        void setAsciiChar(int _asciiChar) {asciiChar = _asciiChar;}
        void setAttributes(int _attributes) {attributes = _attributes;}
        int getX() {return x;}
        int getY() {return y;}
        void setX(int _x) {x = _x;}
        void setY(int _y) {y = _y;}
        int getAsciiChar() {return asciiChar;}
        int getAttributes() {return attributes;}
        int x;
        int y;
        int attributes;
        int asciiChar;
        bool deleted;
    protected:
    private:


};

#endif // BLOCK_H
