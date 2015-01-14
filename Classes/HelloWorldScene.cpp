#include "HelloWorldScene.h"

USING_NS_CC;

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
    
	_shaderIndex = 0;
	_defaultTitle = "Greyscale Shader Samples\nTap the Top-Left/Top-Right to Change Shader.\nTap Bottom to Show Full Color.";

    _visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + _visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL, nullptr );
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    _label = LabelTTF::create( _defaultTitle, "Arial", 32);
    _label->enableStroke( Color3B( 0, 0, 1.0 ), 4, true );
    _label->enableShadow( Size( 4.0, -4.0 ), 1.0, 5.0, true );

    // position the label on the center of the screen
    _label->setPosition(Vec2(origin.x + _visibleSize.width/2,
                            origin.y + _visibleSize.height - _label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild( _label, 1 );

    ////////////////////////

    // Sprite with shader applied
        _spriteWithShader = Sprite::create( "PDITestImage_1280portrait.jpg" );
        _spriteWithShader->setScale( MIN( _visibleSize.width / _spriteWithShader->getContentSize().width, _visibleSize.height / _spriteWithShader->getContentSize().height ) );
        _spriteWithShader->setPosition( Vec2( origin.x + _spriteWithShader->getBoundingBox().size.width / 2, origin.y + _spriteWithShader->getBoundingBox().size.height / 2 ) );
        this->addChild( _spriteWithShader );

        //http://www.roguish.com/blog/?p=775
        ShaderDataProvider tData[] {
        			ShaderDataProvider( "1: Basic\n0.333, 0.333, 0.333", "shaders/LuminanceEqualWeight.fsh" ),
        			ShaderDataProvider( "2: Basic\n0.212655, 0.715158, 0.072187", "shaders/LuminanceA.fsh" ),
        			ShaderDataProvider( "3: Square/sqrt\n0.212655, 0.715158, 0.072187", "shaders/LuminanceAA.fsh" ),
        			ShaderDataProvider( "4: Basic\n0.299, 0.587, 0.114", "shaders/LuminanceB.fsh" ),
        			ShaderDataProvider( "5: Square/sqrt\n0.299, 0.587, 0.114", "shaders/LuminanceBB.fsh" ),
        			ShaderDataProvider( "6: Gamma Inverse/Re-Apply\n0.212655, 0.715158, 0.072187", "shaders/LuminanceC.fsh" ),
        			ShaderDataProvider( "7: Gamma Inverse/Re-Apply\n0.299, 0.587, 0.114", "shaders/LuminanceCC.fsh" )
        };

        // populate _shaderData from the tData array
        // http://www.cplusplus.com/reference/vector/vector/vector/
        // location of start of array, location of start of array + number of elements in array
        // (end? how is the size of each element taken into account?) I think with arrays, adding ints adds bytes of the length of one element in the array.
        // http://stackoverflow.com/questions/8906545/how-to-initialize-a-vector-in-c
//        _shaderData = std::vector< ShaderDataProvider > ( tData, tData + sizeof( tData ) / sizeof( ShaderDataProvider ) );
        // this works: std::begin(tData), std::end(tData)
        // we're forcing the array created with [] syntax to be seen as a std::array container, with begin/end methods
        _shaderData = std::vector< ShaderDataProvider >( std::begin(tData), std::end(tData) );
        // doesn't work. array doesn't seem to have begin/end methods, though it should:
        // http://www.cplusplus.com/reference/array/array/?kw=array
        // oh, ... This class merely adds a layer of member and global functions to it, so that arrays can be used as standard containers.
        // still, can't instatntiate a std::array
        //         // http://stackoverflow.com/questions/14178264/c11-correct-stdarray-initialization
        // std::vector< ShaderDataProvider > _shaderData( tData.begin(), tData.end() );

//        _shaderData.push_back ( ShaderDataProvider( "1: Basic 0.212655, 0.715158, 0.072187", "shaders/LuminanceA.fsh" ) );
//        _shaderData.push_back ( ShaderDataProvider( "2: Basic 0.212655, 0.715158, 0.072187", "shaders/LuminanceAA.fsh" ) );
//        _shaderData.push_back ( ShaderDataProvider( "3: Basic 0.212655, 0.715158, 0.072187", "shaders/LuminanceB.fsh" ) );
//        _shaderData.push_back ( ShaderDataProvider( "4: Basic 0.212655, 0.715158, 0.072187", "shaders/LuminanceBB.fsh" ) );
//        _shaderData.push_back ( ShaderDataProvider( "5: Basic 0.212655, 0.715158, 0.072187", "shaders/LuminanceC.fsh" ) );

        auto it = _shaderData.begin();
        auto itEnd = _shaderData.end();
        for (; it != itEnd; it++ )
		{
        	_shaderProgramStates.push_back( _makeShaderProgramState( it->path ) );
		}

        _defaultShaderProgramState = _makeShaderProgramState( "shaders/NoEffectShader.fsh" );

    	_setNextShader( 0 );

    	_makeGestureControls();

//    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create("HelloWorld.png");
//
//    // position the sprite on the center of the screen
//    sprite->setPosition(Vec2(_visibleSize.width/2 + origin.x, _visibleSize.height/2 + origin.y));
//
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
    
    return true;
}

GLProgramState* HelloWorld::_makeShaderProgramState( std::string pRelativePath )
{
    // Load the external shader file into the application as a CString cast as a GLchar*. Note that the ChannelSwap.fsh shader file can be found in the Resources/shaders folder of our project.
	 	 GLchar * fragmentSource = (GLchar*) String::createWithContentsOfFile( FileUtils::getInstance()->fullPathForFilename( pRelativePath ).c_str() )->getCString();
	// Create a GLProgram with the shader file.
	 	 auto p = GLProgram::createWithByteArrays( ccPositionTextureColor_noMVP_vert, fragmentSource );
	// Create a GLProgramState from the GLProgram.
	 	 GLProgramState* glProgramState = GLProgramState::getOrCreateWithGLProgram( p );
	// These shaders expect the texture to be passed manually.
	 	 glProgramState->setUniformTexture( "u_texture", _spriteWithShader->getTexture() );

	 	 return glProgramState;
}

void HelloWorld::_setNextShader( const int pSelector )
{
	if( pSelector == 0 )
	{
		if( _spriteWithShader->getGLProgramState() != _defaultShaderProgramState )
		{
			_spriteWithShader->setGLProgramState( _defaultShaderProgramState );
			_label->setString( _defaultTitle );
		}
		else
		{
			_spriteWithShader->setGLProgramState( _shaderProgramStates[ _shaderIndex ] );
			_label->setString( _shaderData[ _shaderIndex ].label );
		}
	}
	else
	{
		_shaderIndex += pSelector;
		if( _shaderIndex == _shaderProgramStates.size() )
		{
			_shaderIndex = 0;
		}
		else if( _shaderIndex < 0 )
		{
			_shaderIndex = _shaderProgramStates.size() - 1;
		}
		_spriteWithShader->setGLProgramState( _shaderProgramStates[ _shaderIndex ] );
		_label->setString( _shaderData[ _shaderIndex ].label );
	}
}

void HelloWorld::_makeGestureControls()
{
    _gestureStageTouch = EventListenerTouchOneByOne::create();
    _gestureStageTouch->setSwallowTouches( true );

    _gestureStageTouch->onTouchBegan = [=]( Touch* touch, Event* event )
    {
    	Vec2 tTouchLocation = touch->getLocation();
    	// TR
    	if( tTouchLocation.x > _visibleSize.width * ( 1.0f - _kCornerTapFactor) && tTouchLocation.y > _visibleSize.height * ( 1.0f - _kCornerTapFactor ) )
    	{
    		_setNextShader( 1 );
		}
    	// TL
    	else if( tTouchLocation.x < _visibleSize.width * _kCornerTapFactor &&
    	    	tTouchLocation.y > _visibleSize.height * ( 1.0f - _kCornerTapFactor ) )
		{
    		_setNextShader( -1 );
		}
    	// BL/BR
    	// No X-test. BL/BR respond the same
		else if( tTouchLocation.y < _visibleSize.height * _kCornerTapFactor )
		{
			_setNextShader( 0 );
		}

        return true;
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority( _gestureStageTouch, this );
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
