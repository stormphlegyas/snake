/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Timer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumini <mmoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/16 18:00:37 by mmoumini          #+#    #+#             */
/*   Updated: 2025/04/10 21:16:57 by mmoumini         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef TIMER_HPP
#define TIMER_HPP

#include <SFML/System.hpp>

class Timer {
public:

    Timer();

    void Start();
    void Pause();
    void Reinitialize();

    float GetTime( void );
	float GetTime_sec( void );

private:
    enum State {Started, Paused};

	sf::Clock myClock;

    State myState;
    float myElapsedTime;
};

#endif
