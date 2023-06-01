#ifndef TIMER_H 
#define TIMER_H 

#include <common/entity.h>

class Timer : public Entity
{ 
public: 
    Timer(); 
    virtual ~Timer();

	virtual void update(float deltaTime);

	void StartTimer();
	void TogglePause();
	void StopTimer();

	float Seconds() { return _seconds; };

private:
	float _seconds;
	bool _start;
}; 
#endif // timer_H 
