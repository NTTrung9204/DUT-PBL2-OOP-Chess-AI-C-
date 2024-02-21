﻿#include <SFML/Graphics.hpp>
#include <iostream>
#include <typeinfo>
#include "gameplay.cpp"

using namespace std;
#define SIZE 100
int isChoose = 1;
int choosed = 0;
int chessChoose = 0;
// Khởi tạo màu cho các ô đen và trắng
sf::Color blackColor(209, 139, 71);
sf::Color whiteColor(255, 206, 158);
sf::Color colorBlue(0, 0, 255);
sf::Color colorRed(255, 0, 0);

bool areColorsEqual(const sf::Color& color1, const sf::Color& color2) {
    return (color1.r == color2.r) && (color1.g == color2.g) && (color1.b == color2.b) && (color1.a == color2.a);
}
void ShowEffect(int x, int y, sf::RectangleShape squares[][8], Gameplay &G, int index) {
    cout << "choose : " << chessChoose << endl;
    cout << "index : " << index << endl;
    //vector<Position> P = G.ValidMove(index, Board, G.PosB);
    G.PosB1[index]->PositiveMove();
    stack<Position> P = G.PosB1[index]->Pnew;
    cout << "G: " << G.PosB1[index]->getP().x;
    //for (int i = 0; i < P.size(); i++)
    //{
    //    squares[P[i].x][P[i].y].setFillColor(colorRed);
    //}
    cout << P.empty();
    while (!P.empty())
    {
        cout << "LLL\n";
        Position P1 = P.top();
        cout << P1.x << P1.y << endl;
        squares[P1.x][P1.y].setFillColor(colorRed);
        P.pop();
    }
    G.PosB1[index]->resetPnew();

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

void moveChess(int a, int b, int x, int y, sf::Sprite sprite[], sf::RenderWindow& window, sf::RectangleShape squares[][8], Gameplay &G) {
    sf::Vector2f startPos(a, b);
    sf::Vector2f endPos(x, y);
    sf::Vector2f outPos(-100, -100);
    sf::Clock clock;
    for (int i = 0; i < 32; i++) {
        if (abs(sprite[i].getPosition().x - x) <= 10 && abs(sprite[i].getPosition().y - y) <= 10) {
            sprite[i].setPosition(outPos);
        }
    }
    if (chessChoose >= 16 && chessChoose < 32) {
        if (Board[x / 100][y / 100] > 0)
        {
            for (int i = 0; i < 16; i++)
            {
                if (Board[x / 100][y / 100] == G.PosA[i].value && G.PosA[i].x == x / 100 && G.PosA[i].y == y / 100)
                {
                    G.PosA[i].value = -1;
                    break;
                }
            }
        }
        int index = 0;
        for (int i = 16; i < 32; i++) {
            if (abs(sprite[i].getPosition().x - a) <= 10 && abs(sprite[i].getPosition().y - b) <= 10) {
                index = i-16;
                break;
            }
        }
        Board[x / 100][y / 100] = G.PosB[index].value;
        Board[G.PosB[index].x][G.PosB[index].y] = 0;
        G.PosB[index].x = x / 100;
        G.PosB[index].y = y / 100;
        G.PosB1[index]->setP(x / 100, y / 100);
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

void SelectChess(int x, int y, sf::Sprite sprite[], sf::RenderWindow& window, sf::RectangleShape squares[][8], Gameplay &G) {
    for (int i = 16; i < 32; i++) {
        if (abs(sprite[i].getPosition().x - x * SIZE) <= 10 && abs(sprite[i].getPosition().y - y * SIZE) <= 10) {
            cout << sprite[i].getPosition().x << " " << sprite[i].getPosition().y << endl;
            cout << i << endl;
            ResetColor(squares);
            isChoose = 1;
            choosed = 1;
            chessChoose = i;
            ShowEffect(x, y, squares, G, i - 16);
            squares[x][y].setFillColor(colorBlue);
            return;
        }
    }
    isChoose = 0;
}



int main()
{
    Gameplay G;
    G.begin();
    sf::RenderWindow window(sf::VideoMode(8 * SIZE, 8 * SIZE), "Chess Board");

    // Tạo một bảng 8x8
    sf::RectangleShape squares[8][8];



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
    sf::Texture texture[32];
    sf::Sprite sprite[32];
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

            // Xử lý sự kiện click chuột
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // Lấy vị trí chuột khi click
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                    // Xác định ô được click
                    int col = mousePosition.x / SIZE;
                    int row = mousePosition.y / SIZE;

                    // In ra vị trí ô được click
                    //std::cout << "Row " << row << ", Col " << col << std::endl;
                    //squares[col][row].setFillColor(blackColor);
                    //squares[col][row].move(20, 20);
                    //squares[col][row].setOutlineColor(color);
                    //squares[col][row].setOutlineThickness(2);
                    G.banco();
                    SelectChess(col, row, sprite, window, squares, G);
                    //cout << isChoose << choosed << endl;
                    if (isValidMove(isChoose, choosed, col, row, squares)) {
                        moveChess(sprite[chessChoose].getPosition().x, sprite[chessChoose].getPosition().y, col * SIZE, row * SIZE, sprite, window, squares, G);
                        G.moveOder(Board, -10000, 10000, 5, true, G.PosA, G.PosB);
                        G.MoveA();
                        chessChoose = G.MoveOderCurent;
                        moveChess(sprite[chessChoose].getPosition().x, sprite[chessChoose].getPosition().y, G.MoveOderNext.x * SIZE, G.MoveOderNext.y * SIZE, sprite, window, squares, G);
                    }
                    //sprite.setPosition(col*SIZE, row*SIZE);

                }
            }
        }

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

        window.display();
    }

    return 0;
}


