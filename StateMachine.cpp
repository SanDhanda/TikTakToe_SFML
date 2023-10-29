#include "StateMachine.hpp"

namespace TikTakToeGame {
	
	void StateMachine::AddState(StateRef newState, bool isReplacing) {
		this->_isAdding = true;
		this->_isReplacing = isReplacing;
		this->_newState = std::move(newState);

	}

	void StateMachine::RemoveState() {
		this->_isRemoving = true;
	}

	void StateMachine::ProcessStateChanges() {
		//if removing state and state is not empty, remove top state, if it is still not empty, resume the top state
		if (this->_isRemoving && !this->_states.empty()) { 
			this->_states.pop();
			if (!this->_states.empty()) {
				this->_states.top()->Resume();
			}
			this->_isRemoving = false;
		}
		//if adding a state and states not empty, add state if we are replacing it, otherwise just pause current state 
		if (this->_isAdding) {
			if (!this->_states.empty()) {
				if (this->_isReplacing) {
					this->_states.pop();
				}
			
				else {
					this->_states.top()->Pause();
				} 
			}
			this->_states.push(std::move(this->_newState));
			this->_states.top()->Init();
			this->_isAdding = false;
		}
		//push new state and initialise the top
		
	}

	StateRef& StateMachine::GetActiveState() {
		return this->_states.top();
	}

	void StateMachine::SetIsSinglePlayer(bool isSinglePlayer)
	{
		this->_isSinglePlayer = isSinglePlayer;
	}

	bool StateMachine::GetIsSinglePlayer()
	{
		return this->_isSinglePlayer;
	}

}
