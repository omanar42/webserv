/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:59:30 by omanar            #+#    #+#             */
/*   Updated: 2023/07/20 12:28:39 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include "Request.hpp"

int main() {
	try {
		ServerSocket server;
		int i = 0;
		while (1) {
			std::cout << "\n   | Waiting for client...\n" << std::endl;
			ClientSocket client = server.acceptClient();
			std::cout << "Client connected" << ++i << std::endl;
			std::string request = client.receiveRequest();
			std::cout << "Request received\n" << std::endl;
			std::cout <<  "'" << request << "'" << std::endl << std::endl;
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
