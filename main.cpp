#include<iostream>
#include<vector>

#define BOARD_SIZE 3

using namespace std;

class Player {

public:
    Player()
    {

    }

    Player(string _piece, string _name)
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

    string get_piece()
    {
        return piece;
    }

    void set_piece(char _piece)
    {
        piece = _piece;
    }


private:
    string name;
    string piece;
};

class Board {

public:
    Board(){}

    Board(int _board_length) 
    {
        board_length = _board_length;
        total_moves = 0;
        for(int i = 0; i < board_length; i++) {
            vector<string> row_of_board(board_length, "-");
            board_status.push_back(row_of_board);
        }
    }

    string get_piece_at_position(int _row, int _column)
    {
        return board_status[_row][_column];
    }

    int get_board_length() 
    {
        return board_length;
    }

    bool is_move_valid(int _row, int _column)
    {
        if(board_status[_row][_column] == "-") {
            return true;
        }
        else {
            return false;
        }
    }

    bool is_board_full() {
        if(total_moves == board_length * board_length) {
            return true;
        }
        else {
            return false;
        }
    }

    void add_piece_to_board(string _piece, int _row, int _column)
    {
        board_status[_row][_column] = _piece;
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

    bool move(int _row, int _column, string _piece)
    {
        if(!is_move_valid(_row, _column)) {
            return false;
        }
        else {
            add_piece_to_board(_piece, _row, _column);
            total_moves++;
            return true;
        }
    }

private:
    int board_length;
    int total_moves;
    vector< vector<string> > board_status;
};

class Game {

public:
    Game()
    {
        is_winner_found = false;
        winner = -1;
    }

    Game(vector< pair<string,string> > _names, int _board_size, vector< pair<int,int> > _moves)
    {
        board = Board(_board_size);
        moves = _moves;

        for(int i = 0; i < _names.size(); i++) {
            Player new_player = Player(_names[i].first, _names[i].second);
            players.push_back(new_player);
        }

        is_winner_found = false;
        winner = -1;
    }

    bool check_winner(int _row, int _column, string _piece)
    {
        bool check_row = true;
        for(int i = 0; i < board.get_board_length(); i++) {
            if(i == _column) {
                continue;
            }
            if(board.get_piece_at_position(_row, i) != _piece) {
                check_row = false;
                break;
            }
        }
        if(check_row) {
            return true;
        }

        bool check_column = true;
        for(int i = 0; i < board.get_board_length(); i++) {
            if(i == _row) {
                continue;
            }
            if(board.get_piece_at_position(i, _column) != _piece) {
                check_column = false;
                break;
            }
        }
        if(check_column) {
            return true;
        }

        if(_row == _column) {
            bool check_diagonal = true;
            for(int i = 0; i < board.get_board_length(); i++) {
                if(i == _row) {
                    continue;
                }
                if(board.get_piece_at_position(i, i) != _piece) {
                    check_diagonal = false;
                    break;
                }
            }
            if(check_diagonal) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }

    void print_winner_name() 
    {
        cout << players[winner].get_name() << " has won the game" << endl;
    }
    
    void play_game() 
    {
        int turn = 0;
        int move_number = 0;
        board.print_board_status();
        while(!is_winner_found && !board.is_board_full() && (move_number < moves.size())) {
            int current_turn = turn % 2;
            int row, column;

            row = moves[move_number].first;
            column = moves[move_number].second;

            if(row == -1) {
                break;
            }

            bool did_move = board.move(row, column, players[current_turn].get_piece());

            if(!did_move) {
                cout << "Invalid Move" << endl;
            }
            else {
                board.print_board_status();
                is_winner_found = check_winner(row, column, players[current_turn].get_piece());
                if(is_winner_found == true) {
                    winner = current_turn;
                    print_winner_name();
                }
                turn++;
            }
            move_number++;
            
        }
        if(board.is_board_full()) {
            cout << "Game Over" << endl;
        }
    }

private:
    vector<Player> players;
    Board board;
    vector< pair<int,int> > moves; 
    bool is_winner_found;
    int winner;
};

void get_players_info(Game& _game)
{
    string player_one, player_two;
    getline(cin, player_one);
    getline(cin, player_two);

    vector< pair<string,string> > player_details;
    pair<string,string> player_one_details, player_two_details;

    string temp = "";
    for(int i = 0; i < player_one.length(); i++) {
        if(player_one[i] == ' ') {
            player_one_details.first = temp;
            temp = "";
        }
        else {
            temp += player_one[i];
        }
    }
    player_one_details.second = temp;
    player_details.push_back(player_one_details);

    temp = "";
    for(int i = 0; i < player_two.length(); i++) {
        if(player_two[i] == ' ') {
            player_two_details.first = temp;
            temp = "";
        }
        else {
            temp += player_two[i];
        }
    }
    player_two_details.second = temp;

    player_details.push_back(player_two_details);

    string row = "", column = "";
    string move_input = "";
    vector< pair<int,int> > moves;

    getline(cin,move_input);
    while(move_input != "exit") {
        size_t space_found = move_input.find(" ");
        row = move_input.substr(0, space_found);
        column = move_input.substr(space_found + 1, move_input.length() - space_found - 1);

        pair<int,int> move;
        move.first = (stoi(row) - 1);
        move.second = (stoi(column) - 1);
        moves.push_back(move);

        getline(cin,move_input);
    }
    moves.push_back(make_pair(-1,-1));

    _game = Game(player_details, BOARD_SIZE, moves);
}

int main()
{
    Game game;
    get_players_info(game);
    game.play_game();
}