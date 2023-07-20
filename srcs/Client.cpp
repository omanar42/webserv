/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:58:43 by omanar            #+#    #+#             */
/*   Updated: 2023/07/17 11:15:24 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client() {
	// Define address structure
	_address.sin_family = AF_INET;
	_address.sin_port = htons(_port);
	_address.sin_addr.s_addr = inet_addr(_host.c_str());
	// Create socket
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == -1)
		throw std::runtime_error("Error: " + std::string(strerror(errno)));
	// Connect socket
	if (connect(_socket, (struct sockaddr *)&_address, sizeof(_address)) == -1)
		throw std::runtime_error("Error: " + std::string(strerror(errno)));
}

Client::Client(int socket, struct sockaddr_in address) {
	_socket = socket;
	_address = address;
}

Client::~Client() {
	close(_socket);
}

void Client::closeSocket() {
	close(_socket);
}

int Client::getSocket() const {
	return _socket;
}

int Client::getPort() const {
	return _port;
}

std::string Client::getHost() const {
	return _host;
}

void Client::setHost(std::string host) {
	_host = host;
}

void Client::setPort(int port) {
	_port = port;
}

void Client::setSocket(int socket) {
	_socket = socket;
}

void Client::setAddress(struct sockaddr_in address) {
	_address = address;
}

std::string Client::receiveRequest() {
	char buffer[1024];
	int bytesReceived = recv(_socket, buffer, 1024, 0);
	if (bytesReceived == -1)
		throw std::runtime_error("Error: " + std::string(strerror(errno)));
	return std::string(buffer, bytesReceived);
}

void Client::sendResponse(std::string response) {
	int bytesSent = send(_socket, response.c_str(), response.size(), 0);
	if (bytesSent == -1)
		throw std::runtime_error("Error: " + std::string(strerror(errno)));
}
