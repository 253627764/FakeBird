#include "HelloWorldScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemLabel::create(LabelTTF::create("restart", "Arial", 30), CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
		/*MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));*/

    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + visibleSize.height - closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
#if 0

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

	auto b = Ball::create();
	b->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	auto rotateby = RotateBy::create(2.0f, 45.0f);
	auto repeat = RepeatForever::create(rotateby);
	b->runAction(repeat);

	addChild(b);
    
#endif
#if 0
	//TextFieldTTF* textfield = TextFieldTTF::create("����������", "����", 20);
	TextFieldTTF* textfield = TextFieldTTF::textFieldWithPlaceHolder("input here", "consolas", 20);

	textfield->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(textfield);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [textfield](Touch* t, Event* e)
	{
		if (textfield->getBoundingBox().containsPoint(t->getLocation())){
			textfield->attachWithIME();
		}
		else{
			textfield->detachWithIME();
		}
		//��Ҫ
		return false;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, textfield);
#endif
#if 0
	TableView* tv = TableView::create(this, Size(300, 300));
	tv->setDelegate(this);
	//tv->setAnchorPoint(Vec2(0.5, 0.5));
	tv->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	addChild(tv);
#endif
#if 0
	auto menu = Menu::create(MenuItemImage::create("CloseNormal.png", "CloseSelected.png", [](Ref* r){
		MessageBox("close button touched", "Promption");
	}),/*��������Ǳ䳤�ģ�����������������MenuItem*/ NULL);
	//Ĭ����Ӳ˵�����Ļ���м�
	addChild(menu);
#endif

	//��ӱ������ͼƬ
	auto bg = Sprite::create("background.jpg");
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	bg->setScale(0.6f);
	addChild(bg);
	//��ʼ����ֵ����˺��ӵ�
	_bullet = Sprite::create("bullet.png");
	_bullet->setVisible(false);
	addChild(_bullet, 1);
	//��ʼ���÷�Ϊ-1
	_points = -1;
	//���Ͻ���ӷ�����ǩ
	std::string scoreStr("0");
	_scoreLabel = LabelTTF::create(scoreStr, "Arial", 30.0f);
	_scoreLabel->setAnchorPoint(Vec2(0, 1.0f));
	_scoreLabel->setPosition(Vec2(0, visibleSize.height));
	addChild(_scoreLabel, 1);
	//��ʼ�����粢���ü�����
	m_world = new b2World(b2Vec2(0.0f, -14.0f));
	m_world->SetContactListener(this);
	//�����ϰ������ڵ�
	barrerCollection = Node::create();
	addChild(barrerCollection, 0);
	//��ӵذ��С��
	addGround();
	addBird();
	//�Զ���ʼ��Ϸ
	start();

    return true;
}

void HelloWorld::addBird()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	ball = PhysicsSprite::create("bird.png");

	b2BodyDef body_def; //struct
	body_def.type = b2_dynamicBody;
	body_def.position = b2Vec2(visibleSize.width / 2 / PTMRATIO, visibleSize.height / 2 / PTMRATIO);

	auto ball_body = m_world->CreateBody(&body_def);

	b2PolygonShape shape; //class
	shape.SetAsBox(ball->getContentSize().width / 2 / PTMRATIO *3/4, ball->getContentSize().height / 2 / PTMRATIO*3/4);

	b2FixtureDef fixture_def; //struct
	fixture_def.shape = &shape;
	ball_body->CreateFixture(&fixture_def);

	ball->setPTMRatio(PTMRATIO);
	ball->setB2Body(ball_body);
	addChild(ball);
}

void HelloWorld::addGround()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//auto ground = PhysicsSprite::create("ground.png");
	auto ground = Sprite::create("ground.png");


	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2BodyType::b2_staticBody;
	groundBodyDef.position = b2Vec2(visibleSize.width / 2 /PTMRATIO, ground->getContentSize().height / 2 /PTMRATIO);

	auto groundBody = m_world->CreateBody(&groundBodyDef);
	
	b2PolygonShape shape; //class
	shape.SetAsBox(visibleSize.width / 2 / PTMRATIO, ground->getContentSize().height / 2 / PTMRATIO);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	groundBody->CreateFixture(&fixtureDef);

	//ground->setPTMRatio(PTMRATIO);
	//ע�⣺����Body��ʱ��Ӧ��Ĭ���Ƿŵ���ground��ê�㡿����������ԭ�㡣
	//ground->setB2Body(groundBody);
	ground->setName(std::string("ground"));
	addChild(ground);

	//���ˣ�ǰ��Ĵ��뵼��ͼƬ���鱻Ĭ�Ϸŵ���0��0��λ�ö����Ǹ�������position�������ʾ1/4�ŵذ���ͼ��
	ground->ignoreAnchorPointForPosition(true);
	//����Ĵ����õذ����������

}

void HelloWorld::addBarrerPair(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto downBar = PhysicsSprite::create("down_bar.png");
	auto upBar = PhysicsSprite::create("up_bar.png");
	//��������barrer��size��һ����ģ�
	Size barSize = downBar->getContentSize();
	//����2.5�׷�Χ�ڸ���
	float offset = 0 - CCRANDOM_0_1() * 2.5;
	float gap = 2.0f;

	//down
	b2BodyDef barrerBodyDef;
	barrerBodyDef.type = b2BodyType::b2_kinematicBody;
	barrerBodyDef.linearVelocity = b2Vec2(-2.2f, 0.0f);
	barrerBodyDef.position = b2Vec2((visibleSize.width + barSize.width / 2.1) / PTMRATIO, barSize.height / 2 / PTMRATIO + offset);

	auto barrerBody = m_world->CreateBody(&barrerBodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(barSize.width / 2 / PTMRATIO, barSize.height / 2 / PTMRATIO);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	barrerBody->CreateFixture(&fixtureDef);

	downBar->setB2Body(barrerBody);
	downBar->setPTMRatio(PTMRATIO);

	//up
	b2BodyDef barrerBodyDef2;
	barrerBodyDef2.type = b2BodyType::b2_kinematicBody;
	barrerBodyDef2.linearVelocity = b2Vec2(-2.2f, 0.0f);
	barrerBodyDef2.position = b2Vec2((visibleSize.width + barSize.width / 2.1) / PTMRATIO, barSize.height / 2 / PTMRATIO * 3 + offset + gap);
	auto barrerBody2 = m_world->CreateBody(&barrerBodyDef2);

	b2PolygonShape shape2;
	shape2.SetAsBox(barSize.width / 2 / PTMRATIO, barSize.height / 2 / PTMRATIO);

	b2FixtureDef fixtureDef2;
	fixtureDef2.shape = &shape2;
	barrerBody2->CreateFixture(&fixtureDef2);

	upBar->setB2Body(barrerBody2);
	upBar->setPTMRatio(PTMRATIO);

	barrerCollection->addChild(upBar);
	barrerCollection->addChild(downBar);
	//�÷�++
	setPointsOnLabel(++_points);

	if ( _points > 0 && _points % 10 == 0)
	{
		playBulletAction();
	}
	//ɾ�������߽��physicsSprite��
	//removeBarrersOut();
}

void HelloWorld::onEnter()
{
	/*this->*/Layer::onEnter();

}
void HelloWorld::onExit()
{
	Layer::onExit();
	//����ط��д���ȶ��
	if (nullptr != m_world)
	{
		CC_SAFE_DELETE(m_world);
	}
}
void HelloWorld::update(float dt)
{
	m_world->Step(dt, 8, 3);

}

void HelloWorld::BeginContact(b2Contact* contact)
{
	//���Կ�world���ж��ٸ�body���������ɱ�ǩ��ʾ��
	//auto str1 = String::createWithFormat("%d", m_world->GetBodyCount());
	//auto str2 = String::createWithFormat("points : %d", (_points > 0) ? _points : 0);
	//MessageBox(str2->getCString(), str1->getCString());

	unscheduleUpdate();
	unschedule(schedule_selector(HelloWorld::addBarrerPair));
	//ֹͣ�û�������Ӧ
	_eventDispatcher->removeEventListenersForTarget(this);
	//�ذ�ֹͣ����
	auto ground = getChildByName(std::string("ground"));
	do
	{
		CC_BREAK_IF(!ground);
		ground->stopAllActions();
	} while (0);
}

//TableViewCell* HelloWorld::tableCellAtIndex(TableView *table, ssize_t idx)
//{
//	//��ȡ��һ��TableViewCell
//	TableViewCell* cell = table->dequeueCell();
//	LabelTTF* label = NULL;
//
//	if (NULL == cell){
//		cell = TableViewCell::create();
//		label = LabelTTF::create();
//		label->setTag(2);
//		label->setFontSize(30);
//		label->setAnchorPoint(Vec2(0.0f, 0.0f));
//		//Ϊ��ʱΪ��Ԫ�����һ����ǩ
//		cell->addChild(label);
//	}
//	else{
//		label = (LabelTTF*)cell->getChildByTag(2);
//	}
//	label->setString(StringUtils::format("Label %ld", idx));
//	return cell;
//}
//
//ssize_t HelloWorld::numberOfCellsInTableView(TableView *table)
//{
//	//����100����
//	return 100;
//}
//
//void HelloWorld::tableCellTouched(TableView* table, TableViewCell* cell)
//{
//	//LabelTTF* label = (LabelTTF*)table->getChildByTag(2);
//	LabelTTF* label = (LabelTTF*)cell->getChildByTag(2);
//	//MessageBox(label->getString().c_str(), "Promption");
//	log(label->getString().c_str());
//}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    //Director::getInstance()->end();
	restart();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::removeBarrersOut()
{
	for (auto body = m_world->GetBodyList(); body != nullptr; body = body->GetNext())
	{
		auto pos = body->GetPosition();
		if (pos.x < -2.0f)
		{
			auto s = (PhysicsSprite*)body->GetUserData();
			if (nullptr != s)
			{
				s->removeFromParent();
			}
			m_world->DestroyBody(body);
		}
	}
}
void HelloWorld::start()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* t, Event* e){
		//�������ϵ��ٶ�
		this->ball->getB2Body()->SetLinearVelocity(b2Vec2(0, 5.0));
		//����С�����ת
		auto upRotateAction = RotateTo::create(0.3f, 40.0f);
		//auto balanceAction = RotateTo::create(0.1f, 0.0f);
		auto downRotateAciton = RotateTo::create(0.2f, -80.0f);
		this->ball->runAction(Sequence::create(upRotateAction, /*balanceAction,*/ downRotateAciton, nullptr));
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//NOTE:��ײ���̳�b2ContactListener

	//�ذ����
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//��϶
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto ground = getChildByName(std::string("ground"));
	do
	{
		CC_BREAK_IF(!ground);
		auto moveGround = MoveTo::create(0.5f, Vec2(visibleSize.width - ground->getContentSize().width + origin.x * 2, 0));
		auto back = Place::create(Vec2(0, 0));
		auto sequence = Sequence::create(moveGround, back, nullptr);
		auto repeat = RepeatForever::create(sequence);
		ground->runAction(repeat);
	} while (0);

	scheduleUpdate();
	schedule(schedule_selector(HelloWorld::addBarrerPair), 1.2f);
}

void HelloWorld::restart()
{
	auto barrerVector = barrerCollection->getChildren();
	//for each (Node* n in barrerVector)
	//{
	//	PhysicsSprite* ps = (PhysicsSprite*)n;
	//	auto body = ps->getB2Body();
	//	m_world->DestroyBody(body);
	//	n->removeFromParent();
	//}
	//����std::foreach,����
	//ɾ�������ϰ���
	std::_For_each(barrerVector.begin(), barrerVector.end(), [this](Node* n){
		PhysicsSprite* ps = (PhysicsSprite*)n;
		auto body = ps->getB2Body();
		this->m_world->DestroyBody(body);
		n->removeFromParent();
	});
	//���¿�ʼ��Ϸ
	_points = -1;
	setPointsOnLabel(0);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//ball->setPosition(Vec2(visibleSize.width / 2 / PTMRATIO, visibleSize.height / 2 / PTMRATIO));
	//�����ٶȹ��㣬λ�÷��м䣬������
	ball->getB2Body()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	ball->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	ball->setRotation(0.0f);
	
	start();
}

void HelloWorld::setPointsOnLabel(int score)
{
	if (nullptr != _scoreLabel)
	{
		std::stringstream stream;
		stream << score;
		_scoreLabel->setString(stream.str());
	}
}

void HelloWorld::playBulletAction()
{
	if (nullptr == _bullet)
	{
		return;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size bulletSize = _bullet->getContentSize();

	_bullet->setPosition(Vec2(visibleSize.width + bulletSize.width, visibleSize.height / 2 + bulletSize.height));
	_bullet->setVisible(true);
	auto move = MoveTo::create(1.0f, Vec2(0 - bulletSize.width, visibleSize.height / 2 + bulletSize.height));
	_bullet->runAction(move);
}