#include "PuzzleLayer.h"
#include "SolutionLayer.h"
#include "../nodes/RectRadius.h"
#include "KeyboardLayer.h"

USING_NS_CC;

namespace QUAT {


PuzzleLayer * PuzzleLayer::create(cocos2d::Rect * gameBounds, float fontSize)
{
    PuzzleLayer *pRet = new(std::nothrow) PuzzleLayer(gameBounds, fontSize);
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

bool PuzzleLayer::init() {
	// Init the super class
    if ( !Layer::init() )
    {
        return false;
    }
    
    solutionLayer = QUAT::SolutionLayer::create(gameBounds, fontSize);
    addChild(solutionLayer, 0);

    auto keyboardLayer = QUAT::KeyboardLayer::create(gameBounds, fontSize);
    this->addChild(keyboardLayer); 

	
    return true;
}

PuzzleLayer::PuzzleLayer(cocos2d::Rect * gameBounds, float fontSize) {
	// Copy the gamebounds into the local object
	this->gameBounds = gameBounds;
	this->fontSize = fontSize;
}



}