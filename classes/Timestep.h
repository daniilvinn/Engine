#pragma once

namespace Engine {
	class Timestep
	{
	private:
		static float m_DeltaTime;
		static float m_LastFrame;
	public:
		static void onUpdate();
		static float Delta();
	};
}
