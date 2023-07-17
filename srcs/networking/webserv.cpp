/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:59:30 by omanar            #+#    #+#             */
/*   Updated: 2023/07/17 11:46:54 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerSocket.hpp"
#include "ClientSocket.hpp"
#include "Request.hpp"

int main() {
	try {
		ServerSocket server;
		while (1) {
			std::cout << "\n   | Waiting for client...\n" << std::endl;
			ClientSocket client = server.acceptClient();
			std::cout << "Client connected" << std::endl;
			std::string request = client.receiveRequest();
			Request req(request);
			req.display();
			client.sendResponse("HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body><h1>Hello, World!</h1></body></html>");
			client.closeSocket();
		}
		server.closeSocket();
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
