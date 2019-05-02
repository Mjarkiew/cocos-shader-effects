#include "CSEColorRamp.h"

cocos2d::Layer* CSEColorRamp::create()
{
    CSEColorRamp *ret = new (std::nothrow) CSEColorRamp();
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

bool CSEColorRamp::init()
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
#if 1
    cocos2d::GLProgram* shader = cocos2d::GLProgram::createWithFilenames("shaders/PositionTextureColorNoMVP.vert", "shaders/CSEColorRamp.frag");
#else
    const GLchar* fragmentSource = cocos2d::FileUtils::getInstance()->getStringFromFile("CSEColorRamp.fsh").c_str();
    cocos2d::GLProgram* shader = cocos2d::GLProgram::createWithByteArrays(cocos2d::ccPositionTextureA8Color_vert,
                                                                          fragmentSource);
    std::string vertexLog = shader->getVertexShaderLog();
    std::string fragmentLog = shader->getFragmentShaderLog();
#endif
    shader->bindAttribLocation(cocos2d::GLProgram::ATTRIBUTE_NAME_POSITION, cocos2d::GLProgram::VERTEX_ATTRIB_POSITION);
    shader->bindAttribLocation(cocos2d::GLProgram::ATTRIBUTE_NAME_TEX_COORD, cocos2d::GLProgram::VERTEX_ATTRIB_TEX_COORD);
    shader->link();
    shader->updateUniforms();

    sprite->setGLProgram(shader);

    // 3
    colorRampUniformLocation = glGetUniformLocation(sprite->getGLProgram()->getProgram(), "u_colorRampTexture");
    glUniform1i(colorRampUniformLocation, 1);

    // 4
    colorRampTexture = cocos2d::Director::getInstance()->getTextureCache()->addImage("colorRamp.png");
    colorRampTexture->setAliasTexParameters();
    colorRampTexture->retain();

    // 5
    cocos2d::GLProgramState* state = cocos2d::GLProgramState::getOrCreateWithGLProgram(shader);
    sprite->setGLProgramState(state);

    state->setUniformTexture("u_texture", sprite->getTexture());
    state->setUniformTexture("u_colorRampTexture", colorRampTexture);

    return true;
}