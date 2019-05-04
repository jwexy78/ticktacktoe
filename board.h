#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include <iostream>
#include <string>

#include <assert.h>

class Board
{
public:
    enum Player : char {
        None = 0,
        X = 1,
        O = 2,
        Unknown = 3
    };

    enum GameWinner : char {
        Tie = Player::None,
        P1 = Player::X,
        P2 = Player::O
    };

    static constexpr uint32_t BITS_PER_SQUARE = 2;
    static constexpr uint32_t SQUARE_MASK = 0b11;
    static constexpr uint32_t TURN_MASK = 0b1 << 31;
    static constexpr uint32_t WINNER_OFFSET = 29;
    static constexpr uint32_t WINNER_MASK = 0b11 << WINNER_OFFSET;

    Board();

    // Required functions for being a Game
    bool getTurn() const;
    std::vector<Board> getMoves() const;
    int getScore() const;
    GameWinner getGameWinner() const;

    void makeMove( unsigned int x, unsigned int y );
    void setSquareAt( unsigned x, unsigned int y, Player value );
    Player getSquareAt( unsigned int x, unsigned int y ) const;

    Player getWinner() const;

    std::string toString() const;

private:
    // Holds the squares of the game
    // From MSB -> MSB, looks like ... <0,1><2,0:2><1,0:2><0,0:2>
    uint32_t data_;
};

Board::Board()
: data_( TURN_MASK )
{
}

bool Board::getTurn() const
{
    return !!( data_ & TURN_MASK );
}

std::vector<Board> Board::getMoves() const
{
    std::vector<Board> moves;
    if( getWinner() != Player::None ) {
        return moves;
    }
    for( unsigned int x = 0; x < 3; ++x ) {
        for( unsigned int y = 0; y < 3; ++y ) {
            if( getSquareAt( x, y ) == Player::None ) {
                Board copy( *this );
                copy.makeMove( x, y );
                moves.push_back( copy );
            }
        }
    }
    return moves;
}

void Board::makeMove( unsigned int x, unsigned int y )
{
    assert( getSquareAt( x, y ) == Player::None );
    setSquareAt( x, y, ( getTurn() ? Player::X : Player::O ) );
    data_ = data_ ^ TURN_MASK;
    Player winner = getWinner();
    data_ = ( data_ & (~WINNER_MASK) ) | ( winner << WINNER_OFFSET );
}

int Board::getScore() const
{
    Player winner = getWinner();
    if( winner == Player::None ) {
        return 0;
    }
    if( winner == ( getTurn() ? Player::X : Player::O ) ) {
        return 1;
    } else {
        return -1;
    }
}

Board::Player Board::getSquareAt( unsigned int x, unsigned int y ) const
{
    assert( x < 3 && y < 3 );
    int offset = 3 * y + x;
    int shiftDistance = offset * BITS_PER_SQUARE;
    int masked = data_ & ( SQUARE_MASK << shiftDistance );
    return (Board::Player)( masked >> shiftDistance );
}

void Board::setSquareAt( unsigned int x, unsigned int y, Board::Player value )
{
    assert( x < 3 && y < 3 );
    data_ = ( data_ & (~WINNER_MASK) ) | ( Player::Unknown << WINNER_OFFSET );
    int offset = 3 * y + x;
    int shiftDistance = offset * BITS_PER_SQUARE;
    int masked = data_ & ( ~( SQUARE_MASK << shiftDistance ) );
    data_ = masked | ( value << shiftDistance );
}

Board::GameWinner Board::getGameWinner() const
{
    auto winner = getWinner();
    if( winner == Player::X ) {
        return GameWinner::P1;
     } else if( winner == Player::O ) {
        return GameWinner::P2;
     } else {
        return GameWinner::Tie;
     }
}

Board::Player Board::getWinner() const
{
    Player winner = (Player)( ( data_ & WINNER_MASK ) >> WINNER_OFFSET );
    if( winner != Player::Unknown ) {
        return winner;
    }
    for( unsigned int x = 0; x < 3; ++x ) {
        if( getSquareAt( x, 0 ) == getSquareAt( x, 1 ) &&
            getSquareAt( x, 1 ) == getSquareAt( x, 2 ) &&
            getSquareAt( x, 0 ) != Player::None )
        {
            return getSquareAt( x, 0 );
        }
    }
    for( unsigned int y = 0; y < 3; ++y ) {
        if( getSquareAt( 0, y ) == getSquareAt( 1, y ) &&
            getSquareAt( 1, y ) == getSquareAt( 2, y ) &&
            getSquareAt( 0, y ) != Player::None )
        {
            return getSquareAt( 0, y );
        }
    }
    if( getSquareAt( 0, 0 ) == getSquareAt( 1, 1 ) &&
        getSquareAt( 1, 1 ) == getSquareAt( 2, 2 ) &&
        getSquareAt( 0, 0 ) != Player::None )
    {
        return getSquareAt( 0, 0 );
    }
    if( getSquareAt( 2, 0 ) == getSquareAt( 1, 1 ) &&
        getSquareAt( 1, 1 ) == getSquareAt( 0, 2 ) &&
        getSquareAt( 2, 0 ) != Player::None )
    {
        return getSquareAt( 2, 0 );
    }
    return Player::None;
}

std::string Board::toString() const
{
    auto ptos = []( Player p ) {
        return ( p == Player::X ? "X" :
                    ( p == Player::O ? "O" : " " ) );
    };

    std::string out;
    for( unsigned int y = 0; y < 3; ++ y ) {
        for( unsigned int x = 0; x < 3; ++x ) {
            out += ptos( getSquareAt( x, y ) );
            if( x != 2 ) {
                out += "|";
            }
        }
        if( y != 2 ) {
            out += "\n-----";
        }
        out += "\n";
    }
    return out;
}

#endif
