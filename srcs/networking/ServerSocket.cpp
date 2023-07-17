/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:56:23 by omanar            #+#    #+#             */
/*   Updated: 2023/07/17 11:08:08 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerSocket.hpp"

ServerSocket::ServerSocket() {
	// Define address structure
	memset((char *)&_address, 0, sizeof(_address));
	_address.sin_family = AF_INET;
	_address.sin_port = htons(8080);
	_address.sin_addr.s_addr = htonl(INADDR_ANY);
	_address_len = sizeof(_address);
	// Create socket
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == -1)
		throw std::runtime_error("Error creating socket: " + std::string(strerror(errno)));
	std::cout << "Server socket created" << std::endl;
	// Set socket to non-blocking
	// if (fcntl(_socket, F_SETFL, O_NONBLOCK) == -1)
	// 	throw std::runtime_error("Error: fcntl: " + std::string(strerror(errno)));
	// Bind socket
	if (bind(_socket, (struct sockaddr *)&_address, _address_len) == -1)
		throw std::runtime_error("Error binding socket: " + std::string(strerror(errno)));
	std::cout << "Server socket binded" << std::endl;
	// Listen socket
	if (listen(_socket, SOMAXCONN) == -1)
		throw std::runtime_error("Error listening socket: " + std::string(strerror(errno)));
	std::cout << "Server running. Listening on port " << "8080" << "..." << std::endl;
}


ClientSocket ServerSocket::acceptClient() {
	int clientSocket;
	struct sockaddr_in clientAddress;
	socklen_t clientAddressLen = sizeof(clientAddress);

	clientSocket = accept(_socket, (struct sockaddr *)&clientAddress, &clientAddressLen);
	if (clientSocket == -1)
		throw std::runtime_error("Error accepting client: " + std::string(strerror(errno)));
	ClientSocket client(clientSocket, _address);
	return client;
}

void ServerSocket::closeSocket() {
	close(_socket);
}

int ServerSocket::getSocket() const {
	return _socket;
}

int ServerSocket::getPort() const {
	return _port;
}

std::string ServerSocket::getHost() const {
	return _host;
}

struct sockaddr_in ServerSocket::getAddress() const {
	return _address;
}

void ServerSocket::setSocket(int socket) {
	_socket = socket;
}

void ServerSocket::setPort(int port) {
	_port = port;
}

void ServerSocket::setHost(std::string host) {
	_host = host;
}

void ServerSocket::setAddress(struct sockaddr_in address) {
	_address = address;
}

void ServerSocket::setSocketOptions() {
	int opt = 1;

	if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1)
		throw std::runtime_error("Error: " + std::string(strerror(errno)));
}
