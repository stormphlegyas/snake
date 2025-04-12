/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Timer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumini <mmoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/16 18:01:07 by mmoumini          #+#    #+#             */
/*   Updated: 2025/04/10 21:30:09 by mmoumini         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Timer.hpp"

Timer::Timer( void ) : myState(Paused), myElapsedTime(0.0f)
{
}

void Timer::Start( void )
{
	if(myState != Started)
	{
		myClock.restart();
		myState = Started;
	}
}

void Timer::Pause( void )
{
	if(myState != Paused)
	{
		myState = Paused;
		myElapsedTime += myClock.getElapsedTime().asMilliseconds();
	}
}

void Timer::Reinitialize( void )
{
	myClock.restart();
	Pause();
	myElapsedTime = 0.0f;
}

float Timer::GetTime( void )
{
	float time;

	if(myState == Paused)
	{
		time = myElapsedTime;
	}
	else
	{
		time = myClock.getElapsedTime().asMilliseconds() + myElapsedTime;
	}
	return time;
}

float Timer::GetTime_sec( void )
{
	float time;

	if(myState == Paused)
	{
		time = myElapsedTime;
	}
	else
	{
		time = myClock.getElapsedTime().asSeconds() + myElapsedTime;
	}
	return time;
}
