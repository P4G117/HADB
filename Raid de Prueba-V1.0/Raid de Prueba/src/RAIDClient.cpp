/*
 * Client.cpp
 *
 *  Created on: 21 nov. 2016
 *      Author: randy, gustavo, fernanda
 */

#include "RAIDClient.h"

/**
 * Constructor.
 */
RAIDClient::RAIDClient() {
}


/**
 * Destroyer.
 */
RAIDClient::~RAIDClient() {
}

/**
 *
 * Connects the Client-C++(Mesh Mem Client)to the
 * Server-Java (MeshMem Manager).
 *
 * Returns 1 when successful, -1 when unsuccessful.
 *
 * @params string hostIP, int port
 */
int RAIDClient::startConnection(){
	XMLDocument doc;
	doc.LoadFile("configurationNode.xml");
	const char* host = doc.FirstChildElement( "diskNode" )->FirstChildElement("config")->FirstChildElement("ip")->GetText();
	string portC = doc.FirstChildElement( "diskNode" )->FirstChildElement("config")->FirstChildElement("port")->GetText();

	int port = atoi(portC.c_str());
	//const char *host = hostIP.c_str();

	struct hostent *hostC;
	struct sockaddr_in server;
	if ((hostC = gethostbyname(host)) == NULL){
		cout<<("gethostbyname() error\n");
		return -1;
	}

	if ((descriptor = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		cout<<("socket() error\n");
		return -1;
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr = *((struct in_addr *)hostC->h_addr);
	bzero(&(server.sin_zero), 8);
	if (connect(descriptor, (struct sockaddr *)&server, sizeof(struct sockaddr))  == -1){
		cout<<"connect() error\n";
		return -1;
	}
	return 1;
}

/**
 * Receives a message from the Server-Java (MeshMem Manager)
 *for print it into the  Client-C (MeshMem Client)'s screen.
 *
 *Returns a int on whether the was receive or not.
 *
 *@params, char* buffer, int longitudMensaje
 */
string RAIDClient::receiveMsj(){
	int buffsize = (MAXDATASIZE);
	setsockopt(descriptor, SOL_SOCKET, SO_RCVBUF, &buffsize, sizeof(buffsize));

	char *buffer = new char[MAXDATASIZE];
	int r = recv(descriptor, buffer, MAXDATASIZE, MSG_WAITALL|MSG_CTRUNC);
	if (r < 0){
		cout<<"ERROR reading from socket"<<endl;
	}
	if(r == 0){
			return "Message null\n";
	}

	string message;
	message = buffer;

	return message;
}

/**
 * Sends a message from the  Client-C++ (MeshMem Client)
 * to the Server-Java (MeshMem Manager).
 *
 * @params string mensaje
 */
void RAIDClient::sendMsj(string mensaje){
	int buffsize = (MAXDATASIZE);
	setsockopt(descriptor, SOL_SOCKET, SO_SNDBUF, &buffsize, sizeof(buffsize));

	int len = (mensaje.length());
	const char *buffer = new char[len];
	buffer = mensaje.c_str();

	int s = send(descriptor, buffer, len+1, MSG_OOB|MSG_PEEK);
	if(s < 0){
		cout << "ERROR CLIENT SEND MESSAGE" << endl;
	}
}
