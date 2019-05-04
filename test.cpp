#include "board.h"
#include "minmax_ai.h"

#define CATCH_CONFIG_MAIN

#include "catch.h"

TEST_CASE( "Board Functionality" )
{
    Board b[2];
    std::cout << sizeof( b ) << "\n";
    Board board;

    SECTION( "Zero Initialized" )
    {
        // Require board to be zero initialized
        REQUIRE( board.getSquareAt( 0, 0 ) == Board::Player::None );
        REQUIRE( board.getSquareAt( 1, 0 ) == Board::Player::None );
        REQUIRE( board.getSquareAt( 2, 0 ) == Board::Player::None );
        REQUIRE( board.getSquareAt( 0, 1 ) == Board::Player::None );
        REQUIRE( board.getSquareAt( 1, 1 ) == Board::Player::None );
        REQUIRE( board.getSquareAt( 2, 1 ) == Board::Player::None );
        REQUIRE( board.getSquareAt( 0, 2 ) == Board::Player::None );
        REQUIRE( board.getSquareAt( 1, 2 ) == Board::Player::None );
        REQUIRE( board.getSquareAt( 2, 2 ) == Board::Player::None );
        REQUIRE( board.getTurn() == Board::Player::X );
    }

    SECTION( "Setting and Getting" )
    {
        board.setSquareAt( 1, 1, Board::Player::X );
        board.setSquareAt( 2, 1, Board::Player::O );
        REQUIRE( board.getSquareAt( 1, 1 ) == Board::Player::X );
        REQUIRE( board.getSquareAt( 2, 1 ) == Board::Player::O );
    }

    SECTION( "Checking Vertical Winner" )
    {
        REQUIRE( board.getWinner() == Board::Player::None );
        board.setSquareAt( 1, 0, Board::Player::X );
        board.setSquareAt( 1, 1, Board::Player::X );
        board.setSquareAt( 1, 2, Board::Player::X );
        REQUIRE( board.getWinner() == Board::Player::X );
    }

    SECTION( "Checking Horizontal Winner" )
    {
        REQUIRE( board.getWinner() == Board::Player::None );
        board.setSquareAt( 0, 0, Board::Player::X );
        board.setSquareAt( 1, 0, Board::Player::X );
        board.setSquareAt( 2, 0, Board::Player::X );
        REQUIRE( board.getWinner() == Board::Player::X );
    }

    SECTION( "Basic Gameplay" )
    {
        board.makeMove( 0, 0 );
        board.makeMove( 2, 2 );
        REQUIRE( board.getSquareAt( 0, 0 ) == Board::Player::X );
        REQUIRE( board.getSquareAt( 2, 2 ) == Board::Player::O );
        REQUIRE( board.getTurn() == true );
    }
}

TEST_CASE( "MinMax AI" )
{
    Board board;
    MinMaxAI<Board> ai;

    SECTION( "Win if Possible" )
    {
        board.makeMove( 0, 0 );
        board.makeMove( 2, 0 );
        board.makeMove( 0, 1 );
        board.makeMove( 2, 1 );
        board = ai.makeMove( board );
        REQUIRE( board.getGameWinner() == Board::GameWinner::P1 );
    }

    SECTION( "Prevent Loss if Possible" )
    {
        board.makeMove( 0, 0 );
        board.makeMove( 1, 1 );
        board.makeMove( 2, 0 );
        board = ai.makeMove( board );
        REQUIRE( board.getSquareAt( 1, 0 ) == Board::Player::O );
    }

    SECTION( "Complicated Force Win" )
    {
        board.makeMove( 2, 0 );
        board.makeMove( 0, 2 );
        board = ai.makeMove( board );
        REQUIRE( board.getSquareAt( 0, 0 ) == Board::Player::X );
        board.makeMove( 1, 0 );
        board = ai.makeMove( board );
        REQUIRE( board.getSquareAt( 2, 2 ) == Board::Player::X );
        board = ai.makeMove( board );
        board = ai.makeMove( board );
        REQUIRE( board.getGameWinner() == Board::GameWinner::P1 );
    }
}
