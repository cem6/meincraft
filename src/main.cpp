#include "settings.h"

#include "game.h"
#include "window.h"
#include <iostream>

#include "World/block.h"

int main()
{


    Window window; // muss vor Game instanziiert werden


    Game game;
    game.renderloop();




    return 0;
}


