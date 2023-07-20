/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:05:44 by omanar            #+#    #+#             */
/*   Updated: 2023/07/20 12:01:54 by omanar           ###   ########.fr       */
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
# include <netinet/in.h>
# include <sys/select.h>
# include "Server.hpp"
# include "Client.hpp"

class Server;

std::vector<Server *>*	getServers(char *file);

#endif
