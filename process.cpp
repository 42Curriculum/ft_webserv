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
	Data *config = nullptr;
	int error;

	request = parse_headers(msg, &error);
	lines = parse
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
	std::list<string>::iterator it = config->methods.begin();
	for(; it != config->methods.end; it++)
	{
		if (lines.count(it))
			break ;
	}
	if (it == config->methods.end())
		std::cout << "Methd not allowed" << std::endl;
	if (error > 0)
	{
		if (config->error_pages.count(error))
			return config->error_pages[error].c_str();
		else
		{
			std::string err_file;
			err_file =  "err_pages/" + std::to_string(error) + ".html";
			return err_file.c_str();
		}
	}
	// std::cout << data.operator[](i).params->operator[]("server_name") << std::endl;
	return config->params->operator[]("server_name").c_str();
}

int main()
{
	  const char *s = 
	        "GET / HTTP/1.1\r\n"
			"Host: index/8080\r\n"
            "Connection: keep-alive\r\n"
            "Upgrade-Insecure-Requests: 1\r\n"
            "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
            "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_13_3) AppleWebKit/604.5.6 (KHTML, like Gecko) Version/11.0.3 Safari/604.5.6\r\n"
            "Accept-Language: en-us\r\n"
            "DNT: 1\r\n"
            "Accept-Encoding: gzip, deflate\r\n"
            "\r\n"
            "Usually GET requests don\'t have a body\r\n"
            "But I don\'t care in this case :)";
	std::vector<Data> servers;

	servers = serv_init();
	std::cout << process_request(servers, 8080, s) << std::endl;
}