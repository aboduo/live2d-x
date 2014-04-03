//
//  Live2dXSprite.h
//  live2d_x
//
//  Created by 血染的玩偶 on 14-4-1.
//  Copyright (c) 2014年 qeeplay.com. All rights reserved.
//

#ifndef __live2d_x__Live2dXSprite__
#define __live2d_x__Live2dXSprite__

#include <iostream>
#include "Live2dXTypes.h"

class Live2dXSprite: public CCSprite
{
public:
    Live2dXSprite();
    ~Live2dXSprite();
    static Live2dXSprite* create(const char* pictruePath, const char* configPath);
    
public:
    bool initWithFile(const char* pictruePath, const char* configPath);
    bool initWithConfig(const char* pictruePath,CCDictionary* config);
    void draw();
private:
    void convertDictToConfig(CCDictionary* config);
    
private:
    vector<Live2dX_UV> m_orginUV;//所有坐标位于贴图的多少百分比位置，先按照部件在map中的位置排序，同一部件内的坐标按照id排序
    vector<Live2dX_Color> m_orginColor;//所有坐标位于贴图的多少百分比位置，先按照部件在map中的位置排序，同一部件内的坐标按照id排序
    vector<Live2dX_Vertex> m_orginVertex;//所有坐标当前位于画布的坐标（左下角对齐），先按照部件在map中的位置排序，同一部件内的坐标按照id排序
    vector<Live2dX_Vertex> m_nowVertex;//所有坐标当前位于画布的坐标（左下角对齐），先按照部件在map中的位置排序，同一部件内的坐标按照id排序
    map<string,Live2dX_TriangleList> m_all_units;//所有部件，Live2dX_TriangleList是三角形ID列表
    CCSize m_baseSize;
};

#endif /* defined(__live2d_x__Live2dXSprite__) */
