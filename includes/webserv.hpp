/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:05:44 by omanar            #+#    #+#             */
/*   Updated: 2023/06/10 18:54:18 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <fstream>
# include <sstream>
# include <stdexcept>
# include "config.hpp"

class Server {
	private:
		Config *config;
	public:
		Server(Config *config);
		~Server();
		void printServerConfig();
};

std::vector<Server *>	getServers(char *file);
Server*	getNextServer(std::ifstream &configFile);
Config*	getNextConfig(std::ifstream &configFile);

#endif
