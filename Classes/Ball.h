#pragma once
//上面那句应该只有VC编译器认得！
#include "cocos2d.h"

using namespace cocos2d;

class Ball : public Sprite
{
public:
	//注意init方法返回bool值，重写Node中的init方法
	virtual bool init();

	//如果用户不想自己写create方法（这里也没必要），可以直接使用
	//static Ball* create()
	//{
	//	Ball* b = new Ball();
	//	b->init();
	//	b->autorelease();
	//	return b;
	//}

	CREATE_FUNC(Ball);
};


