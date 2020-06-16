/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 22:56:17 by jjosephi          #+#    #+#             */
/*   Updated: 2020/06/05 22:56:17 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <map>
#include <vector>

const char* process_request(std::vector<Data> data, int port,const char *msg)
{
	std::map<std::string, std::string> request;
	std::map<std::string, std::string> lines;
	const char *s;
	Data *config = nullptr;
	int error;


	error = 200;
	std::map<std::string, const char *(*)(std::map<std::string, std::string>,
	std::map<std::string, std::string>, Data, int)> funcs;
	funcs["GET"] = req_get_head;
	funcs["HEAD"] = *req_get_head;
	funcs["POST"] = *req_post;
	funcs["PUT"] = *req_put;
	funcs["DELETE"] = *req_delete;
	funcs["OPTIONS"] = *req_options;
	funcs["TRACE"] = *req_trace;
	request = parse_headers(msg, &error);
	lines = parse_request_line(msg, &error);
	//Find the correct config file to use for the current request or get the default one if none was found
	for (int i = 0; i < data.size(); i++)
	{
		if (data.operator[](i).get_port() == port)
		{
			if (config == nullptr)
				config = &data.operator[](i);
			if ((data.operator[](i).params->operator[]("server_name").find(request["Host"].substr(0, request["Host"].size() -1))) != data.operator[](i).params->operator[]("server_name").npos)
			{
				//add error check to see if the found parameter is a word or within a word
				config = &data.operator[](i);
				break ;
			}
		}
	}
	if (config->params->operator[]("body_size") != "" && std::stoi(config->params->operator[]("body_size")) < 0)
		error = 413;
	if (request["Content-Lentgh"] == "" )
		error = 401;
	std::list<std::string>::iterator it = config->methods.begin();
	for(; it != config->methods.end(); it++)
	{
		if (lines["Type"] == *it)
			break ;
	}
	if (it == config->methods.end())
		error = 501;
	if (error > 200)
	{
		s = req_error(lines, *config , error);
		return s;
	}
	s = (*funcs[lines["Types"]])(request,lines, *config, error);
	return s;
}
