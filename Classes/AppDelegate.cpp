#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

void AppDelegate::initGLContextAttrs()
{
    // 设置OpenGL上下文属性，如RGB颜色空间、深度缓冲区、模板缓冲区等
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // 初始化导演
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

    // 如果OpenGL视图为空，则创建一个新的
    if (!glview) {
        // 创建一个指定大小的窗口
        // 参数：窗口标题, 窗口矩形(位置x, 位置y, 宽度, 高度), 内容缩放因子
        glview = GLViewImpl::createWithRect("Elimination Card Game", cocos2d::Rect(0, 0, 1080, 2080), 1.0f); //窗口（1080*2080）

        // 设置OpenGL视图
        director->setOpenGLView(glview);
    }

    // 设置设计分辨率大小
    // 参数：宽度, 高度, 分辨率适配策略
    glview->setDesignResolutionSize(1080, 2080, ResolutionPolicy::FIXED_WIDTH);

    // 获取屏幕大小
    Size frameSize = glview->getFrameSize();

    // 开启FPS显示
    director->setDisplayStats(true);

    // 设置FPS为60
    director->setAnimationInterval(1.0f / 60);

    // 创建并运行HelloWorld场景
    auto scene = HelloWorld::createScene();
    director->runWithScene(scene);

    return true;
}

// 当应用程序进入后台时调用
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // 如果使用了简单音频引擎，可以在这里暂停音乐
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// 当应用程序从后台恢复时调用
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // 如果使用了简单音频引擎，可以在这里恢复音乐
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}