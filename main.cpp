/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:01:15 by omanar            #+#    #+#             */
/*   Updated: 2023/06/09 13:58:31 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

Server::Server() {}

Server::Server(Config *config) {
	this->config = config;
}

Server::~Server() {}

void Server::printServerConfig() {
    std::cout << "  Server Name: " << this->config->_server_name << std::endl;
	std::cout << "  Host: " << this->config->_host << std::endl;
	std::cout << "  Port: " << this->config->_port << std::endl;
	std::cout << "  Max Body Size: " << this->config->_max_body_size << std::endl;

	std::vector<Location>::iterator it = this->config->_locations->begin();
	while (it != this->config->_locations->end()) {
		std::cout << "  Location: " << it->_url << " {" << std::endl;
		std::cout << "      Root: " << it->_root << std::endl;
		std::cout << "      Autoindex: " << it->_autoindex << std::endl;
		std::cout << "      Upload Path: " << it->_upload_path << std::endl;
		std::cout << "      Directory Listing: " << it->_directory_listing << std::endl;
		std::cout << "      CGI Pass: " << it->_cgi_pass << std::endl;
		std::cout << "      CGI Extension: " << it->_cgi_extension << std::endl;
		std::cout << "      Methods: ";
		std::vector<std::string>::iterator it2 = it->_methods.begin();
		while (it2 != it->_methods.end()) {
			std::cout << *it2 << " ";
			it2++;
		}
		std::cout << std::endl;
		std::cout << "      Index: ";
		it2 = it->_index.begin();
		while (it2 != it->_index.end()) {
			std::cout << *it2 << " ";
			it2++;
		}
		std::cout << std::endl << "  }" << std::endl;
		it++;
	}
}

Location	ParseLocation(std::ifstream &configFile, std::istringstream &is) {
	std::string line;
	Location location;

	is >> location._url;
	while (getline(configFile, line)) {
		if (line.empty() || line[0] == '#')
			continue;
		if (line == "    }")
			return location;
		std::istringstream iss(line);
		std::string directive;
		iss >> directive;
	
		if (directive == "methods") {
			std::string method;
			while (iss >> method)
				location._methods.push_back(method);
		}
		else if (directive == "root")
			iss >> location._root;
		else if (directive == "autoindex")
			iss >> location._autoindex;
		else if (directive == "index") {
			std::string index;
			while (iss >> index)
				location._index.push_back(index);
		}
		else if (directive == "upload_path")
			iss >> location._upload_path;
		else if (directive == "cgi_pass")
			iss >> location._cgi_pass;
		else if (directive == "cgi_extension")
			iss >> location._cgi_extension;
		else if (directive == "directory_listing")
			iss >> location._directory_listing;
		// else
		// 	throw std::runtime_error("Error: Unknown location directive: " + directive);
	}
	throw std::runtime_error("Error: Location block not closed");
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
	
		if (directive == "server_name") {
			// parse server name until ;
			std::string server_name;
			while (iss >> server_name) {
				if (server_name[server_name.length() - 1] == ';') {
					server_name = server_name.substr(0, server_name.length() - 1);
					config->_server_name = server_name;
					break;
				}
				config->_server_name += server_name + " ";
			}
		}
			// iss >> config->_server_name;
		else if (directive == "host")
			iss >> config->_host;
		else if (directive == "port")
			iss >> config->_port;
		else if (directive == "max_body_size")
			iss >> config->_max_body_size;
		else if (directive == "location")
			config->_locations->push_back(ParseLocation(configFile, iss));
	}
		// else if (directive == "error_pages")
		// 	ParseErrorPages(iss, config);
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
