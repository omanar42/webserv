/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:02:40 by omanar            #+#    #+#             */
/*   Updated: 2023/08/05 22:36:20 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response() {}

Response::~Response() {}

std::string const &Response::getVersion() const { return _version; }

std::string const &Response::getStatusCode() const { return _statusCode; }

std::string const &Response::getStatusMessage() const { return _statusMessage; }

std::string const &Response::getDate() const { return _date; }

std::string const &Response::getServer() const { return _server; }

std::string const &Response::getContentType() const { return _contentType; }

std::string const &Response::getContentLength() const { return _contentLength; }

std::string const &Response::getBody() const { return _body; }

void Response::setVersion(std::string const &version) { _version = version; }

void Response::setStatusCode(std::string const &statusCode) { _statusCode = statusCode; }

void Response::setStatusMessage(std::string const &statusMessage) { _statusMessage = statusMessage; }

void Response::setDate(std::string const &date) { _date = date; }

void Response::setServer(std::string const &server) { _server = server; }

void Response::setContentType(std::string const &contentType) { _contentType = contentType; }

void Response::setContentLength(std::string const &contentLength) { _contentLength = contentLength; }

void Response::setBody(std::string const &body) { _body = body; }

std::string Response::toString() const {
	std::string response;
	response += _version + " " + _statusCode + " " + _statusMessage + "\r\n";
	response += "Date: " + _date + "\r\n";
	response += "Server: " + _server + "\r\n";
	response += "Content-Type: " + _contentType + "\r\n";
	response += "Content-Length: " + _contentLength + "\r\n";
	response += "\r\n";
	response += _body;
	return response;
}
