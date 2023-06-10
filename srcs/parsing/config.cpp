/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:19:39 by omanar            #+#    #+#             */
/*   Updated: 2023/06/10 18:01:46 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.hpp"

Location::Location() {
	this->_url = "";
	this->_root = "";
	this->_redirect = "";
	this->_upload_path = "";
	this->_cgi_pass = "";
	this->_cgi_extension = "";
	this->_directory_listing = false;
}

Config::Config() {
	this->_server_name = "";
	this->_host = "";
	this->_port = "";
	this->_max_body_size = "";
	this->_locations = new std::vector<Location>;
}

Config::~Config() {
	delete this->_locations;
}