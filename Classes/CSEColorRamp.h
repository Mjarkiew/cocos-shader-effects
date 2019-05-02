#ifndef CSECOLORRAMP_H
#define CSECOLORRAMP_H

#include "cocos2d.h"

class CSEColorRamp : public cocos2d::Layer
{
public:
    static cocos2d::Layer* create();
    virtual bool init() override;

private:
    cocos2d::Sprite* sprite;
    int colorRampUniformLocation;
    cocos2d::Texture2D* colorRampTexture;
};

#endif // CSECOLORRAMP_H