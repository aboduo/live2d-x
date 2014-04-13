//
//  Live2dXSprite.cpp
//  live2d_x
//
//  Created by 血染的玩偶 on 14-4-1.
//  Copyright (c) 2014年 qeeplay.com. All rights reserved.
//

#include "Live2dXSprite.h"

Live2dXSprite::Live2dXSprite()
:m_isAnimation(false)
{

}

Live2dXSprite::~Live2dXSprite()
{

}

Live2dXSprite* Live2dXSprite::create(const char* pictruePath, const char* configPath)
{
    Live2dXSprite *pobSprite = new Live2dXSprite();
    if (pobSprite && pobSprite->initWithFile(pictruePath,configPath))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

bool Live2dXSprite::initWithFile(const char* pictruePath, const char* configPath)
{
    bool ret = CCSprite::initWithFile(pictruePath);
    if(ret)
    {
        return initWithConfig(configPath);
    }
    return false;
}

bool Live2dXSprite::initWithConfig( const char* configPath)
{
    CCDictionary* dict = CCDictionary::createWithContentsOfFile(configPath);
    if(dict)
    {
        convertDictToConfig(dict);
        return true;
    }
    return false;
}

void Live2dXSprite::draw()
{
    if(!m_pobTexture)
    {
        return;
    }
    if(m_isAnimation)
    {
        cc_timeval nowTime;
        CCTime::gettimeofdayCocos2d(&nowTime, NULL);
        float deltime = (float)(nowTime.tv_sec - m_nowTime.tv_sec) + (float)(nowTime.tv_usec - m_nowTime.tv_usec)/1000000.0f;
        m_nowTime = nowTime;
        animationUpdate(deltime);
//        animationUpdate(1/30.0f);
    }
#define Live2dX_Vertex_Size sizeof(Live2dX_Vertex)
#define Live2dX_UV_Size sizeof(Live2dX_UV)
#define Live2dX_Color_Size sizeof(Live2dX_Color)
    
#ifndef __QT__
    CC_PROFILER_START_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");
    
    CCAssert(!m_pobBatchNode, "If CCSprite is being rendered by CCSpriteBatchNode, CCSprite#draw SHOULD NOT be called");
    
    CC_NODE_DRAW_SETUP();
    
    ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );
    
    ccGLBindTexture2D( m_pobTexture->getName() );
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );

    
    // vertex
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, Live2dX_Vertex_Size, (void*)m_nowVertex.data());
    
    // texCoods
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, Live2dX_UV_Size, (void*)m_orginUV.data());
    
    // color
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, Live2dX_Color_Size, (void*)m_orginColor.data());
    
    
    glDrawArrays(GL_TRIANGLES, 0, (int)m_nowVertex.size());
    
    CHECK_GL_ERROR_DEBUG();
    
    CC_INCREMENT_GL_DRAWS(1);
    
    CC_PROFILER_STOP_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");
#else
    
    glTranslatef(-0.5f,0,0);
    glEnable(GL_BLEND);
    
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,m_pobTexture->m_name);
    
    for(int i = 0; i < m_nowVertex.size();i+=3)
    {
        float a,b;
        glBegin(GL_TRIANGLES);
        glColor4f(1,1,1,1);
        glTexCoord2f(m_orginUV[i].u,1-m_orginUV[i].v);
        a = m_nowVertex[i].x * 2 / m_baseSize.width - 1;
        b = m_nowVertex[i].y * 2 / m_baseSize.height-1;
        glVertex3f(a,b,0);
        glColor4f(1,1,1,1);
        glTexCoord2f(m_orginUV[i+1].u,1-m_orginUV[i+1].v);
        a = m_nowVertex[i+1].x * 2 / m_baseSize.width - 1;
        b = m_nowVertex[i+1].y * 2 / m_baseSize.height-1;
        glVertex3f(a,b,0);
        glColor4f(1,1,1,1);
        glTexCoord2f(m_orginUV[i+2].u,1-m_orginUV[i+2].v);
        a = m_nowVertex[i+2].x * 2 / m_baseSize.width - 1;
        b = m_nowVertex[i+2].y * 2 / m_baseSize.height-1;
        glVertex3f(a,b,0);
        glColor4f(1,1,1,1);
        glEnd();
    }
#endif
}

void Live2dXSprite::runAnimation(string name)
{
    map<string, Live2dX_Anims>::iterator iter = m_all_anims.find(name);
    CC_ASSERT(iter != m_all_anims.end());
    m_animNowTime = 0;
    m_nowVertex = m_orginVertex;
    m_animTime = 0;
    
    m_curAnims = &iter->second;
    for (Live2dX_Anims::iterator iter2 = m_curAnims->begin();
         iter2 != m_curAnims->end(); ++iter2)
    {
        float time = iter2->delay+iter2->time;
        if (time > m_animTime)
        {
            m_animTime = time;
        }
    }
    CCTime::gettimeofdayCocos2d(&m_nowTime, NULL);
    m_isAnimation = true;
}

void Live2dXSprite::animationUpdate(float time)
{
    m_animNowTime += time;
    if (m_animNowTime >= m_animTime) {
        m_animNowTime = m_animTime;
        m_isAnimation = false;
    }
//    CCLOG("=========");
    for (Live2dX_Anims::iterator anim = m_curAnims->begin();
         anim != m_curAnims->end(); ++anim)
    {
        float p = (m_animNowTime - anim->delay)/(m_animTime - anim->delay);
        for (Live2dX_Unit_Anims::iterator unit_anim = anim->anim->begin();
             unit_anim != anim->anim->end(); ++unit_anim)
        {
            float t = (p - unit_anim->start_perc)/(unit_anim->end_perc - unit_anim->start_perc);
            if (p >= unit_anim->start_perc && p <= unit_anim->end_perc)
            {
                switch (unit_anim->type)
                {
                    case Live2dX_Animation_Position:
                    {
                        map<int,Live2dX_Unit_Anim_Pos>& position = m_all_point_move[unit_anim->anim_id];
                        for (map<int,Live2dX_Unit_Anim_Pos>::iterator pos = position.begin();
                             pos != position.end(); ++pos)
                        {
                            int pos_id = pos->first;
                            float x = pos->second.x + pos->second.x_moveBy*t;
                            float y = pos->second.y + pos->second.y_moveBy*t;
                            Live2dX_TriangleList& tlist = m_all_units[anim->unit_name];
                            for (Live2dX_TriangleList::iterator iter3 = tlist.begin(); iter3 != tlist.end(); ++iter3)
                            {
                                Live2dX_Triangle& trian = *iter3;
                                for (int i = 0; i < 3; ++i)
                                {
                                    if (trian.orginPoint[i] == pos_id)
                                    {
                                        Live2dX_Vertex value = {x,y,0};
                                        m_nowVertex[trian.point[i]] = value;
//                                        CCLOG("%d:%f,%f",trian.point[i],x,y);
                                    }
                                }
                            }
                        }
                    }
                        break;
                        
                    default:
                        break;
                }
            }
        }
    }
}

void Live2dXSprite::convertDictToConfig(CCDictionary* config)
{
    CCDictionary* property = (CCDictionary*)config->objectForKey("property");
    m_baseSize.width = property->valueForKey("width")->intValue();
    m_baseSize.height = property->valueForKey("height")->intValue();
    
    CCDictionary* unit_list = (CCDictionary*)config->objectForKey("unit_list");
    CCArray* unit_names = unit_list->allKeys();
    for (int i = 0; i < unit_names->count(); ++i)
    {
        CCString* unit_name = (CCString*)unit_names->objectAtIndex(i);
        CCDictionary* unit = (CCDictionary*)unit_list->objectForKey(unit_name->m_sString);
        CCArray* point = (CCArray*)unit->objectForKey("point");
        CCArray* triangle = (CCArray*)unit->objectForKey("triangle");
        Live2dX_TriangleList& triangle_list = m_all_units[unit_name->m_sString];
        for (int k = 0; k < triangle->count(); ++k)
        {
            CCArray* triangle_one = (CCArray*)triangle->objectAtIndex(k);
            int point_index[3];
            point_index[0] = intAtArray(0, triangle_one);
            point_index[1] = intAtArray(1, triangle_one);
            point_index[2] = intAtArray(2, triangle_one);
            Live2dX_Triangle tconfig;
            
            for (int m = 0; m < 3; ++m)
            {
                CCArray* origin_points = (CCArray*)point->objectAtIndex(point_index[m]);
                Live2dX_UV uv = {floatAtArray(0,origin_points),floatAtArray(1,origin_points)};
                Live2dX_Vertex vertex = {floatAtArray(2,origin_points),floatAtArray(3,origin_points),0};
                int point_id = (int)m_orginUV.size();
                m_orginUV.push_back(uv);
                m_orginVertex.push_back(vertex);
                m_nowVertex.push_back(vertex);
                m_orginColor.push_back(ccc4(0xff, 0xff,0xff, 0xff));
                tconfig.point[m] = point_id;
                tconfig.orginPoint[m] = point_index[m];
            }
            triangle_list.push_back(tconfig);
        }
//        m_all_units[unit_name->m_sString] = triangle_list;
        CCDictionary* animation = (CCDictionary*)unit->objectForKey("animation");
        if(animation)
        {
            map<string,Live2dX_Unit_Anims>& anim2 = m_all_unitanims[unit_name->m_sString];
            
            CCArray* unit_anim_names = animation->allKeys();
            for (int k = 0; k < unit_anim_names->count(); ++k)
            {
                CCString* unit_anim_name = (CCString*)unit_anim_names->objectAtIndex(k);
                CCArray* unit_anims = (CCArray*)animation->objectForKey(unit_anim_name->m_sString);
                Live2dX_Unit_Anims& unit_anims2 = anim2[unit_anim_name->m_sString];
                for (int m = 0; m < unit_anims->count(); ++m)
                {
                    CCDictionary* anim_item = (CCDictionary*)unit_anims->objectAtIndex(m);
                    Live2dX_Unit_Anim anim;
                    anim.type = (Live2dX_Animation_Type)anim_item->valueForKey("type")->intValue();
                    anim.start_perc = anim_item->valueForKey("start")->floatValue();
                    anim.end_perc = anim_item->valueForKey("end")->floatValue();
                    
                    CCArray* value = (CCArray*)anim_item->objectForKey("value");
                    map<int,Live2dX_Unit_Anim_Pos> anim_pos;
                    int anim_id = m_all_point_move.size();
                    anim.anim_id = anim_id;
                    
                    for (int n = 0; n < value->count(); ++n)
                    {
                        CCDictionary* value_item = (CCDictionary*)value->objectAtIndex(n);
                        
                        Live2dX_Unit_Anim_Pos value  = {
                            value_item->valueForKey("x")->floatValue(),
                            value_item->valueForKey("y")->floatValue(),
                            value_item->valueForKey("x_move")->floatValue(),
                            value_item->valueForKey("y_move")->floatValue(),
                        };
                        
                        anim_pos[value_item->valueForKey("id")->intValue()] = value;
                    }
                    m_all_point_move.push_back(anim_pos);
                    unit_anims2.push_back(anim);
                }
            }
        }
    }
    
    CCDictionary* animation = (CCDictionary*)config->objectForKey("animation");
    CCArray* animation_names = animation->allKeys();
    for (int i = 0;animation_names != NULL && i < animation_names->count(); ++i)
    {
        CCString* animation_name = (CCString*)animation_names->objectAtIndex(i);
        CCArray* animation_items = (CCArray*)animation->objectForKey(animation_name->m_sString);
        Live2dX_Anims& anim_list = m_all_anims[animation_name->m_sString];
        for (int k = 0; k < animation_items->count(); ++k)
        {
            CCDictionary* animation_item = (CCDictionary*)animation_items->objectAtIndex(k);
            Live2dX_Anim value = {
                &m_all_unitanims[animation_item->valueForKey("unit_name")->m_sString][animation_item->valueForKey("anim_name")->m_sString],
                animation_item->valueForKey("unit_name")->m_sString,
                animation_item->valueForKey("delay")->floatValue(),
                animation_item->valueForKey("time")->floatValue()
            };
            anim_list.push_back(value);
        }
    }
}
