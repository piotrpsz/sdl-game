#include "game.h"
#include "actor/ball.h"

int main() {
    game_c game;
    if (game.initialize()) {
        game.run_loop();
    }
    return 0;
}
