/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:43:05 by omanar            #+#    #+#             */
/*   Updated: 2023/07/31 03:04:37 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

std::string Request::requestParser(std::string const &request, std::string const &directive) {
	size_t pos = request.find(directive);
	if (pos == std::string::npos)
		throw std::runtime_error("bad request");
	size_t start = pos + directive.size();
	size_t end = request.find("\r\n", start);
	if (end == std::string::npos)
		throw std::runtime_error("bad request");
	return (request.substr(start, end - start));
}

std::string Request::bodyParser(std::string const &request) {
	size_t pos = request.find("\r\n\r\n");
	if (pos == std::string::npos)
		throw std::runtime_error("bad request");
	size_t start = pos + 4;
	size_t end = request.size();
	return (request.substr(start, end - start));
}

Request::Request(std::string const &request) {

	size_t pos = request.find("\r\n");
	if (pos == std::string::npos)
		throw std::runtime_error("bad request");
	std::string line = request.substr(0, pos);
	std::istringstream iss(line);
	if ((iss >> _method >> _url >> _version).fail())
		throw std::runtime_error("bad request");
	if (_method != "GET" && _method != "POST" && _method != "DELETE")
		throw std::runtime_error("Method not supported");
	if (_version != "HTTP/1.1")
		throw std::runtime_error("Version not supported");

	_host = requestParser(request, "Host: ");
	_userAgent = requestParser(request, "User-Agent: ");
	if (_method == "POST") {
		_contentLength = requestParser(request, "Content-Length: ");
		_contentType = requestParser(request, "Content-Type: ");
		_body = bodyParser(request);
	}
}

Request::~Request() {}

std::string const &Request::getMethod() const { return _method; }

std::string const &Request::getUrl() const { return _url; }

std::string const &Request::getVersion() const { return _version; }

std::string const &Request::getUserAgent() const { return _userAgent; }

std::string const &Request::getHost() const { return _host; }

std::string const &Request::getContentLength() const { return _contentLength; }

std::string const &Request::getContentType() const { return _contentType; }

std::string const &Request::getBody() const { return _body; }

void Request::display() const {
	std::cout << "Method: " << _method << std::endl;
	std::cout << "Url: " << _url << std::endl;
	std::cout << "Version: " << _version << std::endl;
	std::cout << "User-Agent: " << _userAgent << std::endl;
	std::cout << "Host: " << _host << std::endl;
	std::cout << "Content-Length: " << _contentLength << std::endl;
	std::cout << "Content-Type: " << _contentType << std::endl;
	std::cout << "Body: " << _body << std::endl;
}
