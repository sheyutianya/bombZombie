#ifndef _MYCONTACT_LISTENSER_H_
#define _MYCONTACT_LISTENSER_H_

//#include "cocos2d.h"

#include <Box2D/Box2D.h>
#include "cocos2d.h"
#include <list>
#include "Global.h"
using std::vector;

class MyContact
{
public:
	b2Fixture* fixtureA;
	b2Fixture* fixtureB;
	b2WorldManifold manifold;
};

// Contact listener
class MyContactListener : public b2ContactListener
{
	// Callbacks for derived classes.
	virtual void BeginContact(b2Contact* contact) 
	{ 
		if (contact)
		{
			//MyContact mc;
			//mc.fixtureA = contact->GetFixtureA();
			//mc.fixtureB = contact->GetFixtureB();
			//mc.manifold = contact->GetManifold();
			//			  //contact
			//contact_list.push_back(mc);

			//manifold_list.push_back(contact->GetManifold());


			MyContact *mc = new MyContact();
			mc->fixtureA = contact->GetFixtureA();
			mc->fixtureB = contact->GetFixtureB();
			contact->GetWorldManifold(&(mc->manifold));
			contact_list.push_back(mc);
			MyGlobal::testCount++;
		
		}
		B2_NOT_USED(contact); 
	}

	virtual void EndContact(b2Contact* contact) 
	{ 
		//contact_list.clear();
		B2_NOT_USED(contact); 
	}


	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
		
		if (contact)
		{
			//MyContact *mc = new MyContact();
			//mc->fixtureA = contact->GetFixtureA();
			//mc->fixtureB = contact->GetFixtureB();
			//contact->GetWorldManifold(&(mc->manifold));
			//contact_list.push_back(mc);
		}
	

		//B2_NOT_USED(contact);
		B2_NOT_USED(oldManifold);
	}

	virtual void PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse)
	{

		B2_NOT_USED(contact);
		B2_NOT_USED(impulse);
	}


 

public:
	std::vector<MyContact*> contact_list;

	void clearContact() 
	{ 
		for( std::vector<MyContact*>::iterator it = contact_list.begin(); it != contact_list.end();it++)
		{
			//MyContact* contact = ;
			delete *it;
			MyGlobal::testCount--;
			//contact_list.erase( it);
		}
		

		 contact_list.clear();
		 
	}
	//std::list<b2Manifold*> manifold_list;
};
#endif