/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:58:43 by omanar            #+#    #+#             */
/*   Updated: 2023/07/17 11:15:24 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientSocket.hpp"

ClientSocket::ClientSocket() {
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

ClientSocket::ClientSocket(int socket, struct sockaddr_in address) {
	_socket = socket;
	_address = address;
}

ClientSocket::~ClientSocket() {
	close(_socket);
}

void ClientSocket::closeSocket() {
	close(_socket);
}

int ClientSocket::getSocket() const {
	return _socket;
}

int ClientSocket::getPort() const {
	return _port;
}

std::string ClientSocket::getHost() const {
	return _host;
}

void ClientSocket::setHost(std::string host) {
	_host = host;
}

void ClientSocket::setPort(int port) {
	_port = port;
}

void ClientSocket::setSocket(int socket) {
	_socket = socket;
}

void ClientSocket::setAddress(struct sockaddr_in address) {
	_address = address;
}

std::string ClientSocket::receiveRequest() {
	char buffer[1024];
	int bytesReceived = recv(_socket, buffer, 1024, 0);
	if (bytesReceived == -1)
		throw std::runtime_error("Error: " + std::string(strerror(errno)));
	return std::string(buffer, bytesReceived);
}

void ClientSocket::sendResponse(std::string response) {
	int bytesSent = send(_socket, response.c_str(), response.size(), 0);
	if (bytesSent == -1)
		throw std::runtime_error("Error: " + std::string(strerror(errno)));
}
