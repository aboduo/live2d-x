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

#include "cocos2d.h"
using namespace cocos2d;

typedef ccTex2F Live2dX_UV;
typedef ccColor4B Live2dX_Color;
typedef ccVertex3F Live2dX_Vertex;

#define floatAtArray(index,array) ((CCString*)array->objectAtIndex(index))->floatValue()
#define intAtArray(index,array) ((CCString*)array->objectAtIndex(index))->intValue()

struct Live2dX_Triangle
{
    int point[3];
};//point_n是Live2dX_Unit中，points里Live2dXOriginPoint的Index

typedef list<Live2dX_Triangle> Live2dX_TriangleList;

enum Live2dX_Unit_Animation_Type
{
    Live2dX_Unit_Animation_Position = 0,
};

struct Live2dX_Unit_Animation_KeyFrame
{
    float time;
    CCObject* value;
};

struct Live2dX_Unit_Animation
{
    Live2dX_Unit_Animation_Type type;
    Live2dX_Unit_Animation_KeyFrame start;
    Live2dX_Unit_Animation_KeyFrame end;
};

typedef list<Live2dX_Unit_Animation> Live2dX_Unit_Animations;

struct Live2dX_Unit
{
    vector<Live2dX_UV> uvs;
    vector<Live2dX_Vertex> defaults;
    list<Live2dX_Triangle> triangles;
    map<string,Live2dX_Unit_Animations> animations;
};

struct Live2dX_Animation
{
    string unit_name;
    string anim_name;
    float time;
    float delay;
};

typedef list<Live2dX_Animation> Live2dX_Animations;

struct Live2dX_Config
{
    float width;
    float height;
    map<string,Live2dX_Unit> unit_list;
    map<string,Live2dX_Animations> animation;
};

struct Live2dX_UnitID
{
    int begin_index;
    int end_index;
};


#endif
