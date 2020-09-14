#include "physics.h"
#include <vector>
#include <string>
#include "Ball.cpp"
#include "Paddle.cpp"
#include "Brick.cpp"
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

int main()
{
    //Game Window
    int WindowWidth = 800;
    int WindowHeight = 600;
    RenderWindow window(VideoMode(WindowWidth,WindowHeight),"Brick Breaker");
    window.setFramerateLimit(60);
    b2World world(b2Vec2(0.0, 0.0));

    //Integer Variables
    int bw = WindowWidth/3;
    int bh = WindowHeight/6;
    int bx = 0;
    int by = 0;

    //Boolean Variables
    bool bmove = false;
    bool lvl1 = true;
    bool lvl2 = false;
    bool lvl3 = false;
    bool level1 = true;
    bool level2 = false;
    bool level3 = false;
    bool gameover = false;
    bool win = false;

    //Sounds
    SoundBuffer hitbuffer;
    if (!hitbuffer.loadFromFile("hit.flac"))
        return -1;
    Sound hit;
    hit.setBuffer(hitbuffer);

    SoundBuffer paddlebuffer;
    if (!paddlebuffer.loadFromFile("paddle.ogg"))
        return -1;
    Sound paddle;
    paddle.setBuffer(paddlebuffer);

    //Clock
    Clock clock;

    //Vectors
    vector<Brick> Bricks;

    //Font
    Font font;
    font.loadFromFile("arial.ttf");

    //Text
    Text FirstLevel;
    FirstLevel.setFont(font);
    FirstLevel.setString("Level 1");
    FirstLevel.setCharacterSize(200);
    FirstLevel.setFillColor(Color::Yellow);
    Text SecondLevel;
    SecondLevel.setFont(font);
    SecondLevel.setString("Level 2");
    SecondLevel.setCharacterSize(200);
    SecondLevel.setFillColor(Color(255,165,0,255));
    Text ThirdLevel;
    ThirdLevel.setFont(font);
    ThirdLevel.setString("Level 3");
    ThirdLevel.setCharacterSize(200);
    ThirdLevel.setFillColor(Color::Red);
    Text winText;
    winText.setFont(font);
    winText.setString("You Win!");
    winText.setCharacterSize(100);
    winText.setFillColor(Color::White);
    Text loseText;
    loseText.setFont(font);
    loseText.setString("Game Over!");
    loseText.setCharacterSize(100);
    loseText.setFillColor(Color::White);

    //Centering Text
    FloatRect CenterText1 = FirstLevel.getLocalBounds();
    FirstLevel.setOrigin(CenterText1.width/2,CenterText1.height/2);
    FirstLevel.setPosition(WindowWidth/2,WindowHeight/3);

    FloatRect CenterText2 = SecondLevel.getLocalBounds();
    SecondLevel.setOrigin(CenterText2.width/2,CenterText2.height/2);
    SecondLevel.setPosition(WindowWidth/2,WindowHeight/3);

    FloatRect CenterText3 = ThirdLevel.getLocalBounds();
    ThirdLevel.setOrigin(CenterText3.width/2,CenterText3.height/2);
    ThirdLevel.setPosition(WindowWidth/2,WindowHeight/3);

    FloatRect CenterTextWin = winText.getLocalBounds();
    winText.setOrigin(CenterTextWin.width/2,CenterTextWin.height/2);
    winText.setPosition(WindowWidth/2,WindowHeight/3);

    FloatRect CenterTextLose = loseText.getLocalBounds();
    loseText.setOrigin(CenterTextLose.width/2,CenterTextLose.height/2);
    loseText.setPosition(WindowWidth/2,WindowHeight/3);

    //Walls
    Block wallTop = physics::createBox(world,0,-10,800,10,b2_staticBody);
    Block wallRight = physics::createBox(world,800,0,10,600,b2_staticBody);
    Block wallLeft = physics::createBox(world,-10,0,10,600,b2_staticBody);

    //Ball
    Ball mainBall(world, 400, 400, 10, 300.0, 90.0);

    //Paddle
    Paddle mainPaddle(world, 325, 550, 150, 20);

    //Game Loop
    while (window.isOpen()&& !Keyboard::isKeyPressed(Keyboard::Escape))
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (!gameover && !win)
        {

            //Ball Paddle Collision
            mainBall.checkCollision(mainPaddle);
            if(mainBall.checkCollision(mainPaddle))
                paddle.play();

            //If Ball Hits the Bottom
            if (mainBall.getPosition().y > 610)
                gameover = true;

            //If Ball Hits the Walls
            if (physics::checkCollision(mainBall.body, wallLeft))
                hit.play();
            if (physics::checkCollision(mainBall.body, wallRight))
                hit.play();
            if (physics::checkCollision(mainBall.body, wallTop))
                hit.play();

            //Level 1 Bricks
            if (lvl1)
            {
                for (int n = 0; n < 9; n++)
                {
                    Bricks.push_back(Brick(world,bx,by,bw,bh));
                    if (bx < 2*(WindowWidth/3))
                    {
                        bx = bx + bw;
                    }
                    else
                    {
                        bx = 0;
                        bmove = true;
                    }
                    if (bx == 0 && bmove)
                        by = by + bh;
                    if (n == 8)
                        lvl1 = false;
                    if (rand() % 9 + 0 == 1)
                        Bricks[n].PowerUp1();
                }
            }

            //Level 2 Bricks
            if (lvl2)
            {
                for (int n = 0; n < 12; n++)
                {
                    Bricks.push_back(Brick(world,bx,by,bw,bh));
                    if (bx < 2*(WindowWidth/3))
                    {
                        bx = bx + bw;
                    }
                    else
                    {
                        bx = 0;
                        bmove = true;
                    }
                    if (bx == 0 && bmove)
                        by = by + bh;
                    if (n == 11)
                        lvl2 = false;
                    if (rand() % 12 + 0 == 1)
                        Bricks[n].PowerUp2();
                }
            }

            //Level 3 Bricks
            if (lvl3)
            {
                for (int n = 0; n < 15; n++)
                {
                    Bricks.push_back(Brick(world,bx,by,bw,bh));
                    if (bx < 2*(WindowWidth/3))
                    {
                        bx = bx + bw;
                    }
                    else
                    {
                        bx = 0;
                        bmove = true;
                    }
                    if (bx == 0 && bmove)
                        by = by + bh;
                    if (n == 14)
                        lvl3 = false;
                    if (rand() % 15 + 0 == 2)
                        Bricks[n].PowerUp3();
                }
            }

            //Level 1 Win
            if (Bricks.size() == 0 && level1)
            {
                level1 = false;
                level2 = true;
                lvl2 = true;
                bx = 0;
                by = 0;
                bw = WindowWidth/4;
                bh = WindowHeight/6;
                mainBall.speed = 300;
                mainPaddle.speed = 10;
                world.DestroyBody(mainBall.body);
                world.DestroyBody(mainPaddle.body);
                Paddle mainPaddle(world, 325, 550, 150, 20);
                Ball mainBall(world, 400, 400, 10, 300.0, 90.0);
                clock.restart();
            }

            //Level 2 Win
            else if (Bricks.size() == 0 && level2)
            {
                level2 = false;
                level3 = true;
                lvl3 = true;
                bx = 0;
                by = 0;
                bw = WindowWidth/5;
                bh = WindowHeight/6;
                mainBall.changeSize(0.1f);
                world.DestroyBody(mainBall.body);
                world.DestroyBody(mainPaddle.body);
                Paddle mainPaddle(world, 325, 550, 150, 20);
                Ball mainBall(world, 400, 400, 10, 300.0, 90.0);
                clock.restart();
            }

            //Level 3 Win
            else if (Bricks.size() == 0 && level3)
            {
                level3 = false;
                win = true;
            }

            //Drawing Objects
            window.clear();
            world.Step(1.0/60, int32(8), int32(3));
            mainBall.updatePosition(window);
            mainPaddle.updatePosition(window);
            for (int n = 0; n < Bricks.size(); n++)
                Bricks[n].updatePosition(window);

            //Ball Brick Collision
            for (int n = 0; n < Bricks.size(); n++)
            {
                if (mainBall.checkCollision(Bricks[n]))
                {
                    if (Bricks[n].getFillColor() == Color::Cyan)
                    {
                        mainBall.speed = 600;
                        mainPaddle.speed = 20;
                    }
                    if (Bricks[n].getFillColor() == Color::Magenta)
                        mainBall.changeSize(3);
                    if (Bricks[n].getFillColor() == Color::Green)
                        mainPaddle.changeSize(1.5);
                    world.DestroyBody(Bricks[n].body);
                    Bricks.erase(Bricks.begin() + n);
                    hit.play();
                }
            }

            //Text Draw
            if (level1 && clock.getElapsedTime().asSeconds() < 2)
                window.draw(FirstLevel);
            if (level2 && clock.getElapsedTime().asSeconds() < 2)
                window.draw(SecondLevel);
            if (level3 && clock.getElapsedTime().asSeconds() < 2)
                window.draw(ThirdLevel);

            window.display();

        }

        //Win Screen
        else if (win)
        {
            window.clear();
            window.draw(winText);
            window.display();
        }

        //Game Over Screen
        else if (gameover)
        {
            window.clear();
            window.draw(loseText);
            window.display();
        }
    }

    return 0;
}
