/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:17:52 by omanar            #+#    #+#             */
/*   Updated: 2023/07/20 21:40:08 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include "Webserv.hpp"

class Request {
	private:
		std::string _method;
		std::string _url;
		std::string _version;
		std::string _host;
		std::string _userAgent;
		std::string _body;
	public:
		Request(std::string const &request);
		~Request();
		std::string const &getMethod() const;
		std::string const &getUrl() const;
		std::string const &getVersion() const;
		std::string const &getHost() const;
		std::string const &getUserAgent() const;
		std::string const &getBody() const;
		
		void display() const;
};

#endif
