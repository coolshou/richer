#include "RicherPlayer.h"
#include "RicherGameController.h"
#include "GameBaseScene.h"


RicherGameController* rgController;
RicherPlayer::RicherPlayer()
{
	 _comeFromeRow =-1;
	 _comeFromCol =-1;
	stop_x = -100;
	stop_y =0;
}


RicherPlayer::~RicherPlayer()
{
	 left->release();
	 right->release();
	 down->release();
	 up->release();
//	 strength_up->release();

	 free(left_animation);
	 free(right_animation);
	 free(down_animation);
	 free(up_animation);
	// free(strength_up_animation);
}



RicherPlayer* RicherPlayer::create(char* name,int tag, bool enemy,int money,int strength)
{
	RicherPlayer* player = new RicherPlayer();
	player->init(name, tag,enemy,money,strength);
	player->autorelease();
	return player;

}


bool RicherPlayer::init(char* name, int tag,bool enemy,int money,int strength)
{
	this->setTag(tag);
	addPlayerAnimation();
	SpriteFrame* spf;
	switch(tag)
	{
	case PLAYER_1_TAG:
		{
			spf = player_spriteFrameCache->getSpriteFrameByName("player1_anim_01.png");
			break;
		}
	case PLAYER_2_TAG:
		{
			spf = player_spriteFrameCache->getSpriteFrameByName("player2_anim_02.png");
			break;
		}
	}

	setPlayerAnimate();
	Sprite::initWithSpriteFrame(spf);
	_name = name;
	_enemy = enemy;
	_money = money;
	_strength = strength;
	_isMyTurn = true;
	restTimes = 0;

	memset(left_animation, 0, 20);
	memset(right_animation, 0, 20);
	memset(down_animation, 0, 20);
	memset(up_animation, 0, 20);


	stockMap.insert(0,Stock::create(800100,LanguageString::getInstance()->getLanguageString(RICH_TECHNOLOGY),0,10,0,100));
	stockMap.insert(1,Stock::create(800200,LanguageString::getInstance()->getLanguageString(RICH_TECHNOLOGY),0,20,0,200));
	stockMap.insert(2,Stock::create(800300,LanguageString::getInstance()->getLanguageString(RICH_TECHNOLOGY),0,70,0,800));
	stockMap.insert(3,Stock::create(800400,LanguageString::getInstance()->getLanguageString(RICH_TECHNOLOGY),0,10,0,400));
	stockMap.insert(4,Stock::create(800500,LanguageString::getInstance()->getLanguageString(RICH_TECHNOLOGY),0,0,0,0));

	skill_vector.push_back(1);
	skill_vector.push_back(1);
	skill_vector.push_back(1);
	addSkillAnimation();
	return true;
}


void RicherPlayer::addPlayerAnimation()
{
	player_spriteFrameCache = SpriteFrameCache::getInstance();

	int tag = getTag();
	switch(tag)
	{
	case PLAYER_1_TAG:
		{
			player_spriteFrameCache->addSpriteFramesWithFile(PLAYER1_ANIM_PLIST,PLAYER1_ANIM_PNG);
			break;
		}
	case PLAYER_2_TAG:
		{
			player_spriteFrameCache->addSpriteFramesWithFile(PLAYER2_ANIM_PLIST,PLAYER2_ANIM_PNG);
			break;
		}
	}

//	player_spriteFrameCache->addSpriteFramesWithFile("images/strength_up.plist","images/strength_up.png");

	char name[20];
	memset(name, 0, 20);

	for (int i=1; i<=4; i++) 
	{
		sprintf(name, "player%d_anim_%02d.png",tag,i);
		player_anim_left_vector.pushBack(player_spriteFrameCache->getSpriteFrameByName(name));

	}
	for (int i=5; i<=8; i++) 
	{
		sprintf(name, "player%d_anim_%02d.png",tag,i);
		player_anim_right_vector.pushBack(player_spriteFrameCache->getSpriteFrameByName(name));


	}
	for (int i=9; i<=12; i++) 
	{
		sprintf(name, "player%d_anim_%02d.png",tag,i);
		player_anim_down_vector.pushBack(player_spriteFrameCache->getSpriteFrameByName(name));

	}
	for (int i=13; i<=16; i++) 
	{
		sprintf(name, "player%d_anim_%02d.png",tag,i);
		player_anim_up_vector.pushBack(player_spriteFrameCache->getSpriteFrameByName(name));

	}
	/*
	for (int i=1; i<=14; i++) 
	{
		sprintf(name, "strength_up_%02d.png",i);
		player_strength_up_vector.pushBack(player_spriteFrameCache->getSpriteFrameByName(name));
	}
	*/

}



void RicherPlayer::setPlayerAnimate()
{
	int tag = getTag();
	sprintf(left_animation, "left_animation_%d",tag);
	

	sprintf(right_animation, "right_animation_%d",tag);


	sprintf(down_animation, "down_animation_%d",tag);

	sprintf(up_animation, "up_animation_%d",tag);

//	sprintf(strength_up_animation,"strength_up_animation_%d",tag);

	if(!AnimationCache::getInstance()->getAnimation(left_animation))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(player_anim_left_vector,playerGoPerFrameTime),left_animation);
	}
	if(!AnimationCache::getInstance()->getAnimation(right_animation))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(player_anim_right_vector,playerGoPerFrameTime),right_animation);
	}
	if(!AnimationCache::getInstance()->getAnimation(down_animation))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(player_anim_down_vector,playerGoPerFrameTime),down_animation);
	}
	if(!AnimationCache::getInstance()->getAnimation(up_animation))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(player_anim_up_vector,playerGoPerFrameTime),up_animation);
	}
	/*
	if(!AnimationCache::getInstance()->getAnimation(strength_up_animation))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(player_strength_up_vector,playerGoPerFrameTime),strength_up_animation);
	}
	*/
	 left = Animate::create(AnimationCache::getInstance()->getAnimation(left_animation));
	 right =Animate::create( AnimationCache::getInstance()->getAnimation(right_animation));
	 down =Animate::create(AnimationCache::getInstance()->getAnimation(down_animation));
	 up = Animate::create(AnimationCache::getInstance()->getAnimation(up_animation));
	// strength_up = Animate::create(AnimationCache::getInstance()->getAnimation(strength_up_animation));
	 left->retain();
	 right->retain();
	 down->retain();
	 up->retain();
	// strength_up->retain();
}



void RicherPlayer::startGo(std::vector<int> rowVector,std::vector<int> colVector)
{
	//Blink* blink = Blink::create(0.5,1);
	FadeOut* fadeout = FadeOut::create(0.2);
	FadeIn* fadein = FadeIn::create(0.2);
	GameBaseScene::drawPathColor(rowVector,colVector);
	this->setIsMyTurn(false);
	this->runAction(Sequence::create(fadeout,fadein,CallFunc::create([rowVector,colVector,this](){
			RicherGameController* instance =RicherGameController::getInstance();
			instance->startRealGo(rowVector,colVector,this);
		}
		),NULL));
	
}


void RicherPlayer::addSkillAnimation()
{
	char name[20];
	memset(name, 0, 20);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/rain.plist","images/rain.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/change.plist","images/change.png");
	for (int i=1; i<=19; i++) 
	{
		sprintf(name, "rain_%02d.png",i);
		skill_rain_vector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}

	for (int i=1; i<=32; i++) 
	{
		sprintf(name, "change_%02d.png",i);
		skill_transfer_vector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}
	

	if(!AnimationCache::getInstance()->getAnimation("rain_animation"))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(skill_rain_vector,0.1f),"rain_animation");
	}

	if(!AnimationCache::getInstance()->getAnimation("transfer_animation"))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(skill_transfer_vector,0.1f),"transfer_animation");
	}

	 rain_skill =Animate::create(AnimationCache::getInstance()->getAnimation("rain_animation"));
	 transfer_skill = Animate::create(AnimationCache::getInstance()->getAnimation("transfer_animation"));
	 
	 rain_skill->retain();
	 transfer_skill->retain();

}
