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
	_address.sin_family = AF_INET;
	_address.sin_port = htons(_port);
	_address.sin_addr.s_addr = inet_addr(_host.c_str());
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == -1)
		throw std::runtime_error("Error: " + std::string(strerror(errno)));
	if (connect(_socket, (struct sockaddr *)&_address, sizeof(_address)) == -1)
		throw std::runtime_error("Error: " + std::string(strerror(errno)));
}

Client::Client(int socket, struct sockaddr_in address) {
	_socket = socket;
	_address = address;
	this->receiveRequest();
}

Client::~Client() {
	close(_socket);
	delete _request;
	std::cout << "Client deleted" << std::endl;
	// delete _response;
}

void Client::closeSocket() {
	close(_socket);
}

int Client::getSocket() const { return _socket; }

int Client::getPort() const { return _port; }

std::string Client::getHost() const { return _host; }

struct sockaddr_in Client::getAddress() const { return _address; }

Request *Client::getRequest() const { return _request; }

void Client::setHost(std::string host) { _host = host; }

void Client::setPort(int port) { _port = port; }

void Client::setSocket(int socket) { _socket = socket; }

void Client::setAddress(struct sockaddr_in address) { _address = address; }

void Client::receiveRequest() {
	char buffer[BS];
	int bytesReceived = recv(_socket, buffer, BS, 0);
	if (bytesReceived == -1)
		throw std::runtime_error("Error: " + std::string(strerror(errno)));
	_request = new Request(std::string(buffer, bytesReceived));
}

void Client::sendResponse(std::string response) {
	int bytesSent = send(_socket, response.c_str(), response.size(), 0);
	if (bytesSent == -1)
		throw std::runtime_error("Error: " + std::string(strerror(errno)));
}
