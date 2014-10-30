#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h" //libExtention
#include "box2d\box2d.h" //libBox2d

USING_NS_CC;
USING_NS_CC_EXT;

class HelloWorld : public cocos2d::Layer, b2ContactListener /*,TableViewDataSource, TableViewDelegate*/
{

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	//方便用户快速创建create方法，create方法是cocos中类的一个约定方法。最重要的是其中autorelease操作。
    CREATE_FUNC(HelloWorld);

	virtual void onEnter() override;
	virtual void onExit() override;
	virtual void update(float dt) override;

private:
	virtual void BeginContact(b2Contact* contact) override;

private:
	void addBird();
	void addGround();
	void addBarrerPair(float dt);
	void removeBarrersOut();
	void start();
	void restart();
	void setPointsOnLabel(int score);

	void playBulletAction();

private:
	const float PTMRATIO = 48.0f;

	int _points;
	LabelTTF* _scoreLabel;
	b2World* m_world;
	PhysicsSprite* ball;
	Node* barrerCollection;

	Sprite* _bullet;

//public:
//	//重写TableViewDataSource类中一些方法
//	/**
//	* cell height for a given table.
//	* 指定表格单元高度
//	* @param table table to hold the instances of Class
//	* @return cell size
//	*/
//	virtual Size cellSizeForTable(TableView *table) {
//		//return Size::ZERO;
//		return Size(300, 50);
//	};
//	/**
//	* a cell instance at a given index
//	* 指定索引的单元实例
//	* @param idx index to search for a cell
//	* @return cell found at idx
//	*/
//	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
//	/**
//	* Returns number of cells in a given table view.
//	* 指定表视图中有多少单元
//	* @return number of cells
//	*/
//	virtual ssize_t numberOfCellsInTableView(TableView *table);
//public:
//	/**
//	* Delegate to respond touch event
//	* 表单元格被触摸
//	* @param table table contains the given cell
//	* @param cell  cell that is touched
//	* @js NA
//	* @lua NA
//	*/
//	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
};

#endif // __HELLOWORLD_SCENE_H__
