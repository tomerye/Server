/*
 * ClientConnection.h
 *
 *  Created on: Apr 6, 2013
 *      Author: tomer
 */

#ifndef CLIENTCONNECTION_H_
#define CLIENTCONNECTION_H_

#include <boost/asio.hpp>
#include "AsyncSerializationConnection.cpp"
#include "PacketForClient.h"
#include "PacketForServer.h"
#include <boost/system/error_code.hpp>
#include <boost/bind.hpp>
#include <deque>
#include "Server.h"

class Server;
using boost::asio::ip::tcp;

class ClientConnection {
public:
	ClientConnection(tcp::socket *socket, Server *server, size_t id);
	virtual ~ClientConnection();
	tcp::socket& getSocket() const;
	void send(PacketForClient *packet);
private:
	std::deque<PacketForClient*> outPacketsBuffer_;
	Server *pServer_;
	size_t id_;
	void waitForPacket();
	void handleReceivePacket(const boost::system::error_code& e,
			PacketForServer *newPacket);
	void handleSendPacket(const boost::system::error_code& e);
	AsyncSerializationConnection connection_;
};

#endif /* CLIENTCONNECTION_H_ */
