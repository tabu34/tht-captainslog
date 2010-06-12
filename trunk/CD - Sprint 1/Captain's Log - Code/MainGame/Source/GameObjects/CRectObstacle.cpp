//////////////////////////////////////////////////////////////////////
//	File Name	:	"CRectObstacle.cpp"
//
//	Author Name	:	Preston Stoll
// 
//	Purpose		:	To hold all related data and 
//					functionality for a four sided polygon for collision
//////////////////////////////////////////////////////////////////////

#include "CRectObstacle.h"
#include "SGD Wrappers/CSGD_Direct3D.h"
#include "Messaging/CSGD_MessageSystem.h"
#include "Messaging/CSGD_EventSystem.h"
//#include "SGD Wrappers/CSGD_MemoryManager.h"
CRectObstacle::CRectObstacle()
{
	m_nType = OBJ_OBSTACLE;
}

bool CRectObstacle::CheckCollision(CBase* pBase, bool _act)
{
	if(pBase->GetType() == OBJ_GOLFBALL || pBase->GetType() == OBJ_BULLET || pBase->GetType() == OBJ_TURRET && pBase->CanCollide())
	{

		
		tVector2D _sphereCenter;
		float _sphereRadius;
		if(pBase->GetType() == OBJ_GOLFBALL)
		{
			
			_sphereCenter.fX = pBase->GetPosX();
			_sphereCenter.fY = pBase->GetPosY();

			_sphereRadius = pBase->GetWidth() / 2.0f;
		} else {

			_sphereCenter.fX = pBase->GetPosX();
			_sphereCenter.fY = pBase->GetPosY();

			_sphereRadius = pBase->GetWidth() / 2.0f;
		}

		

		tVector2D line;
		tVector2D pt2;
		// Check all four lines for collision
		for(int i = 0; i < 4; i++)
		{
			if(i + 1 <= 3)
				pt2 = m_v2DPoints[i + 1];
			else
				pt2 = m_v2DPoints[0];

			line = pt2 - m_v2DPoints[i];

			// Check if the golfball is within colliding distance
			if(_sphereCenter.fX > max(m_v2DPoints[i].fX, pt2.fX)
				|| _sphereCenter.fX + _sphereRadius< min(m_v2DPoints[i].fX, pt2.fX)
				|| _sphereCenter.fY > max(m_v2DPoints[i].fY, pt2.fY)
				|| _sphereCenter.fY + _sphereRadius < min(m_v2DPoints[i].fY, pt2.fY))
				continue;

			float lineSlope = (pt2.fY - m_v2DPoints[i].fY) / (pt2.fX - m_v2DPoints[i].fX);
			float lineNormalSlope = -(1 / lineSlope);
			float lineNormalK = _sphereCenter.fY - lineNormalSlope * _sphereCenter.fX;
			float lineK = m_v2DPoints[i].fY - lineSlope * m_v2DPoints[i].fX;

			tVector2D pointClosestToCircle;
			pointClosestToCircle.fX = (lineNormalK - lineK) / (lineSlope - lineNormalSlope);
			pointClosestToCircle.fY = pointClosestToCircle.fX * lineSlope + lineK;

			if( (_sphereCenter.fX - pointClosestToCircle.fX) * (_sphereCenter.fX - pointClosestToCircle.fX) + (_sphereCenter.fY - pointClosestToCircle.fY) * (_sphereCenter.fY - pointClosestToCircle.fY) < _sphereRadius * _sphereRadius)
			{
				if(_act)
				{
					if(pBase->GetType() == OBJ_GOLFBALL)
						CSGD_MessageSystem::GetInstance()->SendMsg( new CGolfballCollisionMessage( (CGolfBall*) pBase ) );
					else
					{
						CSGD_EventSystem::GetInstance()->SendEvent("BulletHit", (CBullet*) pBase );
						CSGD_MessageSystem::GetInstance()->SendMsg( new CDestroyBulletMessage( (CBullet*) pBase ) );
					}
				}
 				return true;
			}
			
		}
		return false;
	} else {
		return false;
	}
	
}

void CRectObstacle::Update(float fElapsedTime)
{
	
}

void CRectObstacle::Render()
{
	// CRectObstacles are not visible
	
	 CSGD_Direct3D::GetInstance()->DrawLine((int)m_v2DPoints[0].fX, (int)m_v2DPoints[0].fY, (int)m_v2DPoints[1].fX, (int)m_v2DPoints[1].fY, 255, 255, 255);
	 CSGD_Direct3D::GetInstance()->DrawLine((int)m_v2DPoints[1].fX, (int)m_v2DPoints[1].fY, (int)m_v2DPoints[2].fX, (int)m_v2DPoints[2].fY, 0, 255, 255);
	 CSGD_Direct3D::GetInstance()->DrawLine((int)m_v2DPoints[2].fX, (int)m_v2DPoints[2].fY, (int)m_v2DPoints[3].fX, (int)m_v2DPoints[3].fY, 255, 0, 255);
	 CSGD_Direct3D::GetInstance()->DrawLine((int)m_v2DPoints[3].fX, (int)m_v2DPoints[3].fY, (int)m_v2DPoints[0].fX, (int)m_v2DPoints[0].fY, 255, 255, 0);
		
}




		//if(i + 1 < 4)
		//	line = m_v2DPoints[i + 1] - m_v2DPoints[i];
		//else
		//	line = m_v2DPoints[0] - m_v2DPoints[i];
		//tVector2D lineNormal;
		//lineNormal.fX = -line.fY;
		//lineNormal.fY = line.fX;
		//tVector2D pt1 = m_v2DPoints[i];
		//tVector2D pt2, pt3;

		//if(i + 1 <= 3)
		//	pt2 = m_v2DPoints[i + 1];
		//else
		//	pt2 = m_v2DPoints[0];

		//if(i + 2 == 4)
		//	pt3 = m_v2DPoints[0];
		//else if(i + 2 == 5)
		//	pt3 = m_v2DPoints[1];
		//else
		//	pt3 = m_v2DPoints[i + 2];

		//// Get closest point of sphere to line
		//tVector2D closestPointOnSphere = _sphereCenter - lineNormal;
		//// Check if that point is on the opposite side of the line
		//float functionValue = closestPointOnSphere.fY - pt1.fY -((pt2.fY - pt1.fY) / (pt2.fX - pt1.fX)) * (closestPointOnSphere.fX - pt1.fX);
		//float correctValue = pt3.fY - pt1.fY -((pt2.fY - pt1.fY) / (pt2.fX - pt1.fX)) * (pt3.fX - pt1.fX);


		//if(functionValue < 0.0f && correctValue < 0.0f || functionValue > 0.0f && correctValue > 0.0f)
		//{
		//	// Collision!
		//	return true;
		//}