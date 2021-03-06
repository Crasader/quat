#ifndef __TIMED_LAYER_H__
#define __TIMED_LAYER_H__

#include <sstream>

#include "cocos2d.h"
#include "../Constants.h"

#include "TimedCard.h"
#include "DrawnBanner.h"
#include "IconMenuButton.h"
#include "../models/Game.h"
#include "../models/TimeUtils.h"
#include "../solver/input/BorderedWordNode.h"

namespace QUAT {

USING_NS_CC;

class TimedLayer : public cocos2d::Layer
{
private:
  float fontSize,
  // The size of the card that displays information about
  // the user's endless mode progress
        sectionWidth,
        sectionHeight;

  BorderedWordNode * raceText;

  // Timed Mode header
	cocos2d::Label * time2Label,
                 * time4Label,
                 * time8Label;

  // The banners to display the ranks
  DrawnBanner * rank2Banner,
              * rank4Banner,
              * rank8Banner;


  // Shows progress information
  TimedCard * card;

public:
  IconMenuButton * playButton,
                 * continueTopButton,
                 * restartButton;

	virtual bool init();

	TimedLayer(float fontSize,
             float sectionWidth,
             float sectionHeight);

  void updateFromModel(Game * game);

	static TimedLayer * create(float fontSize,
                             float sectionWidth,
                             float sectionHeight);
};

}
#endif // __TIMED_LAYER_H__

