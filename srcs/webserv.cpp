/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:59:30 by omanar            #+#    #+#             */
/*   Updated: 2023/07/24 02:55:48 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserv.hpp"

Webserv::Webserv(char *ConfigFile) {
	servers = getServers(ConfigFile);
}

Webserv::~Webserv() {
	std::vector<Server *>::iterator it = servers->begin();
	while (it != servers->end())
		delete *it++;
	delete servers;
}

void Webserv::displayInfo() {
	std::vector<Server *>::iterator it = servers->begin();
	while (it != servers->end())
		std::cout << **it++ << std::endl;
}

void Webserv::simulation(Server *server) {
	// while (true) {
		try {
			std::cout << "\n   | Waiting for client...\n" << std::endl;
			Client client = server->acceptClient();
			std::cout << "Client connected" << std::endl;
			client.getRequest()->display();
			std::cout << "Request received\n" << std::endl;
			client.sendResponse("HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body><h1>Hello, World!</h1></body></html>");
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	// }
}

void Webserv::run() {
	std::vector<Server *>::iterator it = servers->begin();
	while (it != servers->end()) {
		(*it)->run();
		it++;
	}
		
	simulation(servers->front());
	// close(server->getSocket());
}
