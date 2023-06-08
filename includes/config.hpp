/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:19:19 by omanar            #+#    #+#             */
/*   Updated: 2023/06/08 22:26:40 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <fstream>
# include <sstream>
# include <stdexcept>

// class Location {
// 	private:
// 		std::string		_url;
// 		std::string		_root;
// 		std::string		_index;
// 		std::string		_autoindex;
// 		std::string		_upload_path;
// 		std::string		_redirection;
// 		std::string		_cgi_pass;
// 		std::string		_cgi_extension;
// 		std::vector<std::string>		_methods;
// 	public:
// 		Location();
// 		~Location();
// 		Location(const Location &src);
// 		Location &operator=(const Location &src);
// };

class Config {
	public:
		std::string		_server_name;
		std::string		_host;
		std::string		_port;
		std::string		_max_body_size;
		std::string		_error_page;
		// std::vector<Location>	_locations;
	
		Config();
		~Config();
		Config(const Config &src);
		Config &operator=(const Config &src);
};

#endif
