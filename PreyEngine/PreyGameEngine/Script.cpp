#include "Script.h"
#include "Entity.h"

Script::Script(Entity* _entity, std::string name)
	:Component(_entity, name)
{
}

Script::~Script()
{

}
