
#include <cmath>

#include "Circle.h"

Circle * Circle::create(const std::string &_name) {
    auto pCircle = new Circle(_name);
    if (pCircle)
        pCircle->autorelease();

    return pCircle;
}

Circle::Circle(const std::string &_name) {
    m_pCircleSprite = cocos2d::Sprite::create(_name);
    m_pCircleSprite->retain();

    auto fileUtils = cocos2d::FileUtils::getInstance();
    auto vshSource = fileUtils->getStringFromFile(
        fileUtils->fullPathForFilename("shaders/circle.vsh")
    );
    auto fshSource = fileUtils->getStringFromFile(
        fileUtils->fullPathForFilename("shaders/circle.fsh")
    );

    auto GLP = cocos2d::GLProgram::createWithByteArrays(
        vshSource.c_str(),
        fshSource.c_str()
    );
    m_pGLPS = cocos2d::GLProgramState::getOrCreateWithGLProgram(GLP);
    m_pCircleSprite->setGLProgram(GLP);
    m_pCircleSprite->setGLProgramState(m_pGLPS);

    setAngle(0);

    addChild(m_pCircleSprite);
}

Circle::~Circle() {
    m_pCircleSprite->release();
}

void Circle::setAngle(float _angle) {
    if (_angle > 6.283185307179586)
        _angle -= 6.283185307179586;

    if (_angle != m_angle) {
        m_angle = _angle;
        m_tanAngle = std::tan(m_angle);

        m_pGLPS->setUniformFloat("angle", m_angle);
        m_pGLPS->setUniformFloat("neededTan", m_tanAngle);
    }
}

