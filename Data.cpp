/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 18:15:31 by jjosephi          #+#    #+#             */
/*   Updated: 2020/05/26 18:15:31 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"
#include <sstream>

Data::Data()
{
	params = new std::map<std::string, std::string>();
	/// need to discuss what default parameters should be //
	for (int i = 0; i < 11; i++)
	{
		params->operator[](key[i]) = defaults[i];
	}
}


Data::Data(std::string content)
{
	size_t offset;
	params = new std::map<std::string, std::string>();
	for (int i = 0; i < 11; i++)
	{
		if (content.find(key[i]) == content.npos)
		{
			std::cout << "Parameter \"" + key[i] + "\" is missing\n";
			throw MissingParamException();
		}
		else
		{
			offset = content.find(key[i]) + key[i].length() + 1;
			std::string val = content.substr(offset, content.find("\n", offset) - offset);		
			if (val == "")
				std::cout << "Warning : Parameter \" " + key[i] + "\" was not set and will have a default value of : " + this->defaults[i] << std::endl;
			params->operator[](key[i]) = val;
			std::cout << "key : " << key[i] << " | value : " << val << std::endl;
		}
	}
	std::istringstream str(content.substr(content.find("[") + 1, (content.find("]") - content.find("[") - 1)));
	std::string word;

	while (str >> word)
	{
		methods.push_back(word);
		std::cout << "method " + word << std::endl;
	}
}

const char* Data::MissingParamException::what() const throw(){return "Missing Parameter";}

