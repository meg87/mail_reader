/*---------------------------------------------------
 this class use IMAP protocol to contact mail server
---------------------------------------------------*/

#include "socket_c.h"
#include <string.h>

using namespace std;

class imap
{
	private:
		char msg[2048], *reply;
		Socket_c *socket;

	public:

	bool Connect(char* address, char* port)
	{
		socket = new Socket_c();

		// send request
		socket->Connect(address, port);

		// recive response
		reply = socket->Recive();

		// convert reply to string
		string status(reply, strlen(reply)); 

		// return status
		if (status.substr(0, 4) == "* OK")
			return true;
		else
			return false;
	}

	bool Login(string username, string password)
	{
		// get username and password then make login request
		string tmp("1 login " + username + " " + password + "\n");

		// convert tmp form string to char* then assgement to msg
		strcpy(msg, tmp.c_str());

		// send request
		socket->Send(msg, strlen(msg));

		// recive response
		reply = socket->Recive();

		// convert reply to string
		string status(reply, strlen(reply)); 

		// return status
		if (status.substr(0, 10) == "1 OK LOGIN")
			return true;
		else
			return false;
	}

	char *Open_mailbox(string name = "inbox")
	{
		// make select request
		string tmp("2 select " + name + "\n");

		// convert request form string to char* 
		strcpy(msg, tmp.c_str());

		// send select request
		socket->Send(msg, strlen(msg));	

		// recive response
		reply = socket->Recive();

		return reply;
	}

	char *Open_message(string num)
	{
		// make fetch request
		string tmp("3 fetch " + num + " body[text]\n");

		// convert request form string to char* 
		strcpy(msg, tmp.c_str());

		// send request
		socket->Send(msg, strlen(msg));

		// recive response
		reply = socket->Recive();

		return reply;
	}

	bool Logout()
	{
		// make logout request
		string tmp("4 logout\n");

		// convert request form string to char* 
		strcpy(msg, tmp.c_str());

		// send request
		socket->Send(msg, strlen(msg));	

		// recive response
		reply = socket->Recive();

		// convert reply to string
		string status(reply, strlen(reply)); 

		// return status
		if (status.substr(0, 5) == "* BYE")
			return true;
		else
			return false;
	}
};
