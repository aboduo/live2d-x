//
//  Live2dXTypes.h
//  live2d_x
//
//  Created by 血染的玩偶 on 14-4-1.
//  Copyright (c) 2014年 qeeplay.com. All rights reserved.
//

#ifndef live2d_x_Live2dXTypes_h
#define live2d_x_Live2dXTypes_h

#include <list>
#include <vector>
#include <map>
using namespace std;

#ifndef __QT__
#include "cocos2d.h"
using namespace cocos2d;
#else

#include "../../../live2d_x_editor/cocos2d/CCTypes.h"
#include "../../../live2d_x_editor/cocos2d/CCString.h"
#include "../../../live2d_x_editor/cocos2d/CCSprite.h"
#include "../../../live2d_x_editor/cocos2d/CCDictionary.h"
#include "../../../live2d_x_editor/cocos2d/CCTime.h"

#endif

typedef CCPoint Live2dX_Pos;
typedef CCSize Live2dX_Size;
typedef ccTex2F Live2dX_UV;
typedef ccColor4B Live2dX_Color;
typedef ccVertex3F Live2dX_Vertex;

#define floatAtArray(index,array) ((CCString*)array->objectAtIndex(index))->floatValue()
#define intAtArray(index,array) ((CCString*)array->objectAtIndex(index))->intValue()

struct Live2dX_Triangle
{
    int point[3];
    int orginPoint[3];
};//point_n是Live2dX_Unit中，points里Live2dXOriginPoint的Index

typedef vector<Live2dX_Triangle> Live2dX_TriangleList;

enum Live2dX_Animation_Type
{
    Live2dX_Animation_Position = 0,
};

struct Live2dX_Unit_Anim_Pos
{
    float x;
    float y;
    float x_moveBy;
    float y_moveBy;
};

struct Live2dX_Unit_Anim
{
    Live2dX_Animation_Type type;
    float start_perc;
    float end_perc;
    int anim_id;
};

typedef list<Live2dX_Unit_Anim> Live2dX_Unit_Anims;

struct Live2dX_Anim
{
    Live2dX_Unit_Anims* anim;
    string unit_name;
    float delay;
    float time;
};

typedef list<Live2dX_Anim> Live2dX_Anims;


#endif
