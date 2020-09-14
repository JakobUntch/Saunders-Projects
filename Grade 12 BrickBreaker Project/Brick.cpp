#ifndef BRICK_CPP
#define BRICK_CPP

#include "physics.h"

using namespace sf;

struct Brick : public sf::RectangleShape
{
    //Constructor
    Brick(b2World &world, float x, float y, float width, float height, b2BodyType type = b2_staticBody)
    {
        b2BodyDef bodyDef;
        bodyDef.position.Set((x + width/2.0)/pixels_per_meter, (y + height/2.0)/pixels_per_meter);
        bodyDef.type = type;
        bodyDef.linearDamping = 0.0;
        b2PolygonShape b2shape;
        b2shape.SetAsBox(width/pixels_per_meter/2.0, height/pixels_per_meter/2.0);
        b2FixtureDef fixtureDef;
        fixtureDef.density = 1.0;
        fixtureDef.friction = 0.0;
        fixtureDef.restitution = 1.0;
        fixtureDef.shape = &b2shape;

        body = world.CreateBody(&bodyDef);
        body->CreateFixture(&fixtureDef);

        this->setSize(sf::Vector2f(width, height));
        this->setOrigin(width/2.0, height/2.0);
        this->setPosition(x, y);
        this->setOutlineThickness(2);
        this->setOutlineColor(Color::Black);
        this->setFillColor(Color::Blue);
    }

    //Member Functions

    //Power Up 1 - Increases Ball and Paddle Speed
    void PowerUp1()
    {
        this->setFillColor(Color::Cyan);
    }

    //Power Up 2 - Increases Ball Size
    void PowerUp2()
    {
        this->setFillColor(Color::Magenta);
    }

    //Power Up 3 - Increases Paddle Size
    void PowerUp3()
    {
        this->setFillColor(Color::Green);
    }

    //Position Updater
    void updatePosition(sf::RenderWindow& render)
    {
        this->setPosition(body->GetPosition().x*pixels_per_meter, body->GetPosition().y*pixels_per_meter);
        this->setRotation(body->GetAngle()*deg_per_rad);
        render.draw(*this);
    }

    //Member Variables
    b2Body* body;
};

#endif // BRICK_CPP
