#include "HelloWorldScene.h"

#include "CSEColorRamp.h"
#include "CSEEmboss.h"
#include "CSEGrass.h"

#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    // 1 - create and initialize a Label
    auto label = cocos2d::Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 64);

    // 2 - ask director the the window size
    auto visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 3 - position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // 4 - add the label as a child to this Layer
    this->addChild(label, 1);

    // 5 - Default font size will be 28 points.
    cocos2d::MenuItemFont::setFontSize(28);

    // 6 - color ramp Menu Item and emboss Menu Item using blocks
    cocos2d::Vector<cocos2d::MenuItem*> items;

    // 6.1 Color Ramp
    cocos2d::MenuItemFont* itemColorRamp = cocos2d::MenuItemFont::create("Color Ramp");
    itemColorRamp->initWithString("Color Ramp", [&](cocos2d::Ref* sender) {
        cocos2d::Scene* scene = cocos2d::Scene::create();
        scene->addChild(CSEColorRamp::create());
        Director::getInstance()->pushScene(scene);
    });
    items.pushBack(itemColorRamp);

    // 6.2 Emboss (+ movement)
    cocos2d::MenuItemFont* itemEmboss = cocos2d::MenuItemFont::create("Emboss");
    itemEmboss->initWithString("Emboss", [&](cocos2d::Ref* sender) {
        cocos2d::Scene* scene = cocos2d::Scene::create();
        scene->addChild(CSEEmboss::create());
        Director::getInstance()->pushScene(scene);
    });
    items.pushBack(itemEmboss);

    // 6.3 Grass
    cocos2d::MenuItemFont* itemGrass = cocos2d::MenuItemFont::create("Grass");
    itemGrass->initWithString("Grass", [&](cocos2d::Ref* sender) {
        cocos2d::Scene* scene = cocos2d::Scene::create();
        scene->addChild(CSEGrass::create());
        Director::getInstance()->pushScene(scene);
    });
    items.pushBack(itemGrass);

    // 7 - Create menu
    cocos2d::Menu* menu = cocos2d::Menu::createWithArray(items);

    // 8 - Configure menu
    menu->alignItemsVerticallyWithPadding(20.0f);
    menu->setPosition(origin.x + visibleSize.width/2,
                      origin.y + visibleSize.height/2 - label->getContentSize().height);

    this->addChild(menu);

    return true;
}
