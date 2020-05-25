/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 07:55:28 by jjosephi          #+#    #+#             */
/*   Updated: 2020/05/25 07:55:28 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <list>

class Data
{
private:
	int port;

	std::string hostname;

	std::string server_name;

	std::string err_page;

	std::string search_dir;

	std::string dir_listing;

	std::list<std::string> methods;

	std::string uploads;

	std::string uploads_dir;
public:
	Data();
	
	~Data();

	
};

Data::Data(/* args */)
{
}

Data::~Data()
{
}
