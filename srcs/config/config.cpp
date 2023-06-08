/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:19:39 by omanar            #+#    #+#             */
/*   Updated: 2023/06/08 22:28:58 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.hpp"

Config::Config() {
	this->_server_name = "";
	this->_host = "";
	this->_port = "";
	this->_max_body_size = "";
	this->_error_page = "";
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
		this->_error_page = src._error_page;
	}
	return *this;
}