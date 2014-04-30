#include "Box2DTMXTool.h"
bool Box2DTMXTool::readTiledMapForBlocks(b2World* world,CCTMXTiledMap* tiledmap,float xOffset){
	/*if(mBody != NULL){
		world->DestroyBody(mBody);
	}*/

	this->contentScaleFactor = CCDirector::sharedDirector()->getContentScaleFactor();
	this->mWorld = world;
	this->mTiledMap = tiledmap;
	
	b2BodyDef body_def;
    body_def.type = b2_staticBody;
    body_def.position.SetZero();
    mBody = world->CreateBody(&body_def);
	mBodyList.push_back(mBody);
   
    // �ҳ��赲�������ڵĲ�
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
        sb_obj->friction = 0;
        sb_obj->restitution = 0.0f;
        
        // ��ȡ������״����ʼ��
        float x = ((CCString*)dict->objectForKey("x"))->floatValue()/contentScaleFactor+ xOffset;
        float y = ((CCString*)dict->objectForKey("y"))->floatValue()/contentScaleFactor;
        
        b2Shape* shape = NULL;
        
        //�����
        CCObject *polygon = dict->objectForKey("polygonPoints");
        if (polygon) {
            CCArray *polygon_points = (CCArray*)polygon;
            
            std::vector<b2Vec2> points;
            
            // ���뽫���ж�ȡ�Ķ���������Ϊ��תy֮�������ζ����˳���Ѿ������ˣ�����b2PolygonShape��crash
            //int c =polygon_points->count();
            //points.resize(c);
            //c--;
            
            CCDictionary* pt_dict;
            CCObject* obj = NULL;
            CCARRAY_FOREACH(polygon_points, obj)
            {
                pt_dict = (CCDictionary*)obj;
                
                if (!pt_dict) {
                    continue;
                }
                
                // �������ʼ���ƫ��
                float offx = ((CCString*)pt_dict->objectForKey("x"))->floatValue()/contentScaleFactor;
                float offy = ((CCString*)pt_dict->objectForKey("y"))->floatValue()/contentScaleFactor;
                
                //points[c--] = (b2Vec2((x + offx) / PTM_RATIO, (y-offy) / PTM_RATIO));
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
                
                float offx = ((CCString*)pt_dict->objectForKey("x"))->floatValue()/contentScaleFactor;
                float offy = ((CCString*)pt_dict->objectForKey("y"))->floatValue()/contentScaleFactor;
                points.push_back(b2Vec2((x + offx) / PTM_RATIO, (y-offy) / PTM_RATIO));
            }
            
            b2ChainShape *ps = new b2ChainShape();
            ps->CreateChain(&points[0], points.size());
            fixture_def.shape = ps;
            
            shape = ps;
            
            sb_obj->shape = StaticBlockObject::ST_POLYGON;
        } else if (dict->objectForKey("ellipse")) {
            float width = ((CCString*)dict->objectForKey("width"))->floatValue()/contentScaleFactor;
            float height = ((CCString*)dict->objectForKey("height"))->floatValue()/contentScaleFactor;
            
            b2CircleShape *ps = new b2CircleShape;
            ps->m_p.Set((x+width/2) / PTM_RATIO, ((y+height/2)) / PTM_RATIO);
            ps->m_radius = width/2/PTM_RATIO;
            fixture_def.shape = ps;
            
            shape = ps;
            
            sb_obj->shape = StaticBlockObject::ST_CIRCLE;
        } else {
            float width = ((CCString*)dict->objectForKey("width"))->floatValue()/contentScaleFactor;
            float height = ((CCString*)dict->objectForKey("height"))->floatValue()/contentScaleFactor;
            
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
    autorelease();
    return true;
}

bool Box2DTMXTool::readTiledMapForBlocks(b2World* world,CCTMXTiledMap *tiledmap){
	return readTiledMapForBlocks(world,tiledmap,0);
}
void Box2DTMXTool::destoryAllBlocks(){
	mWorld->DestroyBody(mBody);
}
Box2DTMXTool::Box2DTMXTool():mBody(NULL),bodyListLength(2){
}

bool Box2DTMXTool::autorelease(){
	if(mBodyList.size() > bodyListLength){
		mWorld->DestroyBody(mBodyList.front());
		mBodyList.pop_front();
	}
	return true;
}