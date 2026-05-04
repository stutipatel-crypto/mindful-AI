#include<iostream>
#include<windows.h>
using namespace std;

// 🎨 Color function
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 🔹 Base Class
class Base
{
public:
    virtual void board() = 0;
};

// 🔹 Derived Class
class TicTacToe : public Base
{
private:
    char brd[3][3];
    char turn;
    int row, column;
    bool draw;

    int scoreX = 0;
    int scoreO = 0;

public:

    TicTacToe() {
        reset();
    }

    void reset() {
        char count = '1';
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                brd[i][j] = count++;

        turn = 'X';
        draw = false;
    }

    // 🔹 Polymorphism
    void board()
    {
        system("cls");

        setColor(11);
        cout<<"\n\n\t TIC TAC TOE GAME\n";

        setColor(10);
        cout<<"\n\tPlayer1 [X] Score: "<<scoreX;

        setColor(12);
        cout<<"\n\tPlayer2 [O] Score: "<<scoreO<<"\n";

        setColor(7);
        cout<<"\n\t     |     |     \n";

        for(int i=0;i<3;i++) {
            cout<<"\t  ";
            for(int j=0;j<3;j++) {

                if(brd[i][j]=='X') setColor(10);
                else if(brd[i][j]=='O') setColor(12);
                else setColor(7);

                cout<<brd[i][j];

                setColor(7);
                if(j<2) cout<<"  |  ";
            }

            cout<<"\n";
            if(i<2) cout<<"\t_____|_____|_____\n\t     |     |     \n";
        }
        cout<<"\n";
    }

    void player_turn()
    {
        int choice;

        setColor(14);
        if(turn=='X')
            cout<<"Player1 [X] turn: ";
        else
            cout<<"Player2 [O] turn: ";

        setColor(7);
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
                cout<<"Invalid choice!\n";
                Beep(300,300);
                player_turn();
                return;
        }

        if(brd[row][column]!='X' && brd[row][column]!='O')
        {
            brd[row][column]=turn;
            Beep(800,100);

            turn = (turn=='X') ? 'O' : 'X';
        }
        else
        {
            cout<<"Box already filled!\n";
            Beep(300,300);
            player_turn();
        }
    }

    bool gameover()
    {
        for(int i=0;i<3;i++)
        {
            if(brd[i][0]==brd[i][1] && brd[i][1]==brd[i][2])
                return false;

            if(brd[0][i]==brd[1][i] && brd[1][i]==brd[2][i])
                return false;
        }

        if(brd[0][0]==brd[1][1] && brd[1][1]==brd[2][2])
            return false;

        if(brd[0][2]==brd[1][1] && brd[1][1]==brd[2][0])
            return false;

        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                if(brd[i][j]!='X' && brd[i][j]!='O')
                    return true;

        draw = true;
        return false;
    }

    void updateScore()
    {
        if(turn=='O') scoreX++;
        else scoreO++;
    }

    void play()
    {
        char choice;

        do {
            reset();

            while(gameover())
            {
                board();
                player_turn();
            }

            board();

            if(turn=='O' && draw==false) {
                setColor(10);
                cout<<"🎉 Player1 [X] Wins!\n";
                updateScore();
            }
            else if(turn=='X' && draw==false) {
                setColor(12);
                cout<<"🎉 Player2 [O] Wins!\n";
                updateScore();
            }
            else {
                setColor(14);
                cout<<"😐 Game is Draw!\n";
            }

            Beep(1000,200);
            Beep(1200,200);

            setColor(7);
            cout<<"\nPlay again? (y/n): ";
            cin>>choice;

        } while(choice=='y' || choice=='Y');

        setColor(11);
        cout<<"\nFinal Score:\n";

        setColor(10);
        cout<<"Player1 [X]: "<<scoreX<<"\n";

        setColor(12);
        cout<<"Player2 [O]: "<<scoreO<<"\n";

        setColor(7);
    }
};

int main()
{
    TicTacToe t;
    t.play();
    return 0;
}