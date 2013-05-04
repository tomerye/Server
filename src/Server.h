/*
 * Server.h
 *
 *  Created on: Apr 6, 2013
 *      Author: tomer
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <boost/asio.hpp>
#include <iostream>
#include "ClientConnection.h"
#include <boost/bind.hpp>

using boost::asio::ip::tcp;
class Server {
public:
	Server(int port, boost::asio::io_service &io_service);
	virtual ~Server();
private:
	tcp::endpoint endpoint_;
	boost::asio::io_service& io_service_;
	tcp::acceptor acceptor_;
	std::map<int, ClientConnection*> connection_map_;
	void startAccept();
	void addNewConnection(const boost::system::error_code& e, size_t *id,
			tcp::socket *newSocket);
	void handleGetNewConnectionID(const boost::system::error_code& e,
			tcp::socket *newSocket);
	 void send(const size_t id , const Packet packet);
};

#endif /* SERVER_H_ */
