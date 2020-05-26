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

#include "Data.hpp"
#include <vector>
#include <sys/types.h>
#include <iostream>
#include <fstream>

int main()
{
	std::list<Data> servers;
	std::ifstream file;
	int pos = 0, start = 0;

	file.open("webserv.config");
	if (!(file.is_open()))
	{
		std::cout << "Config file missing, using default paramters\n";
		servers.push_front(Data());
		//return servers;
		return 0;
	}
	std::string content(std::istreambuf_iterator<char>(file),  (std::istreambuf_iterator<char>()));
	while(pos  != std::string::npos)
	{
		start = content.find("server", pos);
		pos =  content.find("}", start);
		servers.push_front(Data(content.substr(start, pos)));
	}
	return 0;
}