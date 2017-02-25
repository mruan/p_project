/*
	Agent.cpp
*/

#include "Agent.h"

Agent::Agent()
{

}

Agent::~Agent()
{

}

int Agent::communicate(List<Agent*>& peers)
{
	// Convert and encrypt the current state
	// May want to log enc_state

	/*
		For each peer in the list,
		> Communicate
		> add to diff_state
	*/
}

int Agent::updateState()
{
	/*
		> convert diff_state to double
		> and add to state 
		> change alpha
		> log states
	*/
}
