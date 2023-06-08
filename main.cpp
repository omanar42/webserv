/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:01:15 by omanar            #+#    #+#             */
/*   Updated: 2023/06/08 22:29:58 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

Server::Server() {}

Server::Server(Config *config) {
	this->config = config;
}

Server::~Server() {}

void Server::printServerConfig() {
    std::cout << "Server Name: " << this->config->_server_name << std::endl;
	std::cout << "Host: " << this->config->_host << std::endl;
	std::cout << "Port: " << this->config->_port << std::endl;
	std::cout << "Max Body Size: " << this->config->_max_body_size << std::endl;
}

void	ParseServer(std::ifstream &configFile, Config *config)
{
	std::string line;
	while (getline(configFile, line)) {
		if (line.empty() || line[0] == '#')
			continue;
		if (line == "}")
			return;
		std::istringstream iss(line);
		std::string directive;
		iss >> directive;
	
		if (directive == "server_name")
			iss >> config->_server_name;
		else if (directive == "host")
			iss >> config->_host;
		else if (directive == "port")
			iss >> config->_port;
		else if (directive == "max_body_size")
			iss >> config->_max_body_size;
	}
	// else if (directive == "error_pages")
	// 	ParseErrorPages(iss, config);
	// else if (directive == "location")
	// 	ParseLocation(iss, config);
	// else
	// 	throw std::runtime_error("Error: Unknown directive: " + directive);
}

Config	*getNextConfig(std::ifstream &configFile)
{
	std::string line;

	while (getline(configFile, line)) {
		if (line.empty() || line[0] == '#')
			continue;
		std::istringstream iss(line);
		std::string directive;
		iss >> directive;

		if (directive == "server") {
			Config *config = new Config();
			ParseServer(configFile, config);
			return config;
		}
	}
	return NULL;
}

Server *getNextServer(std::ifstream &configFile) {
	Config *config = getNextConfig(configFile);
	if (!config)
		return NULL;
	Server *server = new Server(config);
	return server;
}

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
			std::cout << "-------------------------" << std::endl;
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
