/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 15:18:05 by jjosephi          #+#    #+#             */
/*   Updated: 2020/05/28 15:18:05 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Data.hpp"
# include <iostream>
# include <sstream>
# include <string>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <errno.h>
# include <arpa/inet.h>
# include <vector>
# include <sstream>

std::map<int, std::string> errors{
  errors[200] = " OK";
  errors[201] = " Created";
  errors[204] = " No Content";
  errors[400] = " Bad Request";
  errors[401] = " Unauthorized"`	;
  errors[402] = " Payment Required";
  errors[403] = " Forbidden";
  errors[404] = " Not Found";
  errors[405] = " Method Not Allowed";
  errors[406] = " Not Acceptable";
  errors[407] = " Proxy Authentication Required";
  errors[408] = " Request Timeout";
  errors[409] = " Conflict";
  errors[410] = " Gone";
  errors[411] = " Length Required";
  errors[412] = " Precondition Failed";
  errors[413] = " Payload Too Large";
  errors[414] = " URI Too Long";
  errors[415] = " Unsupported Media Type";
  errors[416] = " Range Not Satisfiable";
  errors[417] = " Expectation Failed";
  errors[418] = " I'm a teapot";
  errors[421] = " Misdirected Request";
  errors[422] = " Unprocessable Entity (WebDAV)";
  errors[423] = " Locked (WebDAV)";
  errors[424] = " Failed Dependency (WebDAV)";
  errors[425] = " Too Early";
  errors[426] = " Upgrade Required";
  errors[428] = " Precondition Required";
  errors[429] = " Too Many Requests";
  errors[431] = " Request Header Fields Too Large";
  errors[451] = " Unavailable For Legal Reasons";
  errors[501] = " Not Implemented";
}


struct sockaddr_in;
struct timeval;

typedef struct s_loop_data
{
	int i, check_socket, on,max_sd, new_sd, size;
	std::vector<int> *listen_sd;
	std::vector<sockaddr_in> *address;
	timeval time_out;
	std::vector<Data> servers;
	fd_set master_set, working_set, reading_set, writing_set; // set of socket descriptors
}				t_loop_data;

std::vector<Data> serv_init();

t_loop_data &loop_init(std::vector<Data> servers);


void slct_loop(t_loop_data* data);

/*parse.cpp*/
std::map<std::string, std::string> parse_headers(const char *s, int *error);

std::map<std::string, std::string> parse_request_line(const char *s, int *error);

/*requests.cpp*/
char *req_error(std::map<std::string, std::string> lines, Data data, int error);

char *req_get_head(std::map<std::string, std::string> request,
	std::map<std::string, std::string> lines, Data data, int error)

char *req_post(std::map<std::string, std::string> request,
	std::map<std::string, std::string> lines, Data data);

char *req_put(std::map<std::string, std::string> request,
	std::map<std::string, std::string> lines, Data data);

char *req_delete(std::map<std::string, std::string> request,
	std::map<std::string, std::string> lines, Data data);

char *req_options(std::map<std::string, std::string> request,
	std::map<std::string, std::string> lines, Data data);

char *req_trace(std::map<std::string, std::string> request,
	std::map<std::string, std::string> lines, Data data);

/*utils.cpp*/
std::string get_extension(std::string filename);


const char* process_request(std::vector<Data> data, int port,const char *msg);

#endif
