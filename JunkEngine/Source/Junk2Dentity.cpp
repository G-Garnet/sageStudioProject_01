#include "..\\Headers\\Junk2Dentity.h"

Junk2DEntity::Junk2DEntity() : Junk2DSprite()
{
    radius = 1.0;
	edge.left = -1;
	edge.top = -1;
	edge.right = 1;
	edge.bottom = 1;
	mass = 20.0;
	velocity.x = 0.0;
	velocity.y = 0.0;
	deltaV.x = 0.0;
	deltaV.y = 0.0;
	active = true;                  // 엔티티 활성화
	rotatedBoxReady = false;
	collisionType = Junk2DentityNS::BOX;
	gravity = Junk2DentityNS::GRAVITY;
	collisionTag = "None";
	isTrigger = false;
	isGravity = false;
	isGround  = false;
	isRigidBody = false;
	isCollid = false;
	isZObject = false;
}

// 충돌체 초기화
void Junk2DEntity::initialize(Graphics *g, const char * filename, int width, int height, int ncols)
{
	Junk2DSprite::settingTexture(g, filename, width, height, ncols);

	center.x = 0.0f;
	center.y = 0.0f;

	edge.left = spriteData.rect.left;
	edge.top = spriteData.rect.top;
	edge.right = spriteData.rect.right;
	edge.bottom = spriteData.rect.bottom;
}

// 충돌체 활성화
void Junk2DEntity::activate()
{
	active = true;
}

void Junk2DEntity::setEdge(int left, int top, int right, int bottom)
{
	edge.left = left;
	edge.top = top;
	edge.right = right;
	edge.bottom = bottom;
}

// 충돌체 업데이트
void Junk2DEntity::update(float frameTime)
{
	velocity += deltaV;
	deltaV.x = 0;
	deltaV.y = 0;
	Junk2DSprite::update(frameTime);
	rotatedBoxReady = false;    // 회전 오프
}

void Junk2DEntity::ai(float frameTime, Junk2DEntity &ent)
{}

// ent와의 충돌 여부
bool Junk2DEntity::collidesWith(Junk2DEntity* ent, VECTOR2 &collisionVector) {
	if (!active || !ent->getActive())
		return false;
	if (collisionType == Junk2DentityNS::CIRCLE && ent->getCollisionType() == Junk2DentityNS::CIRCLE)
		return false;//collideCircle(ent);
	if (collisionType == Junk2DentityNS::BOX && ent->getCollisionType() == Junk2DentityNS::BOX)
		return collideBox(collisionVector, ent);
	if (collisionType != Junk2DentityNS::CIRCLE && ent->getCollisionType() != Junk2DentityNS::CIRCLE)
		return collideRotatedBox(ent);
	//if (collisionType == Junk2DentityNS::CIRCLE)
	//{
	//	//bool collide = ent->collideRotatedBoxCircle(this);
	//	return collide;
	//}
	else
		//return collideRotatedBoxCircle(ent);
	return false;
}

//// 원형 충돌체끼리의 충돌 여부
//bool Junk2DEntity::collideCircle(Junk2DEntity* ent) {
//	distSquared = *getCenter() - *ent->getCenter();
//	distSquared.x = distSquared.x * distSquared.x;
//	distSquared.y = distSquared.y * distSquared.y;
//
//	sumRadiiSquared = (radius*getScale()) + (ent->radius*ent->getScale());
//	sumRadiiSquared *= sumRadiiSquared;
//
//	if (distSquared.x + distSquared.y <= sumRadiiSquared)
//	{
//		return true;
//	}
//	return false;  
//}

// 상자형 충돌체끼리의 충돌 여부
bool Junk2DEntity::collideBox(VECTOR2 &collisionVector, Junk2DEntity* ent)
{
	 // 충돌 활성화 여부
    if (!active || !ent->getActive())
        return false;

	if (isTrigger) {
		if ((getX() + edge.right*getScale() > ent->getX() + ent->getEdge().left * ent->getScale()) &&
			(getX() + edge.left*getScale() < ent->getX() + ent->getEdge().right * ent->getScale()) &&
			(getY() + edge.bottom*getScale() > ent->getY() + ent->getEdge().top * ent->getScale()) &&
			(getY() + edge.top*getScale() < ent->getY() + ent->getEdge().bottom * ent->getScale())) {
			return true;
		}
		return false;
	}

    // 박스 체크
    if( (getX() + edge.right*getScale() >= ent->getX() + ent->getEdge().left * ent->getScale()) &&
        (getX() + edge.left*getScale() <= ent->getX() + ent->getEdge().right * ent->getScale()) &&
        (getY() + edge.bottom*getScale() >= ent->getY() + ent->getEdge().top * ent->getScale()) && 
        (getY() + edge.top*getScale() <= ent->getY() + ent->getEdge().bottom * ent->getScale()) )
    {
        // 충돌 벡터 설정, 재 설정 필요함
		collisionVector = *ent->getCenter() - *getCenter();
        return true;
    }
    return false;
}

// 각도가 틀어진 상자끼리의 충돌 여부
bool Junk2DEntity::collideRotatedBox(Junk2DEntity* ent)
{
    /*computeRotatedBox();                    
    ent->computeRotatedBox();
    if (projectionsOverlap(ent) && ent->projectionsOverlap(this))
    {
        return true;
    }
    return false;*/
	return false;
}
//
//// 
//bool Junk2DEntity::projectionsOverlap(Junk2DEntity* ent)
//{
//    float projection, min01, max01, min03, max03;
//
//    projection = graphics->Vector2Dot(&edge01, ent->getCorner(0));
//    min01 = projection;
//    max01 = projection;
//    for(int c=1; c<4; c++)
//    {
//        projection = graphics->Vector2Dot(&edge01, ent->getCorner(c));
//        if (projection < min01)
//            min01 = projection;
//        else if (projection > max01)
//            max01 = projection;
//    }
//    if (min01 > edge01Max || max01 < edge01Min) 
//        return false;                       
//
//    projection = graphics->Vector2Dot(&edge03, ent->getCorner(0)); // project corner 0
//    min03 = projection;
//    max03 = projection;
//    for(int c=1; c<4; c++)
//    {
//        projection = graphics->Vector2Dot(&edge03, ent->getCorner(c));
//        if (projection < min03)
//            min03 = projection;
//        else if (projection > max03)
//            max03 = projection;
//    }
//    if (min03 > edge03Max || max03 < edge03Min)
//        return false;                       
//
//    return true;                            
//}
//
//bool Junk2DEntity::collideRotatedBoxCircle(Junk2DEntity* ent)
//{
//    float min01, min03, max01, max03, center01, center03;
//
//    computeRotatedBox();                   
//
//    center01 = graphics->Vector2Dot(&edge01, ent->getCenter());
//    min01 = center01 - ent->getRadius()*ent->getScale(); 
//    max01 = center01 + ent->getRadius()*ent->getScale();
//    if (min01 > edge01Max || max01 < edge01Min) 
//        return false;                       
//        
//    center03 = graphics->Vector2Dot(&edge03, ent->getCenter());
//    min03 = center03 - ent->getRadius()*ent->getScale(); 
//    max03 = center03 + ent->getRadius()*ent->getScale();
//    if (min03 > edge03Max || max03 < edge03Min) 
//        return false;                       
//
//    if(center01 < edge01Min && center03 < edge03Min)    
//        return collideCornerCircle(corners[0], ent);
//    if(center01 > edge01Max && center03 < edge03Min)    
//        return collideCornerCircle(corners[1], ent);
//    if(center01 > edge01Max && center03 > edge03Max)    
//        return collideCornerCircle(corners[2], ent);
//    if(center01 < edge01Min && center03 > edge03Max)    
//        return collideCornerCircle(corners[3], ent);
//
//    return true;
//}
//
//bool Junk2DEntity::collideCornerCircle(VECTOR2 corner, Junk2DEntity* ent)
//{
//    distSquared = corner - *ent->getCenter();            // corner - circle
//    distSquared.x = distSquared.x * distSquared.x;      // difference squared
//    distSquared.y = distSquared.y * distSquared.y;
//
//    sumRadiiSquared = ent->getRadius()*ent->getScale();
//    sumRadiiSquared *= sumRadiiSquared;                 
//
//    if(distSquared.x + distSquared.y <= sumRadiiSquared)
//    {
//        return true;
//    }
//    return false;
//}
//
//void Junk2DEntity::computeRotatedBox()
//{
//    if(rotatedBoxReady)
//        return;
//    float projection;
//
//    VECTOR2 rotatedX(cos(spriteData.angle), sin(spriteData.angle));
//    VECTOR2 rotatedY(-sin(spriteData.angle), cos(spriteData.angle));
//
//    const VECTOR2 *center = getCenter();
//    corners[0] = *center + rotatedX * ((float)edge.left*getScale())  +
//                           rotatedY * ((float)edge.top*getScale());
//    corners[1] = *center + rotatedX * ((float)edge.right*getScale()) + 
//                           rotatedY * ((float)edge.top*getScale());
//    corners[2] = *center + rotatedX * ((float)edge.right*getScale()) + 
//                           rotatedY * ((float)edge.bottom*getScale());
//    corners[3] = *center + rotatedX * ((float)edge.left*getScale())  +
//                           rotatedY * ((float)edge.bottom*getScale());
//
//    edge01 = VECTOR2(corners[1].x - corners[0].x, corners[1].y - corners[0].y);
//    graphics->Vector2Normalize(&edge01);
//    edge03 = VECTOR2(corners[3].x - corners[0].x, corners[3].y - corners[0].y);
//    graphics->Vector2Normalize(&edge03);
//
//    projection = graphics->Vector2Dot(&edge01, &corners[0]);
//    edge01Min = projection;
//    edge01Max = projection;
//
//    projection = graphics->Vector2Dot(&edge01, &corners[1]);
//    if (projection < edge01Min)
//        edge01Min = projection;
//    else if (projection > edge01Max)
//        edge01Max = projection;
//
//    projection = graphics->Vector2Dot(&edge03, &corners[0]);
//    edge03Min = projection;
//    edge03Max = projection;
//    projection = graphics->Vector2Dot(&edge03, &corners[3]);
//    if (projection < edge03Min)
//        edge03Min = projection;
//    else if (projection > edge03Max)
//        edge03Max = projection;
//
//    rotatedBoxReady = true;
//}
//
//bool Junk2DEntity::outsideRect(RECT rect)
//{
//    if( spriteData.x + spriteData.width*getScale() < rect.left || 
//        spriteData.x > rect.right ||
//        spriteData.y + spriteData.height*getScale() < rect.top || 
//        spriteData.y > rect.bottom)
//        return true;
//    return false;
//}
//
//void Junk2DEntity::damage(int weapon)
//{}

void Junk2DEntity::bounce(VECTOR2 &collisionVector, Junk2DEntity &ent)
{
	VECTOR2 Vdiff = ent.getVelocity() - velocity;
	VECTOR2 cUV = collisionVector;
	Graphics::Vector2Normalize(&cUV);
	float cUVdotVdiff = Graphics::Vector2Dot(&cUV, &Vdiff);
	float massRatio = 30.0f;
	if (getMass() != 0)
		massRatio *= (ent.getMass() / (getMass() + ent.getMass()));

	// CollisionVector

	if (cUVdotVdiff >= 0)
	{
		if (abs(cUV.x) > abs(cUV.y)) 
			setX(getX() - cUV.x * massRatio);
		else 
			setY(getY() - cUV.y * massRatio);
	}
	else
		deltaV += ((massRatio * cUVdotVdiff) * cUV);
}

void Junk2DEntity::gravityForce()
{
    if (!active && !isGravity)
        return ;

	if (dontMoveRect[3] == 0) {
		setY(getY() + 0.98f);
	}

	//update(0.5f);
}
