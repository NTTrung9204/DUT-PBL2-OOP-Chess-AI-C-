#include <SFML/Graphics.hpp>
#include <iostream>
#include <typeinfo>

using namespace std;


bool areColorsEqual(const sf::Color& color1, const sf::Color& color2) {
    return (color1.r == color2.r) && (color1.g == color2.g) && (color1.b == color2.b) && (color1.a == color2.a);
}
void ShowEffect(int x, int y, sf::RectangleShape squares[][8]) {
    squares[x + 1][y - 1].setFillColor(colorRed);
    squares[x - 1][y - 1].setFillColor(colorRed);
    squares[x][y - 1].setFillColor(colorRed);
    squares[x][y - 2].setFillColor(colorRed);
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
    for (int i = 0; i < 16; i++) {
        if (abs(sprite[i].getPosition().x - x) <= 1 && abs(sprite[i].getPosition().y - y) <= 1) {
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
void SelectChess(int x, int y, sf::Sprite sprite[], sf::RenderWindow& window, sf::RectangleShape squares[][8]) {
    for (int i = 16; i < 32; i++) {
        //cout << i << " " << sprite[i].getPosition().x << " " << sprite[i].getPosition().y << endl;
        if (abs(sprite[i].getPosition().x - x*SIZE) <= 1 && abs(sprite[i].getPosition().y - y*SIZE) <= 1) {
            cout << sprite[i].getPosition().x << " " << sprite[i].getPosition().y << endl;
            cout << i <<endl;
            ResetColor(squares);
            isChoose = 1;
            choosed = 1;
            chessChoose = i;
            ShowEffect(x,y,squares);
            squares[x][y].setFillColor(colorBlue);
            return;
        }
    }
    isChoose = 0;
}

class GiaoDien{
    private:
        sf::RenderWindow window(sf::VideoMode(8 * SIZE, 8 * SIZE), "Chess Board");
        sf::RectangleShape squares[8][8];
        int isChoose = 1;
        int choosed = 0;
        int chessChoose = 0;
        sf::Color blackColor(209, 139, 71);
        sf::Color whiteColor(255, 206, 158);
        sf::Color colorBlue(0, 0, 255);
        sf::Color colorRed(255, 0, 0);
}

int main()
{
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
    if (!texture[0].loadFromFile("rockB.png")) {}
    sprite[0] = sf::Sprite (texture[0]);
    sprite[0].setPosition(0, 0);
    if (!texture[1].loadFromFile("knightB.png")) {}
    sprite[1] = sf::Sprite(texture[1]);
    sprite[1].setPosition(100, 0);
    if (!texture[2].loadFromFile("bishopB.png")) {}
    sprite[2] = sf::Sprite(texture[2]);
    sprite[2].setPosition(200, 0);
    if (!texture[3].loadFromFile("queenB.png")) {}
    sprite[3] = sf::Sprite(texture[3]);
    sprite[3].setPosition(300, 0);
    if (!texture[4].loadFromFile("kingB.png")) {}
    sprite[4] = sf::Sprite(texture[4]);
    sprite[4].setPosition(400, 0);
    if (!texture[5].loadFromFile("bishopB.png")) {}
    sprite[5] = sf::Sprite(texture[5]);
    sprite[5].setPosition(500, 0);
    if (!texture[6].loadFromFile("knightB.png")) {}
    sprite[6] = sf::Sprite(texture[6]);
    sprite[6].setPosition(600, 0);
    if (!texture[7].loadFromFile("rockB.png")) {}
    sprite[7] = sf::Sprite(texture[7]);
    sprite[7].setPosition(700, 0);
    for(int i = 8; i < 16; i++){
        if (!texture[i].loadFromFile("pawnB.png")) {}
        sprite[i] = sf::Sprite(texture[i]);
        sprite[i].setPosition((i-8)*100, 100);
    }
    if (!texture[16].loadFromFile("rockA.png")) {}
    sprite[16] = sf::Sprite (texture[16]);
    sprite[16].setPosition(0, 700);
    if (!texture[17].loadFromFile("knightA.png")) {}
    sprite[17] = sf::Sprite(texture[17]);
    sprite[17].setPosition(100, 700);
    if (!texture[18].loadFromFile("bishopA.png")) {}
    sprite[18] = sf::Sprite(texture[18]);
    sprite[18].setPosition(200, 700);
    if (!texture[19].loadFromFile("queenA.png")) {}
    sprite[19] = sf::Sprite(texture[19]);
    sprite[19].setPosition(300, 700);
    if (!texture[20].loadFromFile("kingA.png")) {}
    sprite[20] = sf::Sprite(texture[20]);
    sprite[20].setPosition(400, 700);
    if (!texture[21].loadFromFile("bishopA.png")) {}
    sprite[21] = sf::Sprite(texture[21]);
    sprite[21].setPosition(500, 700);
    if (!texture[22].loadFromFile("knightA.png")) {}
    sprite[22] = sf::Sprite(texture[22]);
    sprite[22].setPosition(600, 700);
    if (!texture[23].loadFromFile("rockA.png")) {}
    sprite[23] = sf::Sprite(texture[23]);
    sprite[23].setPosition(700, 700);
    for(int i = 24; i < 32; i++){
        if (!texture[i].loadFromFile("pawnA.png")) {}
        sprite[i] = sf::Sprite(texture[i]);
        sprite[i].setPosition((i-24)*100, 600);
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
                    SelectChess(col, row, sprite, window, squares);
                    //cout << isChoose << choosed << endl;
                    if (isValidMove(isChoose, choosed, col, row, squares)) {
                        moveChess(sprite[chessChoose].getPosition().x, sprite[chessChoose].getPosition().y, col * SIZE, row * SIZE, sprite, window, squares);
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


