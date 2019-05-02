#include "CSEEmboss.h"

cocos2d::Layer* CSEEmboss::create()
{
    CSEEmboss *ret = new (std::nothrow) CSEEmboss();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

bool CSEEmboss::init()
{
    if(!cocos2d::Layer::init())
    {
        return false;
    }

    // 1
    sprite = cocos2d::Sprite::create("Default.png");
    sprite->setAnchorPoint(cocos2d::Vec2::ZERO);
    sprite->setRotation(90.0f);
    sprite->setPosition(cocos2d::Vec2(0, 320));

    // 1.1 (back to menu on touch)
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) { return true;};
    touchListener->onTouchMoved = [=](cocos2d::Touch* touch, cocos2d::Event* event) { };
    touchListener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        cocos2d::Director::getInstance()->popScene();
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    this->addChild(sprite, 1);

    // 2
    cocos2d::GLProgram* shader = cocos2d::GLProgram::createWithFilenames("shaders/PositionTextureColorNoMVP.vert", "shaders/CSEEmboss.frag");

    shader->bindAttribLocation(cocos2d::GLProgram::ATTRIBUTE_NAME_POSITION, cocos2d::GLProgram::VERTEX_ATTRIB_POSITION);
    shader->bindAttribLocation(cocos2d::GLProgram::ATTRIBUTE_NAME_TEX_COORD, cocos2d::GLProgram::VERTEX_ATTRIB_TEX_COORD);
    shader->link();
    shader->updateUniforms();

    sprite->setGLProgram(shader);

    // 3
    timeUniformLocation = glGetUniformLocation(sprite->getGLProgram()->getProgram(), "u_time");

    // 4
    this->scheduleUpdate();

    // 5
    cocos2d::GLProgramState* state = cocos2d::GLProgramState::getOrCreateWithGLProgram(shader);
    sprite->setGLProgramState(state);
    state->setUniformTexture("u_texture", sprite->getTexture());
    sprite->getGLProgram()->use();

    return true;
}

void CSEEmboss::update(float deltaTime)
{
    totalTime += deltaTime;
    sprite->getGLProgram()->use();
    glUniform1f(timeUniformLocation, totalTime);
}