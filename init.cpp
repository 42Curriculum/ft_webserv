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

std::vector<Data> serv_init()
{
	std::vector<Data> servers;
	std::ifstream file;
	int pos = 0, start = 0;

	file.open("webserv.config");
	if (!(file.is_open()))
	{
		std::cout << "Config file missing, using default paramters\n";
		servers.push_back(Data());
		return servers;
	}
	std::string content(std::istreambuf_iterator<char>(file),  (std::istreambuf_iterator<char>()));
	while(pos  < content.length() - 1)
	{
		start = content.find("server", pos);
		pos =  content.find("}", start);
		servers.push_back(Data(content.substr(start, pos)));
	}
	return servers;
}

t_loop_data &loop_init(std::vector<Data> servers)
{
	t_loop_data *data = new t_loop_data;
	data->listen_sd = new std::vector<int>();
	data->address = new std::vector<sockaddr_in>();
	int rc;

	data->servers = servers;
	data->size = servers.size();
	FD_ZERO(&data->master_set);
	std::cout<< "START" <<std::endl;
	for (int n = 0; n < data->size; n++)
	{
		/**************************************************************************/
    	/* Create an AF_INET stream socket to receive incoming connections on     */
    	/**************************************************************************/
		std::cout<< "END" <<std::endl;
		data->listen_sd->push_back(socket(AF_INET, SOCK_STREAM, 0));
		if (data->listen_sd->operator[](n) == 0)
		{
			perror("socket() failed");
			exit(EXIT_FAILURE);
		}
		std::cout<< "Stream socket" <<std::endl;
		/**************************************************************************/
		/* Allow socket descriptor to be reuseable                                */
		/**************************************************************************/
		rc = setsockopt(data->listen_sd->operator[](n), SOL_SOCKET, SO_REUSEADDR,
                    (char *)&data->on, sizeof(data->on));
		if (rc < 0)
		{
			perror("set_socketopt() failed");
			close(data->listen_sd->operator[](n));
			exit(-1);
		}
		std::cout<< "Reusable" <<std::endl;
		/**************************************************************************/
		/* Set socket to be nonblocking. All of the sockets for the incoming      */
		/* connections will also be nonblocking since they will inherit that      */
		/* state from the listening socket.                                       */
		/**************************************************************************/
		rc = ioctl(data->listen_sd->operator[](n), FIONBIO, (char *)&data->on);
		if (rc < 0)
		{
			perror("ioctl() failed");
			close(data->listen_sd->operator[](n));
			exit(-1);
		}
		std::cout<< "Nonblocking" <<std::endl;
		/**************************************************************************/
		/* Bind the socket                                                        */
		/**************************************************************************/
		sockaddr_in *add = new sockaddr_in();
		add->sin_family = AF_INET;
		add->sin_addr.s_addr = INADDR_ANY;
		add->sin_port = htons(servers[n].get_port());
		data->address->push_back(*add);
		rc = bind(data->listen_sd->operator[](n), (struct sockaddr *)&data->address->operator[](n), sizeof(data->address->operator[](n)));
		if (rc < 0)
		{
			perror("bind() failed");
			close(data->listen_sd->operator[](n));
			exit(EXIT_FAILURE);
		}
		std::cout<< "Bind" <<  std::to_string(n) << std::endl;
		/**************************************************************************/
		/* Set the listen back log                                                */
		/**************************************************************************/
		rc = listen(data->listen_sd->operator[](n), 32);
		if (rc < 0)
		{
			perror("listen() failed");
			close(data->listen_sd->operator[](n));
			exit(EXIT_FAILURE);
		}
		std::cout<< "Backlog" <<std::endl;
		/**************************************************************************/
		/* Initialize the master fd_set                                           */
		/**************************************************************************/
		FD_SET(data->listen_sd->operator[](n), &data->master_set);
		std::cout<< "Master_set" <<std::endl;
		/**************************************************************************/
		/* Initialize the time_out to 3 minutes. If no activity after 3 minutes,  */
		/* this program will end                                                  */
		/**************************************************************************/
	}
	std::cout<< "Timeout set" <<std::endl;
	data->time_out.tv_sec = 3 * 60;
	data->time_out.tv_usec = 0;
	data->max_sd = data->listen_sd->operator[](data->size - 1);
	std::cout<< "End init" <<std::endl;
	return *data;
}