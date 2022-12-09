#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace std;
using namespace sf;



int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(750, 375), "Arkanoid on C++");
    app.setFramerateLimit(60);

    Texture t1,t2,t3,t4,t5,t6;
    t1.loadFromFile("images/block01.png");
    t2.loadFromFile("images/space_bg.jpg");
    t3.loadFromFile("images/ball.png");
    t4.loadFromFile("images/paddle.png");
    t5.loadFromFile("images/block02.png");
    t6.loadFromFile("images/block03.png");

    bool isgameover = false;

    Sprite sBackground(t2), sBall(t3), sPaddle(t4);
    sPaddle.setPosition(315,365);

    int s = 0, hs = 0;

    Font font;
    font.loadFromFile("SummerPixel22Regular-jE0W7.ttf");
    Text gameover("", font, 60);
    gameover.setFillColor(Color::Red);
    Text score("", font, 25);
    score.setFillColor(Color::Magenta);
    score.setPosition(5, 0);
    Text highscore("", font, 25);
    highscore.setFillColor(Color::Magenta);
    highscore.setPosition(620, 0);

    Sprite block[1000];

    int blockhealth[100];

    int n=0;
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            if (j < 3) {
                block[n].setTexture(t5);
                blockhealth[n] = 5;
            }
            else if (j >= 3 && j < 6) {
                block[n].setTexture(t6);
                blockhealth[n] = 3;
            }
            else {
                block[n].setTexture(t1);
                blockhealth[n] = 1;
            }
            block[n].setPosition(i * 43 + 110, j * 20);
            n++;
        }
    }

    float dx=6, dy=5;
    float x=300, y=300;

    while (app.isOpen())
    {
        if (Keyboard::isKeyPressed(Keyboard::Q)) app.close();

        string txts = "Score:\n" + to_string(s);
        Text score(txts, font, 25);
        score.setFillColor(Color::Magenta);
        score.setPosition(5, 0);
        if (s > hs) {
            hs = s;
        }
        string txths = "High score:\n" + to_string(hs);
        Text highscore(txths, font, 25);
        highscore.setFillColor(Color::Magenta);
        highscore.setPosition(620, 0);

        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed) {
                app.close();
            }
        }

        x += dx;
        for (int i = 0; i < n; i++) {
            if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds())) {
                blockhealth[i]--;
                if (blockhealth[i] == 0) {
                    block[i].setPosition(-100, 0);
                }
                else if (blockhealth[i] == 1) {
                    block[i].setTexture(t1);
                }
                else if (blockhealth[i] == 3) {
                    block[i].setTexture(t6);
                }
                dx = -dx;
                s++;
            }
        }
        y += dy;
        for (int i = 0; i < n; i++) {
            if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds())) {
                blockhealth[i]--;
                if (blockhealth[i] == 0) {
                    block[i].setPosition(-100, 0);
                }
                else if (blockhealth[i] == 1) {
                    block[i].setTexture(t1);
                }
                else if (blockhealth[i] == 3) {
                    block[i].setTexture(t6);
                }
                dy = -dy;
                s++;
            }
        }
        if (x < 0 || x > 738) {
            dx = -dx;
        }

        bool paddleblock = false;

        if (s == 240) {
            gameover.setString("      You've Won!\nPress Enter to start again");
            gameover.setPosition(15, 112);
            dx = 0;
            dy = 0;
            paddleblock = true;
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                dx = 6;
                dy = 5;
                x = 300;
                y = 300;
                s = 0;
                paddleblock = false;
                n = 0;
                for (int i = 1; i <= 10; i++) {
                    for (int j = 1; j <= 10; j++) {
                        if (j < 3) {
                            block[n].setTexture(t5);
                            blockhealth[n] = 5;
                        }
                        else if (j >= 3 && j < 6) {
                            block[n].setTexture(t6);
                            blockhealth[n] = 3;
                        }
                        else {
                            block[n].setTexture(t1);
                            blockhealth[n] = 1;
                        }
                        block[n].setPosition(i * 43 + 110, j * 20);
                        n++;
                    }
                }
                sPaddle.setPosition(315, 365);
                gameover.setPosition(250, 500);
            }
        }

        if (y > 363) {
            gameover.setString("        Game Over\nPress Enter to start again");
            gameover.setPosition(15, 112);
            dx = 0;
            dy = 0;
            paddleblock = true;
            if (Keyboard::isKeyPressed(Keyboard::Enter)) { 
                dx = 6;
                dy = 5;
                x = 300;
                y = 300;
                s = 0;
                paddleblock = false;
                n = 0;
                for (int i = 1; i <= 10; i++) {
                    for (int j = 1; j <= 10; j++) {
                        if (j < 3) {
                            block[n].setTexture(t5);
                            blockhealth[n] = 5;
                        }
                        else if (j >= 3 && j < 6) {
                            block[n].setTexture(t6);
                            blockhealth[n] = 3;
                        }
                        else {
                            block[n].setTexture(t1);
                            blockhealth[n] = 1;
                        }
                        block[n].setPosition(i * 43 + 110, j * 20);
                        n++;
                    }
                }
                sPaddle.setPosition(315, 365);
                gameover.setPosition(250, 500);
            }
        }

        else if (y < 6) {
            dy = -dy;
        }

        if (not(paddleblock)) {
            if (sPaddle.getPosition().x >= 0) {
                if (Keyboard::isKeyPressed(Keyboard::Left)) sPaddle.move(-6, 0);
                if (Keyboard::isKeyPressed(Keyboard::LShift)) sPaddle.move(-12, 0);
            }
            if (sPaddle.getPosition().x <= 696) {
                if (Keyboard::isKeyPressed(Keyboard::Right)) sPaddle.move(6, 0);
                if (Keyboard::isKeyPressed(Keyboard::RShift)) sPaddle.move(12, 0);
            }
        }

        if (FloatRect(x, y, 12, 12).intersects(sPaddle.getGlobalBounds()) && not(paddleblock)) {
            dy = -(rand() % 5 + 2);
        }

        sBall.setPosition(x, y);

        app.clear();
        app.draw(sBackground);
        app.draw(sBall);
        app.draw(sPaddle);
        for (int i = 0; i < n; i++) {
            app.draw(block[i]);
            app.draw(gameover);
            app.draw(score);
            app.draw(highscore);
        }

        app.display();
    }

  return 0;
}