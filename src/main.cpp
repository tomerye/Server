/*
 * main.cpp
 *
 *  Created on: Apr 29, 2013
 *      Author: tomer
 */

#include "Server.h"
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

int main(int argc, char *argv[]) {
	boost::asio::io_service io_service;
	Server server(55555, io_service);
	boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));
	Packet p;
	p.id_ = 333;
	p.file_path_ = "sfdsf";
	p.opcode_ = "ddd";
	char line[10];
	while (std::cin.getline(line, 10))
		server.send(123,p);
//	io_service.run();
	t.join();
	return 0;
}
