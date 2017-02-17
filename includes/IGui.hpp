// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IGui.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/24 19:07:48 by mmoumini          #+#    #+#             //
//   Updated: 2015/06/07 20:01:03 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef IGUI_HPP
 #define IGUI_HPP

class IGui
{
	public:
		virtual void	draw_env( GameEvent &) = 0;
		virtual bool	check_event( GameEvent &) = 0;
		virtual int		init( GameEvent& ) = 0;
};

#endif
