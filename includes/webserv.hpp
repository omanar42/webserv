/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:05:44 by omanar            #+#    #+#             */
/*   Updated: 2023/06/08 22:25:39 by omanar           ###   ########.fr       */
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
		Server();
		Server(Config *config);
		~Server();
		void printServerConfig();
};

#endif
