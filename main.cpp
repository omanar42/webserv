/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:01:15 by omanar            #+#    #+#             */
/*   Updated: 2023/06/10 18:45:14 by omanar           ###   ########.fr       */
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

		Server *server;
		while ((server = getNextServer(configFile))) {
			// server->run();
			std::cout << "--------------- Server ---------------" << std::endl;
			server->printServerConfig();
			delete server;
		}

		configFile.close();

	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
