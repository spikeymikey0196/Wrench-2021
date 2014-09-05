#include "CreatureNode.h"

CreatureNode::CreatureNode(Scene *nScene, Model *nModel, const Vector3 &nPosition, const Vector3 &nOrientation, float nScale)
	: PhysicsNode(nScene, nPosition, nOrientation, nScale, nModel)
{
	aiState = NULL;
	actionState = NULL;
};

void CreatureNode::Update(unsigned int Delta)
{
	if (aiState) aiState->Update(Delta);
	if (actionState) actionState->Update(Delta);

	PhysicsNode::Update(Delta);
};

void CreatureNode::Die()
{
	//solve later
};

void CreatureNode::SetAIState(AIState *nAIState)
{
	aiState = nAIState;
};

void CreatureNode::SetActionState(ActionState *nActionState)
{
	actionState = nActionState;
};

AIState *CreatureNode::GetAIState()
{
	return aiState;
};

ActionState *CreatureNode::GetActionState()
{
	return actionState;
};
