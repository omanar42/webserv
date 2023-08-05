/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 00:22:15 by omanar            #+#    #+#             */
/*   Updated: 2023/08/05 22:24:20 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Webserv.hpp"

class Client;

struct Location {
	std::string	_url;
	std::string	_root;
	std::string	_index;
	std::string	_redirect;
	std::string	_upload_path;
	bool		_directory_listing;
	std::map<std::string, bool>	_methods;
	std::vector<std::string>	_cgi_extensions;
};

class Server {
	private:
		int	_socket;
		int	_port;
		int	_max_body_size;
		std::string	_host;
		std::string	_server_name;
		std::vector<Location>	*_locations;
		std::map<int, std::string>	*_error_pages;
		std::vector<Client>	_clients;
		struct sockaddr_in	_address;
		socklen_t	_address_len;
	public:
		Server();
		~Server();
		int getSocket() const;
		int getPort() const;
		int getMaxBodySize() const;
		std::string getHost() const;
		std::string getServerName() const;
		std::vector<Location> *getLocations() const;
		std::map<int, std::string> *getErrorPages() const;
		struct sockaddr_in getAddress() const;
		socklen_t getAddressLen() const;
		void setSocket(int socket);
		void setPort(int port);
		void setMaxBodySize(int max_body_size);
		void setHost(std::string host);
		void setServerName(std::string server_name);
		void setLocation(Location location);
		void setLocations(std::vector<Location> *locations);
		void setErrorPage(int error_code, std::string error_page);
		void setErrorPages(std::map<int, std::string> *error_pages);
		void setAddress(struct sockaddr_in address);
		void setSocketOptions();
		void run();
		int acceptConnection();
};

std::ostream &operator<<(std::ostream &out, const Server &server);

#endif
