#ifndef WIN_DEBUG_H
#define WIN_DEBUG_H

#include <x2d/debug.h>

class Debugger : public xdDebug
{
public:
	Debugger();
	~Debugger();

	bool init();
	bool listen(const ushort port);
	bool accept();
	bool connect();
	void disconnect();
	bool send(const char *data);
	bool recv(char **data);
	int bytesReady();
	
private:

	// Sockets
	SOCKET m_server;
	SOCKET m_client;
};

#endif // WIN_DEBUG_H