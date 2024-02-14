#include<iostream>
#include <vector>
using namespace std;

class TicTacToe{
    int arr[3][3];
    public:
    void ClearBoard()
    {
        for(int i=0; i<3;i++)
        {
            for(int j=0; j<3; j++)
            {
                arr[i][j] = 0;
            }
        }
    }
    TicTacToe()
    {
        ClearBoard();
    }

    void to_string()const
    {
        cout<<" "<<arr[0][0]<<" |"<<" "<<arr[0][1]<<" |"<<" "<<arr[0][2]<<" "<<endl;
        cout<<"-----------"<<endl;
        cout<<" "<<arr[1][0]<<" |"<<" "<<arr[1][1]<<" |"<<" "<<arr[1][2]<<" "<<endl;
        cout<<"-----------"<<endl;
        cout<<" "<<arr[2][0]<<" |"<<" "<<arr[2][1]<<" |"<<" "<<arr[2][2]<<" "<<endl<<endl;
    }

    int gameStatus()const
    {
        bool isOver = false;
        if(arr[1][1] != 0 && ((arr[0][0] == arr[1][1] && arr[1][1]== arr[2][2]) || arr[0][2] == arr[1][1] && arr[1][1]== arr[2][0])) //diagonal check
            return arr[1][1];
        for(int i=0; i<3; i++)
        {
            if(arr[0][i] == arr[1][i] && arr[1][i] == arr[2][i] && arr[0][i] !=0) // vertical check
                return arr[0][i];

            if(arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2] && arr[i][0] != 0)//horizontal check
                return arr[i][0];

            for(int j=0; j<3; j++)
            {
                if(arr[i][j] == 0)
                {
                    isOver = true;
                    break;
                }
            }
        }

        if(isOver) //empty check
            return 0;
        return 3;
    }

    bool move(int player, int row, int col)
    {
        if(arr[row][col])
            return false;
        
        arr[row][col] = player;
        return true;
    }
    bool isWinningMove(int player, int row, int col)
    {
        TicTacToe tempboard(*this);
        if(tempboard.move(player,row, col))
        {
            return(tempboard.gameStatus() == player);
        }
        return false;
    }
    void bot()
    {
        bool found = false;
        int user = 1,bot=2, row=3, col=3, x,y;
        for(int i=0; i<row; i++)
        {
            for(int j=0; j<col; j++)
            {
                if(isWinningMove(user, i,j)) //checks if the user is wining
                {
                    if(move(bot, i,j))
                    {
                        found = true;
                        break;
                    }
                }
                else if(isWinningMove(bot, i,j))
                {
                    if(move(bot, i,j))
                    {
                        found = true;
                        break;
                    }
                }
            }
            if(found)
                break;
        }
        if(!found)
        {
            do
            {
                x = rand()%3;
                y = rand()%3;
            } while (!move(bot, x,y));
        }
    }

};

int main()
{
    srand(time(0));
    int player = 1, row, col;
    TicTacToe gameboard;
    cout<<"Welcome to the game of tic-tac-toe!"<<endl;
    while(!gameboard.gameStatus())
    {
        if(player == 1)
        {
            cout<<"player "<<player<<"! Enter row and col: ";
            cin>>row>>col;
            if(!gameboard.move(player, row, col))
            {
                cout<<"Place taken Try again"<<endl;
                continue;
            }
            player = 2;
        }
        else
        {
            gameboard.bot();
            player = 1;
        }
        gameboard.to_string();
    }
    if(gameboard.gameStatus() == 1)
        cout<<"Player 1 wins!!"<<endl;
    if(gameboard.gameStatus() == 2)
        cout<<"Player 2 wins!!"<<endl;
    if(gameboard.gameStatus() == 3)
        cout<<"It's a draw"<<endl;
}