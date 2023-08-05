/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:56:40 by omanar            #+#    #+#             */
/*   Updated: 2023/08/05 22:36:40 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Webserv.hpp"

# define BS 1024
# define MAX_CONNECTIONS 100

class Request;
class Response;

class Client {
	private:
		int _socket;
		int _port;
		std::string _host;
		Request *_request;
		// Response *_response;
		struct sockaddr_in _address;
	public:
		Client();
		Client(int socket, struct sockaddr_in address);
		~Client();
		void closeSocket();
		int getSocket() const;
		int getPort() const;
		std::string getHost() const;
		struct sockaddr_in getAddress() const;
		Request *getRequest() const;
		void setSocket(int socket);
		void setPort(int port);
		void setHost(std::string host);
		void setAddress(struct sockaddr_in address);
		void receiveRequest();
		void sendResponse(std::string response);
};

#endif
