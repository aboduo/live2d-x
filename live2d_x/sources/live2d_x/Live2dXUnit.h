//
//  Live2dXUnit.h
//  live2d_x
//
//  Created by 血染的玩偶 on 14-4-11.
//  Copyright (c) 2014年 qeeplay.com. All rights reserved.
//

#ifndef __live2d_x__Live2dXUnit__
#define __live2d_x__Live2dXUnit__

#include <iostream>
#include "Live2dXTypes.h"

class Live2dXGrid;

//三角形索引
struct Live2dXTriangle
{
    GLushort first;
    GLushort second;
    GLushort three;
};

class Live2dXNode;
class Live2dXUnit
{
public:
    Live2dXUnit();
    ~Live2dXUnit();
    bool initWithConfig(CCDictionary* config,Live2dXNode*);
    void draw();
private:
    vector<Live2dX_UV> m_all_uv;
    vector<Live2dX_Vertex> m_orgin_vertex;
    vector<Live2dX_Vertex> m_now_vertex;
    vector<Live2dX_Color> m_now_color;
    vector<Live2dXTriangle> m_all_triangle;
    CCTexture2D* m_texture;
    Live2dXGrid* m_grid; //本部件所属的网格曲面
};

#endif /* defined(__live2d_x__Live2dXUnit__) */
