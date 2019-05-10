#ifndef MIN_MAX_AI_H
#define MIN_MAX_AI_H

#include <vector>
#include <iostream>

#include "game_player.h"

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
            int s = score( board, false );
            if( s > bestScore ) {
                bestPick = board;
                bestScore = s;
            }
        }
        return bestPick;
    }
private:
    int score( const GameType& state, bool isMyTurn )
    {
        auto itr = state.getMovesItr();
        Board board;
        if( !itr.next( board ) ) {
            if( state.getGameWinner() != GameType::GameWinner::Tie ) {
                return ( isMyTurn ? 1 : -1 ) * state.getScore();
            }
            return 0;
        }
        int bestScore = score( board, !isMyTurn );
        while( itr.next( board ) ) {
            int s = score( board, !isMyTurn );
            if( isMyTurn && s > bestScore ) {
                bestScore = s;
            } else if( !isMyTurn && s < bestScore ) {
                bestScore = s;
            }
        }
        return bestScore;
    }

/*
    int alphabeta(state_t state, int depth, int alpha, int beta, small_int_t maximizingPlayer)
    {
        if(depth == 0)
        {
            int score = heuristic_score(state);
            //cout << "Heuristic score = " << score << "\n";
            return score;
        }

        //cout << ">>> Looking At Children...\n";

        if(maximizingPlayer)
        {
            int v = -1 * LARGE_VALUE;
            std::vector<state_t> moves = state.get_all_legal_moves();
            for(auto i = moves.begin(); i != moves.end(); ++i)
            {
                int abscore = alphabeta(*i, depth - 1, alpha, beta, 0);
                //cout << "Got Child Score: " << abscore;
                if(abscore > v)
                    v = abscore;
                
                if(abscore > alpha)
                    alpha = abscore;
                if(beta <= alpha)
                    break;
                //cout << " (" << v << ", " << alpha << ", " << beta << ")\n";
            }
            //cout << ">>> Got Score: " << v << "\n";
            return v;
        }
        else
        {
            int v = LARGE_VALUE;
            std::vector<state_t> moves = state.get_all_legal_moves();
            for(auto i = moves.begin(); i != moves.end(); ++i)
            {
                int abscore = alphabeta(*i, depth - 1, alpha, beta, 0);
                if(abscore < v)
                    v = abscore;
                if(abscore < beta)
                    beta = abscore;
                if(beta <= alpha)
                    break;
                //cout << ">>> Got Score: " << v << "\n";
            }
            return v;
        }
    }*/
/*

    int score_for_me(board_t board, int my_piece)
    {
        int winner = board.get_winner();
        // If I won the board, that's good!
        if(winner == my_piece)
            return 1;
        // If there's a winner who's not me, that's bad
        if(winner != 0)
            return -1;

        std::vector<board_t> moves = board.get_all_moves();
        // If I stalemated the board, that's meh
        if(moves.size() == 0)
            return 0;

        int their_best_score = -2;
        for(auto m = moves.begin(); m != moves.end(); m++)
        {
            // Get how they score their position after me doing a move
            int their_score = score_for_me(*m, (my_piece == X_SQUARE ? O_SQUARE : X_SQUARE));
            if(their_score > their_best_score)
                their_best_score = their_score;
        }
        return -1 * their_best_score;
    }

    board_t get_move(board_t board)
    {
        board_t move;
        int turn = board.get_turn();
        std::vector<board_t> moves = board.get_all_moves();
        int max_score = -2;
        for(int i = 0; i < moves.size(); i++)
        {
            int score = score_for_me(moves[i], board.get_turn());
            if(score > max_score)
            {
                max_score = score;
                move = moves[i];
            }
        }
        return move;
    }
    */
};

#endif
