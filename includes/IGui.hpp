// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IGui.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <mmoumini@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/24 19:07:48 by mmoumini          #+#    #+#             //
//   Updated: 2016/06/23 00:41:18 by mmoumini         ###   ########.fr       //
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
