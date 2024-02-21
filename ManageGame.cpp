#include"chess1.cpp"

class ManagePlayer{
    public:
        Chess *Player[16];

        Pos PosB[16];
        ManagePlayer(){};

        void begin(){
            // tot cua nguoi
        Player[0] = new Tot;
        Player[1] = new Tot;
        Player[2] = new Tot;
        Player[3] = new Tot;
        Player[4] = new Tot;
        Player[5] = new Tot;
        Player[6] = new Tot;
        Player[7] = new Tot;

        // xe cua nguoi
        Player[8] = new Xe;
        Player[9] = new Xe;

        // ma cua nguoi
        Player[10] = new Ma;
        Player[11] = new Ma;

        // tuong cua nguoi
        Player[12] = new Tuong;
        Player[13] = new Tuong;

        // Hau cua nguoi
        Player[14] = new Hau;

        // vua cua nguoi
        Player[15] = new Vua;
        for (int i = 0; i < 8; i++)
        {
            Player[i]->setP(i, 6);
            Player[i]->setIndex(-1);
            Player[i]->setValue();
        }
        Player[8]->setP(0, 7);
        Player[8]->setIndex(-1);
        Player[8]->setValue();
        Player[9]->setP(7, 7);
        Player[9]->setIndex(-1);
        Player[9]->setValue();
        Player[10]->setP(1, 7);
        Player[10]->setIndex(-1);
        Player[10]->setValue();
        Player[11]->setP(6, 7);
        Player[11]->setIndex(-1);
        Player[11]->setValue();
        Player[12]->setP(2, 7);
        Player[12]->setIndex(-1);
        Player[12]->setValue();
        Player[13]->setP(5, 7);
        Player[13]->setIndex(-1);
        Player[13]->setValue();
        Player[14]->setP(3, 7);
        Player[14]->setIndex(-1);
        Player[14]->setValue();
        Player[15]->setP(4, 7);
        Player[15]->setIndex(-1);
        Player[15]->setValue();
        resetPosB();

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
};

class ManageAI{
    public:

        
        ManageAI(){};
        Chess *Computer[16];

        Pos PosA[16];

        int MoveOderCurent; // quan di may se chon hien tai;chi so i trong Pos.
        Location MoveOderNext;// buoc di tiep theo cua may

        void begin(){
             // tot cua may
        Computer[0] = new Tot;
        Computer[1] = new Tot;
        Computer[2] = new Tot;
        Computer[3] = new Tot;
        Computer[4] = new Tot;
        Computer[5] = new Tot;
        Computer[6] = new Tot;
        Computer[7] = new Tot;

        // xe cua may
        Computer[8] = new Xe;
        Computer[9] = new Xe;

        // ma cua may
        Computer[10] = new Ma;
        Computer[11] = new Ma;

        // tuong cua may
        Computer[12] = new Tuong;
        Computer[13] = new Tuong;

        // Hau cua may

        Computer[14] = new Hau;

        // vua cua may
        Computer[15] = new Vua;
        for (int i = 0; i < 8; i++)
        {
            Computer[i]->setP(i, 1);
            Computer[i]->setIndex(1);
            Computer[i]->setValue();
        }
        Computer[8]->setP(0, 0);
        Computer[8]->setIndex(1);
        Computer[8]->setValue();
        Computer[9]->setP(7, 0);
        Computer[9]->setIndex(1);
        Computer[9]->setValue();
        Computer[10]->setP(1, 0);
        Computer[10]->setIndex(1);
        Computer[10]->setValue();
        Computer[11]->setP(6, 0);
        Computer[11]->setIndex(1);
        Computer[11]->setValue();
        Computer[12]->setP(2, 0);
        Computer[12]->setIndex(1);
        Computer[12]->setValue();
        Computer[13]->setP(5, 0);
        Computer[13]->setIndex(1);
        Computer[13]->setValue();
        Computer[14]->setP(3, 0);
        Computer[14]->setIndex(1);
        Computer[14]->setValue();
        Computer[15]->setP(4, 0);
        Computer[15]->setIndex(1);
        Computer[15]->setValue();
        resetPosA();
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
};