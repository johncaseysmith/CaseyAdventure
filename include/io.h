#ifndef IO_H
#define IO_H

#include <stdlib.h>
#include <stdio.h>
#include <Tchar.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <Windows.h>
#include "../include/block.h"
#include "../include/player.h"
#include "../include/monster.h"
#include "../include/princess.h"
#include "../include/treasure.h"
#include "../include/Dungeon.h"

#define FOREGROUND_WHITE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

class IO
{
    public:
        IO() : wHnd(), rHnd(), player(40, 20, 1), dungeon(0), gameOver(false), done(false) {}
        void handle(int score);
        void drawBlock(Block* b) {
            consoleBuffer[b->getX() + 80 * b->getY()].Char.AsciiChar = b->getAsciiChar();
            consoleBuffer[b->getX() + 80 * b->getY()].Attributes = b->getAttributes();
        }
        void drawObjects(std::vector<Block*> objects) { for (Block* b : objects) { if (!b->deleted) drawBlock(b); } }
        std::vector<Block*> objects;
        Room* current;
        Dungeon* dungeon;
        bool done;
        Player player;
    protected:
    private:
        HANDLE wHnd;
        HANDLE rHnd;
        CHAR_INFO consoleBuffer[80 * 50];
        bool appIsRunning;
        bool cursorOn;
        int cursorX;
        int cursorY;
        void drawWalls();
        void northDoor(bool door);
        void eastDoor(bool door);
        void southDoor(bool door);
        void westDoor(bool door);
        void keyboard();
        std::vector<std::vector<Block>> blocks;

        bool gameOver;

};

#endif // IO_H
