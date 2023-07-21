/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:43:05 by omanar            #+#    #+#             */
/*   Updated: 2023/07/21 19:02:02 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

Request::Request(std::string const &request) {

	std::cout << " ---------- Request ---------------\n[" << request << "]" << std::endl;
	std::cout << " ----------------------------------\n" << std::endl;

	size_t pos = request.find("\r\n");
	if (pos == std::string::npos)
		throw std::runtime_error("bad requ1est");
	std::string line = request.substr(0, pos);
	std::istringstream iss(line);
	if ((iss >> _method >> _url >> _version).fail())
		throw std::runtime_error("bad requ2est");
	if (_method != "GET" && _method != "POST" && _method != "DELETE")
		throw std::runtime_error("Method not supported");
	if (_version != "HTTP/1.1")
		throw std::runtime_error("Version not supported");
	size_t end = request.find("\r\n", pos + 2);
	if (end == std::string::npos)
		throw std::runtime_error("bad requ3est");
	pos = request.find("Host: ");
	if (pos == std::string::npos)
		throw std::runtime_error("bad re4quest");
	size_t start = pos + 6;
	end = request.find("\r\n", start);
	if (end == std::string::npos)
		throw std::runtime_error("bad reque5st");
	_host = request.substr(start, end - start);
	pos = request.find("User-Agent: ");
	if (pos == std::string::npos)
		throw std::runtime_error("bad reque6st");
	start = pos + 12;
	end = request.find("\r\n", start);
	if (end == std::string::npos)
		throw std::runtime_error("bad req7uest");
	_userAgent = request.substr(start, end - start);
	pos = request.find("\r\n\r\n");
	if (pos == std::string::npos)
		throw std::runtime_error("bad re8quest");
	start = pos + 4;
	end = request.find("\r\n", start);
	if (end == std::string::npos)
		_body = request.substr(start, request.length() - start);
}

Request::~Request() {}

std::string const &Request::getMethod() const { return _method; }

std::string const &Request::getUrl() const { return _url; }

std::string const &Request::getVersion() const { return _version; }

std::string const &Request::getHost() const { return _host; }

std::string const &Request::getUserAgent() const { return _userAgent; }

std::string const &Request::getBody() const { return _body; }

void Request::display() const {
	std::cout << "Method: " << _method << std::endl;
	std::cout << "Url: " << _url << std::endl;
	std::cout << "Version: " << _version << std::endl;
	std::cout << "Host: " << _host << std::endl;
	std::cout << "User-Agent: " << _userAgent << std::endl;
	std::cout << "Body: " << _body << std::endl;
}
