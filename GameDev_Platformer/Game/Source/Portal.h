#pragma once
#include "Entity.h"
class Portal :    public Entity
{
public:
	Portal(iPoint pos);
	Portal(Collider_Type type, iPoint pos);

	bool LoadState(pugi::xml_node& data);
	bool SaveState(pugi::xml_node& data) const;
private:
	bool Start();
	bool PreUpdate();
	bool Update();
	bool PostUpdate();
	bool Cleanup();

public:
	Animation idlePortalAnim, transitionPortalAnim, openPortalAnim;
	enum PortalState
	{
		P_IDLE,
		P_TRANSITION,
		P_OPEN
	};
	PortalState portalState;
};

