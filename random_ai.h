#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <chrono>

#include "game_player.h"

template<typename GameType>
class RandomAI : public GamePlayer<GameType>
{
public:
    RandomAI()
    {
        long ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::steady_clock::now().time_since_epoch() ).count();
        srand( ns );
    }

    GameType makeMove( const GameType& currentState )
    {
        auto moves = currentState.getMoves();
        assert( moves.size() != 0 );
        return moves[rand() % moves.size()];
    }
};
