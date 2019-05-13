#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <chrono>

#include "game_player.h"
#include "board.h"

template<typename T>
class UserPlayer : public GamePlayer<Board>
{
public:
    Board makeMove( const Board& currentState )
    {
        int x, y;
        std::cout << currentState.toString() << "\n";
        do
        {
            std::cout << "Please enter your move as \"x y\"\n";
        } while( !( std::cin >> x >> y ) || x < 0 || x >= 3 || y < 0 || y >= 3 || currentState.getSquareAt( x, y ) != Board::Player::None );
        Board copy( currentState );
        copy.makeMove( x, y );
        return copy;
    }
};
