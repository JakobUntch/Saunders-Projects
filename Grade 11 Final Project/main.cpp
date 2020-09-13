#include <SFML/Graphics.hpp> //includes SFML libraries
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;
using namespace sf; //for graphics

//Floats
float x = 100;
float y = 425;//
float vx = 0;//float for velocity of character x
float vy = 0;//float for velocity of character y
float g = 2;//float for gravity
float fy = 175;//float for jump height
float posy = 425;//float for y position of character
float speed = 15;//float for bullet speed
//Ints
int vtx = 32;//int for character running animation
int vtx2 = 256;//int for character jumping animation
int bgx = 0;//int for background animation
int py = 500;//int for platform y position
int life = 6;//int for life points
int dpos = -450;//int for first platform deletion point
int points = 0;//int for score
int healthx = 0;//int for health texturerect
int ex1 = 252;//int for enemy animation
//Bools
bool jumping = false;//bool for character jumping
bool shooting = false;//bool for character shooting
bool start = false;//bool for start screen
bool control = false;//bool for control screen
bool falling = false;//bool for character falling
bool on = false;//bool for being on the platform
bool fp = true;//bool for first platform
bool top = false;//bool for platform position tracking
bool inv = false;//bool for invincibility
bool grav = false;//bool for gravity
bool bot = false;//bool for platform position tracking
bool about = false;//bool for about screen
bool winm = true;//bool for win music
bool startm = true;//bool for start music
bool themem = true;//bool for game
bool gamem = true;//bool for game over music
//Vectors
vector<Sprite> b1;//Sprite vector for bullet
vector<int> bx;//int vector for bullet direction
vector<RectangleShape> plat;//Rectangle Shape vector for platform
vector<RectangleShape> enemy1;//Rectangle Shape vector for enemy
vector<RectangleShape> fireball;//Rectangle Shape vector for fireball
vector<Clock> firespeed;//Clock vector for fireball speed
vector<Vector2u> firedirect;//Vector for fireball direction
vector<float> angle;//float vector for fireball launch angle
vector<Clock> invincible;//clock vector for character invincibility timing
//Clocks
Clock clock1;//clock for shooting
Clock clock2;//clock for character animation
Clock clock3;//clock for menu screen
Clock clock4;//clock for platform and enemy
Clock clock5;//clock for background animation
Clock clock6;//clock for character falling
Clock clock7;//clock for enemy animation

//Functions
void Jump()//Function for making the character jump
{
    if(fy > posy || falling)
    {
        vy += g;
    }
    y += vy;
}
void Fall()//Function for making the character fall
{
    if (!jumping && clock6.getElapsedTime().asSeconds() > 0.05)
    {
        vy += g;
        clock6.restart();
    }
    y += vy;
}
void Move()//function for making the character move
{
    x += vx;
}

int main()
{
    RenderWindow window(VideoMode(800,600),"SFML Works");  //creates a window on the screen that is 800 by 600
    window.setFramerateLimit(60); //sets the game loop to run 60 times per second

    //Font
    Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    //Textures
    Texture pt;//Platform
    pt.loadFromFile("plat.png");
    Texture bg;//Background
    bg.loadFromFile("backg3.png");
    Texture player;//Character
    player.loadFromFile("vwalk1.png");
    Texture laser;//Bullet
    laser.loadFromFile("laser.png");
    Texture startscreen;//Start Screen
    startscreen.loadFromFile("start.png");
    Texture logo;//Game logo
    logo.loadFromFile("logo.png");
    Texture duck;//Enemy
    duck.loadFromFile("enemy.png");
    Texture gameover;//Game over text
    gameover.loadFromFile("gameover.png");
    Texture winner;//Win screen logo
    winner.loadFromFile("win.jpg");
    Texture h;//Health HUD
    h.loadFromFile("health.png");
    Texture fb;//Fireball
    fb.loadFromFile("fireball.png");

    //Text
    Text st1("Start",font,32);
    st1.setPosition(365,480);
    Text st2("Controls",font,32);
    st2.setPosition(90,480);
    Text st3("About",font,32);
    st3.setPosition(610,480);
    Text gameovertext("Restart",font,32);
    gameovertext.setPosition(350,480);
    Text score("0",font,32);
    score.setPosition(Vector2f(140,0));
    Text controls("Jump - W \nSpace - Shoot \nEnter - Select \nBackspace - Back",font,96);
    controls.setPosition(15,50);
    Text abouttext("Made by: Jakob Untch \nGrade 11 Computer ISP \nClass: Mr. Vriesinga",font,64);
    abouttext.setPosition(15,50);

    //Shapes
    RectangleShape backg;//Game background
    RectangleShape p1;//Player
    RectangleShape ss;//Start Screen
    RectangleShape button1;//Start button
    RectangleShape button2;//Control button
    RectangleShape button3;//About button
    RectangleShape lg;//Logo for game
    RectangleShape hl;//Highlight for buttons
    RectangleShape platform;//Starting platform
    RectangleShape gm;//Game over text
    RectangleShape gmbutton;//Game over restart button
    RectangleShape h2;//Highlight for game over button
    RectangleShape health;//Health bar HUD
    RectangleShape win;//Win screen logo

    //Shape Positions
    backg.setTexture(&bg);
    backg.setSize(Vector2f(800,600));
    backg.setTextureRect(IntRect(0,0,300,300));
    backg.setPosition(0,0);
    p1.setSize(Vector2f(128,128));
    p1.setPosition(Vector2f(100,500));
    p1.setTexture(&player);
    p1.setOrigin(64,64);
    p1.setTextureRect(IntRect(0,0,32,32));
    p1.setScale(-1.f, 1.f);
    ss.setTexture(&startscreen);
    ss.setSize(Vector2f(800,600));
    button1.setSize(Vector2f(200,100));
    button1.setOrigin(100,50);
    button1.setFillColor(Color(211,211,211));
    button1.setPosition(400,500);
    button2.setSize(Vector2f(200,100));
    button2.setOrigin(100,50);
    button2.setFillColor(Color(211,211,211));
    button2.setPosition(150,500);
    button3.setSize(Vector2f(200,100));
    button3.setOrigin(100,50);
    button3.setFillColor(Color(211,211,211));
    button3.setPosition(650,500);
    lg.setTexture(&logo);
    lg.setSize(Vector2f(600,200));
    lg.setOrigin(300,100);
    lg.setPosition(400,175);
    hl.setFillColor(Color::Yellow);
    hl.setSize(Vector2f(220,120));
    hl.setOrigin(110,60);
    hl.setPosition(400,500);
    platform.setTexture(&pt);
    platform.setSize(Vector2f(600,50));
    platform.setOrigin(300,25);
    platform.setPosition(300,500);
    gm.setTexture(&gameover);
    gm.setSize(Vector2f(400,400));
    gm.setOrigin(200,200);
    gm.setPosition(400,200);
    gmbutton.setSize(Vector2f(300,100));
    gmbutton.setOrigin(150,50);
    gmbutton.setFillColor(Color(211,211,211));
    gmbutton.setPosition(400,500);
    h2.setFillColor(Color::Yellow);
    h2.setSize(Vector2f(320,120));
    h2.setOrigin(160,60);
    h2.setPosition(400,500);
    health.setSize(Vector2f(124,40));
    health.setOrigin(64,20);
    health.setPosition(64,20);
    health.setTexture(&h);
    health.setTextureRect(IntRect(0,0,124,40));
    win.setTexture(&winner);
    win.setSize(Vector2f(800,600));
    win.setOrigin(400,300);
    win.setPosition(400,300);

    //Music
    Music lr;//Music for laser firing
    lr.openFromFile("laser.ogg");
    Music jump;
    jump.openFromFile("jump.ogg");
    Music quack;
    quack.openFromFile("quack.ogg");
    Music winmusic;
    winmusic.openFromFile("win.ogg");
    Music ssm;
    ssm.openFromFile("start.ogg");
    Music thememusic;
    thememusic.openFromFile("theme.ogg");
    Music gameoverm;
    gameoverm.openFromFile("gameover.ogg");

    while (window.isOpen()&& !Keyboard::isKeyPressed(Keyboard::Escape))     //the main game loop, exits if someone closes the window
    {
        Event event; //creates an event object, events include mouse clicks, mouse movement, keyboard presses, etc..
        while (window.pollEvent(event)) //loop that checks for events
        {
            if (event.type == Event::Closed) //checks if window is closed
                window.close();
        }   //ends the event loop

        //Start Screen
        if (!start && !control && !about)
        {
            if (startm)
            {
                ssm.play();
                ssm.setLoop(true);
                startm = false;
            }
            //Moves highlight onto buttons
            if (Keyboard::isKeyPressed(Keyboard::D) && hl.getPosition().x != 650 && clock3.getElapsedTime().asSeconds() > 0.2)
            {
                hl.move(250,0);
                clock3.restart();
            }
            else if (Keyboard::isKeyPressed(Keyboard::A) && hl.getPosition().x != 150 && clock3.getElapsedTime().asSeconds() > 0.2)
            {
                hl.move(-250,0);
                clock3.restart();
            }
            //Checks if button was pressed
            if (Keyboard::isKeyPressed(Keyboard::Return) && hl.getPosition().x == 650)
            {
                about = true;
            }
            if (Keyboard::isKeyPressed(Keyboard::Return) && hl.getPosition().x == 400)
            {
                start = true;
            }
            else if (Keyboard::isKeyPressed(Keyboard::Return) && hl.getPosition().x == 150 && !control)
            {
                control = true;
            }
            //Drawings
            window.clear();
            window.draw(ss);
            window.draw(hl);
            window.draw(button1);
            window.draw(button2);
            window.draw(button3);
            window.draw(st1);
            window.draw(st2);
            window.draw(st3);
            window.draw(lg);
            window.display();
        }

        //Control Screen
        else if (!start && !about && control)
        {
            if (Keyboard::isKeyPressed(Keyboard::BackSpace))
            {
                control = false;
            }
            window.clear();
            window.draw(ss);
            window.draw(controls);
            window.display();
        }

        //About Screen
        else if (!start && !control && about)
        {
            if (Keyboard::isKeyPressed(Keyboard::BackSpace))
            {
                about = false;
            }
            window.clear();
            window.draw(ss);
            window.draw(abouttext);
            window.display();
        }

        //Game Code
        else if (start && life > 0 && points < 20)
        {
            ssm.stop();
            if (themem)
            {
                thememusic.play();
                thememusic.setLoop(true);
                themem = false;
            }
            if (!gamem)
            {
                gameoverm.stop();
                gamem = true;
            }
            score.setString(to_string(points));//Points for HUD
            health.setTextureRect(IntRect(healthx,0,124,40));//Switches amount of hearts on health HUD
            if (clock7.getElapsedTime().asSeconds() > 0.1)//Animation for enemy
            {
                ex1 += 252;
                clock7.restart();
            }
            if (ex1 >= 756)
            {
                ex1 = 252;
            }
            if (clock2.getElapsedTime().asMilliseconds() > 100)//Animates player
            {
                vtx2 = vtx2 + 32;//Running animation
                vtx = vtx + 32;//Shooting while running animation
                clock2.restart();
            }
            if (vtx == 160)
            {
                vtx = 32;
            }
            if (vtx2 == 320)
            {
                vtx2 = 256;
            }
            if (shooting)//Tracks if player is shooting
            {
                p1.setTextureRect(IntRect(vtx2,0,32,32));
            }
            else if (!shooting)
            {
                p1.setTextureRect(IntRect(vtx,0,32,32));
            }
            if (fp)//Beginning platform
            {
                platform.move(-10,0);
            }
            if (platform.getPosition().x < dpos && fp)//Deletes platform after player has left it
            {
                fp = false;
            }
            if (!p1.getGlobalBounds().intersects(platform.getGlobalBounds()) && fp && !jumping && p1.getPosition().x > platform.getPosition().x)//Makes them fall off if they have not jumped
            {
                jumping = true;
                falling = true;
            }
            backg.setTextureRect(IntRect(bgx,0,300,300));//Animates background
            if (clock5.getElapsedTime().asSeconds() > 0.1)//Animation for background
            {
                bgx = bgx + 300;
                clock5.restart();
            }
            if (bgx >= 1200)
            {
                bgx = 0;
            }
            vx = 0;//Movement defaults at 0
            posy = p1.getPosition().y;//Sets variable to players y position
            if (Keyboard::isKeyPressed(Keyboard::W) && jumping == false)//Jumping button for character
            {
                jump.play();//Plays jumping sound effect
                on = false;//Player is now off the platform
                jumping = true;//Player is now jumping
                vy = -20;//Makes the player move up into the air
            }
            if (jumping && !shooting)//Checks if the player is jumping and shooting, then sets texture accordingly
            {
                p1.setTextureRect(IntRect(160,0,32,32));
            }
            else if (jumping && shooting)
            {
                p1.setTextureRect(IntRect(192,0,32,32));
            }
            Move();//Move function
            if (jumping)//Jump function
            {
                Jump();
            }
            if (Keyboard::isKeyPressed(Keyboard::Space) && clock1.getElapsedTime().asSeconds() > 0.3)//Shooting button
            {
                clock1.restart();
                lr.play();//Plays laser sound
                shooting = true;//Player is now shooting
                b1.push_back(Sprite());//Bullet sprite
                b1.back().setTexture(laser);
                b1.back().setOrigin(300,100);
                b1.back().setScale(0.2,0.2);
                b1.back().setPosition(p1.getPosition().x + 64, p1.getPosition().y);
                bx.push_back(45);//Bullet direction
            }
            if (clock1.getElapsedTime().asSeconds() > 0.3)//Shooting speed
            {
                shooting = false;
            }
            for (int i = 0; i < b1.size(); i++)//Bullet movement
            {
                b1[i].move(bx[i],0);
            }

            for (int i = 0; i < b1.size(); i++)//Deletes bullet
            {
                if (b1[i].getPosition().x > 800)
                {
                    b1.erase(b1.begin() + i);
                    bx.erase(bx.begin() + i);
                }
            }
            if (clock4.getElapsedTime().asSeconds() > 1)//Spawns platform
            {
                clock4.restart();
                plat.push_back(RectangleShape());//Platform Shape
                plat.back().setTexture(&pt);
                plat.back().setSize(Vector2f(300,50));
                plat.back().setOrigin(150,25);
                plat.back().setPosition(1100,py);
                enemy1.push_back(RectangleShape());//Enemy Shape
                enemy1.back().setTexture(&duck);
                enemy1.back().setSize(Vector2f(76,112));
                enemy1.back().scale(-1.f,1.f);
                enemy1.back().setOrigin(38,56);
                enemy1.back().setPosition(1200,py-76);
                firespeed.push_back(Clock());//Fireball Speed
                if (py == 240)//Sets the position of the next platform
                {
                    py = 370;
                }
                else if (py == 370 && top)
                {
                    py = 500;
                    top = false;
                }
                else if (py == 370 && !top)
                {
                    py = 240;
                    top = true;
                }
                else if (py == 500)
                {
                    py = 370;
                }
            }
            for (int i = 0; i < plat.size(); i++)//Makes the platform move
            {
                plat[i].move(-9.5,0);
                if (plat[i].getPosition().x < -300)
                {
                    plat.erase(plat.begin() + i);
                }
            }
            for (int i = 0; i < enemy1.size(); i++)//Makes the enemy move
            {
                enemy1[i].move(-10,0);
                if (enemy1[i].getPosition().x < -50)
                {
                    enemy1.erase(enemy1.begin() + i);
                }
            }
            for (int i = 0; i < enemy1.size(); i++)//Enemy texture animation
            {
                enemy1[i].setTextureRect(IntRect(ex1,0,252,288));
            }
            p1.setPosition(x,y);//Sets position of player
            for (int i = 0; i < plat.size(); i++)//Tracks if the player is on or off the platform
            {
                if (p1.getGlobalBounds().intersects(plat[i].getGlobalBounds()) && p1.getPosition().y > plat[i].getPosition().y && !on)
                {
                    jumping = false;
                    falling = false;
                    grav = true;
                    bot = true;
                }
                else if (bot && p1.getPosition().y < plat[i].getPosition().y - 300 && !p1.getGlobalBounds().intersects(plat[i].getGlobalBounds()))
                {
                    bot = false;
                }
                else if (p1.getGlobalBounds().intersects(plat[i].getGlobalBounds()) && !bot && p1.getPosition().y < plat[i].getPosition().y && !on)
                {
                    p1.setPosition(p1.getPosition().x,plat[i].getPosition().y - 75);
                    jumping = false;
                    on = true;
                    falling = false;
                    grav = false;
                    fy = p1.getPosition().y - 250;
                }
                else if (!p1.getGlobalBounds().intersects(plat[i].getGlobalBounds()) && !bot && on && !jumping && p1.getPosition().x > plat[i].getPosition().x + 150)
                {
                    jumping = false;
                    on = false;
                    falling = false;
                    grav = true;
                }
            }
            if (grav && !jumping)//Falling function
            {
                Fall();
            }
            for (int i = 0; i < b1.size(); i++)//Checks if the bullet hits the enemy
            {
                for (int a = 0; a < enemy1.size(); a++)
                {
                    if (b1[i].getGlobalBounds().intersects(enemy1[a].getGlobalBounds()))
                    {
                        quack.play();
                        b1.erase(b1.begin() + i);
                        enemy1.erase(enemy1.begin() + a);
                        points++;
                    }
                }
            }
            for (int i = 0; i < enemy1.size(); i++)//Damages the player if hit by the enemy
            {
                if (!inv && p1.getGlobalBounds().intersects(enemy1[i].getGlobalBounds()))
                {
                    enemy1.erase(enemy1.begin() + i);
                    life--;
                    healthx += 124;
                    inv = true;
                    invincible.push_back(Clock());
                    p1.setFillColor(Color(255,255,255,100));
                }
            }
            if (p1.getPosition().y > 664)//Kills the player if he hits the bottom of the screen
            {
                life = 0;
            }
            for (int i = 0; i < firespeed.size(); i++)//Spawns the fireball and makes it move towards the player
            {
                for (int a = 0; a < enemy1.size(); a++)
                {
                    if (firespeed[i].getElapsedTime().asSeconds() > 1)
                    {
                        fireball.push_back(RectangleShape());//Fireball Shape
                        fireball.back().setSize(Vector2f(256,256));
                        fireball.back().setOrigin(128,128);
                        fireball.back().setTexture(&fb);
                        fireball.back().setScale(0.15,0.15);
                        fireball.back().setPosition(Vector2f(enemy1[a].getPosition().x,enemy1[a].getPosition().y));
                        angle.push_back(atan2(p1.getPosition().y - fireball.back().getPosition().y,
                                              p1.getPosition().x - fireball.back().getPosition().x));//Direction of fireball
                        firespeed.erase(firespeed.begin()+i);
                    }
                }
            }
            for (int i = 0; i < fireball.size(); i++)
            {
                fireball[i].rotate(20);//Makes the fireball spin
                for (int a = 0; a < angle.size(); a++)
                {
                    fireball[i].move(speed*cos(angle[a]),speed*sin(angle[a]));//Makes the fireball move
                    if (!inv && fireball[i].getGlobalBounds().intersects(p1.getGlobalBounds()))//Damages the player if hit by the fireball
                    {
                        fireball.erase(fireball.begin()+i);
                        angle.erase(angle.begin()+a);
                        life--;
                        healthx += 124;
                        inv = true;
                        invincible.push_back(Clock());
                        p1.setFillColor(Color(255,255,255,100));
                    }
                    else if (fireball[i].getPosition().x < 0 || fireball[i].getPosition().x > 800 || fireball[i].getPosition().y > 600 || fireball[i].getPosition().y < 0)//Deletes the fireball if it leaves the screen
                    {
                        fireball.erase(fireball.begin()+i);
                        angle.erase(angle.begin()+a);
                    }
                    for (int b = 0; b < b1.size(); b++)
                    {
                        if (fireball[i].getGlobalBounds().intersects(b1[i].getGlobalBounds()))//Deletes the fireball if it is hit by the bullet
                        {
                            fireball.erase(fireball.begin()+i);
                            angle.erase(angle.begin()+a);
                            b1.erase(b1.begin()+b);
                        }
                    }
                }
            }
            for (int i = 0; i < invincible.size(); i++)//Gives the player invincibility after being recently hit
            {
                if (inv && invincible[i].getElapsedTime().asSeconds() > 3)
                {
                    invincible.erase(invincible.begin() + i);
                    inv = false;
                    p1.setFillColor(Color(255,255,255,255));
                }
            }
            //Drawings
            window.clear(); //clears the screen
            window.draw(backg);
            for (int i = 0; i < plat.size(); i++)
            {
                window.draw(plat[i]);
            }
            window.draw(p1);
            for (int i = 0; i < b1.size(); i++)
            {
                window.draw(b1[i]);
            }
            if (fp)
            {
                window.draw(platform);
            }
            for (int i = 0; i < enemy1.size(); i++)
            {
                window.draw(enemy1[i]);
            }
            for (int i = 0; i < fireball.size(); i++)
            {
                window.draw(fireball[i]);
            }
            window.draw(health);
            window.draw(score);
            window.display();   //displays everything on the video card to the monitor
        }

        //Win Screen
        else if (life > 0 && points >= 20)
        {
            thememusic.stop();
            quack.stop();
            jump.stop();
            lr.stop();
            if (winm)
            {
                winmusic.play();
                winmusic.setLoop(true);
                winm = false;
            }
            window.clear();
            window.draw(win);
            window.display();
        }

        //Game Over Screen
        else if (life == 0)
        {
            thememusic.stop();
            quack.stop();
            jump.stop();
            lr.stop();
            if (gamem)
            {
                gameoverm.play();
                gamem = false;
            }
            window.clear();
            window.draw(gm);
            window.draw(h2);
            window.draw(gmbutton);
            window.draw(gameovertext);
            if (Keyboard::isKeyPressed(Keyboard::Return))
            {
                x = 100;
                y = 425;
                vx = 0;
                vy = 0;
                g = 2;
                vtx = 32;
                vtx2 = 256;
                bgx = 0;
                py = 500;
                ex1 = 252;
                dpos = -450;
                fy = 175;
                posy = 425;
                healthx = 0;
                speed = 15;
                points = 0;
                grav = false;
                jumping = false;
                shooting = false;
                start = true;
                control = false;
                falling = false;
                bot = false;
                on = false;
                fp = true;
                top = false;
                inv = false;
                themem = true;
                clock1.restart();
                clock2.restart();
                clock3.restart();
                clock4.restart();
                clock5.restart();
                clock6.restart();
                b1.clear();
                bx.clear();
                invincible.clear();
                fireball.clear();
                angle.clear();
                p1.setFillColor(Color(255,255,255,255));
                for (int i = 0; i < plat.size(); i++)
                {
                    plat[i].setPosition(1100,py);
                }
                enemy1.clear();
                platform.setPosition(300,500);
                p1.setPosition(Vector2f(100,500));
                life = 6;
            }
            window.display();
        }
    }   //ends the game loop

    return 0;
}
