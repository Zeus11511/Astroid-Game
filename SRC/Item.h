#pragma once

#include "GameObject.h"
#include "BoundingShape.h"
#include "IItemListener.h"

class Item : public GameObject {

	typedef list< IItemListener* > ItemListenerList;
	ItemListenerList mListeners;

public:
	Item(const char* type) : GameObject(type)
	{
		mAngle = rand() % 360;
		mRotation = 0; 
		mPosition.x = rand() / 2;
		mPosition.y = rand() / 2;
		mPosition.z = 0.0;
		mVelocity.x = 5 * cos(DEG2RAD * mAngle);
		mVelocity.y = 5 * sin(DEG2RAD * mAngle);
		mVelocity.z = 0.0;
	}
	~Item(void)
	{
	}

	void AddListener(IItemListener* listener)
	{
		mListeners.push_back(listener);
	}

	void FireItemActiceEvent()
	{
		for (ItemListenerList::iterator lit = mListeners.begin();
			lit != mListeners.end(); ++lit) {
			(*lit)->onItemActive();
		}
	}

	bool CollisionTest(shared_ptr<GameObject> o) {
		if (GetType() == o->GetType()) return false;
		if (o->GetType() == GameObjectType("Asteroid")) return false;
		if (o->GetType() == GameObjectType("Enemy")) return false;
		if (o->GetType() == GameObjectType("Bullet")) return false;
		if (mBoundingShape.get() == NULL) return false;
		if (o->GetBoundingShape().get() == NULL) return false;
		return mBoundingShape->CollisionTest(o->GetBoundingShape());
	}

	void OnCollision(const GameObjectList& objects) {
		mWorld->FlagForRemoval(GetThisPtr());
		FireItemActiceEvent();
	}
};
