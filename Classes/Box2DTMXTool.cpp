#include "Box2DTMXTool.h"
bool Box2DTMXTool::readTiledMapForBlocks(b2World* world,CCTMXTiledMap* tiledmap){
	mTiledMap = tiledmap;
	b2BodyDef body_def;
    body_def.type = b2_staticBody;
    body_def.position.SetZero();
    mBody = world->CreateBody(&body_def);
    
    // 找出阻挡区域所在的层
    CCTMXObjectGroup* group = mTiledMap->objectGroupNamed("Physics");
    
    CCArray* array = group->getObjects();
    CCDictionary* dict;
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(array, pObj)
    {
        dict = (CCDictionary*)pObj;
        if (!dict)
            continue;
        
        b2FixtureDef fixture_def;
        
        StaticBlockObject *sb_obj = new StaticBlockObject();
        
        sb_obj->density = 1.0f;
        sb_obj->friction = 0.2f;
        sb_obj->restitution = 0.f;
        
        // 读取所有形状的起始点
        float x = ((CCString*)dict->objectForKey("x"))->floatValue();
        float y = ((CCString*)dict->objectForKey("y"))->floatValue();
        
        b2Shape* shape = NULL;
        
        //多边形
        CCObject *polygon = dict->objectForKey("polygonPoints");
        if (polygon) {
            CCArray *polygon_points = (CCArray*)polygon;
            
            std::vector<b2Vec2> points;
            
            // 必须将所有读取的定点逆向，因为翻转y之后，三角形定点的顺序已经逆序了，构造b2PolygonShape会crash
			int i = 0;
            
            CCDictionary* pt_dict;
            CCObject* obj = NULL;
            CCARRAY_FOREACH(polygon_points, obj)
            {
                pt_dict = (CCDictionary*)obj;
                
                if (!pt_dict) {
                    continue;
                }
                
                // 相对于起始点的偏移
                float offx = ((CCString*)pt_dict->objectForKey("x"))->floatValue();
                float offy = ((CCString*)pt_dict->objectForKey("y"))->floatValue();
                
                points.push_back(b2Vec2((x + offx) / PTM_RATIO, (y-offy) / PTM_RATIO));
            }
            
            b2PolygonShape *ps = new b2PolygonShape();
            ps->Set(&points[0], points.size());
            fixture_def.shape = ps;
            
            shape = ps;
            
            sb_obj->shape = StaticBlockObject::ST_POLYGON;
        } else if (polygon = dict->objectForKey("polylinePoints")){
            CCArray *polyline_points = (CCArray*)polygon;
            
            std::vector<b2Vec2> points;
            
            CCDictionary* pt_dict;
            CCObject* obj = NULL;
            CCARRAY_FOREACH(polyline_points, obj)
            {
                pt_dict = (CCDictionary*)obj;
                
                if (!pt_dict) {
                    continue;
                }
                
                float offx = ((CCString*)pt_dict->objectForKey("x"))->floatValue();
                float offy = ((CCString*)pt_dict->objectForKey("y"))->floatValue();
                points.push_back(b2Vec2((x + offx) / PTM_RATIO, (y-offy) / PTM_RATIO));
            }
            
            b2ChainShape *ps = new b2ChainShape();
            ps->CreateChain(&points[0], points.size());
            fixture_def.shape = ps;
            
            shape = ps;
            
            sb_obj->shape = StaticBlockObject::ST_POLYGON;
        } else if (dict->objectForKey("ellipse")) {
            float width = ((CCString*)dict->objectForKey("width"))->floatValue();
            float height = ((CCString*)dict->objectForKey("height"))->floatValue();
            
            b2CircleShape *ps = new b2CircleShape;
            ps->m_p.Set((x+width/2) / PTM_RATIO, ((y+height/2)) / PTM_RATIO);
            ps->m_radius = width/2/PTM_RATIO;
            fixture_def.shape = ps;
            
            shape = ps;
            
            sb_obj->shape = StaticBlockObject::ST_CIRCLE;
        } else {
            float width = ((CCString*)dict->objectForKey("width"))->floatValue();
            float height = ((CCString*)dict->objectForKey("height"))->floatValue();
            
            b2PolygonShape *ps = new b2PolygonShape;
            ps->SetAsBox(width/2/PTM_RATIO, height/2/PTM_RATIO, b2Vec2((x+width/2)/PTM_RATIO, (y+height/2)/PTM_RATIO), 0);
            fixture_def.shape = ps;
            
            shape = ps;
            
            sb_obj->shape = StaticBlockObject::ST_POLYGON;

        }

        fixture_def.density = sb_obj->density;
        fixture_def.friction = sb_obj->friction;
        fixture_def.restitution = sb_obj->restitution;

        b2Fixture *fixture = mBody->CreateFixture(&fixture_def);
        sb_obj->fixture = fixture;
        
        if (shape) {
            delete shape;
            shape = NULL;
        }
        
        // Storage the Static block object.
        mStaticBlockList.push_back(sb_obj);
    }
    
    return true;
}

