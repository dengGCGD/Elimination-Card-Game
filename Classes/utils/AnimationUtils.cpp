#include "AnimationUtils.h"

USING_NS_CC;

ActionInterval* AnimationUtils::moveCardTo(Node* target, const Vec2& destPos, float duration, const std::function<void()>& callback) {
    if (!target)
        return nullptr;
    auto move = MoveTo::create(duration, destPos);
    auto seq = callback ? Sequence::create(move, CallFunc::create(callback), nullptr) : move;
    target->runAction(seq);
    return seq;
}

ActionInterval* AnimationUtils::moveCardBack(Node* target, const Vec2& originPos, float duration, const std::function<void()>& callback) {
    return moveCardTo(target, originPos, duration, callback);
}