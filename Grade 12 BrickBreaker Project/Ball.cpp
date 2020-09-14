#ifndef Ball_CPP
#define BALL_CPP

#include "physics.h"
#include "Paddle.cpp"
#include "Brick.cpp"
#include <SFML/Audio.hpp>

struct Ball : public sf::CircleShape
{
    //Constructor
    Ball(b2World &world, float x, float y, float r, float s, float a, b2BodyType type = b2_dynamicBody)
    {

        speed = s;
        angle = a;

        b2BodyDef bodyDef;
        bodyDef.position.Set(x/pixels_per_meter, y/pixels_per_meter);
        bodyDef.type = type;
        bodyDef.linearDamping = 0.0;
        body = world.CreateBody(&bodyDef);

        b2CircleShape b2shape;
        b2shape.m_radius = r/pixels_per_meter;

        b2FixtureDef fixtureDef;
        fixtureDef.density = 1.0;
        fixtureDef.friction = 0.0;
        fixtureDef.restitution = 1.0;
        fixtureDef.shape = &b2shape;

        body->CreateFixture(&fixtureDef);

        this->setRadius(r);
        this->setOrigin(r,r);
        this->setPosition(x, y);
        this->setFillColor(sf::Color::White);

        body->SetLinearVelocity(b2Vec2(speed*cos(angle/deg_per_rad)/pixels_per_meter,speed*sin(angle/deg_per_rad)/pixels_per_meter));

    }

    //Member Functions

    //Position Updater
    void updatePosition(sf::RenderWindow& render)
    {
        this->setPosition(body->GetPosition().x*pixels_per_meter, body->GetPosition().y*pixels_per_meter);
        this->setRotation(body->GetAngle()*deg_per_rad);

        //Limits Ball Speed
        b2Vec2 velocity = body->GetLinearVelocity();
        body->SetLinearVelocity((speed/pixels_per_meter)/velocity.Length()*velocity);

        render.draw(*this);
    }

    //Ball Paddle Collision
    bool checkCollision(const Paddle &p1)
    {
        for (b2ContactEdge* edge = body->GetContactList(); edge; edge = edge->next)
        {
            if (edge->other == p1.body)
            {
                if (edge->contact->IsTouching())
                {
                    //Bounce at an Angle
                    angle = 60.0*(this->getPosition().x - p1.getPosition().x)/(p1.width/2.0)-90;
                    body->SetLinearVelocity(b2Vec2(speed*cos(angle/deg_per_rad)/pixels_per_meter,speed*sin(angle/deg_per_rad)/pixels_per_meter));

                    return true;
                }
            }
        }
        return false;
    }

    //Ball Brick Collision
    bool checkCollision(const Brick &b1)
    {
        for (b2ContactEdge* edge = body->GetContactList(); edge; edge = edge->next)
        {
            if (edge->other == b1.body)
            {
                if (edge->contact->IsTouching())
                {
                    return true;
                }
            }
            return false;
        }
    };

    //Radius Increase (Power Up 2)
    void changeSize(float radiusRatio)
    {
        radius = this->getRadius()*radiusRatio;

        b2Fixture *oldfixture = body->GetFixtureList();
        body->DestroyFixture(oldfixture);

        b2CircleShape b2Shape;
        b2Shape.m_radius = radius/pixels_per_meter;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &b2Shape;
        fixtureDef.density = 1.0;
        fixtureDef.friction = 0;
        fixtureDef.restitution = 1.0;
        body->CreateFixture(&fixtureDef);

        this->setRadius(radius);
        this->setOrigin(radius,radius);
    }

    //Member Variables
    b2Body* body;
    float speed;
    float angle;
    float radius;
};

#endif // Ball_CPP
