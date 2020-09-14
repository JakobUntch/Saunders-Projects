#include "physics.h"
#include <vector>
#include <string>
#include <math.h>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

int main()
{

    //Variables//
    int xs = 0;
    int ys = 0;
    int mpx = 0;
    int mpy = 0;
    int ppx = 0;
    int ppy = 0;
    int stroke = 0;
    int n = 1;
    int lvl = 1;
    int guidex;
    int guidey;
    int guidesize;
    int totalscore;
    int lvl6shape1Movement = 2;
    int lvl6shape2Movement = -2;
    int lvl6shape3Movement = 2;
    int lvl9shape2Movement = -10;
    int Power;
    int powersize;
    bool isMouseDown = false;
    bool showGuide = false;
    bool showPowerBar = false;
    bool addStroke = false;
    bool showEndScreen = false;
    bool movingBlocks = false;
    bool Level8RedCollision = false;
    bool Level9MovementCollision = false;
    bool endgame = false;
    bool collision = true;
    string endgamestring;
    float rotation;
    const float pi = 3.14159265358979323846;

    //Rendering//
    RenderWindow window(VideoMode(512,320),"SFML Works");
    window.setFramerateLimit(60);
    b2World world(b2Vec2(0.0, 9.8));

    //SoundBuffers//
    SoundBuffer hitwav;
    SoundBuffer shootwav;
    SoundBuffer holewav;
    SoundBuffer gameendwav;
    hitwav.loadFromFile("hit.wav");
    shootwav.loadFromFile("shoot.wav");
    holewav.loadFromFile("hole.wav");
    gameendwav.loadFromFile("gameend.wav");

    //Sounds//
    Sound hit;
    Sound shoot;
    Sound holesound;
    Sound gameend;
    hit.setBuffer(hitwav);
    shoot.setBuffer(shootwav);
    holesound.setBuffer(holewav);
    gameend.setBuffer(gameendwav);

    //Textures//
    Texture golfball;
    golfball.loadFromFile("golfball.png");

    //Font//
    Font font;
    font.loadFromFile("arial.ttf");

    //Grass Background//
    RectangleShape background;
    background.setSize(Vector2f(472, 280));
    background.setPosition(Vector2f(20,20));
    background.setFillColor(Color::Green);

    //Shooting Guide//
    RectangleShape guide;
    guide.setFillColor(Color::Red);
    guide.setOrigin(0,2.5);

    //Stroke Counter//
    Text strokeCounter;
    strokeCounter.setFont(font);
    strokeCounter.setPosition(0,0);
    strokeCounter.setFillColor(Color::White);

    //End Game Text//
    Text EndGameText;
    EndGameText.setFont(font);
    EndGameText.setFillColor(Color::White);

    //Shot Power Bar//
    RectangleShape PowerBar;
    PowerBar.setPosition(Vector2f(0,300));
    PowerBar.setFillColor(Color::Red);

    //Golfball//
    Block player = physics::createCircle(world,75,240,10,b2_dynamicBody);
    physics::setBlockTexture(player, &golfball);

    //Outer Walls//
    Block LeftWall = physics::createBox(world,0,0,20,320,b2_staticBody);
    Block RightWall = physics::createBox(world,492,0,20,320,b2_staticBody);
    Block TopWall = physics::createBox(world,20,0,492,20,b2_staticBody);
    Block BotWall = physics::createBox(world,20,300,492,20,b2_staticBody);
    physics::setBlockColor(LeftWall,Color::Black);
    physics::setBlockColor(RightWall,Color::Black);
    physics::setBlockColor(TopWall,Color::Black);
    physics::setBlockColor(BotWall,Color::Black);

    //Holes//
    Block Hole;
    Block Hole2;

    //Level 1//
    vector<Vector2f> lvl1shape1 = {Vector2f(412,300), Vector2f(492,300), Vector2f(492,200)};
    vector<Vector2f> lvl1shape2 = {Vector2f(412,20), Vector2f(492,20), Vector2f(492,120)};
    vector<Block> LevelShape;

    //Level 2//
    vector<Vector2f> lvl2shape1 = {Vector2f(412,300), Vector2f(492,300), Vector2f(492,20)};
    vector<Vector2f> lvl2shape2 = {Vector2f(20,20), Vector2f(20,300), Vector2f(100,300)};
    vector<Vector2f> lvl2shape3 = {Vector2f(492,20), Vector2f(292,20), Vector2f(472,90)};
    vector<Vector2f> lvl2shape4 = {Vector2f(20,20), Vector2f(220,20), Vector2f(40,90)};

    //Level 3//
    vector<Vector2f> lvl3shape1 = {Vector2f(20,185), Vector2f(20,320), Vector2f(256,300), Vector2f(296,185)};
    vector<Vector2f> lvl3shape2 = {Vector2f(326,300), Vector2f(385,130), Vector2f(492,130), Vector2f(492,300)};
    vector<Vector2f> lvl3shape3 = {Vector2f(492,130), Vector2f(492,20), Vector2f(256,20), Vector2f(218,130)};
    vector<Vector2f> lvl3shape4 = {Vector2f(20,185), Vector2f(129,185), Vector2f(186,20), Vector2f(20,20)};

    //Level 4//
    vector<Vector2f> lvl4shape1 = {Vector2f(100,20), Vector2f(20,20), Vector2f(20,120)};
    vector<Vector2f> lvl4shape2 = {Vector2f(100,20), Vector2f(256,180), Vector2f(412,20)};
    vector<Vector2f> lvl4shape3 = {Vector2f(412,20), Vector2f(492,20), Vector2f(492,120)};
    vector<Vector2f> lvl4shape4 = {Vector2f(20,300), Vector2f(100,80), Vector2f(180,300)};
    vector<Vector2f> lvl4shape5 = {Vector2f(180,300), Vector2f(256,220), Vector2f(332,300)};
    vector<Vector2f> lvl4shape6 = {Vector2f(496,300), Vector2f(412,80), Vector2f(332,300)};

    //Level 5//
    vector<Vector2f> lvl5shape1 = {Vector2f(20,60), Vector2f(256,170), Vector2f(492,60)};
    vector<Vector2f> lvl5shape2 = {Vector2f(20,200), Vector2f(128,140), Vector2f(256,200)};
    vector<Vector2f> lvl5shape3 = {Vector2f(256,200), Vector2f(384,140), Vector2f(492,200)};

    //Level 7//
    vector<Vector2f> lvl7shape1 = {Vector2f(20,20), Vector2f(100,145), Vector2f(300,145), Vector2f(380,20)};
    vector<Vector2f> lvl7shape2 = {Vector2f(20,300), Vector2f(100,175), Vector2f(300,175), Vector2f(380,300)};;
    vector<Vector2f> lvl7shape3 = {Vector2f(492,80), Vector2f(350,160), Vector2f(492,240)};

    //Level 8//
    vector<Vector2f> lvl8shape1 = {Vector2f(20,300), Vector2f(200,160), Vector2f(20,160)};
    vector<Vector2f> lvl8shape2 = {Vector2f(492,300), Vector2f(312,160), Vector2f(492,160)};
    vector<Vector2f> lvl8shape3 = {Vector2f(86,80), Vector2f(256,140), Vector2f(426,80)};

    //Level 9//
    vector<Vector2f> lvl9shape1 = {Vector2f(20,300), Vector2f(20,80), Vector2f(400,80)};
    vector<Vector2f> lvl9shape2 = {Vector2f(100,300), Vector2f(400,126), Vector2f(492,126), Vector2f(492,300)};

    //Main Loop//
    while (window.isOpen()&& !Keyboard::isKeyPressed(Keyboard::Escape))
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        //Sounds//
        if (physics::checkCollision(player) && !physics::checkCollision(player,Hole) && !physics::checkCollision(player,Hole2) && collision)
        {
            hit.play();
            collision = false;
        }
        else if (!physics::checkCollision(player) && !collision)
            collision = true;
        if (physics::checkCollision(player,Hole))
            holesound.play();

        //Level 1//
        if (lvl == 1)
        {
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl1shape1,b2_staticBody));
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl1shape2,b2_staticBody));
            LevelShape.push_back(physics::createBox(world,20,150,350,20,b2_staticBody));
            Hole = physics::createCircle(world,75,80,10,b2_staticBody);
            physics::setBlockColor(LevelShape[0], Color::Black);
            physics::setBlockColor(LevelShape[1], Color::Black);
            physics::setBlockColor(LevelShape[2], Color::Black);
            physics::setBlockColor(Hole, Color::Black);
            lvl = 0;
        }

        //Level 2//
        if (lvl == 2)
        {
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl2shape1,b2_staticBody));
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl2shape2,b2_staticBody));
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl2shape3,b2_staticBody));
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl2shape4,b2_staticBody));
            LevelShape.push_back(physics::createBox(world,116,150,280,20,b2_staticBody));
            Hole->SetTransform(b2Vec2(256/pixels_per_meter,90/pixels_per_meter), 0);
            player->SetLinearVelocity(b2Vec2(0,0));
            player->SetTransform(b2Vec2(256/pixels_per_meter,270/pixels_per_meter),0);
            physics::setBlockColor(LevelShape[0], Color::Black);
            physics::setBlockColor(LevelShape[1], Color::Black);
            physics::setBlockColor(LevelShape[2], Color::Black);
            physics::setBlockColor(LevelShape[3], Color::Black);
            physics::setBlockColor(LevelShape[4], Color::Black);
            lvl = 0;
        }

        //Level 3//
        if (lvl == 3)
        {
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl3shape1,b2_staticBody));
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl3shape2,b2_staticBody));
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl3shape3,b2_staticBody));
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl3shape4,b2_staticBody));
            Hole->SetTransform(b2Vec2(211/pixels_per_meter,50/pixels_per_meter),0);
            player->SetLinearVelocity(b2Vec2(0,0));
            player->SetTransform(b2Vec2(291/pixels_per_meter,280/pixels_per_meter),0);
            physics::setBlockColor(LevelShape[0], Color::Black);
            physics::setBlockColor(LevelShape[1], Color::Black);
            physics::setBlockColor(LevelShape[2], Color::Black);
            physics::setBlockColor(LevelShape[3], Color::Black);
            lvl = 0;
        }

        //Level 4//
        if (lvl == 4)
        {
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl4shape1,b2_staticBody));
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl4shape2,b2_staticBody));
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl4shape3,b2_staticBody));
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl4shape4,b2_staticBody));
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl4shape5,b2_staticBody));
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl4shape6,b2_staticBody));
            Hole->SetTransform(b2Vec2(472/pixels_per_meter,160/pixels_per_meter),0);
            player->SetLinearVelocity(b2Vec2(0,0));
            player->SetTransform(b2Vec2(50/pixels_per_meter,150/pixels_per_meter),0);
            physics::setBlockColor(LevelShape[0], Color::Black);
            physics::setBlockColor(LevelShape[1], Color::Black);
            physics::setBlockColor(LevelShape[2], Color::Black);
            physics::setBlockColor(LevelShape[3], Color::Black);
            physics::setBlockColor(LevelShape[4], Color::Black);
            physics::setBlockColor(LevelShape[5], Color::Black);
            lvl = 0;
        }

        //Level 5//
        if (lvl == 5)
        {
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl5shape1,b2_staticBody));
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl5shape2,b2_staticBody));
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl5shape3,b2_staticBody));
            LevelShape.push_back(physics::createBox(world,20,20,472,40,b2_staticBody));
            LevelShape.push_back(physics::createBox(world,20,200,472,100,b2_staticBody));
            Hole->SetTransform(b2Vec2(462/pixels_per_meter,160/pixels_per_meter),0);
            player->SetLinearVelocity(b2Vec2(0,0));
            player->SetTransform(b2Vec2(40/pixels_per_meter,170/pixels_per_meter),0);
            physics::setBlockColor(LevelShape[0], Color::Black);
            physics::setBlockColor(LevelShape[1], Color::Black);
            physics::setBlockColor(LevelShape[2], Color::Black);
            physics::setBlockColor(LevelShape[3], Color::Black);
            physics::setBlockColor(LevelShape[4], Color::Black);
            lvl = 0;
        }

        //Level 6//
        if (lvl == 6)
        {
            LevelShape.push_back(physics::createBox(world,100,20,80,80,b2_dynamicBody));
            LevelShape.push_back(physics::createBox(world,220,220,80,80,b2_dynamicBody));
            LevelShape.push_back(physics::createBox(world,340,20,80,80,b2_dynamicBody));
            physics::noGravity(LevelShape[0]);
            physics::noGravity(LevelShape[1]);
            physics::noGravity(LevelShape[2]);
            Hole->SetTransform(b2Vec2(472/pixels_per_meter,160/pixels_per_meter),0);
            player->SetLinearVelocity(b2Vec2(0,0));
            player->SetTransform(b2Vec2(60/pixels_per_meter,160/pixels_per_meter),0);
            physics::setBlockColor(LevelShape[0], Color::Red);
            physics::setBlockColor(LevelShape[1], Color::Red);
            physics::setBlockColor(LevelShape[2], Color::Red);
            movingBlocks = true;
            lvl = 0;
        }

        //Level 7//
        if (lvl == 7)
        {
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl7shape1,b2_staticBody));
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl7shape2,b2_staticBody));
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl7shape3,b2_staticBody));
            Hole2 = physics::createCircle(world,422,70,10,b2_staticBody);
            Hole->SetTransform(b2Vec2(422/pixels_per_meter,250/pixels_per_meter),0);
            player->SetLinearVelocity(b2Vec2(0,0));
            player->SetTransform(b2Vec2(60/pixels_per_meter,160/pixels_per_meter),0);
            physics::setBlockColor(LevelShape[0], Color::Black);
            physics::setBlockColor(LevelShape[1], Color::Black);
            physics::setBlockColor(LevelShape[2], Color::Black);
            physics::setBlockColor(Hole2, Color::Black);
            movingBlocks = false;
            lvl = 0;
        }

        //Level 8//
        if (lvl == 8)
        {
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl8shape1,b2_staticBody));
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl8shape2,b2_staticBody));
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl8shape3,b2_staticBody));
            LevelShape.push_back(physics::createBox(world,20,40,20,120,b2_staticBody));
            LevelShape.push_back(physics::createBox(world,472,40,20,120,b2_staticBody));
            LevelShape.push_back(physics::createBox(world,100,20,312,20,b2_staticBody));
            LevelShape.push_back(physics::createBox(world,20,20,80,20,b2_staticBody));
            LevelShape.push_back(physics::createBox(world,412,20,80,20,b2_staticBody));
            Hole->SetTransform(b2Vec2(256/pixels_per_meter,60/pixels_per_meter),0);
            player->SetLinearVelocity(b2Vec2(0,0));
            player->SetTransform(b2Vec2(256/pixels_per_meter,270/pixels_per_meter),0);
            physics::deleteBlock(world, Hole2);
            physics::setBlockColor(LevelShape[0], Color::Black);
            physics::setBlockColor(LevelShape[1], Color::Black);
            physics::setBlockColor(LevelShape[2], Color::Black);
            physics::setBlockColor(LevelShape[3], Color::Red);
            physics::setBlockColor(LevelShape[4], Color::Red);
            physics::setBlockColor(LevelShape[5], Color::Red);
            physics::setBlockColor(LevelShape[6], Color::Black);
            physics::setBlockColor(LevelShape[7], Color::Black);
            Level8RedCollision = true;
            lvl = 0;
        }

        //Level 9//
        if (lvl == 9)
        {
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl9shape1,b2_staticBody));
            LevelShape.push_back(physics::createPolygon(world,0,0,lvl9shape2,b2_dynamicBody));
            LevelShape.push_back(physics::createBox(world,400,20,92,20,b2_staticBody));
            LevelShape.push_back(physics::createBox(world,20,20,380,20,b2_staticBody));
            Hole->SetTransform(b2Vec2(50/pixels_per_meter,60/pixels_per_meter),0);
            physics::noGravity(LevelShape[1]);
            player->SetLinearVelocity(b2Vec2(0,0));
            player->SetTransform(b2Vec2(75/pixels_per_meter,300/pixels_per_meter),0);
            physics::setBlockColor(LevelShape[0], Color::Black);
            physics::setBlockColor(LevelShape[1], Color::Red);
            physics::setBlockColor(LevelShape[2], Color::Black);
            physics::setBlockColor(LevelShape[3], Color::Red);
            Level8RedCollision = false;
            Level9MovementCollision = true;
            lvl = 0;
        }

        //End of Game//
        if (endgame)
        {
            gameend.play();
            physics::deleteBlock(world, TopWall);
            physics::deleteBlock(world, BotWall);
            physics::deleteBlock(world, LeftWall);
            physics::deleteBlock(world, RightWall);
            physics::deleteBlock(world, player);
            showEndScreen = true;
            Level9MovementCollision = false;
            endgame = false;
        }

        //Game Loop//
        if (!showEndScreen)
        {
            //Golf Ball Movement//
            physics::noGravity(player);
            physics::noSpin(player);
            if (Mouse::isButtonPressed(Mouse::Left) && player->GetLinearVelocity().x*pixels_per_meter < 1 && player->GetLinearVelocity().y*pixels_per_meter < 1 && player->GetLinearVelocity().x*pixels_per_meter > -1 && player->GetLinearVelocity().y*pixels_per_meter > -1)
            {
                ppx = player->GetPosition().x*pixels_per_meter;
                ppy = player->GetPosition().y*pixels_per_meter;
                mpx = Mouse::getPosition(window).x;
                mpy = Mouse::getPosition(window).y;
                xs = ppx - mpx;
                ys = ppy - mpy;
                if (xs > 200)
                {
                    xs = 200;
                }
                else if (xs < -200)
                {
                    xs = -200;
                }
                if (ys > 200)
                {
                    ys = 200;
                }
                else if (ys < -200)
                {
                    ys = -200;
                }
                isMouseDown = true;
                guide.setPosition(player->GetPosition().x*pixels_per_meter, player->GetPosition().y*pixels_per_meter);
                guidesize = 100;
                guide.setSize(Vector2f(guidesize,5));
                guidex = Mouse::getPosition(window).x - player->GetPosition().x*pixels_per_meter;
                guidey = Mouse::getPosition(window).y - player->GetPosition().y*pixels_per_meter;
                rotation = (atan2(guidey, guidex)) * (180/pi) + 180;
                guide.setRotation(rotation);
                showGuide = true;
                showPowerBar = true;
                powersize = abs(xs) + abs(ys);
                PowerBar.setSize(Vector2f(powersize*3,20));
            }
            else if (!Mouse::isButtonPressed(Mouse::Left) && isMouseDown && abs(xs) >= 20 || abs(ys) >= 20 && !Mouse::isButtonPressed(Mouse::Left) && isMouseDown)
            {
                player->ApplyLinearImpulseToCenter(b2Vec2(xs/20,ys/20),true);
                shoot.play();
                isMouseDown = false;
                showGuide = false;
                showPowerBar = false;
                addStroke = true;
            }
            player->SetLinearDamping(0.5);

            //Level 6 Block Movement and Collision//
            if (movingBlocks)
            {
                if (LevelShape[0]->GetPosition().y*pixels_per_meter >= 230)
                {
                    lvl6shape1Movement = -30;
                }
                else if (LevelShape[0]->GetPosition().y*pixels_per_meter <= 90)
                {
                    lvl6shape1Movement = 30;
                }
                if (LevelShape[1]->GetPosition().y*pixels_per_meter >= 230)
                {
                    lvl6shape2Movement = -30;
                }
                else if (LevelShape[1]->GetPosition().y*pixels_per_meter <= 90)
                {
                    lvl6shape2Movement = 30;
                }
                if (LevelShape[2]->GetPosition().y*pixels_per_meter >= 230)
                {
                    lvl6shape3Movement = -30;
                }
                else if (LevelShape[2]->GetPosition().y*pixels_per_meter <= 90)
                {
                    lvl6shape3Movement = 30;
                }
                LevelShape[0]->ApplyLinearImpulseToCenter(b2Vec2(0,lvl6shape1Movement/pixels_per_meter),true);
                LevelShape[1]->ApplyLinearImpulseToCenter(b2Vec2(0,lvl6shape2Movement/pixels_per_meter),true);
                LevelShape[2]->ApplyLinearImpulseToCenter(b2Vec2(0,lvl6shape3Movement/pixels_per_meter),true);
                if (physics::checkCollision(player,LevelShape[0]) || physics::checkCollision(player,LevelShape[1]) || physics::checkCollision(player,LevelShape[2]))
                {
                    player->SetTransform(b2Vec2(60/pixels_per_meter,160/pixels_per_meter),0);
                    player->SetLinearVelocity(b2Vec2(0,0));
                    physics::deleteBlock(world, LevelShape[0]);
                    physics::deleteBlock(world, LevelShape[1]);
                    physics::deleteBlock(world, LevelShape[2]);
                    LevelShape.clear();
                    LevelShape.push_back(physics::createBox(world,100,20,80,80,b2_dynamicBody));
                    LevelShape.push_back(physics::createBox(world,220,220,80,80,b2_dynamicBody));
                    LevelShape.push_back(physics::createBox(world,340,20,80,80,b2_dynamicBody));
                    lvl6shape1Movement = 2;
                    lvl6shape2Movement = -2;
                    lvl6shape3Movement = 2;
                    physics::noGravity(LevelShape[0]);
                    physics::noGravity(LevelShape[1]);
                    physics::noGravity(LevelShape[2]);
                    physics::setBlockColor(LevelShape[0], Color::Red);
                    physics::setBlockColor(LevelShape[1], Color::Red);
                    physics::setBlockColor(LevelShape[2], Color::Red);
                }
            }

            //Level 8 Red Shape Collision//
            if (Level8RedCollision)
            {
                if (physics::checkCollision(player,LevelShape[3]) || physics::checkCollision(player,LevelShape[4]) || physics::checkCollision(player,LevelShape[5]))
                {
                    player->SetLinearVelocity(b2Vec2(0,0));
                    player->SetTransform(b2Vec2(256/pixels_per_meter,270/pixels_per_meter),0);
                }
            }

            //Level 9 Movement and Collision//
            if (Level9MovementCollision)
            {
                LevelShape[1]->ApplyLinearImpulseToCenter(b2Vec2(lvl9shape2Movement/pixels_per_meter,0),true);
                if (physics::checkCollision(LevelShape[0], LevelShape[1]))
                {
                    lvl9shape2Movement = 0;
                }
                if (physics::checkCollision(player,LevelShape[1]) || physics::checkCollision(player,LevelShape[3]))
                {
                    player->SetLinearVelocity(b2Vec2(0,0));
                    player->SetTransform(b2Vec2(75/pixels_per_meter,300/pixels_per_meter),0);
                    physics::deleteBlock(world, LevelShape[1]);
                    LevelShape[1] = physics::createPolygon(world,0,0,lvl9shape2,b2_dynamicBody);
                    physics::noGravity(LevelShape[1]);
                    physics::setBlockColor(LevelShape[1], Color::Red);
                    lvl9shape2Movement = -10;
                }
            }

            //Stroke Count//
            if (addStroke)
            {
                stroke++;
                addStroke = false;
            }
            strokeCounter.setString(to_string(stroke));

            //Hole Collision//
            if (physics::checkCollision(player, Hole))
            {
                for (int i = 0; i < LevelShape.size(); i++)
                {
                    physics::deleteBlock(world, LevelShape[i]);
                }
                LevelShape.clear();
                n++;
                lvl = n;
                totalscore = totalscore + stroke;
                stroke = 0;
                if (n > 9)
                {
                    endgame = true;
                }
            }
            if (!physics::isDestroyed(Hole2))
            {
                if (physics::checkCollision(player, Hole2))
                {
                    player->SetTransform(b2Vec2(60/pixels_per_meter,160/pixels_per_meter),0);
                    player->SetLinearVelocity(b2Vec2(0,0));
                }
            }

            //Drawing Graphics//
            window.clear();
            window.draw(background);
            if (showGuide)
            {
                window.draw(guide);
            }
            physics::displayWorld(world, window);
            window.draw(strokeCounter);
            if (showPowerBar)
            {
                window.draw(PowerBar);
            }
            window.display();
        }

        //End Game Screen//
        else if (showEndScreen)
        {
            window.clear();
            endgamestring = "      Congratulations!\n    You Finished With a \nTotal Stroke Count of " + to_string(totalscore) + "!";
            EndGameText.setString(endgamestring);
            EndGameText.setOrigin(EndGameText.getLocalBounds().width/2.0f,EndGameText.getLocalBounds().height/2.0f);
            EndGameText.setPosition(256,160);
            window.draw(EndGameText);
            window.display();
        }
    }

    return 0;
}
