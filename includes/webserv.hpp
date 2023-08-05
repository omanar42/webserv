/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:05:44 by omanar            #+#    #+#             */
/*   Updated: 2023/08/05 22:36:32 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <map>
# include <vector>
# include <string>
# include <fstream>
# include <sstream>
# include <iostream>
# include <poll.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <exception>
# include <stdexcept>
# include <sys/time.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <sys/select.h>
# include "Server.hpp"
# include "Client.hpp"
# include "Request.hpp"
# include "Response.hpp"

class Server;

class Webserv {
	private:
		std::vector<Server *>* servers;
		std::vector<struct pollfd> pollfds;
	public:
		Webserv(char *ConfigFile);
		~Webserv();
		void run();
		void simulation();
		void displayInfo();
};

std::vector<Server *>*	getServers(char *file);

#endif
