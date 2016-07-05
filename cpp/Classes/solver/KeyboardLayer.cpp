#include "KeyboardLayer.h"

#include <string>

USING_NS_CC;

namespace QUAT {

KeyboardLayer * KeyboardLayer::create(cocos2d::Rect * gameBounds, float fontSize)
{
    KeyboardLayer *pRet = new(std::nothrow) KeyboardLayer(gameBounds, fontSize);
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

void KeyboardLayer::none() {
}


bool KeyboardLayer::init() {
	// Init the super class
    if ( !Layer::init() )
    {
        return false;
    }
    
    // Calculates all of the necessary ratios
    float width = gameBounds->size.width,
    	  height = gameBounds->size.height,
    	  keyboardHeight = height * 0.3,
          keyboardY = 0,
          ratio = 2.265,
          keyboardWidth = ratio * keyboardHeight;

    if (width < keyboardWidth) {
        keyboardWidth = width;
        keyboardHeight = (1 / ratio) * keyboardWidth;
    }

    // Calculates the rest of them
    float halfWidth = keyboardWidth / 2,
          keyHeight = keyboardHeight * 0.27,
          keyFontSize = keyHeight * 0.5,
          keyWidth = keyboardWidth * 0.080,
          verticalGap = keyboardHeight * 0.07,
          horizontalGap = keyboardWidth * 0.02;

    this->buttons = new std::vector<MenuButton*>();

    std::string rows[] = {
        "QWERTYUIOP",
        "ASDFGHJKL",
        "ZXCVBNM"
    };
    float offsets[3] = {
        0,
        keyboardWidth * 0.05,
        keyboardWidth * 0.16
    };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < rows[i].length(); j++) {
            auto button = MenuButton::create(std::string(1, rows[i].at(j)),
                                         keyFontSize,
                                         keyWidth,
                                         keyHeight,
                                         CC_CALLBACK_0(KeyboardLayer::none, this));
            button->setPositionX((width / 2) 
                                 + offsets[i] 
                                 + (j * (horizontalGap + keyWidth))
                                 - halfWidth + (horizontalGap / 2));
            button->setPositionY(((3 - (i + 1)) * (keyHeight + verticalGap))
                                 + (height * 0.02) + keyboardY);
            this->addChild(button);
            this->buttons->push_back(button);
        }
    }

    this->bounds = new cocos2d::Rect((width / 2) - keyboardWidth / 2,
                                     keyboardY,
                                     keyboardWidth,
                                     keyboardHeight);


    return true;
}

KeyboardLayer::KeyboardLayer(cocos2d::Rect * gameBounds, float fontSize) {
	// Copy the gamebounds into the local object
	this->gameBounds = gameBounds;
	this->fontSize = fontSize;
}

int KeyboardLayer::indexForPoint(cocos2d::Vec2 * point) {
    for(std::vector<MenuButton *>::size_type i = 0; i != this->buttons->size(); i++) {
        MenuButton * button = (*this->buttons)[i];
        if (button->getBounds()->containsPoint(*point)) {
            return (int) i;
        }
    }
    return -1;
}

/**
 * Checks whether a point is in the keyboard.
 */
bool KeyboardLayer::pointInKeyboard(cocos2d::Vec2 * point) {
    return this->bounds->containsPoint(*point);
}

/**
 * Checks whether the point is in a letter.
 */
bool KeyboardLayer::pointInLetter(cocos2d::Vec2 * point) {
    return this->indexForPoint(point) != -1;
}

/**
 * Gets the string for the letter the point is in.
 */
const std::string KeyboardLayer::getLetter(cocos2d::Vec2 * point) {
    return (*this->buttons)[this->indexForPoint(point)]->getText();
}

}