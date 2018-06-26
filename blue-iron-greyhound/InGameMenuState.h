#pragma once

class InGameMenuState
{
	public:
		InGameMenuState();
		~InGameMenuState();

	 void init();
	 void update(double dt);

	 void Cleanup();
	 void Resume();
	 void Pause();

	


private:
};