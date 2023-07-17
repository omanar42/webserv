/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 00:22:15 by omanar            #+#    #+#             */
/*   Updated: 2023/07/17 10:11:14 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERSOCKET_HPP
# define SERVERSOCKET_HPP

# include "ClientSocket.hpp"
# include <vector>
# include <sys/select.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <exception>

class ServerSocket {
	private:
		int _socket;
		int _port;
		std::string _host;
		struct sockaddr_in _address;
		socklen_t _address_len;
	public:
		ServerSocket();
		ClientSocket acceptClient();
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
};

#endif
