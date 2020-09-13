#include <SFML/Graphics.hpp> //includes SFML libraries
#include <iostream>
#include <string>

using namespace std;
using namespace sf; //for graphics

//A function that limits value to the range minn..maxx
float clamp(float value,float minn, float maxx){
    if (value < minn) return minn;
    else if (value > maxx) return maxx;
    else return value;
}

//A Boolean function that takes in a Rectangle and a Circle and returns true if they are intersecting and false if not. The circles origin must be set to its center and the rectangles origin must be set to its top left corner
int checkCollision (RectangleShape &R1,  CircleShape &C1) {

        // Find the closest point to the circle within the rectangle
        float closestX = clamp(C1.getPosition().x, R1.getPosition().x,R1.getPosition().x+R1.getSize().x );
        float closestY = clamp(C1.getPosition().y, R1.getPosition().y,R1.getPosition().y+R1.getSize().y );

        // Calculate the distance between the circle's center and this closest point
        float distanceX = C1.getPosition().x - closestX;
        float distanceY = C1.getPosition().y - closestY;

        // If the distance is less than the circle's radius, an intersection occurs
        float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
        if (distanceSquared < C1.getRadius()*C1.getRadius() && closestY != C1.getPosition().y && closestX != C1.getPosition().x )
        {
           return 3;  //corner hit
        }
        else if (distanceSquared < C1.getRadius()*C1.getRadius() && closestY == C1.getPosition().y ){
            return 1; //side hit
        }
        else if (distanceSquared < C1.getRadius()*C1.getRadius() && closestX == C1.getPosition().x ){
            return 2; //top//bottom hit
        }
        else return 0;
}

int main()
{
    RenderWindow window(VideoMode(800,600),"SFML Works");  //creates a window on the screen that is 800 by 600
    window.setFramerateLimit(60); //sets the game loop to run 60 times per second
    Texture t1;
    t1.loadFromFile("ball1.png");
    Texture bg;
    bg.loadFromFile("background1.png");
    RectangleShape backg(Vector2f(800, 600));
    CircleShape ball (29);
    RectangleShape paddle1(Vector2f(50, 200));
    RectangleShape paddle2 (Vector2f(50, 200));
    paddle1.setFillColor(Color::Blue);
    paddle2.setFillColor(Color::Red);
    Font font;
    font.loadFromFile("C:\\Windows\\Fonts\\comic.ttf");
    Text bscore;
    Text rscore;
    Text p1winner("Player 1 Wins", font, 64);
    Text p2winner ("Player 2 Wins!", font, 64);
    bscore.setFont(font);
    rscore.setFont(font);
    bscore.setFillColor(Color::Blue);
    rscore.setFillColor(Color::Red);
    p1winner.setFillColor(Color::Blue);
    p2winner.setFillColor(Color::Red);
    bscore.setCharacterSize(32);
    rscore.setCharacterSize(32);
    bscore.setPosition(200,500);
    rscore.setPosition(600,500);
    p1winner.setPosition(200,250);
    p2winner.setPosition(200,250);
    ball.setTexture(&t1);
    backg.setTexture(&bg);
    ball.setOrigin (29,29);
    ball.setPosition (400,300);
    paddle1.setPosition(50,200);
    paddle2.setPosition(700,200);
    int pwin = 1;
    int c = 0;
    int posy = 0;
    int c2 = 0;
    int bx = -5;
    int by = 5;
    int score1 = 0;
    int score2 = 0;
    int py = 0;
    int pm = 0;
    int cp = 0;
    int py2 = 0;
    int pm2 = 0;
    while (window.isOpen()&& !Keyboard::isKeyPressed(Keyboard::Escape))     //the main game loop, exits if someone closes the window
     {
        Event event; //creates an event object, events include mouse clicks, mouse movement, keyboard presses, etc..
        while (window.pollEvent(event)) //loop that checks for events
        {
            if (event.type == Event::Closed) //checks if window is closed
                window.close();
        }
        //ends the event loop

        if (checkCollision(paddle1, ball) == 1){
                bx = (bx * -1) + 1;
        }
        else if (checkCollision(paddle1, ball) == 2){
                by = (by * -1) + 1;
        }
        else if (checkCollision(paddle1, ball) == 3){
                bx = (bx * -1) + 1;
                by = (by * -1) + 1;
        }
        if (checkCollision(paddle2, ball) == 1){
                bx = (bx * -1) - 1;
        }
        else if (checkCollision(paddle2, ball) == 2){
                by = (by * -1) + 1;
        }
        else if (checkCollision(paddle2, ball) == 3){
                bx = (bx * -1) - 1;
                by = (by * -1) - 1;
        }
        if (ball.getPosition().y <= 29){
            by = (by * -1) + 1;
        }
        else if (ball.getPosition().y >= 571){
            by = (by * -1) - 1;
        }
        if (ball.getPosition().x >= 771){
            score1++;
            ball.setPosition(400,300);
            bx = -5;
            by = -5;
        }
        else if (ball.getPosition().x <= 29){
            score2++;
            ball.setPosition(400,300);
            bx = 5;
            by = 5;
        }
        if (Keyboard::isKeyPressed(Keyboard::S)){
            if (py > 400){
                paddle1.setPosition(50,400);
            }
            pm = 10;
        }
        else if (Keyboard::isKeyPressed(Keyboard::W)){
            if (py < 0){
                paddle1.setPosition(50,0);
            }
            pm = -10;
        }
        else{
            pm = 0;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)){
            if (py2 > 400){
                paddle2.setPosition(700,400);
            }
            pm2 = 10;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Up)){
            if (py2 < 0){
                paddle2.setPosition(700,0);
            }
            pm2 = -10;
        }
        else{
            pm2 = 0;
        }
        py2 = paddle2.getPosition().y;
        py = paddle1.getPosition().y;
        paddle2.move(0,pm2);
        paddle1.move(0,pm);
        if (pwin == 1) ball.move(bx,by);
        int fc = c % 7;
        int posx = fc * 58;
        if (posx == 348 && c2 < 7){
            posy = posy + 58;
            c2++;
            posx = 0;
            if (posy >= 348){
                posy = 0;
                c2 = 0;
            }
        }
        if (score1 == 10){
            pwin = 2;
        }
        else if (score2 == 10){
            pwin = 3;
        }
        bscore.setString(to_string(score1));
        rscore.setString(to_string(score2));
        ball.setTextureRect(IntRect(posx, posy, 58,58));
        c++;
        window.clear(); //clears the screen
        if (pwin == 1){
        window.draw(backg);
        window.draw(ball);
        window.draw(paddle1);
        window.draw(paddle2);
        window.draw(bscore);
        window.draw(rscore);
        }
        else if (pwin == 2){
            window.draw(p1winner);
        }
        else{
            window.draw(p2winner);
        }
            window.display();
        }
    return 0;
}

