/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:01:15 by omanar            #+#    #+#             */
/*   Updated: 2023/07/20 15:30:47 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserv.hpp"

int	main(int ac, char **av)
{
	try {
		if (ac != 2)
			throw std::runtime_error("Usage: ./webserv [configuration file]");
		Webserv *webserv = new Webserv(av[1]);
		webserv->run();
		delete webserv;
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	// system("leaks webserv");
	return 0;
}
