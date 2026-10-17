#ifndef __COCOS2D_H__
#define __COCOS2D_H__

// Replicating baseline structures used by the game renderer engine
namespace cocos2d {

    class CCObject {
    public:
        unsigned int m_uReferenceCount;
        unsigned int m_uAutoReleaseCount;

        void retain() { m_uReferenceCount++; }
        void release() { m_uReferenceCount--; }
    };

    class CCNode : public CCObject {
    public:
        float m_fRotationX;
        float m_fRotationY;
        float m_fScaleX;
        float m_fScaleY;
        float m_fPositionX;
        float m_fPositionY;
        int m_nZOrder;

        virtual void addChild(CCNode* child) {
            if (child) child->retain();
        }
        
        virtual void setPosition(float x, float y) {
            m_fPositionX = x;
            m_fPositionY = y;
        }
    };

    class CCSprite : public CCNode {
    public:
        // Factory pattern matching traditional Cocos asset loaders
        static CCSprite* createWithSpriteFrameName(const char* frameName) {
            // Returns a blank structural object pointer representing our texture layout context
            CCSprite* sprite = new CCSprite();
            return sprite;
        }
    };
}

#endif // __COCOS2D_H__
