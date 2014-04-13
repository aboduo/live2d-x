//
//  Live2dXUnit.cpp
//  live2d_x
//
//  Created by 血染的玩偶 on 14-4-11.
//  Copyright (c) 2014年 qeeplay.com. All rights reserved.
//

#include "Live2dXUnit.h"

static map<GLuint,int> s_textures;

Live2dXUnit* Live2dXUnit::create(const char* file)
{
//    Live2dXUnit* pRet = new Live2dXUnit();
//    if (pRet && pRet->initWithFile(file))
//    {
//        pRet->autorelease();
//        return pRet;
//    }
//    CC_SAFE_DELETE(pRet);
    return NULL;
}

Live2dXUnit::Live2dXUnit()
:m_texture(0)
,m_grid(NULL)
{
    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("/Users/Sanae/Documents/live2d_x/live2d_x/res/luka_2.png");
    CC_ASSERT(texture);
    m_texture = texture->getName();
    m_all_uv.push_back({0,0});
    m_all_uv.push_back({1,0});
    m_all_uv.push_back({1,1});
    m_all_uv.push_back({0,1});
    
    m_now_vertex.push_back({0,128,0});
    m_now_vertex.push_back({122,128,0});
    m_now_vertex.push_back({122,0,0});
    m_now_vertex.push_back({0,0,0});
    
    m_now_color.push_back({0xff,0xff,0xff,0xff});
    m_now_color.push_back({0xff,0xff,0xff,0xff});
    m_now_color.push_back({0xff,0xff,0xff,0xff});
    m_now_color.push_back({0xff,0xff,0xff,0xff});
    
    m_all_triangle.push_back({0,1,2});
    m_all_triangle.push_back({0,2,3});
    
    
}

Live2dXUnit::~Live2dXUnit()
{
    if (m_texture != 0)
    {
        int count = s_textures[m_texture];
        --count;
        if(count <= 0)
        {
            s_textures.erase(m_texture);
            ccGLDeleteTexture(m_texture);
        }
    }
}

void Live2dXUnit::draw()
{
    if (m_texture == 0)
    {
        return;
    }
#define Live2dX_Vertex_Size sizeof(Live2dX_Vertex)
#define Live2dX_UV_Size sizeof(Live2dX_UV)
#define Live2dX_Color_Size sizeof(Live2dX_Color)
   
    ccGLBindTexture2D( m_texture );

    ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex );
    
    // vertex
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, Live2dX_Vertex_Size, (void*)m_now_vertex.data());
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, Live2dX_UV_Size, (void*)m_all_uv.data());
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, Live2dX_Color_Size, (void*)m_now_color.data());
    
    glDrawElements(GL_TRIANGLES,(GLsizei)m_all_triangle.size()*3, GL_UNSIGNED_SHORT, m_all_triangle.data());
}