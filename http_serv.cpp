/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_serv.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 15:40:51 by jjosephi          #+#    #+#             */
/*   Updated: 2020/06/03 18:18:29 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

std::map<int, std::string> errors = {
  {200, " OK"},
  {201, "Created"},
  {204, "No Content"},
  {400, "Bad Request"},
  {401, "Unauthorized"},
  {402, "Payment Required"},
  {403, "Forbidden"},
  {404, "Not Found"},
  {405, "Method Not Allowed"},
  {406, "Not Acceptable"},
  {407, "Proxy Authentication Required"},
  {408, "Request Timeout"},
  {409, "Conflict"},
  {410, "Gone"},
  {411, "Length Required"},
  {412, "Precondition Failed"},
  {413, "Payload Too Large"},
  {414, "URI Too Long"},
  {415, "Unsupported Media Type"},
  {416, "Range Not Satisfiable"},
  {417, "Expectation Failed"},
  {418, "I'm a teapot"},
  {421, "Misdirected Request"},
  {422, "Unprocessable Entity (WebDAV)"},
  {423, "Locked (WebDAV)"},
  {424, "Failed Dependency (WebDAV)"},
  {425, "Too Early"},
  {426, "Upgrade Required"},
  {428, "Precondition Required"},
  {429, "Too Many Requests"},
  {431, "Request Header Fields Too Large"},
  {451, "Unavailable For Legal Reasons"},
  {501, "Not Implemented"},
};

#define PORT 80
int main(int argc, char const *argv[])
{
	std::vector<Data> servers;
    t_loop_data *data;

	servers = serv_init();
	data = &loop_init(servers);
	slct_loop(data);
}
