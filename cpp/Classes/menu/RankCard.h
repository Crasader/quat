#ifndef __RANK_CARD_H__
#define __RANK_CARD_H__

#include "cocos2d.h"
#include "../Constants.h"
#include "DrawnBanner.h"
#include "../nodes/RectRadius.h"
#include "../models/Game.h"
#include "../nodes/ProgressBar.h"

namespace QUAT {

class RankCard : public cocos2d::Layer
{
private:
	float fontSize,
		  _width,
		  _height,
      borderRadius,
      borderWidth;

	cocos2d::Label * leftLabel,
                 * rightLabel;

	cocos2d::Color4B * defaultColor,
                  * fillInColor;

	RectRadius * border;
  ProgressBar * progress;
  DrawnBanner * drawnBanner;

  // The width of the experience progress
  // bar
  float progressBarWidth;

public:
	virtual bool init();

	RankCard(float fontSize,
			   float width,
			   float height);
  
  float getBorderRadius();
  float getBorderWidth();

  void displayRank(int currentRank);

  // Sets the filled % of the progress bar we use for
  // showing rank progress
	void setProgressPercent(float percent);
 
  void updateFromModel(Game * game);

	static RankCard * create(float fontSize,
							   float width,
							   float height);
};

}
#endif // __RANK_CARD_H__
