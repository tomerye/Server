/*
 * ClientConnection.cpp
 *
 *  Created on: Apr 6, 2013
 *      Author: tomer
 */

#include "ClientConnection.h"

ClientConnection::ClientConnection(tcp::socket *socket):connection_(*socket) {
}

ClientConnection::~ClientConnection() {
	// TODO Auto-generated destructor stub
}

