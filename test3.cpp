#include <SFML/Graphics.hpp>
#include <iostream>
#include <typeinfo>
#include "GameModePvP.cpp"

using namespace std;
#define SIZE 100
// Chế độ chọn của máy
int isChoose = 1;
int choosed = 0;
int chessChoose = 0;
int valueAI = 2;

// Chế độ chọn của người
int isAChoose = 0;
int isBChoose = 0;

// Biến chiếu tướng
int checkMateVar = 0;

// Biến chiếu bí máy
int checkEndGameAI = 0;

// Biến chiếu bí người
int checkEndGamePlayer = 0;

// Biến chiếu bí trắng
int checkEndGameWhite = 0;

// Biến chiếu bí đen
int checkEndGameBlack = 0;


// Khởi tạo màu cho các ô đen và trắng
sf::Color blackColor(209, 139, 71);
sf::Color whiteColor(255, 206, 158);
sf::Color whiteColorHover(255, 255, 158);
sf::Color colorBlue(0, 0, 255);
sf::Color colorRed(255, 0, 0);
sf::RenderWindow window(sf::VideoMode(12 * SIZE, 8 * SIZE), "Chess Board");
sf::Texture texture[32];
sf::Sprite sprite[32];



// Tạo một bảng 8x8
sf::RectangleShape squares[8][8];

// Tạo nút undo
sf::RectangleShape modeButton;

// Tạo nút chọn chế độ người và máy
sf::RectangleShape AIMode;
sf::RectangleShape AIModeEasy;
sf::RectangleShape AIModeMedium;
sf::RectangleShape AIModeHard;
sf::RectangleShape PvPMode;





bool areColorsEqual(const sf::Color& color1, const sf::Color& color2) {
    return (color1.r == color2.r) && (color1.g == color2.g) && (color1.b == color2.b) && (color1.a == color2.a);
}
void ShowEffect(int x, int y, sf::RectangleShape squares[][8], GameModeAI& Game, int index) {
    cout << "choose : " << chessChoose << endl;
    cout << "index : " << index << endl;
    //vector<Position> P = G.ValidMove(index, Board, G.PosB);
    Game.banco();
    for (int i = 0; i < 16; i++) {
        //cout << Game.Player.PosB[i].x << " " << Game.Player.PosB[i].y << endl;
        cout << Game.Player.PosB[i].value << " ";
    }
    
    Game.Player.Player[index]->PositiveMove();
    Stack<Location> P = Game.Player.Player[index]->Pnew;
    //cout << "G: " << Game.Player.Player[index]->getP().x << endl;
    //for (int i = 0; i < P.size(); i++)
    //{
    //    squares[P[i].x][P[i].y].setFillColor(colorRed);
    //}
    while (!P.isEmpty())
    {
        Location P1 = P.top();
        cout << P1.x << P1.y << endl;
        squares[P1.x][P1.y].setFillColor(colorRed);
        P.pop();
    }
    Game.Player.Player[index]->resetPnew();

}
void ShowEffectPvP(int x, int y, sf::RectangleShape squares[][8], GameModePvP& PvP, int index) {
    if (PvP.turn == true) {
        PvP.Player1.Player[index]->PositiveMove();
        Stack<Location> P = PvP.Player1.Player[index]->Pnew;
        while (!P.isEmpty())
        {
            Location P1 = P.top();
            cout << P1.x << P1.y << endl;
            squares[P1.x][P1.y].setFillColor(colorRed);
            P.pop();
        }
        PvP.Player1.Player[index]->resetPnew();
    }
    else {
        PvP.Player2.Computer[index]->PositiveMove();
        Stack<Location> P = PvP.Player2.Computer[index]->Pnew;
        while (!P.isEmpty())
        {
            Location P1 = P.top();
            cout << P1.x << P1.y << endl;
            squares[P1.x][P1.y].setFillColor(colorRed);
            P.pop();
        }
        PvP.Player2.Computer[index]->resetPnew();
    }
    
}
void ResetColor(sf::RectangleShape squares[][8]) {
    bool isBlack = true;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (isBlack) {
                squares[i][j].setFillColor(blackColor);
            }
            else {
                squares[i][j].setFillColor(whiteColor);
            }

            isBlack = !isBlack;
        }
        isBlack = !isBlack;
    }
}

bool isValidMove(int isChoose, int choosed, int x, int y, sf::RectangleShape squares[][8]) {
    return isChoose == 0 && choosed == 1 && areColorsEqual(squares[x][y].getFillColor(), colorRed);

}

void moveChess(int a, int b, int x, int y, sf::Sprite sprite[], sf::RenderWindow& window, sf::RectangleShape squares[][8]) {
    sf::Vector2f startPos(a, b);
    sf::Vector2f endPos(x, y);

    sf::Vector2f outPos(-100, -100);
    sf::Clock clock;
    for (int i = 0; i < 32; i++) {
        if (abs(sprite[i].getPosition().x - x) <= 10 && abs(sprite[i].getPosition().y - y) <= 10) {
            sprite[i].setPosition(outPos);
        }
    }
    while (true)
    {
        //window.clear();
        // Vẽ bàn cờ
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                window.draw(squares[i][j]);
            }
        }
        for (int i = 0; i < 32; i++) {
            window.draw(sprite[i]);
        }

        float duration = 0.1f;
        float elapsedTime = clock.getElapsedTime().asSeconds();
        if (elapsedTime <= duration)
        {
            // Tính toán vị trí mới của hình ảnh
            float interpolation = elapsedTime / duration;
            sf::Vector2f newPosition = startPos + (endPos - startPos) * interpolation;
            sprite[chessChoose].setPosition(newPosition);
            window.draw(sprite[chessChoose]);
            window.display();
        }
        else {
            break;
        }
    }
    ResetColor(squares);
    choosed = 0;
}

void GameModeAI::undo() {
    bool y = true;
    Undo R;

    while (y == true && !U.isEmpty()) {
        R = U.top();

        if (R.PorC == 1) {
            Board[R.begin.x][R.begin.y] = AI.PosA[R.i].value;
            Board[R.end.x][R.end.y] = 0;
            cout << "undo" << AI.PosA[R.i].y << " " << R.begin.y << endl;
            chessChoose = R.i;
            moveChess(AI.PosA[R.i].x * SIZE, AI.PosA[R.i].y * SIZE, R.begin.x * SIZE, R.begin.y * SIZE, sprite, window, squares);
            AI.PosA[R.i].x = R.begin.x;
            AI.PosA[R.i].y = R.begin.y;
            AI.Computer[R.i]->setP(R.begin.x, R.begin.y);
            if (R.checkQueen == true) {
                sprite[R.i] = sf::Sprite(texture[R.i]);
                sprite[R.i].setPosition(R.begin.x * SIZE, R.begin.y * SIZE);
                AI.Computer[R.i]->isQueen = 0;
                AI.Computer[R.i]->setValue();
                Board[R.begin.x][R.begin.y] = AI.Computer[R.i]->getValue();
                AI.PosA[R.i].value = AI.Computer[R.i]->getValue();
            }
            U.pop();
            y = true;

        }
        else if (R.PorC == -1)
        {
            if (R.end.x == Pdie.x) {
                Player.Player[R.i]->alive();
                sprite[R.i + 16].setPosition(R.begin.x * SIZE, R.begin.y * SIZE);
                Player.PosB[R.i].value = Player.Player[R.i]->getIndex() * Player.Player[R.i]->getValue();
                y = true;

            }
            else {
                y = false;
            }
            Board[R.begin.x][R.begin.y] = Player.PosB[R.i].value;
            if (R.end.x != Pdie.x) Board[R.end.x][R.end.y] = 0;
            chessChoose = R.i + 16;
            moveChess(Player.PosB[R.i].x * SIZE, Player.PosB[R.i].y * SIZE, R.begin.x * SIZE, R.begin.y * SIZE, sprite, window, squares);
            Player.PosB[R.i].x = R.begin.x;
            Player.PosB[R.i].y = R.begin.y;
            Player.Player[R.i]->setP(R.begin.x, R.begin.y);
            if (R.checkQueen == true) {
                sprite[R.i + 16] = sf::Sprite(texture[R.i + 16]);
                sprite[R.i + 16].setPosition(R.begin.x * SIZE, R.begin.y * SIZE);
                Player.Player[R.i]->isQueen = 0;
                Player.Player[R.i]->setValue();
                Board[R.begin.x][R.begin.y] = Player.Player[R.i]->getValue()*Player.Player[R.i]->getIndex();
                Player.PosB[R.i].value = Player.Player[R.i]->getValue()*Player.Player[R.i]->getIndex();
            }
            U.pop();
            if (y == false && !U.isEmpty())
            {

                R = U.top();

                if (R.end.x == Pdie.x) {
                    AI.Computer[R.i]->alive();
                    sprite[R.i].setPosition(R.begin.x * SIZE, R.begin.y * SIZE);
                    AI.PosA[R.i].value = AI.Computer[R.i]->getValue();
                    Board[AI.PosA[R.i].x][AI.PosA[R.i].y] = AI.PosA[R.i].value;
                    U.pop();

                }
            }
        }
    }

}
void GameModePvP::undo() {
    bool y = true;
    Undo R;
    while (y == true && !U.isEmpty()) {
        turn = !turn;
        R = U.top();
        //cout << "<<" << R.PorC << " " << R.i << " " << R.begin.x << R.begin.y << R.end.x << R.end.y << endl;
        if (R.PorC == -1) {
            Board[R.begin.x][R.begin.y] = Player1.PosB[R.i].value;
            Board[R.end.x][R.end.y] = 0;
            chessChoose = R.i + 16;
            moveChess(Player1.PosB[R.i].x * SIZE, Player1.PosB[R.i].y * SIZE, R.begin.x * SIZE, R.begin.y * SIZE, sprite, window, squares);
            Player1.PosB[R.i].x = R.begin.x;
            Player1.PosB[R.i].y = R.begin.y;
            Player1.Player[R.i]->setP(R.begin.x, R.begin.y);
            if (R.checkQueen == true) {
                sprite[R.i + 16] = sf::Sprite(texture[R.i + 16]);
                sprite[R.i + 16].setPosition(R.begin.x * SIZE, R.begin.y * SIZE);
                cout << " Vi tri " << sprite[R.i + 16].getPosition().x << sprite[R.i + 16].getPosition().y << endl;
                Player1.Player[R.i]->isQueen = 0;
                Player1.Player[R.i]->setValue();
                Board[R.begin.x][R.begin.y] = Player1.Player[R.i]->getValue()*Player1.Player[R.i]->getIndex();
                Player1.PosB[R.i].value = Player1.Player[R.i]->getValue()*Player1.Player[R.i]->getIndex();
            }
            U.pop();
            if (U.isEmpty()) {
                y = false;
                break;
            }
            R = U.top();
            if (R.PorC == 1 && R.end.x == Pdie.x) {
                Player2.Computer[R.i]->alive();
                sprite[R.i].setPosition(R.begin.x * SIZE, R.begin.y * SIZE);
                Player2.PosA[R.i].value = Player2.Computer[R.i]->getValue();
                Board[Player2.PosA[R.i].x][Player2.PosA[R.i].y] = Player2.PosA[R.i].value;
                U.pop();
            }
            y = false;

        }
        else if (R.PorC == 1) {
            Board[R.begin.x][R.begin.y] = Player2.PosA[R.i].value;
            Board[R.end.x][R.end.y] = 0;
            chessChoose = R.i;
            moveChess(Player2.PosA[R.i].x * SIZE, Player2.PosA[R.i].y * SIZE, R.begin.x * SIZE, R.begin.y * SIZE, sprite, window, squares);
            Player2.PosA[R.i].x = R.begin.x;
            Player2.PosA[R.i].y = R.begin.y;
            Player2.Computer[R.i]->setP(R.begin.x, R.begin.y);
            if (R.checkQueen == true) {
                sprite[R.i] = sf::Sprite(texture[R.i]);
                sprite[R.i].setPosition(R.begin.x * SIZE, R.begin.y * SIZE);
                Player2.Computer[R.i]->isQueen = 0;
                Player2.Computer[R.i]->setValue();
                Board[R.begin.x][R.begin.y] = Player2.Computer[R.i]->getValue();
                Player2.PosA[R.i].value = Player2.Computer[R.i]->getValue();
            }
            U.pop();
            if (U.isEmpty()) {
                y = false;
                break;
            }
            R = U.top();
            if (R.PorC == -1 && R.end.x == Pdie.x) {
                Player1.Player[R.i]->alive();
                sprite[R.i + 16].setPosition(R.begin.x * SIZE, R.begin.y * SIZE);
                Player1.PosB[R.i].value = Player1.Player[R.i]->getValue() * Player1.Player[R.i]->getIndex();
                Board[Player1.PosB[R.i].x][Player1.PosB[R.i].y] = Player1.PosB[R.i].value;
                U.pop();
            }
            y = false;

        }
    }
}
void SelectChess(int x, int y, sf::Sprite sprite[], sf::RenderWindow& window, sf::RectangleShape squares[][8], GameModeAI& Game) {

    for (int i = 16; i < 32; i++) {
        if (abs(sprite[i].getPosition().x - x * SIZE) <= 10 && abs(sprite[i].getPosition().y - y * SIZE) <= 10) {
            //cout << sprite[i].getPosition().x << " " << sprite[i].getPosition().y << endl;
            //cout << i << endl;
            ResetColor(squares);
            isChoose = 1;
            choosed = 1;
            chessChoose = i;
            ShowEffect(x, y, squares, Game, i - 16);
            squares[x][y].setFillColor(colorBlue);
            return;
        }
    }
    isChoose = 0;
}

void SelectChessPvP(int x, int y, sf::Sprite sprite[], sf::RenderWindow& window, sf::RectangleShape squares[][8], GameModePvP& PvP) {
    if (PvP.turn == true) {
        // Kiểm tra xem quân nào được chọn ở bên trắng
        for (int i = 16; i < 32; i++) {
            if (abs(sprite[i].getPosition().x - x * SIZE) <= 10 && abs(sprite[i].getPosition().y - y * SIZE) <= 10) {
                cout << "\nVi tri cac quan : " << sprite[i].getPosition().x << sprite[i].getPosition().y << endl;
                ResetColor(squares);
                ShowEffectPvP(x, y, squares, PvP, i - 16);
                squares[x][y].setFillColor(colorBlue);
                isAChoose = 0;
                isBChoose = 1;
                chessChoose = i;
                return;
            }
        }
    }
    else {
        // Kiểm tra xem quân nào được chọn ở bên đen
        for (int i = 0; i < 16; i++) {

            if (abs(sprite[i].getPosition().x - x * SIZE) <= 10 && abs(sprite[i].getPosition().y - y * SIZE) <= 10) {
                cout << "\nVi tri cac quan : " << sprite[i].getPosition().x << sprite[i].getPosition().y << endl;
                ResetColor(squares);
                ShowEffectPvP(x, y, squares, PvP, i);
                squares[x][y].setFillColor(colorBlue);
                isAChoose = 1;
                isBChoose = 0;
                chessChoose = i;
                return;
            }
        }
    }
    
}
int main(){
    
    sf::Font font;
    if (!font.loadFromFile("Roboto/Roboto-Medium.ttf")) {
        return -1;
    }

    sf::Text AIText;
    AIText.setFont(font);
    AIText.setString("AI");
    AIText.setCharacterSize(90);
    AIText.setFillColor(sf::Color::Black);
    AIText.setPosition(950, 42);

    sf::Text AIEasyText;
    AIEasyText.setFont(font);
    AIEasyText.setString("Easy");
    AIEasyText.setCharacterSize(90);
    AIEasyText.setFillColor(sf::Color::Black);
    AIEasyText.setPosition(910, 137);

    sf::Text AIMediumText;
    AIMediumText.setFont(font);
    AIMediumText.setString("Normal");
    AIMediumText.setCharacterSize(90);
    AIMediumText.setFillColor(sf::Color::Black);
    AIMediumText.setPosition(855, 342);

    sf::Text AIHardText;
    AIHardText.setFont(font);
    AIHardText.setString("Hard");
    AIHardText.setCharacterSize(90);
    AIHardText.setFillColor(sf::Color::Black);
    AIHardText.setPosition(910, 542);

    sf::Text PvPText;
    PvPText.setFont(font);
    PvPText.setString("PvP");
    PvPText.setCharacterSize(90);
    PvPText.setFillColor(sf::Color::Black);
    PvPText.setPosition(920, 192);

    sf::Text undoText;
    undoText.setFont(font);
    undoText.setString("Undo");
    undoText.setCharacterSize(90);
    undoText.setFillColor(sf::Color::Black);
    undoText.setPosition(900, 342);

    sf::Text checkMateText;
    checkMateText.setFont(font);
    checkMateText.setString("Checkmate!");
    checkMateText.setCharacterSize(60);
    checkMateText.setFillColor(sf::Color::Red);
    checkMateText.setPosition(850, 600);

    sf::Text AIWinText;
    AIWinText.setFont(font);
    AIWinText.setString("AI Win!");
    AIWinText.setCharacterSize(60);
    AIWinText.setFillColor(sf::Color::Yellow);
    AIWinText.setPosition(910, 600);

    sf::Text YouWinText;
    YouWinText.setFont(font);
    YouWinText.setString("You Win!");
    YouWinText.setCharacterSize(60);
    YouWinText.setFillColor(sf::Color::Yellow);
    YouWinText.setPosition(880, 600);

    sf::Text WhiteWinText;
    WhiteWinText.setFont(font);
    WhiteWinText.setString("White Win!");
    WhiteWinText.setCharacterSize(60);
    WhiteWinText.setFillColor(sf::Color::Yellow);
    WhiteWinText.setPosition(850, 600);

    sf::Text BlackWinText;
    BlackWinText.setFont(font);
    BlackWinText.setString("Black Win!");
    BlackWinText.setCharacterSize(60);
    BlackWinText.setFillColor(sf::Color::Yellow);
    BlackWinText.setPosition(850, 600);
    



    // Biến chế độ
    int menuGame = 0;

    // Tạo chế độ AI
    GameModeAI Game;
    Game.begin();

    // Tạo chế độ PvP
    GameModePvP PvP;
    PvP.begin();

    //Tạo nút undo
    modeButton.setSize(sf::Vector2f(300, 100));
    modeButton.setPosition(850, 350);
    modeButton.setFillColor(whiteColor);
    modeButton.setOutlineColor(blackColor);
    modeButton.setOutlineThickness(8.0f);

    //Tạo nút AIMode
    AIMode.setSize(sf::Vector2f(300, 100));
    AIMode.setPosition(850, 50);
    AIMode.setFillColor(whiteColor);
    AIMode.setOutlineColor(blackColor);

    //Tạo nút chế độ dễ
    AIModeEasy.setSize(sf::Vector2f(300, 100));
    AIModeEasy.setPosition(850, 150);
    AIModeEasy.setFillColor(whiteColor);
    AIModeEasy.setOutlineColor(blackColor);

    //Tạo nút chế độ trung bình
    AIModeMedium.setSize(sf::Vector2f(300, 100));
    AIModeMedium.setPosition(850, 350);
    AIModeMedium.setFillColor(whiteColor);
    AIModeMedium.setOutlineColor(blackColor);

    //Tạo nút chế độ khó
    AIModeHard.setSize(sf::Vector2f(300, 100));
    AIModeHard.setPosition(850, 550);
    AIModeHard.setFillColor(whiteColor);
    AIModeHard.setOutlineColor(blackColor);


    //Tạo nút PvPMode
    PvPMode.setSize(sf::Vector2f(300, 100));
    PvPMode.setPosition(850, 200);
    PvPMode.setFillColor(whiteColor);
    PvPMode.setOutlineColor(blackColor);

    // Tạo bàn cờ vua
    bool isBlack = true;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            squares[i][j].setSize(sf::Vector2f(SIZE, SIZE));
            squares[i][j].setPosition(i * SIZE, j * SIZE);

            if (isBlack) {
                squares[i][j].setFillColor(blackColor);
            }
            else {
                squares[i][j].setFillColor(whiteColor);
            }

            isBlack = !isBlack;
        }
        isBlack = !isBlack;
    }
 


    
        // Tạo hình ảnh từ tệp

    if (!texture[8].loadFromFile("rockA.png")) {}
    sprite[8] = sf::Sprite(texture[8]);
    sprite[8].setPosition(0, 0);
    if (!texture[9].loadFromFile("rockA.png")) {}
    sprite[9] = sf::Sprite(texture[9]);
    sprite[9].setPosition(700, 0);
    if (!texture[10].loadFromFile("knightA.png")) {}
    sprite[10] = sf::Sprite(texture[10]);
    sprite[10].setPosition(100, 0);
    if (!texture[11].loadFromFile("knightA.png")) {}
    sprite[11] = sf::Sprite(texture[11]);
    sprite[11].setPosition(600, 0);
    if (!texture[12].loadFromFile("bishopA.png")) {}
    sprite[12] = sf::Sprite(texture[12]);
    sprite[12].setPosition(200, 0);
    if (!texture[13].loadFromFile("bishopA.png")) {}
    sprite[13] = sf::Sprite(texture[13]);
    sprite[13].setPosition(500, 0);
    if (!texture[14].loadFromFile("queenA.png")) {}
    sprite[14] = sf::Sprite(texture[14]);
    sprite[14].setPosition(300, 0);
    if (!texture[15].loadFromFile("kingA.png")) {}
    sprite[15] = sf::Sprite(texture[15]);
    sprite[15].setPosition(400, 0);
    for (int i = 0; i < 8; i++) {
        if (!texture[i].loadFromFile("pawnA.png")) {}
        sprite[i] = sf::Sprite(texture[i]);
        sprite[i].setPosition(i * 100, 100);
    }
    if (!texture[24].loadFromFile("rockB.png")) {}
    sprite[24] = sf::Sprite(texture[24]);
    sprite[24].setPosition(0, 700);
    if (!texture[25].loadFromFile("rockB.png")) {}
    sprite[25] = sf::Sprite(texture[25]);
    sprite[25].setPosition(700, 700);
    if (!texture[26].loadFromFile("knightB.png")) {}
    sprite[26] = sf::Sprite(texture[26]);
    sprite[26].setPosition(100, 700);
    if (!texture[27].loadFromFile("knightB.png")) {}
    sprite[27] = sf::Sprite(texture[27]);
    sprite[27].setPosition(600, 700);
    if (!texture[28].loadFromFile("bishopB.png")) {}
    sprite[28] = sf::Sprite(texture[28]);
    sprite[28].setPosition(200, 700);
    if (!texture[29].loadFromFile("bishopB.png")) {}
    sprite[29] = sf::Sprite(texture[29]);
    sprite[29].setPosition(500, 700);
    if (!texture[30].loadFromFile("queenB.png")) {}
    sprite[30] = sf::Sprite(texture[30]);
    sprite[30].setPosition(300, 700);
    if (!texture[31].loadFromFile("kingB.png")) {}
    sprite[31] = sf::Sprite(texture[31]);
    sprite[31].setPosition(400, 700);
    for (int i = 16; i < 24; i++) {
        if (!texture[i].loadFromFile("pawnB.png")) {}
        sprite[i] = sf::Sprite(texture[i]);
        sprite[i].setPosition((i - 16) * 100, 600);
    }
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    int col = mousePosition.x / SIZE;
                    int row = mousePosition.y / SIZE;

                    cout << "Toa do : " << col << " " << row << endl;

                    // Chọn chế độ
                    if (menuGame == 0) {
                        if (mousePosition.x - 850 >= 0 && mousePosition.x <= 1150 && mousePosition.y >= 50 && mousePosition.y <= 150) {

                            menuGame = -1;

                        }

                        if (mousePosition.x - 850 >= 0 && mousePosition.x <= 1150 && mousePosition.y >= 200 && mousePosition.y <= 300) {

                            menuGame = 2;

                        }

                    }
                    if (menuGame == -1) {
                        if (mousePosition.x - 850 >= 0 && mousePosition.x <= 1150 && mousePosition.y >= 150 && mousePosition.y <= 250) {
                            menuGame = 1;
                            valueAI = 2;
                        }
                        if (mousePosition.x - 850 >= 0 && mousePosition.x <= 1150 && mousePosition.y >= 350 && mousePosition.y <= 450) {
                            menuGame = 1;
                            valueAI = 4;
                        }
                        if (mousePosition.x - 850 >= 0 && mousePosition.x <= 1150 && mousePosition.y >= 550 && mousePosition.y <= 650) {
                            menuGame = 1;
                            valueAI = 5;
                        }
                    }

                    // Đấu với máy
                    if (menuGame == 1) {
                        if (mousePosition.x - 850 >= 0 && mousePosition.x <= 1150 && mousePosition.y >= 350 && mousePosition.y <= 450) {

                            Game.undo();

                        }
                        SelectChess(col, row, sprite, window, squares, Game);

                        if (isValidMove(isChoose, choosed, col, row, squares)) {

                            int indexP = Game.MoveB(chessChoose - 16, col, row);
                            if (indexP != -1) {
                                sprite[indexP + 16] = sf::Sprite(texture[30]);
                                sprite[indexP + 16].setPosition(Game.Player.PosB[indexP].x * SIZE, Game.Player.PosB[indexP].y * SIZE);
                            }
                            if (Game.checkMate(Board, Game.AI.PosA, Game.Player.PosB) == -1) {
                                checkMateVar = 1;
                                Game.undo();
                                break;
                            }

                            checkMateVar = Game.checkMate(Board, Game.AI.PosA, Game.Player.PosB);
                            moveChess(sprite[chessChoose].getPosition().x, sprite[chessChoose].getPosition().y, col * SIZE, row * SIZE, sprite, window, squares);
                            if (checkMateVar == 1) {
                                if (Game.endGamePlayer()) {
                                    checkEndGameAI = Game.endGamePlayer();
                                    break;
                                }
                            }

                            Game.moveOder(Board, -10000, 10000, valueAI, valueAI, true, Game.AI.PosA, Game.Player.PosB);
                            Game.banco();
                            cout << Game.AI.MoveOderCurent;
                            int indexAI = Game.MoveA();
                            if (indexAI != -1) {
                                sprite[indexAI] = sf::Sprite(texture[14]);
                                sprite[indexAI].setPosition(Game.AI.PosA[indexAI].x * SIZE, Game.AI.PosA[indexAI].y * SIZE);
                            }

                            chessChoose = Game.AI.MoveOderCurent;
                            moveChess(sprite[chessChoose].getPosition().x, sprite[chessChoose].getPosition().y, Game.AI.MoveOderNext.x * SIZE, Game.AI.MoveOderNext.y * SIZE, sprite, window, squares);
                            // Kiểm tra chiếu tướng
                            checkMateVar = Game.checkMate(Board, Game.AI.PosA, Game.Player.PosB);
                            if (checkMateVar == -1) {
                                if (Game.endGameAI()) {
                                    checkEndGamePlayer = Game.endGameAI();
                                }
                            }


                        }
                    }

                    // Đấu với người
                    if (menuGame == 2) {
                        if (mousePosition.x - 850 >= 0 && mousePosition.x <= 1150 && mousePosition.y >= 350 && mousePosition.y <= 450) {
                            PvP.undo();
                        }
                        SelectChessPvP(col, row, sprite, window, squares, PvP);
                        if (isValidMove(isAChoose, isBChoose, col, row, squares)) {
                            // Nước đi bên trắng
                            int index = PvP.Move(chessChoose - 16, col, row);
                            if (index != -1) {
                                //phong hậu bên trắng
                                sprite[index + 16] = sf::Sprite(texture[30]);
                                sprite[index + 16].setPosition(PvP.Player1.PosB[index].x * SIZE, PvP.Player1.PosB[index].y * SIZE);
                            }
                            // Trắng di chuyển nhưng trắng vẫn bị chiếu -> undo lại
                            if (PvP.checkMate(Board, PvP.Player2.PosA, PvP.Player1.PosB) == -1) {
                                checkMateVar = 1;
                                PvP.undo();
                                break;
                            }
                            checkMateVar = PvP.checkMate(Board, PvP.Player2.PosA, PvP.Player1.PosB);

                            if (checkMateVar == 1) {
                                if (PvP.endGameP1()) {
                                    checkEndGameWhite = PvP.endGameP1();
                                }
                            }

                            moveChess(sprite[chessChoose].getPosition().x, sprite[chessChoose].getPosition().y, col * SIZE, row * SIZE, sprite, window, squares);

                        }

                        if (isValidMove(isBChoose, isAChoose, col, row, squares)) {
                            // Nước đi bên đen
                            int index = PvP.Move(chessChoose, col, row);
                            if (index != -1) {
                                //phong hậu bên đen
                                sprite[index] = sf::Sprite(texture[14]);
                                sprite[index].setPosition(PvP.Player2.PosA[index].x * SIZE, PvP.Player2.PosA[index].y * SIZE);
                            }

                            if (PvP.checkMate(Board, PvP.Player2.PosA, PvP.Player1.PosB) == 1) {
                                checkMateVar = 1;
                                PvP.undo();
                                break;
                            }
                            checkMateVar = PvP.checkMate(Board, PvP.Player2.PosA, PvP.Player1.PosB);
                            if (checkMateVar == -1) {
                                checkMateVar = 1;
                            }
                            if (checkMateVar == 1) {
                                if (PvP.endGameP2()) {
                                    checkEndGameBlack = PvP.endGameP2();
                                }
                            }
                            moveChess(sprite[chessChoose].getPosition().x, sprite[chessChoose].getPosition().y, col * SIZE, row * SIZE, sprite, window, squares);

                        }


                    }

                }
            }


            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
                (AIMode.getGlobalBounds().contains(mousePos)) ? AIMode.setFillColor(blackColor) : AIMode.setFillColor(whiteColor);
                (AIModeEasy.getGlobalBounds().contains(mousePos)) ? AIModeEasy.setFillColor(blackColor) : AIModeEasy.setFillColor(whiteColor);
                (AIModeMedium.getGlobalBounds().contains(mousePos)) ? AIModeMedium.setFillColor(blackColor) : AIModeMedium.setFillColor(whiteColor);
                (AIModeHard.getGlobalBounds().contains(mousePos)) ? AIModeHard.setFillColor(blackColor) : AIModeHard.setFillColor(whiteColor);
                (PvPMode.getGlobalBounds().contains(mousePos)) ? PvPMode.setFillColor(blackColor) : PvPMode.setFillColor(whiteColor);
                (modeButton.getGlobalBounds().contains(mousePos)) ? modeButton.setFillColor(blackColor) : modeButton.setFillColor(whiteColor);
            }
        }
            

        window.clear();

        // Vẽ bàn cờ
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                window.draw(squares[i][j]);
            }
        }

        // Vẽ quân cờ
        for (int i = 0; i < 32; i++) {
            window.draw(sprite[i]);
        }


        // Vẽ nút chọn chế độ
        if (menuGame == 0) {
            window.draw(AIMode);
            window.draw(PvPMode);
            window.draw(PvPText);
            window.draw(AIText);
        }

        // Vẽ nút undo và chế độ với máy
        if (menuGame == -1) {
            window.draw(AIModeEasy);
            AIModeEasy.setOutlineThickness(8.0f);
            window.draw(AIModeMedium);
            AIModeMedium.setOutlineThickness(8.0f);
            window.draw(AIModeHard);
            AIModeHard.setOutlineThickness(8.0f);
            window.draw(AIEasyText);
            window.draw(AIMediumText);
            window.draw(AIHardText);
        }

        // Vẽ nút undo và chế độ với máy
        if(menuGame == 1) {
            window.draw(AIMode);
            window.draw(modeButton);
            AIMode.setOutlineThickness(8.0f);
            PvPMode.setOutlineThickness(8.0f);
            window.draw(AIText);
            window.draw(undoText);
            if (valueAI == 2) {
                AIModeEasy.setPosition(850, 200);
                AIEasyText.setPosition(910, 185);
                window.draw(AIModeEasy);
                window.draw(AIEasyText);
            }
            if (valueAI == 4) {
                AIModeEasy.setPosition(850, 200);
                AIMediumText.setPosition(855, 190);
                window.draw(AIModeEasy);
                window.draw(AIMediumText);
            }
            if (valueAI == 5) {
                AIModeEasy.setPosition(850, 200);
                AIHardText.setPosition(910, 190);
                window.draw(AIModeEasy);
                window.draw(AIHardText);
            }
        }

        // Vẽ nút undo và chế độ với người
        if (menuGame == 2) {
            window.draw(PvPMode);
            window.draw(modeButton);
            PvPMode.setOutlineThickness(8.0f);
            AIMode.setOutlineThickness(8.0f);
            window.draw(PvPText);
            window.draw(undoText);
        }

        if (checkMateVar) {
            window.draw(checkMateText);
        }

        if (checkEndGamePlayer) {
            checkMateVar = 0;
            window.draw(AIWinText);
        }

        if (checkEndGameAI) {
            checkMateVar = 0;
            window.draw(YouWinText);
        }

        if (checkEndGameWhite) {
            checkMateVar = 0;
            window.draw(WhiteWinText);
        }

        if (checkEndGameBlack) {
            checkMateVar = 0;
            window.draw(BlackWinText);
        }

        window.display();
    }

    return 0;
}


