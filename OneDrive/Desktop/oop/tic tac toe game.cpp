#include<iostream>
using namespace std;

char brd[3][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'}};
char turn='X';
int row,column;
bool draw = false;

void bord()
{
    system("cls");
    cout<<"\n\n\t TIC TAC TOE GAME\n";
    cout<<"\n\tPlayer1 [X]\n\tPlayer2 [O]\n";

    cout<<"\t\t     |     |     \n";
    cout<<"\t\t  "<<brd[0][0]<<"  |  "<<brd[0][1]<<"  |  "<<brd[0][2]<<"\n";
    cout<<"\t\t_____|_____|_____\n";
    cout<<"\t\t     |     |     \n";
    cout<<"\t\t  "<<brd[1][0]<<"  |  "<<brd[1][1]<<"  |  "<<brd[1][2]<<"\n";
    cout<<"\t\t_____|_____|_____\n";
    cout<<"\t\t     |     |     \n";
    cout<<"\t\t  "<<brd[2][0]<<"  |  "<<brd[2][1]<<"  |  "<<brd[2][2]<<"\n";
    cout<<"\t\t     |     |     \n";
}

void player_turn()
{
    int choice;
    
    if(turn=='X')
        cout<<"\nPlayer1 [X], enter position (1-9): ";
    else
        cout<<"\nPlayer2 [O], enter position (1-9): ";
    
    cin>>choice;

    switch(choice)
    {
        case 1: row=0; column=0; break;
        case 2: row=0; column=1; break;
        case 3: row=0; column=2; break;
        case 4: row=1; column=0; break;
        case 5: row=1; column=1; break;
        case 6: row=1; column=2; break;
        case 7: row=2; column=0; break;
        case 8: row=2; column=1; break;
        case 9: row=2; column=2; break;
        default:
            cout<<"Invalid choice! Try again.\n";
            player_turn();
            return;
    }

    if(brd[row][column] != 'X' && brd[row][column] != 'O')
    {
        brd[row][column] = turn;
        turn = (turn == 'X') ? 'O' : 'X';
    }
    else
    {
        cout<<"Box already filled! Try again.\n";
        player_turn();
    }
}

bool gameover()
{
    // Rows & Columns
    for(int i=0;i<3;i++)
    {
        if((brd[i][0]==brd[i][1] && brd[i][1]==brd[i][2]) ||
           (brd[0][i]==brd[1][i] && brd[1][i]==brd[2][i]))
            return false;
    }

    // Diagonals
    if((brd[0][0]==brd[1][1] && brd[1][1]==brd[2][2]) ||
       (brd[0][2]==brd[1][1] && brd[1][1]==brd[2][0]))
        return false;

    // Continue game
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(brd[i][j] != 'X' && brd[i][j] != 'O')
                return true;

    draw = true;
    return false;
}

int main()
{
    while(gameover())
    {
        bord();
        player_turn();
    }

    bord();

    if(draw == false)
    {
        if(turn == 'X')
            cout<<"\nPlayer2 [O] wins!\n";
            else 
        
        cout<<"\nPlayer1 [X] wins!\n";
    }