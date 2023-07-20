/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:01:15 by omanar            #+#    #+#             */
/*   Updated: 2023/07/20 13:11:10 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

int	main(int ac, char **av)
{
	try {
		if (ac != 2)
			throw std::runtime_error("Usage: ./webserv [configuration file]");
		std::vector<Server *> *servers = getServers(av[1]);
		
		std::vector<Server *>::iterator it = servers->begin();
		while (it != servers->end()) {
			std::cout << **it << std::endl;
			delete *it++;
		}
		delete servers;
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	// system("leaks webserv");
	return 0;
}
