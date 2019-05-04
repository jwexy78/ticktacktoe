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
        Unknown
    };

    enum GameWinner : char {
        Tie = Player::None,
        P1 = Player::X,
        P2 = Player::O
    };

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

    Player turn_;
    Player squares_[9];
    Player winner_;
};

Board::Board()
: turn_( Player::X )
, squares_{ Player::None }
, winner_( Player::None )
{
}

bool Board::getTurn() const
{
    return turn_ == Player::X;
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
    setSquareAt( x, y, turn_ );
    turn_ = ( turn_ == Player::X ? Player::O : Player::X );
    winner_ = getWinner();
}

int Board::getScore() const
{
    Player winner = getWinner();
    if( winner == Player::None ) {
        return 0;
    }
    if( winner == turn_ ) {
        return 1;
    } else {
        return -1;
    }
}

Board::Player Board::getSquareAt( unsigned int x, unsigned int y ) const
{
    assert( x < 3 && y < 3 );
    return squares_[3 * y + x];
}

void Board::setSquareAt( unsigned int x, unsigned int y, Board::Player value )
{
    assert( x < 3 && y < 3 );
    winner_ = Player::Unknown;
    squares_[3 * y + x] = value;
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
    if( winner_ != Player::Unknown ) {
        return winner_;
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
