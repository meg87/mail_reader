/*-------------------------
 Mail Reader (IMAP Client)
-------------------------*/

#include <iostream>
#include "imap.h"

using namespace std;

int main(int argc, char *argv[])
{
	imap *email = new imap();
	string username, password, msg_txt, msg_num;
	
	// check aragments
	if (argc < 3) 
	{
		cerr << "USAGE: " << argv[0] <<  " <address> <port>" << endl;
		exit(0);
	}

	// connect
	if (email->Connect(argv[1], argv[2]))
		cout << "Welcome to Mail Reader (IMAP Client)" << endl;
	else
	{
		cerr << "ERORR: connect fail !" << endl;
		return 0;
	}

	// login
	while (1)
	{
		cout << "Enter email : ";
		cin >> username;

		cout << "Enter password : ";
		cin >> password;

		if (email->Login(username, password))
			break;
		else
			cerr << "ERORR: login fail !" << endl;
	}

	// open mailbox
	cout << "Status of mailbox :" << endl;
	cout << email->Open_mailbox();

	while (1)
	{
		cout << "Enter number of message to read it : ";
		cin >> msg_num;

		msg_txt = email->Open_message(msg_num);

		cout << msg_txt;
	}

	if(email->Logout())
		cout << "Goodbye ,," << endl;
}
