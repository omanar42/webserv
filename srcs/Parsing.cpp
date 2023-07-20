/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:21:29 by omanar            #+#    #+#             */
/*   Updated: 2023/07/20 13:08:18 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool	isNumber(const std::string& s) {
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

void	hostChecker(std::string const &host) {
	if (host[0] == '.' || host[host.length() - 1] == '.')
		throw std::runtime_error("Error: Invalid host");
	std::vector<std::string> tokens;
	std::istringstream iss(host);
	std::string token;
	while (getline(iss, token, '.')) {
		if (token.empty())
			throw std::runtime_error("Error: Invalid host");
		if (!isNumber(token) || atoi(token.c_str()) > 255)
			throw std::runtime_error("Error: Invalid host");
		tokens.push_back(token);
	}
	if (tokens.size() != 4)
		throw std::runtime_error("Error: Invalid host");
}

std::string	parser(std::string const &line) {
	std::string value;
	std::string token;
	size_t pos = line.find(';');
	if (pos == std::string::npos)
		throw std::runtime_error("Error: missing ';'");
	std::string tmp = line.substr(0, pos);
	std::istringstream iss(tmp);
	iss >> token;
	iss >> value;
	if (value.empty())
		throw std::runtime_error("Error: missing value");
	if ((iss >> token))
		throw std::runtime_error("Error: syntax error: '" + token + "'");
	return value;
}

void	errorPagesLineChecker(std::string &line) {
	std::string token;
	std::istringstream iss(line);
	iss >> token;
	if (token.empty() || token[0] == '#')
		return;
	if (token == "}") {
		if ((iss >> token) && token[0] != '#')
			throw std::runtime_error("Error: error_pages syntax error: '" + token + "'");
		return;
	}
	size_t pos = line.find(';');
	if (pos == std::string::npos)
		throw std::runtime_error("Error: missing ';'");
	line = line.substr(0, pos);
	if (isNumber(token))
		return;
	throw std::runtime_error("Error: error_pages syntax error: '" + token + "'");
}

void	ParseErrorPage(std::ifstream &configFile, Server *server) {
	std::string line;
	while (getline(configFile, line)) {
		errorPagesLineChecker(line);
		std::vector<int> errors;
		std::istringstream iss(line);
		std::string token;
		int number;

		while (iss >> token) {
			if (token == "}") {
				if ((iss >> token) && token[0] != '#')
					throw std::runtime_error("Error: server syntax error: '" + token + "'");
				return;
			}
			if (token.empty() || token == "#")
				break;
			if (isNumber(token)) {
				number = atoi(token.c_str());
				if (number < 100 || number > 599)
					throw std::runtime_error("Error: error_pages: invalid status code: " + token);
				errors.push_back(number);
			}
			else {
				if (iss >> token)
					throw std::runtime_error("Error: error_pages syntax error: '" + token + "'");
				std::vector<int>::iterator it = errors.begin();
				for (; it != errors.end(); it++)
					server->setErrorPage(*it, token);
				break;
			}
		}
	}
	throw std::runtime_error("Error: error_pages block not closed");
}

void	parseMethods(std::string &line, std::map<std::string, bool> &methods) {
	size_t pos = line.find(';');
	if (pos == std::string::npos)
		throw std::runtime_error("Error: missing ';'");
	line.erase(pos);
	std::string token;
	std::istringstream iss(line);
	iss >> token;
	while (iss >> token) {
		if (token == "GET")
			methods.insert(std::pair<std::string, bool>("GET", true));
		else if (token == "POST")
			methods.insert(std::pair<std::string, bool>("POST", true));
		else if (token == "DELETE")
			methods.insert(std::pair<std::string, bool>("DELETE", true));
		else
			throw std::runtime_error("Error: Unknown method: " + token);
	}
}

void	parseExtensions(std::string &line, std::vector<std::string> &extensions) {
	size_t pos = line.find(';');
	if (pos == std::string::npos)
		throw std::runtime_error("Error: missing ';'");
	line.erase(pos);
	std::string token;
	std::istringstream iss(line);
	iss >> token;
	while (iss >> token) {
		if (token[0] != '.')
			throw std::runtime_error("Error: extension must start with '.'");
		extensions.push_back(token);
	}
	if (extensions.size() > 2)
		throw std::runtime_error("Error: too many extensions");
	for (std::vector<std::string>::iterator it = extensions.begin(); it != extensions.end(); it++) {
		if (*it != ".php" && *it != ".py")
			throw std::runtime_error("Error: invalid extension: " + *it);
	}
}

Location	ParseLocation(std::ifstream &configFile, std::istringstream &is) {
	std::string line;
	Location location;

	is >> location._url;
	if (location._url.empty() || location._url[0] == '{')
		throw std::runtime_error("Error: missing url");
	is >> line;
	if (line != "{" || ((is >> line) && line[0] != '#'))
		throw std::runtime_error("Error: location syntax error: '" + line + "'");
	line.clear();
	while (getline(configFile, line)) {
		std::istringstream iss(line);
		std::string directive;
		iss >> directive;
		if (directive == "}") {
			if ((iss >> directive) && directive[0] != '#')
				throw std::runtime_error("Error: location syntax error: '" + directive + "'");
			return location;
		}
		if (directive.empty() || directive[0] == '#')
			continue;
		else if (directive == "methods")
			parseMethods(line, location._methods);
		else if (directive == "redirect")
			location._redirect = parser(line);
		else if (directive == "index")
			location._index = parser(line);
		else if (directive == "root")
			location._root = parser(line);
		else if (directive == "upload_path")
			location._upload_path = parser(line);
		else if (directive == "directory_listing") {
			directive = parser(line);
			if (directive == "on")
				location._directory_listing = true;
			else if (directive == "off")
				location._directory_listing = false;
			else
				throw std::runtime_error("Error: Unknown directory_listing directive: " + directive);
		}
		else if (directive == "cgi_extensions")
			parseExtensions(line, location._cgi_extensions);
		else
			throw std::runtime_error("Error: Unknown location directive: " + directive);
	}
	throw std::runtime_error("Error: Location block not closed");
}

Server*	ParseServer(std::ifstream &configFile) {
	Server *server = new Server();
	std::string line;
	while (getline(configFile, line)) {
		std::istringstream iss(line);
		std::string directive;
		iss >> directive;

		if (directive == "}") {
			if ((iss >> directive) && directive[0] != '#')
				throw std::runtime_error("Error: server syntax error: '" + directive + "'");
			return server;
		}
		if (directive.empty() || directive[0] == '#')
			continue;
		if (directive == "server_name")
			server->setServerName(parser(line));
		else if (directive == "host") {
			server->setHost(parser(line));
			hostChecker(server->getHost());
		}
		else if (directive == "port") {
			std::string port;
			port = parser(line);
			if (isNumber(port)) {
				server->setPort(atoi(port.c_str()));
				if (server->getPort() < 0 || server->getPort() > 65535)
					throw std::runtime_error("Error: port number out of range");
			}
			else
				throw std::runtime_error("Error: Invalid port number");
		}
		else if (directive == "max_body_size") {
			std::string size;
			iss >> size;
			size = parser(line);
			if (isNumber(size))
				server->setMaxBodySize(atoi(size.c_str()));
			else
				throw std::runtime_error("Error: Invalid client_max_body_size value");
		}
		else if (directive == "error_pages") {
			iss >> directive;
			if (directive != "{" || ((iss >> directive) && directive[0] != '#'))
				throw std::runtime_error("Error: error_pages syntax error: '" + directive + "'");
			ParseErrorPage(configFile, server);
		}
		else if (directive == "location") {
			server->setLocation(ParseLocation(configFile, iss));
		}
		else
			throw std::runtime_error("Error: Unknown directive: " + directive);
	}
	throw std::runtime_error("Error: server block not closed");
}

Server*	getNextServer(std::ifstream &configFile) {
	std::string line;

	while (getline(configFile, line)) {
		std::istringstream iss(line);
		std::string directive;
		iss >> directive;
		if (directive.empty() || directive[0] == '#')
			continue;
		else if (directive == "server") {
			iss >> directive;
			if (directive != "{" || ((iss >> directive) && directive[0] != '#'))
				throw std::runtime_error("Error: server syntax error: '" + directive + "'");
			return ParseServer(configFile);
		}
		else
			throw std::runtime_error("Error: Unknown directive: " + directive);
	}
	return NULL;
}

void	isMissing(Server *server) {
	bool missing = true;
	if (server->getHost().empty())
		throw std::runtime_error("Error: Missing host directive");
	if (server->getPort() == -1)
		throw std::runtime_error("Error: Missing host directive");
	if (server->getMaxBodySize() == -1)
		throw std::runtime_error("Error: Missing max_body_size directive");
	std::vector<Location>::iterator it = server->getLocations()->begin();
	for (; it != server->getLocations()->end(); it++) {
		if (it->_url == "/")
			missing = false;
		if (it->_root.empty())
			throw std::runtime_error("Error: Missing root directive");
		if (it->_index.empty())
			throw std::runtime_error("Error: Missing index directive");
	}
	if (missing)
		throw std::runtime_error("Error: Missing default location");
}

bool isDuplicate(std::vector<Server *> *servers, std::string const &host, int const &port) {
	std::vector<Server *>::iterator it = servers->begin();
	for (; it != servers->end(); it++) {
		if ((*it)->getHost() == host && (*it)->getPort() == port)
			return true;
	}
	return false;
}


std::vector<Server *>*	getServers(char *file) {
	std::ifstream	configFile(file);
	if (!configFile.is_open())
		throw std::runtime_error("Error: Failed to open configuration file: " + std::string(file));

	std::vector<Server *> *servers = new std::vector<Server *>;

	Server *server = getNextServer(configFile);
	while (server) {
		isMissing(server);
		bool duplicate = isDuplicate(servers, server->getHost(), server->getPort());
		if (!duplicate)
			servers->push_back(server);
		server = getNextServer(configFile);
	}

	configFile.close();
	return servers;
}
