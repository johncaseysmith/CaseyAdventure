#include "../include/io.h"

void IO::handle(int score) {
    // Set up the handles for reading/writing:
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);

    // Title bar
    SetConsoleTitle(TEXT("My shiny new title bar!"));

    // Set up the required window size
    SMALL_RECT windowSize = {0, 0, 79, 49};

    // Change the console window size
    SetConsoleWindowInfo(wHnd, TRUE, &windowSize);

    // Create a COORD to hold the buffer size:
    COORD bufferSize = {80, 50};

    // Change the internal buffer size:
    SetConsoleScreenBufferSize(wHnd, bufferSize);

    // Set up the character buffer:
    //CHAR_INFO consoleBuffer[80 * 50];



    // Clear the CHAR_INFO buffer:
    for (int x=0; x < 80; ++x) {

        // Fill it with black-backgrounded spaces
        //consoleBuffer[i].Char.AsciiChar = 0xFE;
        //consoleBuffer[i].Attributes = 0;

        blocks.push_back(std::vector<Block>());
        // create blocks
        for (int y = 0; y < 50; ++y) {
            blocks[x].push_back(Block(x, y));
            drawBlock(&blocks[x][y]);
        }
    }

    // Set up the positions:
    COORD charBufSize = {80,50};
    COORD characterPos = {0,0};
    SMALL_RECT writeArea = {0,0,79,49};

    // Write the characters:
    WriteConsoleOutputA(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);



    // Boolean flag to state whether app is running or not.
    appIsRunning = true;


    cursorX = 40;
    cursorY = 20;
    cursorOn = false;
    drawWalls();
    player.score = score;
    objects.push_back(&player);

    char buffer1[8];
    char buffer2[8];
    for (int i = 0; i < 8; i++) {buffer1[i] = 0;}
    for (int i = 0; i < 8; i++) {buffer2[i] = 0;}

    appIsRunning = true;
    // If we set appIsRunning to false, the program will end!
    while (appIsRunning) {

        northDoor(current->north);
        eastDoor(current->east);
        southDoor(current->south);
        westDoor(current->west);

        itoa(player.score,buffer1,10);
        for (int i = 0; i < 8; i++) {
            blocks[5+i][45].setAsciiChar(buffer1[i]);
            blocks[5+i][45].setAttributes(FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
            drawBlock(&blocks[5+i][45]);
        }

        itoa(dungeon->enemies,buffer2,10);
        for (int i = 0; i < 8; i++) {
            blocks[25+i][45].setAsciiChar(buffer2[i]);
            blocks[25+i][45].setAttributes(FOREGROUND_RED | FOREGROUND_INTENSITY);
            drawBlock(&blocks[25+i][45]);
        }

        WriteConsoleOutputA(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);

        // KEYBOARD INPUT
        keyboard();

        drawObjects(objects);

        while (gameOver) {
            for (int y = 0; y < 50; ++y) {
                for (int x = 0; x < 80; ++x) {
                    blocks[x][y].setAsciiChar(rand() % 256);
                    blocks[x][y].setAttributes(rand() % 256);
                    drawBlock(&blocks[x][y]);
                    WriteConsoleOutputA(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
                    keyboard();
                    if (done) {
                        break;
                    }
                }
                if (done) {
                    break;
                }
            }
            gameOver = false;
            appIsRunning = false;
        }
    }
}

void IO::drawWalls() {

    // DRAW WALLS
    // horizontal single pipe
    for (int x = 6; x < 74; ++x) {
        //top
        blocks[x][5].setAsciiChar(0xC4);
        blocks[x][5].setAttributes(FOREGROUND_WHITE | FOREGROUND_INTENSITY);
        drawBlock(&blocks[x][5]);
        //bottom
        blocks[x][35].setAsciiChar(0xC4);
        blocks[x][35].setAttributes(FOREGROUND_WHITE | FOREGROUND_INTENSITY);
        drawBlock(&blocks[x][35]);
    }

    // vertical single pipe
    for (int y = 6; y < 35; ++y) {
        //top
        blocks[5][y].setAsciiChar(0xB3);
        blocks[5][y].setAttributes(FOREGROUND_WHITE | FOREGROUND_INTENSITY);
        drawBlock(&blocks[5][y]);
        //bottom
        blocks[74][y].setAsciiChar(0xB3);
        blocks[74][y].setAttributes(FOREGROUND_WHITE | FOREGROUND_INTENSITY);
        drawBlock(&blocks[74][y]);
    }

    // corner pipes
    blocks[5][5].setAsciiChar(0xDA);
    blocks[5][5].setAttributes(FOREGROUND_WHITE | FOREGROUND_INTENSITY);
    drawBlock(&blocks[5][5]);

    blocks[74][5].setAsciiChar(0xBF);
    blocks[74][5].setAttributes(FOREGROUND_WHITE | FOREGROUND_INTENSITY);
    drawBlock(&blocks[74][5]);

    blocks[74][35].setAsciiChar(0xD9);
    blocks[74][35].setAttributes(FOREGROUND_WHITE | FOREGROUND_INTENSITY);
    drawBlock(&blocks[74][35]);

    blocks[5][35].setAsciiChar(0xC0);
    blocks[5][35].setAttributes(FOREGROUND_WHITE | FOREGROUND_INTENSITY);
    drawBlock(&blocks[5][35]);


    // DRAW BORDER
    // horizontal double pipe
    for (int x = 1; x < 79; ++x) {
        //top
        blocks[x][0].setAsciiChar(0xCD);
        blocks[x][0].setAttributes(FOREGROUND_WHITE | FOREGROUND_INTENSITY);
        drawBlock(&blocks[x][0]);
        //bottom
        blocks[x][40].setAsciiChar(0xCD);
        blocks[x][40].setAttributes(FOREGROUND_WHITE | FOREGROUND_INTENSITY);
        drawBlock(&blocks[x][40]);
    }

    // vertical double pipe
    for (int y = 1; y < 40; ++y) {
        //top
        blocks[0][y].setAsciiChar(0xBA);
        blocks[0][y].setAttributes(FOREGROUND_WHITE | FOREGROUND_INTENSITY);
        drawBlock(&blocks[0][y]);
        //bottom
        blocks[79][y].setAsciiChar(0xBA);
        blocks[79][y].setAttributes(FOREGROUND_WHITE | FOREGROUND_INTENSITY);
        drawBlock(&blocks[79][y]);
    }

    // corner pipes
    blocks[0][0].setAsciiChar(0xC9);
    blocks[0][0].setAttributes(FOREGROUND_WHITE | FOREGROUND_INTENSITY);
    drawBlock(&blocks[0][0]);

    blocks[79][0].setAsciiChar(0xBB);
    blocks[79][0].setAttributes(FOREGROUND_WHITE | FOREGROUND_INTENSITY);
    drawBlock(&blocks[79][0]);

    blocks[79][40].setAsciiChar(0xBC);
    blocks[79][40].setAttributes(FOREGROUND_WHITE | FOREGROUND_INTENSITY);
    drawBlock(&blocks[79][40]);

    blocks[0][40].setAsciiChar(0xC8);
    blocks[0][40].setAttributes(FOREGROUND_WHITE | FOREGROUND_INTENSITY);
    drawBlock(&blocks[0][40]);
}

void IO::northDoor(bool door) {
    if (door && current->north == dungeon->boss && dungeon->enemies) {
        blocks[38][5].setAsciiChar(0xDB);
        blocks[39][5].setAsciiChar(0xDB);
        blocks[40][5].setAsciiChar(0xDB);
        blocks[41][5].setAsciiChar(0xDB);
        blocks[42][5].setAsciiChar(0xDB);
    } else if (door && current->north == dungeon->boss && !dungeon->enemies) {
        blocks[38][5].setAsciiChar(0xDB);
        blocks[39][5].setAsciiChar(0x00);
        blocks[40][5].setAsciiChar(0x00);
        blocks[41][5].setAsciiChar(0x00);
        blocks[42][5].setAsciiChar(0xDB);
    } else if (door) {
        blocks[38][5].setAsciiChar(0xC4);
        blocks[39][5].setAsciiChar(0x00);
        blocks[40][5].setAsciiChar(0x00);
        blocks[41][5].setAsciiChar(0x00);
        blocks[42][5].setAsciiChar(0xC4);
    } else {
        blocks[38][5].setAsciiChar(0xC4);
        blocks[39][5].setAsciiChar(0xC4);
        blocks[40][5].setAsciiChar(0xC4);
        blocks[41][5].setAsciiChar(0xC4);
        blocks[42][5].setAsciiChar(0xC4);
    }
    drawBlock(&blocks[38][5]);
    drawBlock(&blocks[39][5]);
    drawBlock(&blocks[40][5]);
    drawBlock(&blocks[41][5]);
    drawBlock(&blocks[42][5]);
}

void IO::eastDoor(bool door) {
    if (door && current->east == dungeon->boss && dungeon->enemies) {
        blocks[74][18].setAsciiChar(0xDB);
        blocks[74][19].setAsciiChar(0xDB);
        blocks[74][20].setAsciiChar(0xDB);
        blocks[74][21].setAsciiChar(0xDB);
        blocks[74][22].setAsciiChar(0xDB);
    } else if (door && current->east == dungeon->boss && !dungeon->enemies) {
        blocks[74][18].setAsciiChar(0xDB);
        blocks[74][19].setAsciiChar(0x00);
        blocks[74][20].setAsciiChar(0x00);
        blocks[74][21].setAsciiChar(0x00);
        blocks[74][22].setAsciiChar(0xDB);
    } else if (door) {
        blocks[74][18].setAsciiChar(0xB3);
        blocks[74][19].setAsciiChar(0x00);
        blocks[74][20].setAsciiChar(0x00);
        blocks[74][21].setAsciiChar(0x00);
        blocks[74][22].setAsciiChar(0xB3);
    } else {
        blocks[74][18].setAsciiChar(0xB3);
        blocks[74][19].setAsciiChar(0xB3);
        blocks[74][20].setAsciiChar(0xB3);
        blocks[74][21].setAsciiChar(0xB3);
        blocks[74][22].setAsciiChar(0xB3);
    }
    drawBlock(&blocks[74][18]);
    drawBlock(&blocks[74][19]);
    drawBlock(&blocks[74][20]);
    drawBlock(&blocks[74][21]);
    drawBlock(&blocks[74][22]);
}

void IO::southDoor(bool door) {
    if (door && current->south == dungeon->boss && dungeon->enemies) {
        blocks[38][35].setAsciiChar(0xDB);
        blocks[39][35].setAsciiChar(0xDB);
        blocks[40][35].setAsciiChar(0xDB);
        blocks[41][35].setAsciiChar(0xDB);
        blocks[42][35].setAsciiChar(0xDB);
    } else if (door && current->south == dungeon->boss && !dungeon->enemies) {
        blocks[38][35].setAsciiChar(0xDB);
        blocks[39][35].setAsciiChar(0x00);
        blocks[40][35].setAsciiChar(0x00);
        blocks[41][35].setAsciiChar(0x00);
        blocks[42][35].setAsciiChar(0xDB);
    } else if (door) {
        blocks[38][35].setAsciiChar(0xC4);
        blocks[39][35].setAsciiChar(0x00);
        blocks[40][35].setAsciiChar(0x00);
        blocks[41][35].setAsciiChar(0x00);
        blocks[42][35].setAsciiChar(0xC4);
    } else {
        blocks[38][35].setAsciiChar(0xC4);
        blocks[39][35].setAsciiChar(0xC4);
        blocks[40][35].setAsciiChar(0xC4);
        blocks[41][35].setAsciiChar(0xC4);
        blocks[42][35].setAsciiChar(0xC4);
    }
    drawBlock(&blocks[38][35]);
    drawBlock(&blocks[39][35]);
    drawBlock(&blocks[40][35]);
    drawBlock(&blocks[41][35]);
    drawBlock(&blocks[42][35]);
}

void IO::westDoor(bool door) {
    if (door && current->west == dungeon->boss && dungeon->enemies) {
        blocks[5][18].setAsciiChar(0xDB);
        blocks[5][19].setAsciiChar(0xDB);
        blocks[5][20].setAsciiChar(0xDB);
        blocks[5][21].setAsciiChar(0xDB);
        blocks[5][22].setAsciiChar(0xDB);
    } else if (door && current->west == dungeon->boss && !dungeon->enemies) {
        blocks[5][18].setAsciiChar(0xDB);
        blocks[5][19].setAsciiChar(0x00);
        blocks[5][20].setAsciiChar(0x00);
        blocks[5][21].setAsciiChar(0x00);
        blocks[5][22].setAsciiChar(0xDB);
    } else if (door) {
        blocks[5][18].setAsciiChar(0xB3);
        blocks[5][19].setAsciiChar(0x00);
        blocks[5][20].setAsciiChar(0x00);
        blocks[5][21].setAsciiChar(0x00);
        blocks[5][22].setAsciiChar(0xB3);
    } else {
        blocks[5][18].setAsciiChar(0xB3);
        blocks[5][19].setAsciiChar(0xB3);
        blocks[5][20].setAsciiChar(0xB3);
        blocks[5][21].setAsciiChar(0xB3);
        blocks[5][22].setAsciiChar(0xB3);
    }
    drawBlock(&blocks[5][18]);
    drawBlock(&blocks[5][19]);
    drawBlock(&blocks[5][20]);
    drawBlock(&blocks[5][21]);
    drawBlock(&blocks[5][22]);
}

void IO::keyboard() {

        // How many events have happened?
    DWORD numEvents = 0;

    // How many events have we read from the console?
    DWORD numEventsRead = 0;

    // Find out how many console events have happened:
    GetNumberOfConsoleInputEvents(rHnd, &numEvents);

    // If it's not zero (something happened...)
    if (numEvents != 0) {

        // Create a buffer of that size to store the events
        INPUT_RECORD *eventBuffer = new INPUT_RECORD[numEvents];

        // Read the console events into that buffer, and save how
        // many events have been read into numEventsRead.
        ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);

        // Now, cycle through all the events that have happened:
        for (DWORD i = 0; i < numEventsRead; ++i) {

            // Check the event type: was it a key?
            if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown) {

                // Yes! Was the key code the escape key?
                if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {

                    // Yes, it was, so set the appIsRunning to false.
                    appIsRunning = false;
                }

                // TURN CURSOR ON AND OFF
                else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'x') {
                    if (cursorOn) {
                        drawBlock(&blocks[cursorX][cursorY]);
                    } else {
                        consoleBuffer[cursorX + 80 * cursorY].Char.AsciiChar = 0xB0;
                        consoleBuffer[cursorX + 80 * cursorY].Attributes = FOREGROUND_WHITE | FOREGROUND_INTENSITY;
                    }
                    cursorOn = !cursorOn;
                }

                // CURSOR KEY CONTROL
                else if (cursorOn && cursorY > 1 && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_UP) {
                    drawBlock(&blocks[cursorX][cursorY]);
                    --cursorY;
                    consoleBuffer[cursorX + 80 * cursorY].Char.AsciiChar = 0xB0;
                    consoleBuffer[cursorX + 80 * cursorY].Attributes = FOREGROUND_WHITE | FOREGROUND_INTENSITY;
                } else if (cursorOn && cursorY < 39 && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_DOWN) {
                    drawBlock(&blocks[cursorX][cursorY]);
                    ++cursorY;
                    consoleBuffer[cursorX + 80 * cursorY].Char.AsciiChar = 0xB0;
                    consoleBuffer[cursorX + 80 * cursorY].Attributes = FOREGROUND_WHITE | FOREGROUND_INTENSITY;
                } else if (cursorOn && cursorX < 78 && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_RIGHT) {
                    drawBlock(&blocks[cursorX][cursorY]);
                    ++cursorX;
                    consoleBuffer[cursorX + 80 * cursorY].Char.AsciiChar = 0xB0;
                    consoleBuffer[cursorX + 80 * cursorY].Attributes = FOREGROUND_WHITE | FOREGROUND_INTENSITY;
                } else if (cursorOn && cursorX > 1 && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_LEFT) {
                    drawBlock(&blocks[cursorX][cursorY]);
                    --cursorX;
                    consoleBuffer[cursorX + 80 * cursorY].Char.AsciiChar = 0xB0;
                    consoleBuffer[cursorX + 80 * cursorY].Attributes = FOREGROUND_WHITE | FOREGROUND_INTENSITY;
                }

                // PLAYER CONTROLS

                else if (!cursorOn) {
                    if (player.y == 6 && current->north && blocks[player.x][player.y-1].asciiChar != 0xDB && (player.x == 39 || player.x == 40 || player.x == 41) && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_UP) {
                        drawBlock(&blocks[player.x][player.y]);
                        player.y--;
                        current = current->north;
                        for (Block* b : objects) {
                            blocks[b->x][b->y].setAsciiChar(0x00);
                            drawBlock(&blocks[b->x][b->y]);
                        }
                        objects.clear();
                        objects.push_back(&player);
                        for (Block* b : current->objects) {
                            objects.push_back(b);
                        }

                        northDoor(current->north);
                        eastDoor(current->east);
                        southDoor(current->south);
                        westDoor(current->west);
                        player.y = 34;
                    } else if (player.y == 34 && current->south && blocks[player.x][player.y+1].asciiChar != 0xDB && (player.x == 39 || player.x == 40 || player.x == 41) && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_DOWN) {
                        drawBlock(&blocks[player.x][player.y]);
                        player.y++;
                        current = current->south;
                        for (Block* b : objects) {
                            blocks[b->x][b->y].setAsciiChar(0x00);
                            drawBlock(&blocks[b->x][b->y]);
                        }
                        objects.clear();
                        objects.push_back(&player);
                        for (Block* b : current->objects) {
                            objects.push_back(b);
                        }
                        northDoor(current->north);
                        eastDoor(current->east);
                        southDoor(current->south);
                        westDoor(current->west);
                        player.y = 6;
                    } else if (player.x == 73 && current->east && blocks[player.x+1][player.y].asciiChar != 0xDB && (player.y == 19 || player.y == 20 || player.y == 21) && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_RIGHT) {
                        drawBlock(&blocks[player.x][player.y]);
                        player.x++;
                        current = current->east;
                        for (Block* b : objects) {
                            blocks[b->x][b->y].setAsciiChar(0x00);
                            drawBlock(&blocks[b->x][b->y]);
                        }
                        objects.clear();
                        objects.push_back(&player);
                        for (Block* b : current->objects) {
                            objects.push_back(b);
                        }
                        northDoor(current->north);
                        eastDoor(current->east);
                        southDoor(current->south);
                        westDoor(current->west);
                        player.x = 6;
                    } else if (player.x == 6 && current->west && blocks[player.x-1][player.y].asciiChar != 0xDB && (player.y == 19 || player.y == 20 || player.y == 21) && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_LEFT) {
                        drawBlock(&blocks[player.x][player.y]);
                        player.x--;
                        current = current->west;
                        for (Block* b : objects) {
                            blocks[b->x][b->y].setAsciiChar(0x00);
                            drawBlock(&blocks[b->x][b->y]);
                        }
                        objects.clear();
                        objects.push_back(&player);
                        for (Block* b : current->objects) {
                            objects.push_back(b);
                        }
                        northDoor(current->north);
                        eastDoor(current->east);
                        southDoor(current->south);
                        westDoor(current->west);
                        player.x = 73;
                    }

                    else if (player.getY() > 6 && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_UP) {
                        drawBlock(&blocks[player.getX()][player.getY()]);
                        player.y--;
                    } else if (player.getY() < 34 && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_DOWN) {
                        drawBlock(&blocks[player.getX()][player.getY()]);
                        player.y++;
                    } else if (player.getX() < 73 && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_RIGHT) {
                        drawBlock(&blocks[player.getX()][player.getY()]);
                        player.x++;
                    } else if (player.getX() > 6 && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_LEFT) {
                        drawBlock(&blocks[player.getX()][player.getY()]);
                        player.x--;
                    }

                    else if (gameOver && eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_RETURN) {
                        done = true;
                    }

                    for (unsigned int i = 0; i < objects.size(); i++) {
                        Block* b = objects[i];
                        if (!b->deleted && b->asciiChar != player.asciiChar && player.x == b->x && player.y == b->y) {
                            if (b->asciiChar == 0x02) { dungeon->enemies--; }
                            else if (b->asciiChar == 0x24) { player.score++; dungeon->monies--; }
                            else if (b->asciiChar == 0x0C) { gameOver = true; }
                            b->deleted = true;
                        }
                    }
                }
            }
        }

        // Clean up our event buffer:
        delete[] eventBuffer;
    }
}
