/*
 * RAIDClient.h
 *
 *  Created on: Nov 24, 2016
 *      Author: randy, gustavo, fernanda
 */

#ifndef TECMFS_RAID5_RAIDCLIENT_H_
#define TECMFS_RAID5_RAIDCLIENT_H_


#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <net/if.h>
#include <errno.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sys/stat.h>

#include "tinyxml2.h"

#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif


#define MAXDATASIZE 64000000

using namespace tinyxml2;
using namespace std;

/**
 * Class for the creation for a C/C++ socket for the RAID 5
 * memory storage system.
 */

class RAIDClient {

private:
	/*Attributes.*/
	int descriptor;

public:
	/*Methods.*/
	RAIDClient(); /*Constructor.*/
	virtual ~RAIDClient(); /*Destroyer.*/


	int startConnection(); /*Makes Connections.*/
	string receiveMsj(); /*Receive messages from the Server.*/
	void sendMsj(string mensaje); /*Send message to the Server.*/
	char getBuffer(); /*Manager for the buffer.*/
};

#endif /* TECMFS_RAID5_RAIDCLIENT_H_ */
