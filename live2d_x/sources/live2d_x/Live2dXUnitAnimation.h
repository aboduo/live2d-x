//
//  Live2dXUnitAnimation.h
//  live2d_x
//
//  Created by 血染的玩偶 on 14-4-13.
//  Copyright (c) 2014年 qeeplay.com. All rights reserved.
//

#ifndef __live2d_x__Live2dXUnitAnimation__
#define __live2d_x__Live2dXUnitAnimation__

#include <iostream>
#include "Live2dXTypes.h"

enum Live2dXUnitAxisType
{
    Live2dXUnitAxisX = 0,
    Live2dXUnitAxisY,
    Live2dXUnitAxisXY,
};

class Live2dXUnitAnimation
{
public:
    Live2dXUnitAnimation();
    ~Live2dXUnitAnimation();
private:
    Live2dXUnitAxisType m_type;
    vector<Live2dX_Vertex> m_vertex[9];
    
};


#endif /* defined(__live2d_x__Live2dXUnitAnimation__) */
