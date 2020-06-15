/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 08:06:34 by jjosephi          #+#    #+#             */
/*   Updated: 2020/05/25 08:06:34 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

std::string get_extension(std::string filename)
{
	for (int i = 0; i < filename.length(); i++)
	{
		if (filename[i] == '.')
			break;
	}
	return filename.substr(i, filename.length());
}
