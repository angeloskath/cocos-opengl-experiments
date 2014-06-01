#ifndef __TILING_SPRITE_H__
#define __TILING_SPRITE_H__

#include "cocos2d.h"

class TilingSprite : public cocos2d::Node
{
    public:
        static TilingSprite * create(const std::string &_name);

        /**
         * Set the offset from the texture's origin. For instance if this is
         * half the texture's size then the texture will begin showing from
         * that point.
         */
        void setOffset(const cocos2d::Point &_off);
        void setOffsetX(float _offX);
        void setOffsetY(float _offY);

        /**
         * Get the current offset
         */
        const cocos2d::Point &getOffset() const {
            return m_offset;
        }
        float getOffsetX() {
            return m_offset.x;
        }
        float getOffsetY() {
            return m_offset.y;
        }


        /**
         * Set the scale as uniform to the shader.
         */
        virtual void setScale(float _sX, float _sY) override;
        virtual void setScale(float _sXY) override;
        virtual void setScaleX(float _sX) override;
        virtual void setScaleY(float _sY) override;

    protected:
        TilingSprite(const std::string &_name);

        void updateOffsetUniform();
        void updateScaleUniform();

    private:
        cocos2d::Sprite * m_pSprite;
        cocos2d::Point m_offset;
};

#endif //__TILING_SPRITE_H__
