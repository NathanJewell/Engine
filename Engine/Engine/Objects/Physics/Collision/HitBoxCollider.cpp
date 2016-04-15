#include "HitBoxCollider.hpp"


HitBoxCollider::HitBoxCollider()
{
    knockback = 1;
}


HitBoxCollider::~HitBoxCollider()
{
}


sf::Vector2f getNewPosition(HitBox* boxA, sf::Vector2f velA, HitBox* boxB, sf::Vector2f velB)
{
    sf::Vector2f corVel(0,0);
    if (checkCollision(boxA, boxB))
    {
        magsqA = velA.x * velA*x + velA.y + velA.y;
        magsqB = velB.x * velB*x + velB.y + velB.y;

        if (fabs(magsqA) < .001)
        {

        }
        else if (fabs(magsqB) < .001)
        {

        }

    }


    return corVel;

}

bool HitBoxCollider::checkCollision(HitBox* boxA, HitBox* boxB)
{
	bool collided;

	if ((boxA->getType() == HitBox::AABB) && (boxB->getType() == HitBox::AABB))
	{
		collided = collideDoubleAABB(downcastAABB(boxA), downcastAABB(boxB));
	}
	else if ((boxA->getType() == HitBox::CIRC) && (boxB->getType() == HitBox::AABB))
	{
		collided = collideAABBCirc(downcastAABB(boxB), downcastCirc(boxA));
	}
	else if ((boxA->getType() == HitBox::AABB) && (boxB->getType() == HitBox::CIRC))
	{
		collided = collideAABBCirc(downcastAABB(boxA), downcastCirc(boxB));
	}
	else if ((boxA->getType() == HitBox::CIRC) && (boxB->getType() == HitBox::CIRC))
	{
		collided = collideDoubleCirc(downcastCirc(boxA), downcastCirc(boxB));
	}

	return collided;
}

//private

bool HitBoxCollider::collideDoubleAABB(AAHitbox* boxA, AAHitbox* boxB)
{
	enum boundpos { Top = 0, Right, Bot, Left, BOUND_SIZE};

	double boundsA[BOUND_SIZE];

	boundsA[Top] = boxA->getCorners().first.y;
	boundsA[Right] = boxA->getCorners().second.x;
	boundsA[Bot] = boxA->getCorners().second.y;
	boundsA[Left] = boxA->getCorners().first.x;

	double boundsB[BOUND_SIZE];

	boundsB[Top] = boxB->getCorners().first.y;
	boundsB[Right] = boxB->getCorners().second.x;
	boundsB[Bot] = boxB->getCorners().second.y;
	boundsB[Left] = boxB->getCorners().first.x;

	bool collided = true;

	if ((boundsA[Top] > boundsB[Bot]) || (boundsA[Bot] < boundsB[Top]) || (boundsA[Right] < boundsB[Left]) || (boundsA[Left] > boundsB[Right]))
	{
		collided = false;
	}

	return collided;

}

bool HitBoxCollider::collideAABBCirc(AAHitbox* boxA, CircularHitbox* boxB)
{

	enum cornerNames {TL = 0, TR, BR, BL, CORNER_SIZE};

	bool boxTest = false;
	bool circPointTest = false;
	bool rectPointTest = false;
	bool positionTest = false;


	AAHitbox testor;
	const sf::Vector2f circpos = boxB->getPosition();
	const double rad = boxB->getRadius();
	testor.setPosition(circpos);
	testor.setSize(sf::Vector2f(2 * rad, 2 * rad));

	boxTest = collideDoubleAABB(boxA, &testor);




	if (boxTest)
	{
		positionTest = boxB->isPointInside(boxB->getPosition()) || boxA->isPointInside(boxA->getPosition());
		if (!positionTest)
		{
			sf::Vector2f corners[CORNER_SIZE];
			corners[TL] = boxA->getCorners().first;
			corners[TR] = sf::Vector2f(boxA->getCorners().second.x, boxA->getCorners().first.y);
			corners[BR] = boxA->getCorners().second;
			corners[BL] = sf::Vector2f(boxA->getCorners().first.x, boxA->getCorners().second.y);


			for (unsigned int i = 0; i < CORNER_SIZE; i++)
			{
				if (boxB->isPointInside(corners[i]))
				{
					circPointTest = true;
					break;
				}
			}

			if (!circPointTest)
			{
				for (unsigned int i = 0; i < CORNER_SIZE; i++)
				{
					if (testor.isPointInside(corners[i]))
					{
						rectPointTest = true;
						break;
					}
				}

			}
		}

	}


	bool retVal = boxTest;
	if (boxTest)
	{
		if (positionTest)
		{
			retVal = positionTest;
		}
		else
		{
			if (circPointTest)
			{
				retVal = true;
			}
			else
			{
				retVal = !rectPointTest;
			}
		}

	}

	return retVal;




}

bool HitBoxCollider::collideDoubleCirc(CircularHitbox* boxA, CircularHitbox* boxB)
{
	const double distX = boxA->getPosition().x - boxB->getPosition().x;
	const double distY = boxA->getPosition().y - boxB->getPosition().y;
	const double radsum = boxA->getRadius() + boxB->getRadius();

	return (distX * distX + distY * distY  < radsum * radsum);
}

AAHitbox* HitBoxCollider::downcastAABB(HitBox* box)
{
	if (box->getType() == HitBox::AABB)
	{
		return (AAHitbox*)(box);
	}
}

CircularHitbox* HitBoxCollider::downcastCirc(HitBox* box)
{
	if (box->getType() == HitBox::CIRC)
	{
		return (CircularHitbox*)(box);
	}
}


sf::Vector2f HitBoxCollider::getCorVelDoubleAABB( sf::Vector2f vel, AAHitbox* boxA, AAHitbox* boxB)
{
    unsigned double mag = sqrt(distSq(vel));
    sf::Vector2f velnorm(vel.x/mag, vel.y/mag);

    sf::Vector2f apos(boxA->getPosition());

    yBoundTop = boxB->getCorners().first.y;
    yBoundBot = boxB->getCorners().second.y;
    xBoundLeft = boxB->getCorners().first.x;
    xBoundRight = boxB->getCorners().second.x;


   std::Vector<sf::Vector2f> intPoints;

   sf::Vector2f testPoint;
   if ((apos.y < yBoundTop && apos.y + vel.y > yBoundTop || apos.y > yBoundTop && apos.y + vel.y < yBoundTop))
   {

   }



    intPoint[0] =

}

	sf::Vector2f HitBoxCollider::getCorVelCircAABB(sf::Vector2f vel, CircularHitbox* circA,  AAHitbox* boxB);
	sf::Vector2f HitBoxCollider::getCorVelAABBCirc(sf::Vector2f vel, AAHitbox* boxB, CircularHitbox* circA)
	sf::Vector2f HitBoxCollider::getCorVelDoubleCirc(sf::Vector2f vel, CircularHitbox* circA, CircularHitbox* circB);


	unsigned double HitBoxCollider::distSq(sf::Vector2f vec)
	{
	    return (unsigned double)(vec.x * vec.x + vec.y * vec.y);
	}