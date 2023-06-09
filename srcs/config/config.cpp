/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:19:39 by omanar            #+#    #+#             */
/*   Updated: 2023/06/09 22:57:23 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.hpp"

Config::Config() {
	this->_server_name = "";
	this->_host = "";
	this->_port = "";
	this->_max_body_size = "";
	this->_locations = new std::vector<Location>;
}

Config::Config(const Config &src) {
	*this = src;
}

Config::~Config() {
}

Config &Config::operator=(const Config &src) {
	if (this != &src) {
		this->_server_name = src._server_name;
		this->_host = src._host;
		this->_port = src._port;
		this->_max_body_size = src._max_body_size;
	}
	return *this;
}

Location::Location() {
	this->_url = "";
	this->_root = "";
	this->_autoindex = "";
	this->_upload_path = "";
	this->_directory_listing = "";
	this->_cgi_pass = "";
	this->_cgi_extension = "";
}

Location::Location(const Location &src) {
	*this = src;
}

Location::~Location() {
}

Location &Location::operator=(const Location &src) {
	if (this != &src) {
		this->_url = src._url;
		this->_root = src._root;
		this->_autoindex = src._autoindex;
		this->_upload_path = src._upload_path;
		this->_directory_listing = src._directory_listing;
		this->_cgi_pass = src._cgi_pass;
		this->_cgi_extension = src._cgi_extension;
		this->_index = src._index;
		this->_methods = src._methods;
	}
	return *this;
}