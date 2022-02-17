#include<iostream>
#include<vector>

using namespace std;

class Player {

public:
    Player()
    {

    }

    Player(string _name, char _piece)
    {
        name = _name;
        piece = _piece;
    }

    string get_name()
    {
        return name;
    }

    void set_name(string _name)
    {
        name = _name;
    }

    char get_piece()
    {
        return piece;
    }

    void set_piece(char _piece)
    {
        piece = _piece;
    }


private:
    string name;
    char piece;
};

class Board {

public:
    Board()
    {
        board_status.clear();
    }

    Board(int _board_length) 
    {
        board_length = _board_length;
        is_winner_found = false;
        winner = -1;
        for(int i = 0; i < board_length; i++) {
            vector<char> row_of_board(board_length, '-');
            board_status.push_back(row_of_board);
        }
    }

    char get_piece_at_position(int _row, int _column)
    {
        return board_status[_row][_column];
    }

    void add_piece_to_board(char _piece)
    {

    }

    bool is_move_valid()
    {

    }

    void print_board_status()
    {
        for(int i = 0; i < board_length; i++) {
            for(int j = 0; j < board_length; j++) {
                cout << board_status[i][j] << " ";
            }
            cout << endl;
        }
    }

    int move()
    {

    }

private:
    int board_length;
    bool is_winner_found;
    int winner;
    vector< vector<char> > board_status;
};

class Game {

public:

private:
    vector<Player> players;
    Board board;
};

int main()
{

}