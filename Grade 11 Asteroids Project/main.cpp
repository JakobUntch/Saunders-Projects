#include <SFML/Graphics.hpp> //includes SFML libraries
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <string>

using namespace std;
using namespace sf; //for graphics

int main()
{
    RenderWindow window(VideoMode(800,600),"SFML Works");  //creates a window on the screen that is 800 by 600
    window.setFramerateLimit(60); //sets the game loop to run 60 times per second

    Texture t1; //Spaceship texture
    t1.loadFromFile("spaceship.png");
    Texture backg;//Background texture
    backg.loadFromFile("background.jpg");
    Sprite p1;//Spaceship sprite
    p1.setTexture(t1);
    RectangleShape bg;//Background shape
    bg.setTexture(&backg);
    Texture a1;//Asteroid texture
    a1.loadFromFile("rock.png");
    Texture bt1;//Bullet texture
    bt1.loadFromFile("fire_blue.png");
    Texture explosion;//Explosion texture
    explosion.loadFromFile("ex1.png");

    Font font;
    font.loadFromFile("whitrabt.ttf");//Font for start screen and game over screen
    Text start ("ASTEROIDS",font,64);//Title
    start.setPosition(245,150);
    Text click ("PRESS SPACE TO START",font,32);//How to begin game
    click.setPosition(220,300);
    Text health ("HEALTH: 3",font,24);//Health bar
    health.setPosition(25,550);
    Text point ("POINTS: 0",font,24);//Points bar
    point.setPosition(650,550);
    Text gameover ("GAME OVER",font,64);//Game over screen
    gameover.setPosition(250,250);

    bg.setOrigin(400,300);
    bg.setSize(Vector2f(800,600));
    bg.setPosition(400,300);
    p1.setTextureRect(IntRect(0,0,39,40));
    p1.setOrigin(15,15);
    p1.setPosition(400,300);
    p1.setScale(1.5,1.5);

    Clock clock;//Clock for shooting speed
    Clock clock2;//Clock for asteroid spawning speed

    Music menu;//Music for title screen
    menu.openFromFile("menu.wav");
    Music m1;//Music for main game
    m1.openFromFile("main.ogg");
    Music die;//Music for game over screen
    die.openFromFile("die.wav");
    Music lr;//Music for laser firing
    lr.openFromFile("laser.wav");
    Music hit;//Music for getting hit
    hit.openFromFile("hit.wav");

    vector<Sprite> b1;//Bullet
    vector<Vector2f> b1_angle;//Bullet angle
    vector<Clock> c1;//Clock for bullet speed
    vector<CircleShape> ast;//Asteroid
    vector<Sprite> ex;//Explosion
    vector<string> spawnSide;//Spawn side of asteroids
    vector<Clock> exp;//How long the explosion is on the screen
    float delta;//Holds the time used for bullet speed
    float speed = 2000;//Speed of bullet
    float rad = 3.1459 / 180;//Used to convert degrees into radicals
    float xpos;//Used to set bullet position to ship position
    float ypos;//Used to set bullet position to ship position
    float astt = 1;//Asteroid spawing rate
    int y1 = 40;//Spaceship texture rect position 1
    int y2 = 0;//Spaceship texture rect position 2
    int x1 = 0;//Asteroids texture rect position
    int rn = 0;//Holds a random number
    int life = 3;//Life of spaceship
    int score = 0;//Tracks how many asteroids were killed
    int sp =  4;//Speed of asteroids
    bool a = false;//Controls which screen is shown
    bool r = true;//Used for main music
    bool s = true;//Used for menu music
    bool t = true;//Used for game over music

    while (window.isOpen()&& !Keyboard::isKeyPressed(Keyboard::Escape))     //the main game loop, exits if someone closes the window
    {
        Event event; //creates an event object, events include mouse clicks, mouse movement, keyboard presses, etc..
        while (window.pollEvent(event)) //loop that checks for events
        {
            if (event.type == Event::Closed) //checks if window is closed
                window.close();
        }   //ends the event loop
        if (!a)
        {
            if (s) //Plays menu music
            {
                menu.play();
                menu.setLoop(true);
                s = false;
            }
            if (Keyboard::isKeyPressed(Keyboard::Space)) //Starts game if space is pressed
            {
                a = true;
            }
            window.clear();
            window.draw(bg);//Background
            window.draw(start);//Start Text
            window.draw(click);//Start Game Text
            window.display();
        }

        else if (a == true && life > 0)
        {
            if (r) //Plays main music
            {
                menu.stop();
                m1.play();
                m1.setLoop(true);
                r = false;
            }
            health.setString("HEALTH: " + to_string(life));//Health Bar
            point.setString("POINTS: " + to_string(score));//Points Bar
            p1.setTextureRect(IntRect(0,y2,39,y1));//Ship Texture Rect
            y1 = 40;//Default Ship Rect Y1
            y2 = 0;//Default Ship Rect Y1
            if (p1.getPosition().x >= 785) //Stops the ship from going off the edge
            {
                p1.setPosition(784,p1.getPosition().y);
            }
            if (p1.getPosition().x <= 15)
            {
                p1.setPosition(16,p1.getPosition().y);
            }
            if (p1.getPosition().y >= 585)
            {
                p1.setPosition(p1.getPosition().x,584);
            }
            if (p1.getPosition().y <= 15)
            {
                p1.setPosition(p1.getPosition().x,16);
            }
            if (Keyboard::isKeyPressed(Keyboard::W)) //Moves ship up
            {
                p1.move(0,-7);
                y1 = 42;
                y2 = 40;
            }
            if (Keyboard::isKeyPressed(Keyboard::S)) //Moves ship down
            {
                p1.move(0,7);
                y1 = 42;
                y2 = 40;
            }
            if (Keyboard::isKeyPressed(Keyboard::A)) //Moves ship left
            {
                p1.move(-7,0);
                y1 = 42;
                y2 = 40;
            }
            if (Keyboard::isKeyPressed(Keyboard::D)) //Moves ship right
            {
                p1.move(7,0);
                y1 = 42;
                y2 = 40;
            }
            if (Keyboard::isKeyPressed(Keyboard::Left)) //Rotates ship counter-clockwise
            {
                p1.rotate(-6);
                y1 = 42;
                y2 = 40;
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)) //Rotates ship clockwise
            {
                p1.rotate(6);
                y1 = 42;
                y2 = 40;
            }
            if (clock2.getElapsedTime().asSeconds() > astt) //Spawns an asteroid every astt seconds
            {
                clock2.restart();
                ast.push_back(CircleShape());
                ast.back().setRadius(32);
                ast.back().setScale(1.5,1.5);
                ast.back().setTexture(&a1);
                rn = rand() % 4 + 1;//Makes the asteroid spawn on a random side
                if (rn == 1)
                {
                    ast.back().setPosition(0, rand() % 601);
                    spawnSide.push_back("left");
                }
                else if (rn == 2)
                {
                    ast.back().setPosition(736, rand() % 601);
                    spawnSide.push_back("right");
                }
                else if (rn == 3)
                {
                    ast.back().setPosition(rand() % 801, 0);
                    spawnSide.push_back("top");
                }
                else if (rn == 4)
                {
                    ast.back().setPosition(rand() % 801, 536);
                    spawnSide.push_back("bot");
                }

            }
            if (x1 != 960) //Changes the x position for the asteroid texture rect
            {
                x1 = x1 + 64;
            }
            else
            {
                x1 = 0;//Sets the x back to the start when it reaches the end
            }

            for (int i = 0; i < ast.size(); i++)
            {
                if (spawnSide[i] == "left")
                {
                    ast[i].move(sp, 0);
                }
                else if (spawnSide[i] == "right")
                {
                    ast[i].move(sp * -1, 0);

                }
                else if (spawnSide[i] == "top")
                {
                    ast[i].move(0, sp);
                }
                else if (spawnSide[i] == "bot")
                {
                    ast[i].move(0, sp * -1);
                }
            }
            for (int i = 0; i < ast.size(); i++)
            {
                if (ast[i].getGlobalBounds().intersects(p1.getGlobalBounds())) //Checks if the ship hits the asteroid
                {
                    hit.play();
                    ast.erase(ast.begin() + i);
                    spawnSide.erase(spawnSide.begin() + i);
                    life--;//Takes away one life
                }
                if (ast[i].getPosition().x > 864 || ast[i].getPosition().x < -64 || ast[i].getPosition().y > 664 || ast[i].getPosition().y < -64) //Despawns the asteroid if it reaches the edge of the screen
                {
                    ast.erase(ast.begin() + i);
                    spawnSide.erase(spawnSide.begin() + i);
                }
                for (int a = 0; a < b1.size(); a++)
                {
                    if (ast[i].getGlobalBounds().intersects(b1[a].getGlobalBounds()))  //Checks to see if the bullet has touched an asteroid
                    {
                        score++;
                        ex.push_back(Sprite());//Spawns an explosion where the asteroid was hit
                        ex.back().setPosition(ast[i].getPosition().x,ast[i].getPosition().y);
                        ex.back().setTexture(explosion);
                        ex.back().setScale(1.5,1.5);
                        exp.push_back(Clock());
                        b1.erase(b1.begin() + a);
                        b1_angle.erase(b1_angle.begin() +i );
                        c1.erase(c1.begin() + i);
                        ast.erase(ast.begin() + i);
                        spawnSide.erase(spawnSide.begin() + i);
                        if (score % 10 == 1) //Increases the asteroid speed everytime the player gets 10 points
                        {
                            if (score != 1)
                            {
                                sp++;
                            }
                        }
                        if (score % 20 == 1) //Increases the spawnrate of the asteroids every 20 points
                        {
                            if (score != 1 && astt > 0.4)
                            {
                                astt = astt - 0.1;
                            }
                        }
                        if (score % 30 == 1) //Gives the player an extra life every 30 points
                        {
                            if (score != 1)
                            {
                                life++;
                            }
                        }
                    }
                    if (b1[a].getPosition().x > 800 || b1[a].getPosition().x < 0 || b1[a].getPosition().y > 600 || b1[a].getPosition().y < 0) //Deletes the bullet after it reaches the edge of the screen
                    {
                        b1.erase(b1.begin() + a);
                        b1_angle.erase(b1_angle.begin() + i);
                        c1.erase(c1.begin() + i);
                    }
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Space)&&clock.getElapsedTime().asSeconds() > 0.3) //Shoots a bullet everytime space is pressed
            {
                clock.restart();
                lr.play();
                b1.push_back(Sprite());
                b1.back().setPosition(p1.getPosition());
                b1.back().setTexture(bt1);
                b1.back().setRotation(p1.getRotation());
                c1.push_back(Clock());
                b1_angle.push_back(Vector2f(sin(p1.getRotation()*rad),-cos(p1.getRotation()*rad)));
            }
            for (int i = 0; i < b1.size(); i++) //Moves the bullet
            {
                delta = c1[i].getElapsedTime().asSeconds();
                Vector2f dis(b1_angle[i]*speed*delta);
                b1[i].move(dis);
                c1[i].restart();
            }
            window.clear(); //clears the screen
            window.draw(bg);
            window.draw(p1); //draws the circle to the video card
            window.draw(health);
            window.draw(point);
            for (int i = 0; i < b1.size(); i++) //Background
            {
                window.draw(b1[i]);
            }
            for (int i = 0; i < ast.size(); i++) //Asteroid
            {
                ast[i].setTextureRect(IntRect(x1,0,64,64));
                window.draw(ast[i]);
            }
            for (int i = 0; i < ex.size(); i++) //Explosion
            {
                window.draw(ex[i]);
                if (exp[i].getElapsedTime().asSeconds() > 0.5) //Deletes the sprite after 0.5 seconds
                {
                    exp.erase(exp.begin() + i);
                    ex.erase(ex.begin() + i);
                }
            }
            window.display();   //displays everything on the video card to the monitor
        }   //ends the game loop
        else if (life == 0) //Game over screen
        {
            window.clear();
            window.draw(bg);
            window.draw(gameover);
            window.display();
            if (t) //Plays the game over music
            {
                m1.stop();
                die.play();
                die.setLoop(true);
                t = false;
            }
        }
    }
    return 0;
}
