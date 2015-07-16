#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ConstUtil.h"
#include "stock/Stock.h"

USING_NS_CC;
USING_NS_CC_EXT;

class RicherPlayer: public Sprite
{
public:
	RicherPlayer();
	~RicherPlayer();

	SpriteFrameCache* player_spriteFrameCache;

	static RicherPlayer* create(char* name, int tag,bool enemy,int money=200000,int strength=100);
	bool init(char* name,int tag, bool enemy,int money,int strength);  
	void startGo(std::vector<int> rowVector,std::vector<int> colVector);

	CC_SYNTHESIZE(Vector<SpriteFrame*>, player_anim_left_vector, Anim_left_vector);
	CC_SYNTHESIZE(Vector<SpriteFrame*>, player_anim_right_vector, Anim_right_vector);
	CC_SYNTHESIZE(Vector<SpriteFrame*>, player_anim_down_vector, Anim_down_vector);
	CC_SYNTHESIZE(Vector<SpriteFrame*>, player_anim_up_vector, Anim_up_vector);
//	CC_SYNTHESIZE(Vector<SpriteFrame*>, player_strength_up_vector, Player_strength_up_vector);

	CC_SYNTHESIZE(Animate* ,left,Left);
	CC_SYNTHESIZE(Animate* ,right, Right);
	CC_SYNTHESIZE(Animate* , down, Down);
	CC_SYNTHESIZE(Animate* ,up,Up);
//	CC_SYNTHESIZE(Animate* ,strength_up,Strength_up);

	void addPlayerAnimation();
	void setPlayerAnimate();

	void addSkillAnimation();
//	void setSkillAnimate();
	CC_SYNTHESIZE(Vector<SpriteFrame*>, skill_rain_vector, Skill_rain_vector);
	CC_SYNTHESIZE(Vector<SpriteFrame*>, skill_transfer_vector, Skill_transfer_vector);

	CC_SYNTHESIZE(Animate* ,rain_skill,RainSkill);
	CC_SYNTHESIZE(Animate* ,transfer_skill, Transfer_skill);

	int restTimes ;
	std::vector<int> lottery_vector;
	Map<int,Stock*> stockMap ;
	std::vector<int> skill_vector;
	float stop_x;
	float stop_y;

private :
	CC_SYNTHESIZE(std::string, _name, Name);
	CC_SYNTHESIZE(int, _money, Money);
	CC_SYNTHESIZE(int, _strength, Strength);
	CC_SYNTHESIZE(bool, _enemy, Enemy);

	CC_SYNTHESIZE(int, _comeFromeRow , ComeFromeRow);
	CC_SYNTHESIZE(int, _comeFromCol, ComeFromCol);

	CC_SYNTHESIZE(bool, _isMyTurn, IsMyTurn);

	CC_SYNTHESIZE(int, _building_1_tiledID, Building_1_tiledID);
	CC_SYNTHESIZE(int, _building_2_tiledID, Building_2_tiledID);
	CC_SYNTHESIZE(int, _building_3_tiledID, Building_3_tiledID);
	char left_animation[20];
	char right_animation[20];
	char down_animation[20];
	char up_animation[20];
//	char strength_up_animation[20];

};

#endif