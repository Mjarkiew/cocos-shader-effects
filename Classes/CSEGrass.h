#ifndef CSEGRASS_H
#define CSEGRASS_H

#include "cocos2d.h"

class CSEGrass : public cocos2d::Layer
{
public:
    static cocos2d::Layer* create();
    virtual bool init() override;
    virtual void update(float deltaTime) override;

private:
    cocos2d::Sprite* sprite;
    int timeUniformLocation;
    float totalTime;
};

#endif //CSEGRASS_H