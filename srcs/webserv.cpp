/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:59:30 by omanar            #+#    #+#             */
/*   Updated: 2023/08/05 22:29:13 by omanar           ###   ########.fr       */
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
			// std::vector<struct pollfd>::iterator it = pollfds.begin();
			for (size_t i = 0; i < pollfds.size(); ++i) {
				// std::cout << "Dkhaaaaal ============ " << std::endl;
				if (pollfds[i].revents & POLLIN) {
					std::vector<Server *>::iterator it2 = servers->begin();
					while (it2 != servers->end()) {
						if ((*it2)->getSocket() == pollfds[i].fd) {
							int clientSocket = (*it2)->acceptConnection();
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
						// int clientSocket = it->fd;

						// char buffer[1024];
						// memset(buffer, 0, 1024);
						// int bytesRead = recv(clientSocket, buffer, 1024, 0);
						// if (bytesRead == -1)
						// 	throw std::runtime_error("Recv failed " + std::string(strerror(errno)));
						// else if (bytesRead == 0) {
						// 	std::cout << "Client disconnected" << std::endl;
						// 	close(clientSocket);
						// 	it = pollfds.erase(it);
						// 	continue ;
						// } else {
						// 	std::cout << "Received request: " << std::endl << buffer << std::endl;
						// 	it->events = POLLOUT;
						// }

						char buffer[1024];
						ssize_t bytesRead = recv(pollfds[i].fd, buffer, sizeof(buffer), 0);
						if (bytesRead <= 0) {
							close(pollfds[i].fd);
							pollfds.erase(pollfds.begin() + i);
						} else {
							std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Hello, World!</h1></body></html>";
							send(pollfds[i].fd, response.c_str(), response.size(), 0);
							close(pollfds[i].fd);
						}
					}
				}
				// if (it->revents & POLLOUT) {
				// 	int clientSocket = it->fd;
				// 	std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Hello, World!</h1></body></html>";
				// 	int bytesSent = send(clientSocket, response.c_str(), response.size(), 0);
				// 	if (bytesSent == -1)
				// 		throw std::runtime_error("Send Failed: " + std::string(strerror(errno)));
				// 	else
				// 		std::cout << "Response sent" << std::endl;
				// 	close(clientSocket);
				// }
				// it++;
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
