
#include "chess.cpp"
class Gameplay
{

public:
    Gameplay(){};
    Chess *PosA1[16];
    Chess *PosB1[16];

    // tao quan co cho may gia lap nuoc di
    Pos PosA[16];
    Pos PosB[16];

    // may di
    int MoveOderCurent; // quan di may se chon hien tai;chi so i trong Pos.
    Position MoveOderNext;

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
        // tot cua may
        PosA1[0] = new Tot;
        PosA1[1] = new Tot;
        PosA1[2] = new Tot;
        PosA1[3] = new Tot;
        PosA1[4] = new Tot;
        PosA1[5] = new Tot;
        PosA1[6] = new Tot;
        PosA1[7] = new Tot;

        // xe cua may
        PosA1[8] = new Xe;
        PosA1[9] = new Xe;

        // ma cua may
        PosA1[10] = new Ma;
        PosA1[11] = new Ma;

        // tuong cua may
        PosA1[12] = new Tuong;
        PosA1[13] = new Tuong;

        // Hau cua may

        PosA1[14] = new Hau;

        // vua cua may
        PosA1[15] = new Vua;

        // tot cua nguoi
        PosB1[0] = new Tot;
        PosB1[1] = new Tot;
        PosB1[2] = new Tot;
        PosB1[3] = new Tot;
        PosB1[4] = new Tot;
        PosB1[5] = new Tot;
        PosB1[6] = new Tot;
        PosB1[7] = new Tot;

        // xe cua nguoi
        PosB1[8] = new Xe;
        PosB1[9] = new Xe;

        // ma cua nguoi
        PosB1[10] = new Ma;
        PosB1[11] = new Ma;

        // tuong cua nguoi
        PosB1[12] = new Tuong;
        PosB1[13] = new Tuong;

        // Hau cua nguoi
        PosB1[14] = new Hau;

        // vua cua nguoi
        PosB1[15] = new Vua;
        for (int i = 0; i < 8; i++)
        {
            PosA1[i]->setP(i, 1);
            PosA1[i]->setIndex(1);
            PosA1[i]->setValue();
        }
        for (int i = 0; i < 8; i++)
        {
            PosB1[i]->setP(i, 6);
            PosB1[i]->setIndex(-1);
            PosB1[i]->setValue();
        }
        PosA1[8]->setP(0, 0);
        PosA1[8]->setIndex(1);
        PosA1[8]->setValue();
        PosA1[9]->setP(7, 0);
        PosA1[9]->setIndex(1);
        PosA1[9]->setValue();
        PosB1[8]->setP(0, 7);
        PosB1[8]->setIndex(-1);
        PosB1[8]->setValue();
        PosB1[9]->setP(7, 7);
        PosB1[9]->setIndex(-1);
        PosB1[9]->setValue();

        PosA1[10]->setP(1, 0);
        PosA1[10]->setIndex(1);
        PosA1[10]->setValue();
        PosA1[11]->setP(6, 0);
        PosA1[11]->setIndex(1);
        PosA1[11]->setValue();
        PosB1[10]->setP(1, 7);
        PosB1[10]->setIndex(-1);
        PosB1[10]->setValue();
        PosB1[11]->setP(6, 7);
        PosB1[11]->setIndex(-1);
        PosB1[11]->setValue();

        PosA1[12]->setP(2, 0);
        PosA1[12]->setIndex(1);
        PosA1[12]->setValue();
        PosA1[13]->setP(5, 0);
        PosA1[13]->setIndex(1);
        PosA1[13]->setValue();
        PosB1[12]->setP(2, 7);
        PosB1[12]->setIndex(-1);
        PosB1[12]->setValue();
        PosB1[13]->setP(5, 7);
        PosB1[13]->setIndex(-1);
        PosB1[13]->setValue();

        PosA1[14]->setP(3, 0);
        PosA1[14]->setIndex(1);
        PosA1[14]->setValue();
        PosB1[14]->setP(3, 7);
        PosB1[14]->setIndex(-1);
        PosB1[14]->setValue();

        PosA1[15]->setP(4, 0);
        PosA1[15]->setIndex(1);
        PosA1[15]->setValue();
        PosB1[15]->setP(4, 7);
        PosB1[15]->setIndex(-1);
        PosB1[15]->setValue();

        resetPosA();
        resetPosB();
    }
    void resetPosA()
    {
        // quan tot
        for (int i = 0; i < 8; i++)
        {
            PosA[i].value = 10;
            PosA[i].x = i;
            PosA[i].y = 1;
        }
        // quan xe
        PosA[8].value = 50;
        PosA[8].x = 0;
        PosA[8].y = 0;
        PosA[9].value = 50;
        PosA[9].x = 7;
        PosA[9].y = 0;
        // quan ma
        PosA[10].value = 30;
        PosA[10].x = 1;
        PosA[10].y = 0;
        PosA[11].value = 30;
        PosA[11].x = 6;
        PosA[11].y = 0;
        // quan tuong
        PosA[12].value = 35;
        PosA[12].x = 2;
        PosA[12].y = 0;
        PosA[13].value = 35;
        PosA[13].x = 5;
        PosA[13].y = 0;
        // quan hau;
        PosA[14].value = 90;
        PosA[14].x = 3;
        PosA[14].y = 0;
        // quan vua
        PosA[15].value = 1000;
        PosA[15].x = 4;
        PosA[15].y = 0;
    }
    void resetPosB()
    {
        // quan tot
        for (int i = 0; i < 8; i++)
        {
            PosB[i].value = -10;
            PosB[i].x = i;
            PosB[i].y = 6;
        }
        // quan xe
        PosB[8].value = -50;
        PosB[8].x = 0;
        PosB[8].y = 7;
        PosB[9].value = -50;
        PosB[9].x = 7;
        PosB[9].y = 7;
        // quan ma
        PosB[10].value = -30;
        PosB[10].x = 1;
        PosB[10].y = 7;
        PosB[11].value = -30;
        PosB[11].x = 6;
        PosB[11].y = 7;
        // quan tuong
        PosB[12].value = -35;
        PosB[12].x = 2;
        PosB[12].y = 7;
        PosB[13].value = -35;
        PosB[13].x = 5;
        PosB[13].y = 7;
        // quan hau;
        PosB[14].value = -90;
        PosB[14].x = 3;
        PosB[14].y = 7;
        // quan vua
        PosB[15].value = -1000;
        PosB[15].x = 4;
        PosB[15].y = 7;
    }
    vector<Position> ValidMove(int i, int Board[][8], Pos PosA[])
    {
        vector<Position> arr;
        Position new1;
        if (PosA[i].value == -1)
            return arr;
        else if (abs(PosA[i].value) == 10)
        {
            int k = -1 * PosA[i].value / abs(PosA[i].value);
            if ((Board[PosA[i].x][PosA[i].y - k] == 0) && (PosA[i].y - k >= 0) && (PosA[i].y - k < 8))
            {
                new1.x = PosA[i].x;
                new1.y = PosA[i].y - k;
                arr.push_back(new1);
            };
            if ((PosA[i].y == 1 || PosA[i].y == 6) && (Board[PosA[i].x][PosA[i].y - 2 * k] == 0) && (Board[PosA[i].x][PosA[i].y - k] == 0) && (PosA[i].y - 2 * k >= 0) && (PosA[i].y - 2 * k < 8))
            {
                new1.x = PosA[i].x;
                new1.y = PosA[i].y - 2 * k;
                arr.push_back(new1);
            };
            if ((PosA[i].value * Board[PosA[i].x + 1][PosA[i].y - k] < 0) && (PosA[i].y - k >= 0) && (PosA[i].y - k < 8) && (PosA[i].x + 1 < 8))
            {
                new1.x = PosA[i].x + 1;
                new1.y = PosA[i].y - k;
                arr.push_back(new1);
            };
            if ((PosA[i].value * Board[PosA[i].x - 1][PosA[i].y - k] < 0) && (PosA[i].y - k >= 0) && (PosA[i].y - k < 8) && (PosA[i].x - 1 >= 0))
            {
                new1.x = PosA[i].x - 1;
                new1.y = PosA[i].y - k;
                arr.push_back(new1);
            };
            return arr;
        }
        else if (abs(PosA[i].value) == 30)
        { // 14
            int k = PosA[i].value / abs(PosA[i].value);
            if ((Board[PosA[i].x + 2][PosA[i].y + 1] == 0 || k * Board[PosA[i].x + 2][PosA[i].y + 1] < 0) && (PosA[i].x + 2 < 8) && (PosA[i].y + 1 < 8))
            {
                new1.x = PosA[i].x + 2;
                new1.y = PosA[i].y + 1;
                arr.push_back(new1);
            };
            if ((Board[PosA[i].x + 1][PosA[i].y + 2] == 0 || k * Board[PosA[i].x + 1][PosA[i].y + 2] < 0) && (PosA[i].x + 1 < 8) && (PosA[i].y + 2 < 8))
            {
                new1.x = PosA[i].x + 1;
                new1.y = PosA[i].y + 2;
                arr.push_back(new1);
            };
            if ((Board[PosA[i].x - 1][PosA[i].y - 2] == 0 || k * Board[PosA[i].x - 1][PosA[i].y - 2] < 0) && (PosA[i].x - 1 >= 0) && (PosA[i].y - 2 >= 0))
            {
                new1.x = PosA[i].x - 1;
                new1.y = PosA[i].y - 2;
                arr.push_back(new1);
            };
            if ((Board[PosA[i].x - 2][PosA[i].y - 1] == 0 || k * Board[PosA[i].x - 2][PosA[i].y - 1] < 0) && (PosA[i].x - 2 >= 0) && (PosA[i].y - 1 >= 0))
            {
                new1.x = PosA[i].x - 2;
                new1.y = PosA[i].y - 1;
                arr.push_back(new1);
            };
            if ((Board[PosA[i].x + 1][PosA[i].y - 2] == 0 || k * Board[PosA[i].x + 1][PosA[i].y - 2] < 0) && (PosA[i].x + 1 < 8) && (PosA[i].y - 2 >= 0))
            {
                new1.x = PosA[i].x + 1;
                new1.y = PosA[i].y - 2;
                arr.push_back(new1);
            };
            if ((Board[PosA[i].x - 1][PosA[i].y + 2] == 0 || k * Board[PosA[i].x - 1][PosA[i].y + 2] < 0) && (PosA[i].x - 1 >= 0) && (PosA[i].y + 2 < 8))
            {
                new1.x = PosA[i].x - 1;
                new1.y = PosA[i].y + 2;
                arr.push_back(new1);
            };
            if ((Board[PosA[i].x - 2][PosA[i].y + 1] == 0 || k * Board[PosA[i].x - 2][PosA[i].y + 1] < 0) && (PosA[i].x - 2 >= 0) && (PosA[i].y + 1 < 8))
            {
                new1.x = PosA[i].x - 2;
                new1.y = PosA[i].y + 1;
                arr.push_back(new1);
            };
            if ((Board[PosA[i].x + 2][PosA[i].y - 1] == 0 || k * Board[PosA[i].x + 2][PosA[i].y - 1] < 0) && (PosA[i].x + 2 < 8) && (PosA[i].y - 1 >= 0))
            {
                new1.x = PosA[i].x + 2;
                new1.y = PosA[i].y - 1;
                arr.push_back(new1);
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
                        arr.push_back(new1);
                    };
                    break;
                }
                new1.x = i1;
                new1.y = j;
                arr.push_back(new1);
            }
            for (int i1 = PosA[i].x + 1, j = PosA[i].y - 1; (i1 < 8 && j >= 0); i1++, j--)
            {

                if (Board[i1][j] != 0)
                {
                    if (Board[i1][j] * k < 0)
                    {
                        new1.x = i1;
                        new1.y = j;
                        arr.push_back(new1);
                    };
                    break;
                }
                new1.x = i1;
                new1.y = j;
                arr.push_back(new1);
            }
            for (int i1 = PosA[i].x - 1, j = PosA[i].y - 1; (i1 >= 0 && j >= 0); i1--, j--)
            {

                if (Board[i1][j] != 0)
                {
                    if (Board[i1][j] * k < 0)
                    {
                        new1.x = i1;
                        new1.y = j;
                        arr.push_back(new1);
                    };
                    break;
                }
                new1.x = i1;
                new1.y = j;
                arr.push_back(new1);
            }
            for (int i1 = PosA[i].x - 1, j = PosA[i].y + 1; (i1 >= 0 && j < 8); i1--, j++)
            {

                if (Board[i1][j] != 0)
                {
                    if (Board[i1][j] * k < 0)
                    {
                        new1.x = i1;
                        new1.y = j;
                        arr.push_back(new1);
                    };
                    break;
                }
                new1.x = i1;
                new1.y = j;
                arr.push_back(new1);
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
                        arr.push_back(new1);
                    };
                    break;
                }
                new1.x = i1;
                new1.y = PosA[i].y;
                arr.push_back(new1);
            }
            for (int i1 = PosA[i].x - 1; i1 >= 0; i1--)
            {
                if (Board[i1][PosA[i].y] != 0)
                {
                    if (Board[i1][PosA[i].y] * k < 0)
                    {
                        new1.x = i1;
                        new1.y = PosA[i].y;
                        arr.push_back(new1);
                    };
                    break;
                }
                new1.x = i1;
                new1.y = PosA[i].y;
                arr.push_back(new1);
            }
            for (int i1 = PosA[i].y + 1; i1 < 8; i1++)
            {
                if (Board[PosA[i].x][i1] != 0)
                {
                    if (Board[PosA[i].x][i1] * k < 0)
                    {
                        new1.x = PosA[i].x;
                        new1.y = i1;
                        arr.push_back(new1);
                    };
                    break;
                }
                new1.x = PosA[i].x;
                new1.y = i1;
                arr.push_back(new1);
            }
            for (int i1 = PosA[i].y - 1; i1 >= 0; i1--)
            {
                if (Board[PosA[i].x][i1] != 0)
                {
                    if (Board[PosA[i].x][i1] * k < 0)
                    {
                        new1.x = PosA[i].x;
                        new1.y = i1;
                        arr.push_back(new1);
                    };
                    break;
                }
                new1.x = PosA[i].x;
                new1.y = i1;
                arr.push_back(new1);
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
                        arr.push_back(new1);
                    };
                    break;
                }
                new1.x = i1;
                new1.y = j;
                arr.push_back(new1);
            }
            for (int i1 = PosA[i].x + 1, j = PosA[i].y - 1; (i1 < 8 && j >= 0); i1++, j--)
            {

                if (Board[i1][j] != 0)
                {
                    if (Board[i1][j] * k < 0)
                    {
                        new1.x = i1;
                        new1.y = j;
                        arr.push_back(new1);
                    };
                    break;
                }
                new1.x = i1;
                new1.y = j;
                arr.push_back(new1);
            }
            for (int i1 = PosA[i].x - 1, j = PosA[i].y - 1; (i1 >= 0 && j >= 0); i1--, j--)
            {

                if (Board[i1][j] != 0)
                {
                    if (Board[i1][j] * k < 0)
                    {
                        new1.x = i1;
                        new1.y = j;
                        arr.push_back(new1);
                    };
                    break;
                }
                new1.x = i1;
                new1.y = j;
                arr.push_back(new1);
            }
            for (int i1 = PosA[i].x - 1, j = PosA[i].y + 1; (i1 >= 0 && j < 8); i1--, j++)
            {

                if (Board[i1][j] != 0)
                {
                    if (Board[i1][j] * k < 0)
                    {
                        new1.x = i1;
                        new1.y = j;
                        arr.push_back(new1);
                    };
                    break;
                }
                new1.x = i1;
                new1.y = j;
                arr.push_back(new1);
            }
            for (int i1 = PosA[i].x + 1; i1 < 8; i1++)
            {
                if (Board[i1][PosA[i].y] != 0)
                {
                    if (Board[i1][PosA[i].y] * k < 0)
                    {
                        new1.x = i1;
                        new1.y = PosA[i].y;
                        arr.push_back(new1);
                    };
                    break;
                }
                new1.x = i1;
                new1.y = PosA[i].y;
                arr.push_back(new1);
            }
            for (int i1 = PosA[i].x - 1; i1 >= 0; i1--)
            {
                if (Board[i1][PosA[i].y] != 0)
                {
                    if (Board[i1][PosA[i].y] * k < 0)
                    {
                        new1.x = i1;
                        new1.y = PosA[i].y;
                        arr.push_back(new1);
                    };
                    break;
                }
                new1.x = i1;
                new1.y = PosA[i].y;
                arr.push_back(new1);
            }
            for (int i1 = PosA[i].y + 1; i1 < 8; i1++)
            {
                if (Board[PosA[i].x][i1] != 0)
                {
                    if (Board[PosA[i].x][i1] * k < 0)
                    {
                        new1.x = PosA[i].x;
                        new1.y = i1;
                        arr.push_back(new1);
                    };
                    break;
                }
                new1.x = PosA[i].x;
                new1.y = i1;
                arr.push_back(new1);
            }
            for (int i1 = PosA[i].y - 1; i1 >= 0; i1--)
            {
                if (Board[PosA[i].x][i1] != 0)
                {
                    if (Board[PosA[i].x][i1] * k < 0)
                    {
                        new1.x = PosA[i].x;
                        new1.y = i1;
                        arr.push_back(new1);
                    };
                    break;
                }
                new1.x = PosA[i].x;
                new1.y = i1;
                arr.push_back(new1);
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
                arr.push_back(new1);
            };
            if ((Board[PosA[i].x + 1][PosA[i].y + 1] * k <= 0) && (PosA[i].x + 1 < 8) && (PosA[i].y + 1 < 8))
            {
                new1.x = PosA[i].x + 1;
                new1.y = PosA[i].y + 1;
                arr.push_back(new1);
            };
            if ((Board[PosA[i].x + 1][PosA[i].y - 1] * k <= 0) && (PosA[i].x + 1 < 8) && (PosA[i].y - 1 >= 0))
            {
                new1.x = PosA[i].x + 1;
                new1.y = PosA[i].y - 1;
                arr.push_back(new1);
            };
            if ((Board[PosA[i].x - 1][PosA[i].y] * k <= 0) && (PosA[i].x - 1 >= 0))
            {
                new1.x = PosA[i].x - 1;
                new1.y = PosA[i].y;
                arr.push_back(new1);
            };
            if ((Board[PosA[i].x - 1][PosA[i].y + 1] * k <= 0) && (PosA[i].x - 1 >= 0) && (PosA[i].y + 1 < 8))
            {
                new1.x = PosA[i].x - 1;
                new1.y = PosA[i].y + 1;
                arr.push_back(new1);
            };
            if ((Board[PosA[i].x - 1][PosA[i].y - 1] * k <= 0) && (PosA[i].x - 1 >= 0) && (PosA[i].y - 1 >= 0))
            {
                new1.x = PosA[i].x - 1;
                new1.y = PosA[i].y - 1;
                arr.push_back(new1);
            };
            if ((Board[PosA[i].x][PosA[i].y + 1] * k <= 0) && (PosA[i].y + 1 < 8))
            {
                new1.x = PosA[i].x;
                new1.y = PosA[i].y + 1;
                arr.push_back(new1);
            };
            if ((Board[PosA[i].x][PosA[i].y - 1] * k <= 0) && (PosA[i].y - 1 >= 0))
            {
                new1.x = PosA[i].x;
                new1.y = PosA[i].y - 1;
                arr.push_back(new1);
            };
        }
        return arr;
    }
    int valueCal(int arr[][8])
    {
        int sum = 0;

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {

                sum += arr[i][j];
            }
        }

        return sum;
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
    int moveOder(int arr[][8], int alpha, int beta, int depth, bool luot, Pos PosA[], Pos PosB[])
    {
        if ((depth == 0) || (PosA[15].value == -1) || (PosB[15].value == -1))
            return valueCal(arr);
        if (luot == true)
        {

            for (int i = 0; i < 16; i++)
            {
                vector<Position> Parr = ValidMove(i, arr, PosA);
                int ParrL = Parr.size();
                // cout<<"y  i= "<<i<<" ParrL: "<<ParrL<<" depth: "<<depth<<endl;
                for (int j = 0; j < ParrL; j++)
                {
                    // cout<<i<<"=="<<Parr[j].x<<" "<<Parr[j].y<<arr[Parr[j].x][Parr[j].y]<<endl;
                    int b[8][8];
                    CopyMang(arr, b);
                    Pos a1[16];
                    CopyPos(PosA, a1);
                    Pos a2[16];
                    CopyPos(PosB, a2);
                    int tam = b[PosA[i].x][PosA[i].y]; // tam=PosA[i].value;

                    b[PosA[i].x][PosA[i].y] = 0;
                    // an quan
                    if (b[Parr[j].x][Parr[j].y] < 0)
                    {
                        // cout<<"=="<<b[Parr[j].x][Parr[j].y]<<endl;
                        for (int k = 0; k < 16; k++)
                        {
                            if ((a2[k].x == Parr[j].x) && (a2[k].y == Parr[j].y))
                            {
                                a2[k].value = -1;
                                break;
                            }
                        }
                    }
                    // phong hau
                    if ((Parr[j].y == 7) && (i >= 0) && (i < 8))
                    {
                        tam = 90;
                    }
                    // thay doi gia tri tren ban co
                    b[Parr[j].x][Parr[j].y] = tam;

                    // thay doi chi so quan hien tai trong mang a1(mang nhap cua PosA)
                    a1[i].x = Parr[j].x;
                    a1[i].y = Parr[j].y;
                    a1[i].value = tam;

                    int tmp = moveOder(b, alpha, beta, depth - 1, false, a1, a2);
                    // cout<<i<<" ///////////////"<<tmp<<endl;
                    if (alpha < tmp)
                    {
                        alpha = tmp;
                        if (depth == 5)
                        {

                            MoveOderCurent = i;
                            MoveOderNext = Parr[j];
                            // cout<<"MoveOdercurent: i, "<<i<<" MoveOderNext: "<<MoveOderNext.x<<" "<<MoveOderNext.y<<endl;
                            // console.log(moveOderCurent,moveOderNext)
                        }
                        if (alpha >= beta)
                            return alpha;
                    }
                }
            }
            return alpha;
        }
        else
        {

            for (int i = 0; i < 16; i++)
            {
                vector<Position> Parr = ValidMove(i, arr, PosB);
                int ParrL = Parr.size();
                //    cout<<"N  "<<"i= "<<i<<" ParrL: "<<ParrL<<endl;
                for (int j = 0; j < ParrL; j++)
                {
                    int b[8][8];
                    CopyMang(arr, b);
                    Pos b1[16];
                    CopyPos(PosA, b1);
                    Pos b2[16];
                    CopyPos(PosB, b2);
                    int tam = b[PosB[i].x][PosB[i].y]; // tam=PosB[i].value;
                    b[PosB[i].x][PosB[i].y] = 0;
                    // an quan
                    if (b[Parr[j].x][Parr[j].y] > 0)
                    {
                        for (int k = 0; k < 16; k++)
                        {
                            if ((b1[k].x == Parr[j].x) && (b1[k].y == Parr[j].y))
                            {
                                b1[k].value = -1;
                                break;
                            }
                        }
                    }
                    // phong hau
                    if ((Parr[j].y == 7) && (i >= 0) && (i < 8))
                    {
                        tam = -90;
                    }
                    // thay doi gia tri tren ban co
                    b[Parr[j].x][Parr[j].y] = tam;
                    // thay doi chi so quan hien tai trong mang a1(mang nhap cua PosA)
                    b2[i].x = Parr[j].x;
                    b2[i].y = Parr[j].y;
                    b2[i].value = tam;

                    int tmp = moveOder(b, alpha, beta, depth - 1, true, b1, b2);

                    if (beta > tmp)
                    {
                        beta = tmp;
                    }
                    if (alpha >= beta)
                        return beta;
                }
            }
            return beta;
        }
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
    //  void banconhap(){
    //     cout<<"////////////////////////////////////"<<endl;
    //      for (int i=0;i<16;i++){
    //         cout<<PosB1[i]->getValue()<<" "<<PosB1[i]->P.x<<" "<<PosB1[i]->P.y<<endl;
    //     }
    //     cout<<"////////////////////////////////////"<<endl;

    // }

    void MoveB()
    {
        int j, x1, y1, a, b;
        int i = 1;
        while (i)
        {
            banco();
            cin >> j;
            vector<Position> P = ValidMove(j, Board, PosB);
            for (int i = 0; i < P.size(); i++)
            {
                cout << endl
                     << P[i].x << " " << P[i].y;
            }
            cout << endl
                 << "dich: ";
            cin >> x1 >> y1;
            if (Board[x1][y1] > 0)
            {
                for (int i = 0; i < 16; i++)
                {
                    if (Board[x1][y1] == PosA[i].value && PosA[i].x == x1 && PosA[i].y == y1)
                    {
                        PosA[i].value = -1;
                        PosA1[i]->die();
                        break;
                    }
                }
            }
            Board[x1][y1] = PosB[j].value;
            Board[PosB[j].x][PosB[j].y] = 0;
            PosB[j].x = x1;
            PosB[j].y = y1;
            PosB1[j]->setP(x1, y1);
            i = 0;
        }
    }
    void AiEat()
    {
        for (int i = 0; i < 16; i++)
        {
            if ((PosB[i].x == MoveOderNext.x) && (PosB[i].y == MoveOderNext.y) && (Board[MoveOderNext.x][MoveOderNext.y] == PosB[i].value))
            {
                PosB[i].value = -1;
                PosB1[i]->die();
            }
        }
    }
    void MoveA()
    {
        if (Board[MoveOderNext.x][MoveOderNext.y] < 0)
            AiEat();
        Board[MoveOderNext.x][MoveOderNext.y] = PosA[MoveOderCurent].value;
        Board[PosA[MoveOderCurent].x][PosA[MoveOderCurent].y] = 0;
        PosA[MoveOderCurent].x = MoveOderNext.x;
        PosA[MoveOderCurent].y = MoveOderNext.y;
        PosA1[MoveOderCurent]->setP(MoveOderNext.x, MoveOderNext.y);
    }
    void show()
    {
        for (int i = 0; i < 16; i++)
        {
            cout << "x= ";
            cout << PosA[i].x;
            cout << ", y=";
            cout << PosA[i].y;
            cout << ", value= ";
            cout << PosA[i].value;
            cout << endl;
        }
        cout << "-----------------------------" << endl;
        for (int i = 0; i < 16; i++)
        {
            cout << "x= " << PosB[i].x << ", y=" << PosB[i].y << ", value= " << PosB[i].value;
            cout << endl;
        }
    }
};

// int main()
// {

//     Gameplay G;
//     G.begin();

//     while (true)
//     {

//         G.MoveB();
//         G.moveOder(Board, -10000, 10000, 5, true, G.PosA, G.PosB);
//         cout << endl
//              << "END: " << G.MoveOderCurent << " " << G.MoveOderNext.x << " " << G.MoveOderNext.y << endl;
//         G.MoveA();
//     }

//     cout << endl;
// }