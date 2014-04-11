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

class Live2dXGrid
{
public:
    Live2dXGrid();
    ~Live2dXGrid();
    void visit();
private:
    Live2dXUnit* m_bind_unit;//绑定的部件
    Live2dX_Pos m_grid_handler[8]; //曲面网格的8个手柄端点（4端点，每端点2个）
    Live2dX_Pos m_orgin_point; //本网格在父网格中的初始坐标
    vector<Live2dXGrid*> m_children;
    Live2dXGrid* m_parent;
    Live2dX_Size m_size;
};

#endif /* defined(__live2d_x__Live2dXGrid__) */
