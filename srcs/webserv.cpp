/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:59:30 by omanar            #+#    #+#             */
/*   Updated: 2023/08/05 23:24:37 by omanar           ###   ########.fr       */
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

void Webserv::simulation() {
	while (true) {
		int res = poll(&pollfds[0], pollfds.size(), -1);
		if (res == -1)
			throw std::runtime_error("Poll failed");
		else if (res > 0) {
			for (size_t i = 0; i < pollfds.size(); ++i) {
				// std::cout << "Dkhaaaaal ============ " << std::endl;
				if (pollfds[i].revents & POLLIN) {
					std::vector<Server *>::iterator it2 = servers->begin();
					while (it2 != servers->end()) {
						if ((*it2)->getSocket() == pollfds[i].fd) {
							struct sockaddr_in clientAddress;
							socklen_t clientAddressLen = sizeof(clientAddress);
							int clientSocket = accept((*it2)->getSocket(), (struct sockaddr *)&clientAddress, &clientAddressLen); 
							if (clientSocket == -1)
								throw std::runtime_error("Accept failed: " + std::string(strerror(errno)));
							struct pollfd pollfd;
							memset(&pollfd, 0, sizeof(pollfd));
							pollfd.fd = clientSocket;
							pollfd.events = POLLIN;
							pollfd.revents = 0;
							pollfds.push_back(pollfd);
							
							break ;
						}
						it2++;
					}
					if (it2 == servers->end()) {
						char buffer[1024];
						memset(buffer, 0, 1024);
						int bytesRead = recv(pollfds[i].fd, buffer, sizeof(buffer), 0);
						if (bytesRead < 0) {
							std::cout << "Client disconnected" << std::endl;
							close(pollfds[i].fd);
							pollfds.erase(pollfds.begin() + i);
						} else {
							std::cout << "Received request: " << std::endl << buffer << std::endl;
							pollfds[i].events = POLLOUT;
						}
					}
				}
				else if (pollfds[i].revents & POLLOUT) {
					std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 48\r\n\r\n<html><body><h1>Hello, World!</h1></body></html>";
					int bytesSent = send(pollfds[i].fd, response.c_str(), response.size(), 0);
					if (bytesSent < 0)
						std::cout << "Error sending response" << std::endl;
					else
						std::cout << "Response sent" << std::endl;
					close(pollfds[i].fd);
				}
			}
		}
	}
}

void Webserv::run() {
	std::vector<Server *>::iterator it = servers->begin();
	while (it != servers->end()) {
		(*it)->run();
		it++;
	}
	
	it = servers->begin();
	while (it != servers->end()) {
		struct pollfd pollfd;
		memset(&pollfd, 0, sizeof(pollfd));
		pollfd.fd = (*it)->getSocket();
		pollfd.events = POLLIN;
		pollfd.revents = 0;
		pollfds.push_back(pollfd);
		it++;
	}

	simulation();
}
