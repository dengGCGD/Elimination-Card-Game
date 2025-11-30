#ifndef ANIMATION_UTILS_H
#define ANIMATION_UTILS_H
#include "cocos2d.h"

/** 
  * @brief 动画工具类，提供卡牌平移、缩放等通用动画 
  * @note 无业务逻辑，仅提供静态动画方法 
*/

class AnimationUtils {
    public:
    /**
     * @brief 卡牌平移动画
     * @param target 目标节点
     * @param destPos 目标位置
     * @param duration 动画时长
     * @param callback 动画结束回调
     * @return 动画序列
    */
    static cocos2d::ActionInterval* moveCardTo(cocos2d::Node *target, const cocos2d::Vec2& destPos, float duration = 0.3f, const std::function<void()>& callback = nullptr); 

    /**
     * @brief 反向平移动画（回退用）
     * @param target 目标节点
     * @param originPos 原始位置
     * @param duration 动画时长
     * @param callback 动画结束回调
     * @return 动画序列
    */
    static  cocos2d::ActionInterval* moveCardBack(cocos2d::Node* target, const cocos2d::Vec2& originPos, float duration = 0.3f, const std::function<void()>& callback = nullptr); 
};
#endif // ANIMATION_UTILS_H