#pragma once

namespace TikTakToeGame
{
	class State {
	public:
		virtual void Init()=0;
		virtual void HandleInput() {};
		virtual void Update(float dt) {};
		//dt - delta between each frame
		virtual void Draw(float dt) {};
		virtual void Pause() {};
		virtual void Resume() {};
		virtual void LoadTextures() {};
		virtual void SetTextures() {};
		virtual void SetPositions() {};

	private:
		
	};
}