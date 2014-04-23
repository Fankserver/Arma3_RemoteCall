#include <sstream>
#include <thread>

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#pragma comment (lib, "Ws2_32.lib") // Need to link with Ws2_32.lib
#endif

#ifndef REMOTECALL_H
#define REMOTECALL_H

// compat
#ifdef _MSC_VER
#define snprintf _snprintf
#endif

#define REMOTECALL_VERSION 1
#define REMOTECALL_SOCKBUFFER 512

class RemoteCall {
private:
	struct serverS {
		int port;
		char *password;
	};
	struct clientS {
		unsigned char version;
		char *password;
	};

private:
	serverS server;
	char *header;

	std::thread socketThread;

	void _buildHeader();
	void _initServerSocket();
	void _initClientSocket(RemoteCall *Object, LPVOID lpParameter);

public:
	RemoteCall();
	~RemoteCall();

	void initServer();

	const char *socketHandshake();
	const char *socketQueryId();
	const char *socketQueryContent();
};

#endif