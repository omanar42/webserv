/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:43:05 by omanar            #+#    #+#             */
/*   Updated: 2023/07/17 11:47:31 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

Request::Request(std::string const &request) {
	std::vector<std::string> lines;
	std::stringstream ss(request);
	std::string line;
	while (std::getline(ss, line, '\n')) {
		lines.push_back(line);
	}
	std::vector<std::string> firstLine;
	std::stringstream ssFirstLine(lines[0]);
	std::string word;
	while (std::getline(ssFirstLine, word, ' ')) {
		firstLine.push_back(word);
	}
	_method = firstLine[0];
	_url = firstLine[1];
	_version = firstLine[2];
	for (size_t i = 1; i < lines.size(); i++) {
		std::stringstream ssLine(lines[i]);
		std::string key;
		std::string value;
		std::getline(ssLine, key, ':');
		std::getline(ssLine, value, ':');
		if (key == "Host") {
			_host = value;
		} else if (key == "User-Agent") {
			_userAgent = value;
		}
	}
	_body = lines[lines.size() - 1];
}

Request::~Request() {}

std::string const &Request::getMethod() const {
	return _method;
}

std::string const &Request::getUrl() const {
	return _url;
}

std::string const &Request::getVersion() const {
	return _version;
}

std::string const &Request::getHost() const {
	return _host;
}

std::string const &Request::getUserAgent() const {
	return _userAgent;
}

std::string const &Request::getBody() const {
	return _body;
}

void Request::display() const {
	std::cout << "Method: " << _method << std::endl;
	std::cout << "Url: " << _url << std::endl;
	std::cout << "Version: " << _version << std::endl;
	std::cout << "Host: " << _host << std::endl;
	std::cout << "User-Agent: " << _userAgent << std::endl;
	std::cout << "Body: " << _body << std::endl;
}
