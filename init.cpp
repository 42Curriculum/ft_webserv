/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 07:54:13 by jjosephi          #+#    #+#             */
/*   Updated: 2020/05/25 07:54:13 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <vector>
#include <sys/types.h>
#include <iostream>
#include <fstream>

std::list<Data> init()
{
	std::list<Data> servers;
	std::ifstream file;
	int pos = 0, start = 0;

	file.open("webserv.config");
	if (!(file.is_open()))
	{
		std::cout << "Config file missing, using default paramters\n";
		servers.push_front(Data());
		return servers;
	}
	std::string content(std::istreambuf_iterator<char>(file),  (std::istreambuf_iterator<char>()));
	while(pos  < content.length() - 1)
	{
		start = content.find("server", pos);
		pos =  content.find("}", start);
		servers.push_front(Data(content.substr(start, pos)));
	}
	return servers;
}