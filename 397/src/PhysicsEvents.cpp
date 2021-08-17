//
// Created by Bryce standley on 23/6/21.
//
#include "tnahpch.h"
#include "PhysicsEvents.h"

void PhysicsEvents::onContact(const CollisionCallback::CallbackData &callbackData)
{
	if(callbackData.getNbContactPairs() < 1) return;
	//Collisions are registered here, do what you need to do stuff with the collision data
	//This converts an objects tag back into a tag we can understand so we can check if something hit another thing
	rp3d::RigidBody* b1 = (rp3d::RigidBody*)callbackData.getContactPair(0).getBody1();
	rp3d::RigidBody* b2 = (rp3d::RigidBody*)callbackData.getContactPair(0).getBody2();
	auto t1 = reinterpret_cast<BoundingBox::CollisionTag>(*static_cast<BoundingBox::CollisionTag*>(b1->getUserData()));
	auto t2 = reinterpret_cast<BoundingBox::CollisionTag>(*static_cast<BoundingBox::CollisionTag*>(b2->getUserData()));

	if(!t1 || !t2) return;


	if(BoundingBox::CompareTag(t1, BoundingBox::TOKEN) || BoundingBox::CompareTag(t2, BoundingBox::TOKEN))
	{
		if(BoundingBox::CompareTag(t1, BoundingBox::PLAYER) || BoundingBox::CompareTag(t2, BoundingBox::PLAYER))
		{
			//From here we now know the collision happened between a token and a player
			std::cout << "Player Hit a Token" << std::endl;
		}
	}

	if(BoundingBox::CompareTag(t1, BoundingBox::TOKEN) || BoundingBox::CompareTag(t2, BoundingBox::TOKEN))
	{
		if(BoundingBox::CompareTag(t1, BoundingBox::TERRAIN) || BoundingBox::CompareTag(t2, BoundingBox::TERRAIN))
		{
			if(BoundingBox::CompareTag(t1, BoundingBox::TOKEN))
			{
				//b1 is the token
				b1->setType(rp3d::BodyType::STATIC);
				b1->enableGravity(false);
				b1->getCollider(0)->setIsTrigger(true);
			}
			else if(BoundingBox::CompareTag(t2, BoundingBox::TOKEN))
			{
				b2->setType(rp3d::BodyType::STATIC);
				b2->enableGravity(false);
				b2->getCollider(0)->setIsTrigger(true);
			}


		}
	}

}

void PhysicsEvents::onTrigger(const rp3d::OverlapCallback::CallbackData &callbackData)
{
	//Collisions are registered here, do what you need to do stuff with the collision data
	//This converts an objects tag back into a tag we can understand so we can check if something hit another thing
	if(callbackData.getNbOverlappingPairs() < 1) return;
	rp3d::RigidBody* b1 = (rp3d::RigidBody*)callbackData.getOverlappingPair(0).getBody1();
	rp3d::RigidBody* b2 = (rp3d::RigidBody*)callbackData.getOverlappingPair(0).getBody2();
	auto t1 = reinterpret_cast<BoundingBox::CollisionTag>(*static_cast<BoundingBox::CollisionTag*>(b1->getUserData()));
	auto t2 = reinterpret_cast<BoundingBox::CollisionTag>(*static_cast<BoundingBox::CollisionTag*>(b2->getUserData()));

	if(!t1 || !t2) return;

	if(BoundingBox::CompareTag(t1, BoundingBox::TOKEN) || BoundingBox::CompareTag(t2, BoundingBox::TOKEN))
	{
		if(BoundingBox::CompareTag(t1, BoundingBox::PLAYER) || BoundingBox::CompareTag(t2, BoundingBox::PLAYER))
		{
			//From here we now know the collision happened between a token and a player
			std::cout << "Player Hit a Token" << std::endl;
		}
	}
}
