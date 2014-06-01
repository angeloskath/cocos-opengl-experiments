
#include "TilingSprite.h"

TilingSprite * TilingSprite::create(const std::string &_name) {
    auto pTS = new TilingSprite(_name);
    if (!pTS)
        return nullptr;

    pTS->autorelease();

    return pTS;
}
TilingSprite::TilingSprite(const std::string &_name) : m_offset(cocos2d::Point::ZERO) {
    m_pSprite = cocos2d::Sprite::create(_name);

    auto fileUtils = cocos2d::FileUtils::getInstance();
    auto vshSource = fileUtils->getStringFromFile(
        fileUtils->fullPathForFilename("shaders/generic.vsh")
    );
    auto fshSource = fileUtils->getStringFromFile(
        fileUtils->fullPathForFilename("shaders/tiling-sprite.fsh")
    );

    auto GLP = cocos2d::GLProgram::createWithByteArrays(
        vshSource.c_str(),
        fshSource.c_str()
    );
    auto GLPS = cocos2d::GLProgramState::getOrCreateWithGLProgram(GLP);
    m_pSprite->setGLProgram(GLP);
    m_pSprite->setGLProgramState(GLPS);

    // make it repeat
    cocos2d::GL::bindTexture2D(m_pSprite->getTexture()->getName());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    addChild(m_pSprite);
}

void TilingSprite::setOffset(const cocos2d::Point &_off) {
    m_offset = _off;

    updateOffsetUniform();
}
void TilingSprite::setOffsetX(float _offX) {
    m_offset.x = _offX;

    updateOffsetUniform();
}
void TilingSprite::setOffsetY(float _offY) {
    m_offset.y = _offY;

    updateOffsetUniform();
}

void TilingSprite::setScale(float _sX, float _sY) {
    cocos2d::Node::setScale(_sX, _sY);

    updateScaleUniform();
    updateOffsetUniform();
}
void TilingSprite::setScale(float _sXY) {
    cocos2d::Node::setScale(_sXY);

    updateScaleUniform();
    updateOffsetUniform();
}
void TilingSprite::setScaleX(float _sX) {
    cocos2d::Node::setScaleX(_sX);

    updateScaleUniform();
    updateOffsetUniform();
}
void TilingSprite::setScaleY(float _sY) {
    cocos2d::Node::setScaleY(_sY);

    updateScaleUniform();
    updateOffsetUniform();
}

void TilingSprite::updateOffsetUniform() {
    auto tsize = m_pSprite->getTexture()->getContentSize();
    m_pSprite->getGLProgramState()->setUniformVec2(
        "offset",
        cocos2d::Vec2(
            (m_offset.x/tsize.width)*_scaleX,
            (m_offset.y/tsize.height)*_scaleY
        )
    );
}

void TilingSprite::updateScaleUniform() {
    m_pSprite->getGLProgramState()->setUniformVec2(
        "scale",
        cocos2d::Vec2(_scaleX, _scaleY)
    );
}

