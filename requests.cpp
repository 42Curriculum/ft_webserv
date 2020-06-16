/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requests.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 23:15:48 by jjosephi          #+#    #+#             */
/*   Updated: 2020/06/13 23:15:48 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <fstream>
#include <time.h>
#include <experimental/filesystem>


const char *req_error(std::map<std::string, std::string> lines, Data data, int error)
{
	std::string response;
	std::ifstream fd;
	std::string file, extension, path;

	if (data.params->operator[]("search_dir") != "")
		path = data.params->operator[]("search_dir");
	file = path + lines["Path"];
	fd.open(data.error_pages.at(error));
	while(std::getline(fd, file));
	response = "HTTP/1.1 " + std::to_string(error) + errors[error] + "\nDate: "//date here
	+ "Last-Modified" + "\nContent-Language: en\n" + "Content-Length: " + std::to_string(file.length()) + "\nContent-Type: " + extension +
	"\n" + "Content-Location: "+ path + "\nServer: ft_webserv" + file;

	return response.c_str();
}

const char *req_get_head(std::map<std::string, std::string> request,
	std::map<std::string, std::string> lines, Data data, int error)
{
	std::string response;
	std::string file, extension, path;
	std::ifstream fd;
	int size;

	if (data.params->operator[]("search_dir") != "")
		path = data.params->operator[]("search_dir");
	file = path + lines["Path"];
	fd.open(file);
	std::cout << "file path :" + file << std::endl;
	if (!fd.is_open())
		error = 404;
	while (std::getline(fd, file));
	size = file.size();
	if (std::stoi(data.params->operator[]("body_size")) < size)
		error = 413;
	//insert error if file empty or exceeds body_max
	response = "HTTP/1.1 " + std::to_string(error) + errors[error] + "\nDate: " //date here
	+ "Last-Modified" + "\nContent-Language: en\n" + "Content-Length: " + std::to_string(size) + "\nContent-Type: " + extension +
	"\n" + "Content-Location: "+ path + "\nServer: ft_webserv";
	if (lines["Type"] == "GET" && error == 200)
		response = response + file;
	return response.c_str();
}

const char *req_post(std::map<std::string, std::string> request,
	std::map<std::string, std::string> lines, Data data, int error)
{
	std::string response;
	std::string file, extension, path;
	std::ifstream fd;
	int size;
	if (data.params->operator[]("search_dir") != "")
		path = data.params->operator[]("search_dir");
	file = path + lines["Path"];
	extension = get_extension(lines["Path"]);
	if (extension != data.params->operator[]("CGI_extension"))
		error = 501;
	else
	{
		if (fork() == 0)
		{
			system(file.c_str());
			exit(0);
		}
	}
	response = "HTTP/1.1 " + std::to_string(error) + errors[error] + "\nDate: " //date here
	+ "Last-Modified" + "\nContent-Language: en\n" + "Content-Length: " + "77" + "\nContent-Type: text/html" +
	"\n" + "Content-Location: "+ path + "\nServer: ft_webserv";
	if (error == 200)
		response = response + "<html>\n<body>\n<h1>Request was Processed Successfully</h1>\n</body>\n</html>";
	else
		response = response + "<html>\n<body>\n<h1>Request not Processed Successfully</h1>\n</body>\n</html>";
	return response.c_str();
}

const char *req_put(std::map<std::string, std::string> request,
	std::map<std::string, std::string> lines, Data data,int error)
{
	std::string response;
	std::string file, body, path;
	std::ifstream fd;
	int size;

	if (error == 200)
		error = 201;
	if (data.params->operator[]("uploads") == "yes")
	{
		file = data.params->operator[]("uploads_dir") + lines["Path"];
		fd.open(file);
		if (fd.is_open())
			error = 409;
		else
		{
			path = "echo " + request["Body"] + ">" + data.params->operator[]("uploads_dir") + lines["Path"];
			system(path.c_str());
		}
	}
	else
		error = 501;
	std::cout << "file path :" + file << std::endl;
	if (error > 201)
		body =	"<html>\n<body>\n<h1>The file could not be created.</h1>\n</body>\n</html>";
	else
		body =	"<html>\n<body>\n<h1>The file was created.</h1>\n</body>\n</html>";
	//insert error if file empty or exceeds body_max
	response = "HTTP/1.1 " + std::to_string(error) + errors[error] + "\nDate: " //date here
	+ "Last-Modified" + "\nContent-Language: en\n" + "Content-Length: " + std::to_string(body.size()) + "\nContent-Type: text/html" +
	"\n" + "Content-Location: "+ path + "\nServer: ft_webserv" + body;
	return response.c_str();
}

const char *req_delete(std::map<std::string, std::string> request,
	std::map<std::string, std::string> lines, Data data, int error)
{
	std::string response;
	std::string file, extension, path;
	std::ifstream fd;
	int size;

	if (data.params->operator[]("search_dir") != "")
		path = data.params->operator[]("search_dir");
	file = path + lines["Path"];
	fd.open(file);
	std::cout << "file path :" + file << std::endl;
	if (!fd.is_open())
		error = 404;

	fd.close();
	file = "rm -f " + file;
	system(file.c_str());
	size = file.size();
	//insert error if file empty or exceeds body_max
	if (error > 200)
		response = "<html>\n<body>\n<h1>URL not found.</h1>\n</body>\n</html>";
	else
		response = "<html>\n<body>\n<h1>URL deleted.</h1>\n</body>\n</html>";
	response = "HTTP/1.1 " + std::to_string(error) + errors[error] + "\nDate: " //date here
	+ "Last-Modified" + "\nContent-Language: en\n" + "Content-Length: " + std::to_string(response.length()) + "\nContent-Type: text/html" +
	"\n" + "Content-Location: "+ path + "\nServer: ft_webserv" + response;
	return response.c_str();
}

const char *req_options(std::map<std::string, std::string> request,
	std::map<std::string, std::string> lines, Data data, int error)
{
	std::string response, allowed;

	std::list<std::string>::iterator it = data.methods.begin();
	for (; it != data.methods.end(); it++)
	{
		allowed = allowed + *it + ",";
	}
	response = "HTTP/1.1 " + std::to_string(error) + errors[error] + "\nDate: " //date here
	+ "Last-Modified" + "Allowed: " + allowed + "\nContent-Language: en\n" + "Content-Length: " + std::to_string(request["request"].length()) + "\nContent-Type: httpd/unix-directory" +
	"\n" + "\nServer: ft_webserv";

	return response.c_str();
}

const char *req_trace(std::map<std::string, std::string> request,
	std::map<std::string, std::string> lines, Data data, int error)
{
	std::string response;

	response = "HTTP/1.1 " + std::to_string(error) + errors[error] + "\nDate: " //date here
	+ "Last-Modified" + "\nContent-Language: en\n" + "Content-Length: " + std::to_string(request["request"].length()) + "\nContent-Type: message/http" +
	"\n" + "\nServer: ft_webserv";
	if (error == 200)
		response = response + request["request"];

	return response.c_str();
}
