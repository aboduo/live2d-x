//
//  Live2dXUnit.cpp
//  live2d_x
//
//  Created by 血染的玩偶 on 14-4-11.
//  Copyright (c) 2014年 qeeplay.com. All rights reserved.
//

#include "Live2dXUnit.h"
#include "Live2dXNode.h"

static map<GLuint,int> s_textures;


Live2dXUnit::Live2dXUnit()
:m_texture(0)
,m_grid(NULL)
{
}

Live2dXUnit::~Live2dXUnit()
{
    CC_SAFE_RELEASE(m_texture);
}

bool Live2dXUnit::initWithConfig(CCDictionary* config,Live2dXNode* orginNode)
{
    int textureid = config->valueForKey("texture")->intValue();
    m_texture = orginNode->m_textures[textureid];
    m_texture->retain();
    typeAt(CCArray, uv, config);
    typeAt(CCArray, vertex, config);
    for (int i = 0; i < uv->count(); ++i)
    {
        CCArray* pos = (CCArray*)uv->objectAtIndex(i);
        float u = ((CCString*)pos->objectAtIndex(0))->floatValue();
        float v = ((CCString*)pos->objectAtIndex(1))->floatValue();
        m_all_uv.push_back({u,v});
        
        CCArray* ver = (CCArray*)vertex->objectAtIndex(i);
        float x = ((CCString*)ver->objectAtIndex(0))->floatValue();
        float y = ((CCString*)ver->objectAtIndex(1))->floatValue();
        m_now_vertex.push_back({x,y,0});
        m_now_color.push_back(ccc4(0xff, 0xff, 0xff, 0xff));
    }
    typeAt(CCArray, triangle, config);
    for (int i = 0; i < triangle->count(); ++i)
    {
        CCArray* tri = (CCArray*)triangle->objectAtIndex(i);
        int i_0 = ((CCString*)tri->objectAtIndex(0))->intValue();
        int i_1 = ((CCString*)tri->objectAtIndex(1))->intValue();
        int i_2 = ((CCString*)tri->objectAtIndex(2))->intValue();
        m_all_triangle.push_back({(GLushort)i_0,(GLushort)i_1,(GLushort)i_2});
    }
    return true;
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
   
    ccGLBindTexture2D( m_texture->getName() );

    ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex );
    
    // vertex
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, Live2dX_Vertex_Size, (void*)m_now_vertex.data());
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, Live2dX_UV_Size, (void*)m_all_uv.data());
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, Live2dX_Color_Size, (void*)m_now_color.data());
    
    glDrawElements(GL_TRIANGLES,(GLsizei)m_all_triangle.size()*3, GL_UNSIGNED_SHORT, m_all_triangle.data());
}