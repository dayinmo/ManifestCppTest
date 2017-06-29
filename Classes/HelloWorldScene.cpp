#include "HelloWorldScene.h"

USING_NS_CC;
using namespace cocos2d::ui;
USING_NS_CC_EXT;

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
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Button* button = Button::create("CloseNormal.png", "CloseSelected.png");
    button->setPosition(Vec2(getContentSize().width/2, getContentSize().height/2));
    button->addClickEventListener(CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    addChild(button);;
    std::string storagePath = FileUtils::getInstance()->getWritablePath()+"ManifestCppTest/";
    CCLOG("storagePath %s", storagePath.c_str());
    _assetsMangerEx = AssetsManagerEx::create("project.manifest", storagePath);
    _assetsMangerEx->retain();
    return true;
}

void HelloWorld::downLoadCallback(EventAssetsManagerEx *event)
{
    CCLOG("event %d", event->getEventCode());
    switch (event->getEventCode()) {
        case EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST:
            CCLOG("EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST");
            break;
        case EventAssetsManagerEx::EventCode::ERROR_DOWNLOAD_MANIFEST:
            CCLOG("EventAssetsManagerEx::EventCode::ERROR_DOWNLOAD_MANIFEST");
            break;
        case EventAssetsManagerEx::EventCode::ERROR_PARSE_MANIFEST:
            CCLOG("EventAssetsManagerEx::EventCode::ERROR_PARSE_MANIFEST");
            break;
        case EventAssetsManagerEx::EventCode::NEW_VERSION_FOUND:
            CCLOG("EventAssetsManagerEx::EventCode::NEW_VERSION_FOUND");
            break;
        case EventAssetsManagerEx::EventCode::ALREADY_UP_TO_DATE:
            CCLOG("EventAssetsManagerEx::EventCode::ALREADY_UP_TO_DATE");
            break;
        case EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION:
            CCLOG("EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION");
            break;
        case EventAssetsManagerEx::EventCode::ASSET_UPDATED:
            CCLOG("EventAssetsManagerEx::EventCode::ASSET_UPDATED");
            break;
        case EventAssetsManagerEx::EventCode::ERROR_UPDATING:
            CCLOG("EventAssetsManagerEx::EventCode::ERROR_UPDATING");
            break;
        case EventAssetsManagerEx::EventCode::UPDATE_FINISHED:
            CCLOG("EventAssetsManagerEx::EventCode::UPDATE_FINISHED");
            break;
        case EventAssetsManagerEx::EventCode::UPDATE_FAILED:
            CCLOG("EventAssetsManagerEx::EventCode::UPDATE_FAILED");
            break;
        case EventAssetsManagerEx::EventCode::ERROR_DECOMPRESS:
            CCLOG("EventAssetsManagerEx::EventCode::ERROR_DECOMPRESS");
            break;
        default:
            CCLOG("default");
            break;
    }
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    if(!_assetsMangerEx->getLocalManifest()->isLoaded())
    {
        CCLOG("加载本地manifest文件失败");
        return;
    }
    CCLOG("本地文件版本号为:%s", _assetsMangerEx->getLocalManifest()->getVersion().c_str());
    _assetsManagerExListener = EventListenerAssetsManagerEx::create(_assetsMangerEx, CC_CALLBACK_1(HelloWorld::downLoadCallback, this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_assetsManagerExListener, 1);
    _assetsMangerEx->update();
}
