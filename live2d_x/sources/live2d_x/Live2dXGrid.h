//
//  Live2dXGrid.h
//  live2d_x
//
//  Created by 血染的玩偶 on 14-4-11.
//  Copyright (c) 2014年 qeeplay.com. All rights reserved.
//

#ifndef __live2d_x__Live2dXGrid__
#define __live2d_x__Live2dXGrid__

#include <iostream>
#include "Live2dXUnit.h"
#include "Live2dXUnitAnimation.h"

class Live2dXNode;
class Live2dXGrid:public CCNode
{
public:
    Live2dXGrid();
    ~Live2dXGrid();
    static Live2dXGrid* create(CCDictionary* config,Live2dXNode* orginNode);
    bool initWithConfig(CCDictionary* config,Live2dXNode* orginNode);
    void draw();
private:
    Live2dX_Pos m_grid_handler[8]; //曲面网格的8个手柄端点（4端点，每端点2个）
    Live2dXUnit* m_bind_unit;
    int m_width_count; //宽的网格数
    int m_height_count; //高的网格数
    vector<Live2dXUnitAnimation*> m_all_unit_animations;
//    friend class Live2dXNode;
};

#endif /* defined(__live2d_x__Live2dXGrid__) */
