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


#define PORT 80
int main(int argc, char const *argv[])
{
	std::vector<Data> servers;
    t_loop_data *data;

	servers = serv_init();
	data = &loop_init(servers);
	slct_loop(data);
}