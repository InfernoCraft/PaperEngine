#include "Engine.h"
#include "Object.h"
#include "utils/Core.h"

namespace Paper
{
	Object::Object(std::string name, const Transform& transform)
		: transform(transform), name(name)
	{
		//coreID = Core::RequestID(this);
	}

	Object::~Object()
	{
		//Core::AddToDelete(coreID);
	}

	void Object::SetName(const std::string name)
	{
		this->name = name;
	}

	std::string Object::GetName()
	{
		return name;
	}

	entity_id Object::GetCoreID() const
	{
		return coreID;
	}
}
