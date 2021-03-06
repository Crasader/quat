#ifndef __TIMED_TRANSITION_LAYER_H__
#define __TIMED_TRANSITION_LAYER_H__

#include "cocos2d.h"
#include "../Constants.h"
#include "../nodes/CircleNode.h"
#include "../nodes/IconNode.h"
#include "../models/Game.h"
#include "../models/TimeUtils.h"
#include "../menu/BannerButton.h"
#include "../GameStateController.h"

USING_NS_CC;
namespace QUAT {

#define TRANS_SECS 3

class TimedTransitionLayer : public cocos2d::Layer
{
private:
  // The bounds of the game client
  cocos2d::Rect * gameBounds;

  // Animates a countdown to get the user ready
  CircleNode * circle;

  // The text that sits in the middle of the circle
	cocos2d::Label * topText,
                 * bottomText,
                 * scoreText;

  IconNode * star;
  
  // The amount of time remaining on the countdown.
  float timeLeft;

	// Controls the entire game so we can move to other screens
	GameStateController * GSC;

  // Pointer to the game model so we can take input and manipulate it
  Game * game;

  // Buttons that let the user control the rank they want to go to
  BannerButton * rank2Button,
               * rank4Button,
               * rank8Button;
  
  void handleRankClick(int button);

public:
  // Callbacks for each rank button
  void rankButtonCallback2();
  void rankButtonCallback4();
  void rankButtonCallback8();

  // Updates the layer from the game model
  void updateFromModel();

	/**
	 * Initialize the background layer.
	 * @return Whether or not the layer was initialized successfully.
	 */
	virtual bool init();

  void reset();

	TimedTransitionLayer(cocos2d::Rect * gameBounds,
                       Game * game,
                       GameStateController * GSC);

	static TimedTransitionLayer * create(cocos2d::Rect * gameBounds,
                                       Game * game,
                                       GameStateController * GSC);
  
  void update(float delta) override;
};

}

#endif // __TIMED_TRANSITION_LAYER_H__
