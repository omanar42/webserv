/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:56:40 by omanar            #+#    #+#             */
/*   Updated: 2023/07/20 10:36:19 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <string>
# include <iostream>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <cstring>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/time.h>
# include <sys/select.h>
# include <vector>
# include <map>
# include <algorithm>
# include <exception>

# define BUFFER_SIZE 1024
# define MAX_CONNECTIONS 100

class Client {
	private:
		int _socket;
		int _port;
		std::string _host;
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
		void setSocket(int socket);
		void setPort(int port);
		void setHost(std::string host);
		void setAddress(struct sockaddr_in address);
		void setSocketOptions();
		void sendResponse(std::string response);
		std::string receiveRequest();
};

#endif