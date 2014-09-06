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

void CreatureNode::SetAIState(shared_ptr<AIState> nAIState)
{
	aiState = nAIState;
};

void CreatureNode::SetActionState(shared_ptr<ActionState> nActionState)
{
	actionState = nActionState;
};

shared_ptr<AIState> CreatureNode::GetAIState()
{
	return aiState;
};

shared_ptr<ActionState> CreatureNode::GetActionState()
{
	return actionState;
};
