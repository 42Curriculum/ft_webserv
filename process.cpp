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
	char *response;
	Data *config = nullptr;
	int error;


	error = 200;
	std::map<std::string, std::string> lines, Data data)> funcs;
	if (data.params["body_size"] != "" && std::stoi(data.params["body_size"]) < 0)
		error = 413;
	if (request["Content-Lentgh"] == "" )
		error = 401;
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
	std::list<std::string>::iterator it = config->methods.begin();
	for(; it != config->methods.end(); it++)
	{
		if (lines["Type"] == *it)
			break ;
	}
	if (it == config->methods.end())
		error = 501;
	if (errors > 200)
	{
		s = req_error(lines, data , error);
		return s;
	}
	s = (*funcs[lines["Types"])(request,lines, data, error);
	// std::cout << data.operator[](i).params->operator[]("server_name") << std::endl;
	return s;
}

// int main()
// {
// 	  const char *s =
// 	        "GET / HTTP/1.1\r\n"
// 			"Host: index/8080\r\n"
//             "Connection: keep-alive\r\n"
//             "Upgrade-Insecure-Requests: 1\r\n"
//             "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
//             "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_13_3) AppleWebKit/604.5.6 (KHTML, like Gecko) Version/11.0.3 Safari/604.5.6\r\n"
//             "Accept-Language: en-us\r\n"
//             "DNT: 1\r\n"
//             "Accept-Encoding: gzip, deflate\r\n"
//             "\r\n"
//             "Usually GET requests don\'t have a body\r\n"
//             "But I don\'t care in this case :)";
// 	std::vector<Data> servers;

// 	//servers = serv_init();
// 	//std::cout << process_request(servers, 8080, s) << std::endl;
// 	std::map<std::string, char* (*func)(std::map<std::string, std::string> request,


// }
