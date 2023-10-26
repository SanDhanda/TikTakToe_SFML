#pragma once
#include <memory>
#include <stack>

#include "State.hpp"

namespace TikTakToeGame {
	typedef std::unique_ptr<State> StateRef;
	class StateMachine
	{
	public:
		StateMachine();
		virtual ~StateMachine();

		//isReplacing - do you want to replace the current state with the new one - i.e. main menu to game - want to replace
		void AddState(StateRef newState, bool isReplacing = true);

		void RemoveState();
		void ProcessStateChanges();

		StateRef& GetActiveState();
	private:
		std::stack<StateRef> _states;
		StateRef _newState;
		bool _isRemoving;
		bool _isAdding;
		bool _isReplacing;



	};
}

