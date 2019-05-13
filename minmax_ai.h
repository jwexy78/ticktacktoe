#ifndef MIN_MAX_AI_H
#define MIN_MAX_AI_H

#include <vector>
#include <iostream>

#include "game_player.h"

static int counter_board = 0;

template<typename GameType>
class MinMaxAI : public GamePlayer<GameType>
{
public:
    GameType makeMove( const GameType& currentState )
    {
        auto itr = currentState.getMovesItr();
        Board board;
        assert( itr.next( board ) );
        int bestScore = score( board, false );
        GameType bestPick = board;
        while( itr.next( board ) ) {
            int s = score( board, false, bestScore );
            if( s > bestScore ) {
                bestPick = board;
                bestScore = s;
            }
        }
        return bestPick;
    }
private:
    int score( const GameType& state, bool isMyTurn, int min = INT_MIN, int max = INT_MAX )
    {
        ++counter_board;
        auto itr = state.getMovesItr();
        Board board;
        if( !itr.next( board ) ) {
            if( state.getGameWinner() != GameType::GameWinner::Tie ) {
                return ( isMyTurn ? 1 : -1 ) * state.getScore();
            }
            return 0;
        }
        int searchMin = ( max == INT_MAX ? INT_MIN : max );
        int searchMax = ( min == INT_MIN ? INT_MAX : min );
        int bestScore = score( board, !isMyTurn );
        if( bestScore >= max ) {
            return max;
        } else if( bestScore <= min ) {
            return min;
        }
        if( isMyTurn ) {
            searchMin = bestScore;
        } else {
            searchMax = bestScore;
        }
        while( itr.next( board ) ) {
            int s = score( board, !isMyTurn, searchMin, searchMax );
            if( isMyTurn ) {
                // Maximizing game score
                if( s > bestScore ) {
                    bestScore = s;
                    if( bestScore >= max ) {
                        return max;
                    }
                }
                if( s > searchMax ) {
                    searchMax = s;
                }
            } else {
                // Minimizing game score
                if( s < bestScore ) {
                    bestScore = s;
                    if( bestScore <= min ) {
                        return min;
                    }
                }
                if( s < searchMin ) {
                    searchMin = s;
                }
            }
        }
        return bestScore;
    }
};

#endif
