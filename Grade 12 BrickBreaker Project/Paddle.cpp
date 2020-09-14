#ifndef PADDLE_CPP
#define PADDLE_CPP

#include "physics.h"

using namespace sf;

struct Paddle : public sf::RectangleShape
{
    //Constructor
    Paddle(b2World &world, float x, float y, float w, float h, b2BodyType type = b2_kinematicBody)
    {
        width = w;
        height = h;
        speed = 10;

        b2BodyDef bodyDef;
        bodyDef.position.Set((x + width/2.0)/pixels_per_meter, (y + height/2.0)/pixels_per_meter);
        bodyDef.type = type;
        bodyDef.linearDamping = 0.0;
        body = world.CreateBody(&bodyDef);

        b2PolygonShape b2shape;
        b2shape.SetAsBox(width/pixels_per_meter/2.0, height/pixels_per_meter/2.0);

        b2FixtureDef fixtureDef;
        fixtureDef.density = 1.0;
        fixtureDef.friction = 0.0;
        fixtureDef.restitution = 1.0;
        fixtureDef.shape = &b2shape;
        body->CreateFixture(&fixtureDef);

        this->setSize(sf::Vector2f(width, height));
        this->setOrigin(width/2.0, height/2.0);
        this->setPosition(x, y);
        this->setFillColor(sf::Color::White);
    }

    //Member Functions

    //Position Updater and Keyboard Controls
    void updatePosition(sf::RenderWindow& render)
    {
        if (Keyboard::isKeyPressed(Keyboard::A) && this->getPosition().x > width/2.0)
        {
            body->SetLinearVelocity(b2Vec2(-speed,0));
        }
        else if (Keyboard::isKeyPressed(Keyboard::D) && this->getPosition().x < 800 - width/2.0)
        {
            body->SetLinearVelocity(b2Vec2(speed,0));
        }
        else
        {
            body->SetLinearVelocity(b2Vec2(0,0));
        }

        this->setPosition(body->GetPosition().x*pixels_per_meter, body->GetPosition().y*pixels_per_meter);
        this->setRotation(body->GetAngle()*deg_per_rad);
        render.draw(*this);
    }

    //Width Increaser (Power Up 3)
    void changeSize(float widthRatio)
    {
        b2Fixture *oldfixture = body->GetFixtureList();
        body->DestroyFixture(oldfixture);

        width = widthRatio*width;

        b2PolygonShape b2shape;
        b2shape.SetAsBox(width/pixels_per_meter/2.0, height/pixels_per_meter/2.0);

        b2FixtureDef fixtureDef;
        fixtureDef.density = 1.0;
        fixtureDef.friction = 0.0;
        fixtureDef.restitution = 1.0;
        fixtureDef.shape = &b2shape;
        body->CreateFixture(&fixtureDef);

        this->setSize(sf::Vector2f(width, height));
        this->setOrigin(width/2.0, height/2.0);
    }

    //Member Variables
    b2Body* body;
    float width;
    float height;
    float speed;

};

#endif // PADDLE_CPP

