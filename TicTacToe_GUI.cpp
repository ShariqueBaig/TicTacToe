#include<iostream>
#include <vector>
#include "raylib.h"
using namespace std;
const int swidth = 800, sheight = 800, offset = 50;
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

    void print_board() const
    {
        ClearBackground(LIGHTGRAY);
        // DrawRectangle(offset, offset, (swidth - offset*2 ), 0, BLACK);
        DrawRectangle(offset, sheight/3, (swidth - offset*2 ), 40, BLACK); // horizontal line
        DrawRectangle(offset, 2*sheight/3, (swidth - offset*2 ), 40, BLACK); //horizontal line
        DrawRectangle(swidth/3, offset, 40 , (swidth - offset*2), BLACK); //vertical line
        DrawRectangle(2*swidth/3, offset, 40, (swidth - offset*2), BLACK); //vertical line

        if(arr[0][0])
        {
            DrawText(TextFormat("%i", arr[0][0]), 150,80, 200, YELLOW);
            // if(arr[0][0] == 1)
            //     DrawText("X", 150,150, 100, YELLOW);  to add later
        }
        if(arr[0][1])
            DrawText(TextFormat("%i", arr[0][1]), 150 + (swidth- offset*2)/3,80 , 200, YELLOW);
        if(arr[0][2])
            DrawText(TextFormat("%i", arr[0][2]), 150 + 2*(swidth- offset*2)/3,80 , 200, YELLOW);
        if(arr[1][0])
            DrawText(TextFormat("%i", arr[1][0]), 150,80 + 20 +(sheight- offset*2)/3, 200, YELLOW);
        if(arr[1][1])
            DrawText(TextFormat("%i", arr[1][1]), 150 + (swidth- offset*2)/3,80 + 20+(sheight- offset*2)/3, 200, YELLOW);
        if(arr[1][2])
            DrawText(TextFormat("%i", arr[1][2]), 150 + 2*(swidth- offset*2)/3,80 + 20 + (sheight- offset*2)/3, 200, YELLOW);
        if(arr[2][0])
            DrawText(TextFormat("%i", arr[2][0]), 150,80 +20+ 2*(sheight- offset*2)/3, 200, YELLOW);
        if(arr[2][1])
            DrawText(TextFormat("%i", arr[2][1]), 150 + (swidth- offset*2)/3,80 +20+ 2*(sheight- offset*2)/3, 200, YELLOW);
        if(arr[2][2])
            DrawText(TextFormat("%i", arr[2][2]), 150 + 2*(swidth- offset*2)/3,80 +20+ 2*(sheight- offset*2)/3, 200, YELLOW);
    }

    // void to_string()const
    // {
    //     cout<<" "<<arr[0][0]<<" |"<<" "<<arr[0][1]<<" |"<<" "<<arr[0][2]<<" "<<endl;
    //     cout<<"-----------"<<endl;
    //     cout<<" "<<arr[1][0]<<" |"<<" "<<arr[1][1]<<" |"<<" "<<arr[1][2]<<" "<<endl;
    //     cout<<"-----------"<<endl;
    //     cout<<" "<<arr[2][0]<<" |"<<" "<<arr[2][1]<<" |"<<" "<<arr[2][2]<<" "<<endl<<endl;
    // }

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

    void player1win()
    {
        ClearBackground(BLUE);
        DrawText("Player 1 won!!", offset, sheight/2, 100, BLACK);
    }
    void player2win()
    {
        ClearBackground(BLUE);
        DrawText("Player 2 won!!", offset, sheight/2, 100, BLACK);
    }
    void draw()
    {
        ClearBackground(BLUE);
        DrawText("Its a draw!", offset, sheight/2, 100, BLACK);
    }

};

int main()
{
    Vector2 mousepos = {-1.0f, -1.0f};
    InitWindow(swidth, sheight, "TicTacToe go brrrrrr!!!");
    SetTargetFPS(60);
    srand(time(0));
    int player = 1, row, col;
    TicTacToe gameboard;
    // cout<<"Welcome to the game of tic-tac-toe!"<<endl;
    while(!WindowShouldClose())
    {
        while(!gameboard.gameStatus())
        {
            BeginDrawing();
            ClearBackground(WHITE);
            if(player == 1)
            {
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {    
                    mousepos = GetMousePosition();// complete this
                    if(mousepos.x >= 50 && mousepos.y>= 50 && mousepos.x <= 260 && mousepos.y <= 260)
                    {
                        row = 0, col =0;
                        if(!gameboard.move(player, row, col))
                        {
                            cout<<"Place taken Try again"<<endl;
                            continue;
                        }
                        player = 2;
                    }
                    else if(mousepos.x >= 310 && mousepos.y>= 50 && mousepos.x <= 530 && mousepos.y <= 260)
                    {
                        row = 0, col =1;
                        if(!gameboard.move(player, row, col))
                        {
                            cout<<"Place taken Try again"<<endl;
                            continue;
                        }
                        player = 2;
                    }
                    else if(mousepos.x >= 580 && mousepos.y>= 50 && mousepos.x <= 750 && mousepos.y <= 260)
                    {
                        row = 0, col =2;
                        if(!gameboard.move(player, row, col))
                        {
                            cout<<"Place taken Try again"<<endl;
                            continue;
                        }
                        player = 2;
                    }
                    else if(mousepos.x >= 60 && mousepos.y>= 310 && mousepos.x <= 260 && mousepos.y <= 530)
                    {
                        row = 1, col =0;
                        if(!gameboard.move(player, row, col))
                        {
                            cout<<"Place taken Try again"<<endl;
                            continue;
                        }
                        player = 2;
                    }
                    else if(mousepos.x >= 310 && mousepos.y>= 310 && mousepos.x <= 530 && mousepos.y <= 530)
                    {
                        row = 1, col =1;
                        if(!gameboard.move(player, row, col))
                        {
                            cout<<"Place taken Try again"<<endl;
                            continue;
                        }
                        player = 2;
                    }
                    else if(mousepos.x >= 580 && mousepos.y>= 310 && mousepos.x <= 750 && mousepos.y <= 530)
                    {
                        row = 1, col =2;
                        if(!gameboard.move(player, row, col))
                        {
                            cout<<"Place taken Try again"<<endl;
                            continue;
                        }
                        player = 2;
                    }
                    else if(mousepos.x >= 60 && mousepos.y>= 580 && mousepos.x <= 260 && mousepos.y <= 750)
                    {
                        row = 2, col =0;
                        if(!gameboard.move(player, row, col))
                        {
                            cout<<"Place taken Try again"<<endl;
                            continue;
                        }
                        player = 2;
                    }
                    else if(mousepos.x >= 310 && mousepos.y>= 580 && mousepos.x <= 530 && mousepos.y <= 750)
                    {
                        row = 2, col =1;
                        if(!gameboard.move(player, row, col))
                        {
                            cout<<"Place taken Try again"<<endl;
                            continue;
                        }
                        player = 2;
                    }
                    else if(mousepos.x >= 580 && mousepos.y>= 580 && mousepos.x <= 750 && mousepos.y <= 750)
                    {
                        row = 2, col =2;
                        if(!gameboard.move(player, row, col))
                        {
                            cout<<"Place taken Try again"<<endl;
                            continue;
                        }
                        player = 2;
                    }
                }
                
                // cout<<"player "<<player<<"! Enter row and col: ";
                // cin>>row>>col;
            }
            else
            {
                gameboard.bot();
                player = 1;
            }
            // gameboard.to_string();
            gameboard.print_board();
            EndDrawing();
        }
        BeginDrawing();
        if(gameboard.gameStatus() == 1)
            gameboard.player1win();
            // cout<<"Player 1 wins!!"<<endl;
        if(gameboard.gameStatus() == 2)
            gameboard.player2win();
            // cout<<"Player 2 wins!!"<<endl;
        if(gameboard.gameStatus() == 3)
            gameboard.draw();
            // cout<<"It's a draw"<<endl;
        EndDrawing();
    }
}