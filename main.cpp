#include <iostream>
#include <vector>
#include <unistd.h>

#include "board.h"
#include "random_ai.h"
#include "minmax_ai.h"

template<template<typename> class GP1, template<typename> class GP2, typename GameType>
void play( int rounds, int& wins1, int& wins2, int& ties )
{
    wins1 = 0;
    wins2 = 0;
    ties = 0;
    GP1<GameType> p1;
    GP2<GameType> p2;
    for( int i = 0; i < rounds; ++i ) {
        GameType game;
        bool p1Starting = i & 1;
        bool playerTurn = p1Starting;
        while( game.getMoves().size() > 0 &&
               game.getWinner() == Board::Player::None )
        {
            if( playerTurn ) {
                game = p1.makeMove( game );
            } else {
                game = p2.makeMove( game );
            }
            playerTurn = !playerTurn;
        }
        if( game.getGameWinner() == GameType::GameWinner::P1 ) {
            if( p1Starting ) {
                wins1++;
            } else {
                wins2++;
            }
        } else if( game.getGameWinner() == GameType::GameWinner::P2 ) {
            if( p1Starting ) {
                wins2++;
            } else {
                wins1++;
            }
        } else {
            ties++;
        }
        std::cout << game.toString() << "\n";
    }
}

int main()
{
    int win1;
    int win2;
    int ties;
    play<MinMaxAI,RandomAI,Board>( 100, win1, win2, ties );
    std::cout << "P1 Wins: " << win1 << "\nP2 Wins: " << win2 << "\nTies: "
              << ties << "\n";
//    play<MinMaxAI,MinMaxAI,Board>( 100, win1, win2, ties );
//    std::cout << "P1 Wins: " << win1 << "\nP2 Wins: " << win2 << "\nTies: "
//              << ties << "\n";
}
