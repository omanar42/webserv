/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:01:15 by omanar            #+#    #+#             */
/*   Updated: 2023/06/10 14:27:42 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

int	main(int ac, char **av)
{
	try {

		if (ac != 2)
			throw std::runtime_error("Usage: ./webserv [configuration file]");

		std::ifstream	configFile(av[1]);
		if (!configFile.is_open())
			throw std::runtime_error("Error: Failed to open configuration file: " + std::string(av[1]));

		Server *server = getNextServer(configFile);
		while (server) {
			// server->run();
			std::cout << "--------------- Server ---------------" << std::endl;
			server->printServerConfig();
			server = getNextServer(configFile);
		}

		configFile.close();

	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	
	return 0;
}
