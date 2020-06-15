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
#include <vector>

Data::Data()
{
	params = new std::map<std::string, std::string>();
	/// need to discuss what default parameters should be //
	for (int i = 0; i < 10; i++)
	{
		params->operator[](key[i]) = defaults[i];
	}
}



Data::Data(std::string content)
{
	size_t offset;
	params = new std::map<std::string, std::string>();
	for (int i = 0; i < 10; i++)
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
/////////////////////////////////////////////////////////////////////////////////////////
// THIS WILL NEED TO BE UNCOMMENTED. I ONLY COMMENTED IT BECAUSE IT"S ANNOYING AS HECK///
/////////////////////////////////////////////////////////////////////////////////////////
			// if (val == "")
			// 	std::cout << "Warning : Parameter \" " + key[i] + "\" was not set and will have a default value of : " + this->defaults[i] << std::endl;
			params->operator[](key[i]) = val;
		}
	}
	for (int i = 400; i < 505; i++)
	{
		error_pages[i] ="err_pages/" + std::to_string(i) + ".html";
		if (i == 417)
			i = 499;
	}
	std::istringstream str(content.substr(content.find("err_page [") + 1, content.size()));
	std::string word;
	std::vector<int> vec;
	bool isNum = true;
	while (str >> word)
	{
		if (word == "]")
			break ;
		for (int i = 0; i < word.length(); i++)
		{
			if (!std::isdigit(word[i]))
			{
				isNum = false;
				break ;
			}
		}
		if (isNum)
			vec.push_back(std::stoi(word));
		else
		{
			for (int i = 0; i < vec.size(); i++)
				error_pages.operator[](vec[i]) = word;
		}
	}
	std::istringstream strmethod(content.substr(content.find("method [") + 1, content.size()));
	while (strmethod >> word)
	{
		methods.push_back(word);
		if (word == "]")
		break ;
	}
}

int Data::get_port(){return std::stoi(params->operator[]("port"));}

const char* Data::MissingParamException::what() const throw(){return "Missing Parameter";}

