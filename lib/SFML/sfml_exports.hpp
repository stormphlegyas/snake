/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sfml_exports.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumini <mmoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:38:16 by mmoumini          #+#    #+#             */
/*   Updated: 2025/04/12 17:38:24 by mmoumini         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#pragma once

#ifdef _WIN32
# define DLL_EXPORT extern "C" __declspec(dllexport)
#else
# define DLL_EXPORT extern "C"
#endif
