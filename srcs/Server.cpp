/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:56:23 by omanar            #+#    #+#             */
/*   Updated: 2023/07/17 11:08:08 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() {
	_locations = new std::vector<Location>;
	_error_pages = new std::map<int, std::string>;
	memset((char *)&_address, 0, sizeof(_address));
}

Server::~Server() {
	close(_socket);
	delete _locations;
	delete _error_pages;
}

int Server::getSocket() const { return _socket; }

int Server::getPort() const { return _port; }

int Server::getMaxBodySize() const { return _max_body_size; }

std::string Server::getHost() const { return _host; }

std::string Server::getServerName() const { return _server_name; }

std::vector<Location> *Server::getLocations() const { return _locations; }

std::map<int, std::string> *Server::getErrorPages() const { return _error_pages; }

struct sockaddr_in Server::getAddress() const { return _address; }

socklen_t Server::getAddressLen() const { return _address_len; }

void Server::setSocket(int socket) { _socket = socket; }

void Server::setPort(int port) { _port = port; }

void Server::setMaxBodySize(int max_body_size) { _max_body_size = max_body_size; }

void Server::setHost(std::string host) { _host = host; }

void Server::setServerName(std::string server_name) { _server_name = server_name; }

void Server::setLocations(std::vector<Location> *locations) { _locations = locations; }

void Server::setErrorPages(std::map<int, std::string> *error_pages) { _error_pages = error_pages; }

void Server::setAddress(struct sockaddr_in address) { _address = address; }

void Server::setLocation(Location location) {
	_locations->push_back(location);
}


void Server::setErrorPage(int error_code, std::string error_page) {
	this->_error_pages->insert(std::pair<int, std::string>(error_code, error_page));
}

void Server::setSocketOptions() {
	int opt = 1;

	if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1)
		throw std::runtime_error("Error: " + std::string(strerror(errno)));
}

void Server::createSocket() {
	// Define address structure
	_address.sin_family = AF_INET;
	_address.sin_port = htons(8080);
	_address.sin_addr.s_addr = htonl(INADDR_ANY);
	_address_len = sizeof(_address);
	// Create socket
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == -1)
		throw std::runtime_error("Error creating socket: " + std::string(strerror(errno)));
	std::cout << "Server socket created" << std::endl;
	// if (fcntl(_socket, F_SETFL, O_NONBLOCK) == -1)
	// 	throw std::runtime_error("Error: fcntl: " + std::string(strerror(errno)));
	// std::cout << "Server socket set to non-blocking" << std::endl;
	if (bind(_socket, (struct sockaddr *)&_address, _address_len) == -1)
		throw std::runtime_error("Error binding socket: " + std::string(strerror(errno)));
	std::cout << "Server socket binded" << std::endl;
	if (listen(_socket, SOMAXCONN) == -1)
		throw std::runtime_error("Error listening socket: " + std::string(strerror(errno)));
	std::cout << "Server running. Listening on port " << "8080" << "..." << std::endl;
}

Client Server::acceptClient() {
	int clientSocket;
	struct sockaddr_in clientAddress;
	socklen_t clientAddressLen = sizeof(clientAddress);

	clientSocket = accept(_socket, (struct sockaddr *)&clientAddress, &clientAddressLen);
	if (clientSocket == -1)
		throw std::runtime_error("Error accepting client: " + std::string(strerror(errno)));
	Client client(clientSocket, _address);
	return client;
}

std::ostream &operator<<(std::ostream &out, const Server &server) {
	out << "<---------------- Server ---------------->" << std::endl;
	out << "     Socket: " << server.getSocket() << std::endl;
	out << "     Port: " << server.getPort() << std::endl;
	out << "     Max body size: " << server.getMaxBodySize() << std::endl;
	out << "     Host: " << server.getHost() << std::endl;
	out << "     Server name: " << server.getServerName() << std::endl;
	out << std::endl;
	out << "     Locations:" << std::endl;
	for (std::vector<Location>::const_iterator it = server.getLocations()->begin(); it != server.getLocations()->end(); it++) {
		out << "          <--------- Location --------->" << std::endl;
		out << "          Url: " << (*it)._url << std::endl;
		out << "          Root: " << (*it)._root << std::endl;
		out << "          Index: " << (*it)._index << std::endl;
		out << "          Redirect: " << (*it)._redirect << std::endl;
		out << "          Upload path: " << (*it)._upload_path << std::endl;
		out << "          Directory listing: " << (*it)._directory_listing << std::endl;
		out << "          Methods: ";
		for (std::map<std::string, bool>::const_iterator it2 = (*it)._methods.begin(); it2 != (*it)._methods.end(); it2++)
			out << it2->first << ": " << it2->second << " | ";
		out << std::endl;
		out << "          Cgi extensions: ";
		for (std::vector<std::string>::const_iterator it2 = (*it)._cgi_extensions.begin(); it2 != (*it)._cgi_extensions.end(); it2++)
			out << *it2 << " | ";
		out << std::endl << std::endl;
	}
	out << std::endl;
	out << "          <--------- Error pages --------->" << std::endl;
	for (std::map<int, std::string>::const_iterator it = server.getErrorPages()->begin(); it != server.getErrorPages()->end(); it++)
		out << "          " << it->first << ": " << it->second << std::endl;
	out << "<---------------- End Server ---------------->" << std::endl;
	return out;
}
