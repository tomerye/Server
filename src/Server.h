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

class ClientConnection;

using boost::asio::ip::tcp;
class Server {
public:
	Server(int port, boost::asio::io_service &io_service);
	virtual ~Server();
	void deleteConnection(const char id);
	void send(const char id , const Packet packet);
private:
	tcp::endpoint endpoint_;
	boost::asio::io_service& io_service_;
	tcp::acceptor acceptor_;
	std::map<int, ClientConnection*> connection_map_;
	void startAccept();
	void addNewConnection(const boost::system::error_code& e, char *id,
			tcp::socket *newSocket);
	void handleGetNewConnectionID(const boost::system::error_code& e,
			tcp::socket *newSocket);

};

#endif /* SERVER_H_ */
