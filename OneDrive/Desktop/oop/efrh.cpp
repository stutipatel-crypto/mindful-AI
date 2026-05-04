#include<iostream>
using namespace std;

// 🔹 Base Class (Abstraction + Inheritance)
class Board
{
protected:
    char brd[3][3];

public:
    Board()
    {
        char ch = '1';
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                brd[i][j] = ch++;
    }

    // 🔹 Virtual Function (Polymorphism)
    virtual void display()
    {
        cout<<"\n";
        for(int i=0;i<3;i++)
        {
            cout<<"  "<<brd[i][0]<<" | "<<brd[i][1]<<" | "<<brd[i][2]<<"\n";
            if(i<2) cout<<" ---|---|---\n";
        }
        cout<<"\n";
    }
};

// 🔹 Derived Class (Inheritance + Encapsulation)
class Game : public Board
{
private:
    char turn;
    bool draw;

public:
    Game()
    {
        turn = 'X';
        draw = false;
    }

    void playerTurn()
    {
        int choice;
        cout<<"Player "<<turn<<" turn: ";
        cin>>choice;

        int row = (choice-1)/3;
        int col = (choice-1)%3;

        if(choice<1 || choice>9 || brd[row][col]=='X' || brd[row][col]=='O')
        {
            cout<<"Invalid move! Try again.\n";
            playerTurn();
            return;
        }

        brd[row][col] = turn;
        turn = (turn=='X') ? 'O' : 'X';
    }

    bool gameOver()
    {
        // rows & columns
        for(int i=0;i<3;i++)
        {
            if(brd[i][0]==brd[i][1] && brd[i][1]==brd[i][2])
                return false;

            if(brd[0][i]==brd[1][i] && brd[1][i]==brd[2][i])
                return false;
        }

        // diagonals
        if(brd[0][0]==brd[1][1] && brd[1][1]==brd[2][2])
            return false;

        if(brd[0][2]==brd[1][1] && brd[1][1]==brd[2][0])
            return false;

        // check empty
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                if(brd[i][j]!='X' && brd[i][j]!='O')
                    return true;

        draw = true