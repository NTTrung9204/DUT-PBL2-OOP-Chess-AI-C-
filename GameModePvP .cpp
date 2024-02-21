// #include"ManageGame.cpp"
// #include"chess1.cpp"
#include "GameModeAI.cpp"
class GameModePvP{
    public:
        GameModePvP(){};

        bool turn;

        ManagePlayer Player1;
        ManageAI Player2;

        Stack<Undo> U;
        Location Pdie;

        void begin()
    {
        int board[8][8] =
            {50, 10, 0, 0, 0, 0, -10, -50,
             30, 10, 0, 0, 0, 0, -10, -30,
             35, 10, 0, 0, 0, 0, -10, -35,
             90, 10, 0, 0, 0, 0, -10, -90,
             1000, 10, 0, 0, 0, 0, -10, -1000,
             35, 10, 0, 0, 0, 0, -10, -35,
             30, 10, 0, 0, 0, 0, -10, -30,
             50, 10, 0, 0, 0, 0, -10, -50};
        ;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                Board[i][j] = board[i][j];
            }
        }
        
        Player1.begin();
        Player2.begin();
        

        Pdie.x=-100;
        Pdie.y=-100;

        turn = true;
        
    }
    void banco()
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (Board[j][i] == 10)
                    printf("%2s", "P");
                else if (Board[j][i] == 50)
                    printf("%2s", "R");
                else if (Board[j][i] == 30)
                    printf("%2s", "H");
                else if (Board[j][i] == 35)
                    printf("%2s", "B");
                else if (Board[j][i] == 90)
                    printf("%2s", "Q");
                else if (Board[j][i] == 1000)
                    printf("%2s", "K");
                else if (Board[j][i] == -10)
                    printf("%2s", "p");
                else if (Board[j][i] == -50)
                    printf("%2s", "r");
                else if (Board[j][i] == -30)
                    printf("%2s", "h");
                else if (Board[j][i] == -35)
                    printf("%2s", "b");
                else if (Board[j][i] == -90)
                    printf("%2s", "q");
                else if (Board[j][i] == -1000)
                    printf("%2s", "k");
                else
                    printf("%2s", "");
            }
            cout << endl;
        }
    }
    void CopyMang(int begin[][8], int end[][8])
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                end[i][j] = begin[i][j];
            }
        }
    }
    void CopyPos(Pos begin[], Pos end[])
    {
        for (int i = 0; i < 16; i++)
        {

            end[i] = begin[i];
        }
    }
    Stack<Location> ValidMove(int i, int Board[][8], Pos PosA[])
    {
        // cout<<".."<<PosA[i].x<<PosA[i].y<<endl;
        Stack<Location> arr;
        Location new1;
        if (PosA[i].value == -1)
            return arr;
        else if (abs(PosA[i].value) == 10)
        {
            int k = -1 * PosA[i].value / abs(PosA[i].value);
            if ((Board[PosA[i].x][PosA[i].y - k] == 0) && (PosA[i].y - k >= 0) && (PosA[i].y - k < 8))
            {
                new1.x = PosA[i].x;
                new1.y = PosA[i].y - k;
                arr.push(new1);
            };
            if ((PosA[i].y == 1 || PosA[i].y == 6) && (Board[PosA[i].x][PosA[i].y - 2 * k] == 0) && (Board[PosA[i].x][PosA[i].y - k] == 0) && (PosA[i].y - 2 * k >= 0) && (PosA[i].y - 2 * k < 8))
            {
                new1.x = PosA[i].x;
                new1.y = PosA[i].y - 2 * k;
                arr.push(new1);
            };
            if ((PosA[i].value * Board[PosA[i].x + 1][PosA[i].y - k] < 0) && (PosA[i].y - k >= 0) && (PosA[i].y - k < 8) && (PosA[i].x + 1 < 8))
            {
                new1.x = PosA[i].x + 1;
                new1.y = PosA[i].y - k;
                arr.push(new1);
            };
            if ((PosA[i].value * Board[PosA[i].x - 1][PosA[i].y - k] < 0) && (PosA[i].y - k >= 0) && (PosA[i].y - k < 8) && (PosA[i].x - 1 >= 0))
            {
                new1.x = PosA[i].x - 1;
                new1.y = PosA[i].y - k;
                arr.push(new1);
            };

            // phong hau 
            return arr;
        }
        else if (abs(PosA[i].value) == 30)
        { // 1 7
            int k = PosA[i].value / abs(PosA[i].value);
            if ((Board[PosA[i].x + 2][PosA[i].y + 1] == 0 || k * Board[PosA[i].x + 2][PosA[i].y + 1] < 0) && (PosA[i].x + 2 < 8) && (PosA[i].y + 1 < 8))
            {
                new1.x = PosA[i].x + 2;
                new1.y = PosA[i].y + 1;
                arr.push(new1);
            };
            if ((Board[PosA[i].x + 1][PosA[i].y + 2] == 0 || k * Board[PosA[i].x + 1][PosA[i].y + 2] < 0) && (PosA[i].x + 1 < 8) && (PosA[i].y + 2 < 8))
            {
                new1.x = PosA[i].x + 1;
                new1.y = PosA[i].y + 2;
                arr.push(new1);
            };
            if ((Board[PosA[i].x - 1][PosA[i].y - 2] == 0 || k * Board[PosA[i].x - 1][PosA[i].y - 2] < 0) && (PosA[i].x - 1 >= 0) && (PosA[i].y - 2 >= 0))
            {
                new1.x = PosA[i].x - 1;
                new1.y = PosA[i].y - 2;
                arr.push(new1);
            };
            if ((Board[PosA[i].x - 2][PosA[i].y - 1] == 0 || k * Board[PosA[i].x - 2][PosA[i].y - 1] < 0) && (PosA[i].x - 2 >= 0) && (PosA[i].y - 1 >= 0))
            {
                new1.x = PosA[i].x - 2;
                new1.y = PosA[i].y - 1;
                arr.push(new1);
            };
            if ((Board[PosA[i].x + 1][PosA[i].y - 2] == 0 || k * Board[PosA[i].x + 1][PosA[i].y - 2] < 0) && (PosA[i].x + 1 < 8) && (PosA[i].y - 2 >= 0))
            {
                new1.x = PosA[i].x + 1;
                new1.y = PosA[i].y - 2;
                arr.push(new1);
            };
            if ((Board[PosA[i].x - 1][PosA[i].y + 2] == 0 || k * Board[PosA[i].x - 1][PosA[i].y + 2] < 0) && (PosA[i].x - 1 >= 0) && (PosA[i].y + 2 < 8))
            {
                new1.x = PosA[i].x - 1;
                new1.y = PosA[i].y + 2;
                arr.push(new1);
            };
            if ((Board[PosA[i].x - 2][PosA[i].y + 1] == 0 || k * Board[PosA[i].x - 2][PosA[i].y + 1] < 0) && (PosA[i].x - 2 >= 0) && (PosA[i].y + 1 < 8))
            {
                new1.x = PosA[i].x - 2;
                new1.y = PosA[i].y + 1;
                arr.push(new1);
            };
            if ((Board[PosA[i].x + 2][PosA[i].y - 1] == 0 || k * Board[PosA[i].x + 2][PosA[i].y - 1] < 0) && (PosA[i].x + 2 < 8) && (PosA[i].y - 1 >= 0))
            {
                new1.x = PosA[i].x + 2;
                new1.y = PosA[i].y - 1;
                arr.push(new1);
            };
            return arr;
        }
        else if (abs(PosA[i].value) == 35)
        {
            int k = PosA[i].value / abs(PosA[i].value);
            for (int i1 = PosA[i].x + 1, j = PosA[i].y + 1; (i1 < 8 && j < 8); i1++, j++)
            {

                if (Board[i1][j] != 0)
                {
                    if (Board[i1][j] * k < 0)
                    {
                        new1.x = i1;
                        new1.y = j;
                        arr.push(new1);
                    };
                    break;
                }
                new1.x = i1;
                new1.y = j;
                arr.push(new1);
            }
            for (int i1 = PosA[i].x + 1, j = PosA[i].y - 1; (i1 < 8 && j >= 0); i1++, j--)
            {

                if (Board[i1][j] != 0)
                {
                    if (Board[i1][j] * k < 0)
                    {
                        new1.x = i1;
                        new1.y = j;
                        arr.push(new1);
                    };
                    break;
                }
                new1.x = i1;
                new1.y = j;
                arr.push(new1);
            }
            for (int i1 = PosA[i].x - 1, j = PosA[i].y - 1; (i1 >= 0 && j >= 0); i1--, j--)
            {

                if (Board[i1][j] != 0)
                {
                    if (Board[i1][j] * k < 0)
                    {
                        new1.x = i1;
                        new1.y = j;
                        arr.push(new1);
                    };
                    break;
                }
                new1.x = i1;
                new1.y = j;
                arr.push(new1);
            }
            for (int i1 = PosA[i].x - 1, j = PosA[i].y + 1; (i1 >= 0 && j < 8); i1--, j++)
            {

                if (Board[i1][j] != 0)
                {
                    if (Board[i1][j] * k < 0)
                    {
                        new1.x = i1;
                        new1.y = j;
                        arr.push(new1);
                    };
                    break;
                }
                new1.x = i1;
                new1.y = j;
                arr.push(new1);
            }
            return arr;
        }
        else if (abs(PosA[i].value) == 50)
        {
            int k = PosA[i].value / abs(PosA[i].value);
            for (int i1 = PosA[i].x + 1; i1 < 8; i1++)
            {
                if (Board[i1][PosA[i].y] != 0)
                {
                    if (Board[i1][PosA[i].y] * k < 0)
                    {
                        new1.x = i1;
                        new1.y = PosA[i].y;
                        arr.push(new1);
                    };
                    break;
                }
                new1.x = i1;
                new1.y = PosA[i].y;
                arr.push(new1);
            }
            for (int i1 = PosA[i].x - 1; i1 >= 0; i1--)
            {
                if (Board[i1][PosA[i].y] != 0)
                {
                    if (Board[i1][PosA[i].y] * k < 0)
                    {
                        new1.x = i1;
                        new1.y = PosA[i].y;
                        arr.push(new1);
                    };
                    break;
                }
                new1.x = i1;
                new1.y = PosA[i].y;
                arr.push(new1);
            }
            for (int i1 = PosA[i].y + 1; i1 < 8; i1++)
            {
                if (Board[PosA[i].x][i1] != 0)
                {
                    if (Board[PosA[i].x][i1] * k < 0)
                    {
                        new1.x = PosA[i].x;
                        new1.y = i1;
                        arr.push(new1);
                    };
                    break;
                }
                new1.x = PosA[i].x;
                new1.y = i1;
                arr.push(new1);
            }
            for (int i1 = PosA[i].y - 1; i1 >= 0; i1--)
            {
                if (Board[PosA[i].x][i1] != 0)
                {
                    if (Board[PosA[i].x][i1] * k < 0)
                    {
                        new1.x = PosA[i].x;
                        new1.y = i1;
                        arr.push(new1);
                    };
                    break;
                }
                new1.x = PosA[i].x;
                new1.y = i1;
                arr.push(new1);
            }
            return arr;
        }
        else if (abs(PosA[i].value) == 90)
        {
            int k = PosA[i].value / abs(PosA[i].value);
            for (int i1 = PosA[i].x + 1, j = PosA[i].y + 1; (i1 < 8 && j < 8); i1++, j++)
            {

                if (Board[i1][j] != 0)
                {
                    if (Board[i1][j] * k < 0)
                    {
                        new1.x = i1;
                        new1.y = j;
                        arr.push(new1);
                    };
                    break;
                }
                new1.x = i1;
                new1.y = j;
                arr.push(new1);
            }
            for (int i1 = PosA[i].x + 1, j = PosA[i].y - 1; (i1 < 8 && j >= 0); i1++, j--)
            {

                if (Board[i1][j] != 0)
                {
                    if (Board[i1][j] * k < 0)
                    {
                        new1.x = i1;
                        new1.y = j;
                        arr.push(new1);
                    };
                    break;
                }
                new1.x = i1;
                new1.y = j;
                arr.push(new1);
            }
            for (int i1 = PosA[i].x - 1, j = PosA[i].y - 1; (i1 >= 0 && j >= 0); i1--, j--)
            {

                if (Board[i1][j] != 0)
                {
                    if (Board[i1][j] * k < 0)
                    {
                        new1.x = i1;
                        new1.y = j;
                        arr.push(new1);
                    };
                    break;
                }
                new1.x = i1;
                new1.y = j;
                arr.push(new1);
            }
            for (int i1 = PosA[i].x - 1, j = PosA[i].y + 1; (i1 >= 0 && j < 8); i1--, j++)
            {

                if (Board[i1][j] != 0)
                {
                    if (Board[i1][j] * k < 0)
                    {
                        new1.x = i1;
                        new1.y = j;
                        arr.push(new1);
                    };
                    break;
                }
                new1.x = i1;
                new1.y = j;
                arr.push(new1);
            }
            for (int i1 = PosA[i].x + 1; i1 < 8; i1++)
            {
                if (Board[i1][PosA[i].y] != 0)
                {
                    if (Board[i1][PosA[i].y] * k < 0)
                    {
                        new1.x = i1;
                        new1.y = PosA[i].y;
                        arr.push(new1);
                    };
                    break;
                }
                new1.x = i1;
                new1.y = PosA[i].y;
                arr.push(new1);
            }
            for (int i1 = PosA[i].x - 1; i1 >= 0; i1--)
            {
                if (Board[i1][PosA[i].y] != 0)
                {
                    if (Board[i1][PosA[i].y] * k < 0)
                    {
                        new1.x = i1;
                        new1.y = PosA[i].y;
                        arr.push(new1);
                    };
                    break;
                }
                new1.x = i1;
                new1.y = PosA[i].y;
                arr.push(new1);
            }
            for (int i1 = PosA[i].y + 1; i1 < 8; i1++)
            {
                if (Board[PosA[i].x][i1] != 0)
                {
                    if (Board[PosA[i].x][i1] * k < 0)
                    {
                        new1.x = PosA[i].x;
                        new1.y = i1;
                        arr.push(new1);
                    };
                    break;
                }
                new1.x = PosA[i].x;
                new1.y = i1;
                arr.push(new1);
            }
            for (int i1 = PosA[i].y - 1; i1 >= 0; i1--)
            {
                if (Board[PosA[i].x][i1] != 0)
                {
                    if (Board[PosA[i].x][i1] * k < 0)
                    {
                        new1.x = PosA[i].x;
                        new1.y = i1;
                        arr.push(new1);
                    };
                    break;
                }
                new1.x = PosA[i].x;
                new1.y = i1;
                arr.push(new1);
            }
            return arr;
        }
        else if (abs(PosA[i].value) == 1000)
        {
            int k = PosA[i].value / abs(PosA[i].value);
            if ((Board[PosA[i].x + 1][PosA[i].y] * k <= 0) && (PosA[i].x + 1 < 8))
            {
                new1.x = PosA[i].x + 1;
                new1.y = PosA[i].y;
                arr.push(new1);
            };
            if ((Board[PosA[i].x + 1][PosA[i].y + 1] * k <= 0) && (PosA[i].x + 1 < 8) && (PosA[i].y + 1 < 8))
            {
                new1.x = PosA[i].x + 1;
                new1.y = PosA[i].y + 1;
                arr.push(new1);
            };
            if ((Board[PosA[i].x + 1][PosA[i].y - 1] * k <= 0) && (PosA[i].x + 1 < 8) && (PosA[i].y - 1 >= 0))
            {
                new1.x = PosA[i].x + 1;
                new1.y = PosA[i].y - 1;
                arr.push(new1);
            };
            if ((Board[PosA[i].x - 1][PosA[i].y] * k <= 0) && (PosA[i].x - 1 >= 0))
            {
                new1.x = PosA[i].x - 1;
                new1.y = PosA[i].y;
                arr.push(new1);
            };
            if ((Board[PosA[i].x - 1][PosA[i].y + 1] * k <= 0) && (PosA[i].x - 1 >= 0) && (PosA[i].y + 1 < 8))
            {
                new1.x = PosA[i].x - 1;
                new1.y = PosA[i].y + 1;
                arr.push(new1);
            };
            if ((Board[PosA[i].x - 1][PosA[i].y - 1] * k <= 0) && (PosA[i].x - 1 >= 0) && (PosA[i].y - 1 >= 0))
            {
                new1.x = PosA[i].x - 1;
                new1.y = PosA[i].y - 1;
                arr.push(new1);
            };
            if ((Board[PosA[i].x][PosA[i].y + 1] * k <= 0) && (PosA[i].y + 1 < 8))
            {
                new1.x = PosA[i].x;
                new1.y = PosA[i].y + 1;
                arr.push(new1);
            };
            if ((Board[PosA[i].x][PosA[i].y - 1] * k <= 0) && (PosA[i].y - 1 >= 0))
            {
                new1.x = PosA[i].x;
                new1.y = PosA[i].y - 1;
                arr.push(new1);
            };
        }
        return arr;
    }
    void undo();
    int Move(int j, int x1, int y1){
        banco();
        if (turn==true){
        Stack<Location> P = ValidMove(j, Board, Player1.PosB);
        for (int i = 0; i < P.getCurrent(); i++)
        {
            cout << endl << P.top().x << " " << P.top().y;
        }
        if (Board[x1][y1]>0){
            for (int i=0;i<16;i++){
                if (Board[x1][y1] == Player2.PosA[i].value && Player2.PosA[i].x == x1 && Player2.PosA[i].y == y1){
                    Player2.PosA[i].value = -1;
                    Player2.Computer[i]->die();
                    //undo
                    Undo m;
                    m.i=i;
                    m.PorC=1;
                    m.begin.x=x1;
                    m.begin.y=y1;
                    m.end=Pdie;
                    U.push(m);
                    

                    break;

                }
            }
        }
        Undo n;
        //undo
        
        n.i=j;
        n.PorC=-1;
        n.begin.x=Player1.PosB[j].x;
        n.begin.y=Player1.PosB[j].y;
        n.end.x=x1;
        n.end.y=y1;
        

        Board[x1][y1] = Player1.PosB[j].value;
        Board[Player1.PosB[j].x][Player1.PosB[j].y] = 0;
        Player1.PosB[j].x = x1;
        Player1.PosB[j].y = y1;
        Player1.Player[j]->setP(x1, y1);

        turn=!turn;
        // kiem tra phong hau
        if (Player1.PosB[j].value==-10 && y1==0){
            n.checkQueen = true;
            Player1.PosB[j].value=-90;
            Player1.Player[j]->BecomeQueen();
            Board[x1][y1] = Player1.PosB[j].value;
            U.push(n);
            return j;
        }
        U.push(n);
        return -1;
        }
    else if (turn==false){
        Stack<Location> P = ValidMove(j, Board, Player2.PosA);
 
        for (int i = 0; i < P.getCurrent(); i++)
        {
            cout << endl << P.top().x << " " << P.top().y;
        }

        if (Board[x1][y1]<0){
            for (int i=0;i<16;i++){
                if (Board[x1][y1] == Player1.PosB[i].value && Player1.PosB[i].x == x1 && Player1.PosB[i].y == y1){
                    Player1.PosB[i].value = -1;
                    Player1.Player[i]->die();

                    //undo
                    Undo m;
                    m.i=i;
                    m.PorC=-1;
                    m.begin.x=x1;
                    m.begin.y=y1;
                    m.end=Pdie;
                    U.push(m);

                    break;
                }
            }
        }
        Undo n;
        //undo
        
        n.i=j;
        n.PorC=1;
        n.begin.x=Player2.PosA[j].x;
        n.begin.y=Player2.PosA[j].y;
        n.end.x=x1;
        n.end.y=y1;
        

        Board[x1][y1] = Player2.PosA[j].value;
        Board[Player2.PosA[j].x][Player2.PosA[j].y] = 0;
        Player2.PosA[j].x = x1;
        Player2.PosA[j].y = y1;
        Player2.Computer[j]->setP(x1, y1);

        turn=!turn;
        // kiem tra phong hau
        if (Player2.PosA[j].value==10 && y1==7){
            n.checkQueen = true;
            Player2.PosA[j].value=90;
            Player2.Computer[j]->BecomeQueen();
            Board[x1][y1] = Player2.PosA[j].value;
            U.push(n);
            return j;
            
        }
        U.push(n);
        return -1;
    }

    }
    int checkMate(int Board[][8],Pos PosA[],Pos PosB[]) {

        for (int i = 0; i < 16; i++) {
            Stack<Location> P = ValidMove(i, Board, PosB);
            for (int i = 0; i < P.getCurrent(); i++) {
                if (P.top().x == PosA[15].x && P.top().y == PosA[15].y)
                    return 1;
                P.pop();
            }
        }
        for (int i = 0; i < 16; i++) {
            Stack<Location> P = ValidMove(i, Board, PosA);
            for (int i = 0; i < P.getCurrent(); i++) {
                if (P.top().x == PosB[15].x && P.top().y ==PosB[15].y)
                    return -1;
                P.pop();
            }
        }
        return 0;

    }
    int endGameP2() {
        int arr[8][8];
        for (int i = 0; i < 16; i++) {
            Stack<Location> P = ValidMove(i, Board, Player1.PosB);
            for (int j = 0; j < P.getCurrent(); j++) {
                CopyMang(Board, arr);
                Pos a[16];
                CopyPos(Player2.PosA, a);
                Pos b[16];
                CopyPos(Player1.PosB, b);
                int tam = Player1.PosB[i].value;
                arr[Player1.PosB[i].x][Player1.PosB[i].y] = 0;
                if (arr[P.top().x][P.top().y] > 0)
                {
                    for (int k = 0; k < 16; k++)
                    {
                        if ((a[k].x == P.top().x) && (a[k].y == P.top().y))
                        {
                            a[k].value = -1;
                            break;
                        }
                    }
                }

                arr[P.top().x][P.top().y] = tam;
                b[i].x = P.top().x;
                b[i].y = P.top().y;
                b[i].value = tam;

                if (checkMate(arr, a, b) == 0) {
                    return 0;
                }
                P.pop();
            }
        }
        return 1;

    }
    int endGameP1() {
        int arr[8][8];
        for (int i = 0; i < 16; i++) {
            Stack<Location> P = ValidMove(i, Board, Player2.PosA);
            for (int j = 0; j < P.getCurrent(); j++) {
                CopyMang(Board, arr);
                Pos a[16];
                CopyPos(Player2.PosA, a);
                Pos b[16];
                CopyPos(Player1.PosB, b);
                int tam = Player2.PosA[i].value;
                arr[Player2.PosA[i].x][Player2.PosA[i].y] = 0;
                if (arr[P.top().x][P.top().y] < 0)
                {
                    for (int k = 0; k < 16; k++)
                    {
                        if ((b[k].x == P.top().x) && (b[k].y == P.top().y))
                        {
                            b[k].value = -1;
                            break;
                        }
                    }
                }

                arr[P.top().x][P.top().y] = tam;
                a[i].x = P.top().x;
                a[i].y = P.top().y;
                a[i].value = tam;

                if (checkMate(arr, a, b) == 0) {
                    return 0;
                }
                P.pop();
            }
        }
        return 1;

    }
    
};
