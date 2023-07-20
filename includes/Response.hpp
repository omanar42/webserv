/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:59:13 by omanar            #+#    #+#             */
/*   Updated: 2023/07/17 13:08:22 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include <string>
# include <vector>
# include <sstream>
# include <iostream>

class Response {
	private:
		std::string _version;
		std::string _statusCode;
		std::string _statusMessage;
		std::string _date;
		std::string _server;
		std::string _contentType;
		std::string _contentLength;
		std::string _body;
	public:
		Response();
		~Response();
		std::string const &getVersion() const;
		std::string const &getStatusCode() const;
		std::string const &getStatusMessage() const;
		std::string const &getDate() const;
		std::string const &getServer() const;
		std::string const &getContentType() const;
		std::string const &getContentLength() const;
		std::string const &getBody() const;
		void setVersion(std::string const &version);
		void setStatusCode(std::string const &statusCode);
		void setStatusMessage(std::string const &statusMessage);
		void setDate(std::string const &date);
		void setServer(std::string const &server);
		void setContentType(std::string const &contentType);
		void setContentLength(std::string const &contentLength);
		void setBody(std::string const &body);
		std::string toString() const;
};

#endif
