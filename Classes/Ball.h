#pragma once
//�����Ǿ�Ӧ��ֻ��VC�������ϵã�
#include "cocos2d.h"

using namespace cocos2d;

class Ball : public Sprite
{
public:
	//ע��init��������boolֵ����дNode�е�init����
	virtual bool init();

	//����û������Լ�дcreate����������Ҳû��Ҫ��������ֱ��ʹ��
	//static Ball* create()
	//{
	//	Ball* b = new Ball();
	//	b->init();
	//	b->autorelease();
	//	return b;
	//}

	CREATE_FUNC(Ball);
};


