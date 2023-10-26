#pragma once

namespace TikTakToeGame
{
	class State {
	public:
		virtual void Init() = 0;
		virtual void HandleInput() = 0;
		virtual void Update() = 0;
		//dt - delta between each frame
		virtual void Draw(float dt) = 0;
		virtual void Pause() = 0;
		virtual void Resume() = 0;
	};
}