//
//  Gate.cpp
//  ColorGate
//
//  Created by xiaoming on 16/4/28.
//
//

#include "Gate.hpp"

Gate::Gate(GATE_COLOR gateColor,GATE_POS gatePos)
{
    Node::init();
    this->setContentSize(Size(GATE_CIRCLE_SIZE, GATE_CIRCLE_SIZE));
    this->setAnchorPoint(Vec2(0.5, 0.5));
    myColor=gateColor;
    myPos=gatePos;
    bg = Sprite::create("backCircle.png");
    bg->setPosition(Vec2(GATE_CIRCLE_SIZE/2, GATE_CIRCLE_SIZE/2));
    bg->setColor(Gate::getColor3B(myColor));
    this->addChild(bg);
    this->autorelease();
}

void Gate::onExit()
{
    bg->stopAllActions();
    Node::onExit();
}

GATE_POS Gate::getGatePos()
{
    return myPos;
}
GATE_COLOR Gate::getGateColor()
{
    return myColor;
}

void Gate::gateFadeIn()
{
    bg->setScale(0.4);
    auto scaleTo=ScaleTo::create(0.4, 1);
    bg->runAction(scaleTo);
}

Color3B Gate::getColor3B(GATE_COLOR color)
{
    float r,g,b;
    switch (color) {
        case RED:
        {
            r=255;
            g=97;
            b=60;
            break;
        }
        case YELLOW:
        {
            r=255;
            g=215;
            b=47;
            break;
        }
        case BLUE:
        {
            r=41;
            g=159;
            b=215;
            break;
        }
        default:
        {
            r=255;
            g=255;
            b=255;
            break;
        }
            
    }
    return Color3B(r,g,b);
}
Color4B Gate::getColor4B(GATE_COLOR color)
{
    float r,g,b;
    switch (color) {
        case RED:
        {
            r=255;
            g=97;
            b=60;
            break;
        }
        case YELLOW:
        {
            r=255;
            g=215;
            b=47;
            break;
        }
        case BLUE:
        {
            r=41;
            g=159;
            b=215;
            break;
        }
        default:
        {
            r=255;
            g=255;
            b=255;
            break;
        }
            
    }
    return Color4B(r, g, b, 152);
}

std::string Gate::getPressSoundEffect()
{
    std::string fileName="gatePress_"+Value((int)myColor+1).asString()+".mp3";
    return fileName;
}

