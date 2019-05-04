#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "has_method.h"

DEFINE_HAS_CHECK_0(bool,getTurn)

// typedef std::vector vec_t;

template<typename GameType>
class GamePlayer
{
static_assert( HAS_CHECK_NAME_0(bool,getTurn)<GameType>::value,
               "GamePlayer template requires GameType to have 'bool getTurn()` defined" );
// TODO: Static Asserts
//static_assert( HAS_CHECK_NAME_1(vec_t<GameType>,getMoves)<GameType>::value,
//                "GamePlayer template requires GameType to have `vector<GameType> getMoves()` defined" );
public:
    virtual GameType makeMove( const GameType& currentState ) = 0;
};

#endif
