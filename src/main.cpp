/*
 * main.cpp
 *
 *  Created on: Apr 29, 2013
 *      Author: tomer
 */

#include "Server.h"
#include <boost/asio.hpp>
int main(int argc,char *argv[]){
	boost::asio::io_service io_service;
	Server server(55555,io_service);
	io_service.run();

	return 0;
}
