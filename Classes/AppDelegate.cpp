#include "AppDelegate.h"
#include "MainScene.hpp"
USING_NS_CC;
AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("MiniGameHor", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("MiniGameHor");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // Set the design resolution
    this->setDesignResolution();

    std::vector<std::string>searchPath;
    searchPath.push_back("effect");
    searchPath.push_back("sound");
    searchPath.push_back("myImage/mainScene");
    searchPath.push_back("myImage/battleScene");
    searchPath.push_back("myImage/others");
    FileUtils::getInstance()->setSearchPaths(searchPath);
    
    
    int evaluatedOpen=UserDefault::getInstance()->getIntegerForKey("evaluatedOpen", 0)+1;
    if (evaluatedOpen>100000) {
        evaluatedOpen=100000;
    }
    UserDefault::getInstance()->setIntegerForKey("evaluatedOpen", evaluatedOpen);
    UserDefault::getInstance()->flush();
    
    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = MainScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}


void AppDelegate::setDesignResolution()
{
    auto glview = Director::getInstance()->getOpenGLView();
    float frameWidth=glview->getFrameSize().width;
    float frameHeight=glview->getFrameSize().height;
    float frameRatio = frameHeight/frameWidth;
    float designHeight=640;
    float designWidth=1136;
    if (fabsf(frameRatio-1.775f)>fabsf(frameRatio-1.5f)) {
        designWidth=960;
    }
    glview->setDesignResolutionSize(designWidth, designHeight, ResolutionPolicy::EXACT_FIT);
}
