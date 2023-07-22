/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:17:52 by omanar            #+#    #+#             */
/*   Updated: 2023/07/22 13:34:30 by omanar           ###   ########.fr       */
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
		std::string _userAgent;
		std::string _host;
		std::string _contentLength;
		std::string _contentType;
		std::string _body;
	public:
		Request(std::string const &request);
		~Request();
		std::string const &getMethod() const;
		std::string const &getUrl() const;
		std::string const &getVersion() const;
		std::string const &getUserAgent() const;
		std::string const &getHost() const;
		std::string const &getContentLength() const;
		std::string const &getContentType() const;
		std::string const &getBody() const;
		std::string requestParser(std::string const &request, std::string const &directive);
		std::string bodyParser(std::string const &request);
		
		void display() const;
};

#endif
