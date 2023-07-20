/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:05:44 by omanar            #+#    #+#             */
/*   Updated: 2023/07/20 21:18:56 by omanar           ###   ########.fr       */
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
	public:
		Webserv(char *ConfigFile);
		~Webserv();
		void run();
		void simulation(Server *server);
		void displayInfo();
};

std::vector<Server *>*	getServers(char *file);

#endif
