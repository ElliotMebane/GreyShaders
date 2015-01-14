#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
private:
	struct ShaderDataProvider {
		ShaderDataProvider(const std::string& pLabel, const std::string& pPath) :
		    label(pLabel), path(pPath) {}

		std::string label;
		std::string path;
	};
	const float _kCornerTapFactor = 0.5f;
	std::vector< GLProgramState* > _shaderProgramStates;
	Sprite* _spriteWithShader;
	int _shaderIndex;
	EventListenerTouchOneByOne* _gestureStageTouch;
	Size _visibleSize;
	GLProgramState* _defaultShaderProgramState;
	LabelTTF* _label;
	std::string _defaultTitle;
	std::vector< ShaderDataProvider > _shaderData;

	GLProgramState* _makeShaderProgramState( std::string pRelativePath );
	void _setNextShader( const int pSelector );
	void _makeGestureControls();

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
