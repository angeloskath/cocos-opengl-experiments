#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include <string>

#include "cocos2d.h"

class Circle : public cocos2d::Node
{
    public:
        static Circle * create(const std::string &_name);

        ~Circle();

        void setAngle(float _angle);

    protected:
        Circle(const std::string &_name);

    // members
    private:
        cocos2d::Sprite * m_pCircleSprite;
        cocos2d::GLProgramState * m_pGLPS;

        float m_tanAngle;
        float m_angle;
};

#endif // __CIRCLE_H__
