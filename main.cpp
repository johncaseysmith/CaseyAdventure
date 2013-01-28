#include <iostream>
#include "include/Game.h"

using namespace std;

int main()
{
    int i = 0;
    int score = 0;
    while (true) {
        Game game;
        Dungeon dungeon;
        while(!game.generate_dungeon(dungeon, 4 + i));
        game.populate_dungeon(dungeon);
        dungeon.boss->objects.push_back(new Princess(40, 20));
        game.io.dungeon = &dungeon;

        cout << "Please type 'start' to begin..." << endl;

        bool done = false;
        string s;
        while (!done && !game.io.done) {
            cin >> s;
            if (s == "start") {
                game.io.handle(score);
            }
        }
        i = i + 1;
        score = game.io.player.score;
    }

    return 0;
}
