#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;
string FilleClient = "ClientData.txt";
void MainMenueScreen();

enum eBankClient{ ShowClientList=1, AddNewClient=2, DeleteClient=3, UpdateClientInfo=4, FindClient=5,Exit=6};

struct sClient
{
	string Account;
	string PinCode;
	string Name;
	string Phone;
	double Balance;
	bool MarkForDelete = false;
};

vector <string> SplitWord(string S1, string Delim)
{
	string sWord;
	short Pos = 0;
	vector <string> vsword;

	while ((Pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, Pos);
		if (sWord != "")
		{
			vsword.push_back(sWord);
		}

		S1.erase(0, Pos + Delim.length());

	}

	if (S1 != "")
	{
		vsword.push_back(S1);
	}
	return vsword;
}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
	sClient Client;
	vector<string> vClientData;
	vClientData = SplitWord(Line, Seperator);
	Client.Account = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.Balance = stod(vClientData[4]);
	return Client;
}

vector <sClient> LoadCleintsDataFromFile(string FileName)
{
	vector <sClient> vClient;

	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		sClient Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			vClient.push_back(Client);
		}

		MyFile.close();

	}
	return vClient;
}

void PrintInfoClient(sClient Client)
{
	cout << left << "| " << setw(18) << Client.Account
		<< "| " << setw(12) << Client.PinCode
		<< "| " << setw(30) << Client.Name
		<< "| " << setw(13) << Client.Phone
		<< "| " << setw(8) << Client.Balance
		<< endl;
}

void ShowClientListScreen(vector <sClient>& vClient)
{
	cout << "                                      Client List ( " << vClient.size() << " ) Client(s).\n\n";
	cout << left << "-----------------------------------------------------------------------------------------------------\n\n";
	cout << left << "| " << setw(18) << "Account Number" << "| " << setw(12) << "Pin Code" << "| " << setw(30) << "Client Name" << "| " << setw(13) << "Phone" << "| " << setw(8) << "Balance" << endl;
	cout << left << "\n-----------------------------------------------------------------------------------------------------\n\n";

	for (sClient Client : vClient)
	{
		PrintInfoClient(Client);
		cout << endl;
	}

	cout << left << "-----------------------------------------------------------------------------------------------------\n\n";

}

bool FindClientAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
	for (sClient C : vClients)
	{
		if (C.Account == AccountNumber)
		{
			return true;
		}
	}
	return false;
}

sClient ReadNewClient(vector<sClient>& vClient)
{
	sClient Client;

	cout << "Enter Account Number ? ";
	getline(cin >> ws, Client.Account);
	while (FindClientAccountNumber(Client.Account, vClient))
	{
		cout << "Client With [" << Client.Account << "] already exists!, Enter another Account Number :";
		getline(cin >> ws, Client.Account);
	}
	cout << "Enter PinCode ? ";
	getline(cin, Client.PinCode);

	cout << "Enter Name ? ";
	getline(cin, Client.Name);

	cout << "Enter Phone ?";
	getline(cin, Client.Phone);

	cout << "Enter AccuntBalance ? ";
	cin >> Client.Balance;


	return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
	string stClientRecord = "";

	stClientRecord += Client.Account + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.Balance);

	return stClientRecord;
}

vector <sClient> SaveCleintsDataToFile(string FileName, vector<sClient>& vClients)
{
	fstream MyFile;

	MyFile.open(FileName, ios::out);//overwrite
	string DataLine;

	if (MyFile.is_open())
	{
		for (sClient C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}

void AddLineToFile(string Line, string NameFile)
{
	fstream MyFille;

	MyFille.open(NameFile, ios::out | ios::app);

	if (MyFille.is_open())
	{
		MyFille << Line << endl;
		MyFille.close();
	}
}

void AddNewClients(vector <sClient>& vClient)
{
	sClient Client;
	Client = ReadNewClient(vClient);
	AddLineToFile(ConvertRecordToLine(Client), FilleClient);
	vClient = LoadCleintsDataFromFile(FilleClient);
}

void AddClients(vector <sClient>& vClient)
{
	char Yes = 'Y';
	do
	{
		cout << "\nAdding New Client : \n\n";
		AddNewClients(vClient);
		cout << "\nClient Added Successfully , Do Youwant to add more clients ?\n";
		cin >> Yes;

	} while (toupper(Yes) == 'Y');
}

string ReadAccountNumber()
{
	string Account;
	cout << "Enter Account Number : " << endl;
	cin >> Account;
	return Account;
}

void PrintClientRecord(sClient Client)
{
	cout << "\n\nThe following is the extracted client record:\n";
	cout << "\nAccout Number  : " << Client.Account;
	cout << "\nPin Code       : " << Client.PinCode;
	cout << "\nName           : " << Client.Name;
	cout << "\nPhone          : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.Balance;
	cout << endl;

}

bool FindClientByAccountNumber(string AccountNumber, vector<sClient>& vClients, sClient& Client)
{
	for (sClient C : vClients)
	{
		if (C.Account == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	for (sClient& C : vClients)
	{
		if (C.Account == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientRecord(Client);


		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> Answer;


		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);

			SaveCleintsDataToFile(FilleClient, vClients);

			vClients = LoadCleintsDataFromFile(FilleClient);

			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}


	else
	{
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";
		return false;
	}
}

void UpDateInfoClientInVector(string AccountNumber, vector<sClient>& vClients, sClient UpdateClient)
{
	for (short i = 0; i < vClients.size(); i++)
	{
		if (vClients[i].Account == AccountNumber)
		{
			vClients[i].Balance = UpdateClient.Balance;
			vClients[i].Name = UpdateClient.Name;
			vClients[i].Phone = UpdateClient.Phone;
			vClients[i].PinCode = UpdateClient.PinCode;
			return;
		}
	}
}

sClient EnterUpdateForClient()
{
	sClient Client;

	cout << "\n\nEnter PinCode ? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name ? ";
	getline(cin, Client.Name);

	cout << "Enter Phone ?";
	getline(cin, Client.Phone);

	cout << "Enter AccuntBalance ? ";
	cin >> Client.Balance;


	return Client;
}

bool UpDateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientRecord(Client);


		cout << "\n\nAre you sure you want Updata this client? y/n ? ";
		cin >> Answer;


		if (Answer == 'y' || Answer == 'Y')
		{
			UpDateInfoClientInVector(AccountNumber, vClients, EnterUpdateForClient());

			SaveCleintsDataToFile(FilleClient, vClients);

			vClients = LoadCleintsDataFromFile(FilleClient);

			cout << "\n\nClient UpDated Successfully.";
			return true;
		}
	}


	else
	{
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";
		return false;
	}
}

void DisplayClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
	sClient Client;

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientRecord(Client);
	}
	else
	{
		cout << "\nClient with Account Number ("
			<< AccountNumber
			<< ") is Not Found!";
	}
}

void DeleteClientScreen(vector<sClient>& vClient)
{
	cout << "- - - - - - - - - - - - - - - - - - - - -\n";
	cout << "\t   Delete Clients Screen\n";
	cout << "- - - - - - - - - - - - - - - - - - - - -\n";

	DeleteClientByAccountNumber(ReadAccountNumber(), vClient);
}

void AddNewClientScreen(vector<sClient>& vClient)
{
	cout << "- - - - - - - - - - - - - - - - - - - - -\n";
	cout << "\t   Add New Clients Screen\n";
	cout << "- - - - - - - - - - - - - - - - - - - - -\n";

	AddClients(vClient);
}

void UpdateClientInfoScreen(vector<sClient>& vClient)
{
	cout << "- - - - - - - - - - - - - - - - - - - - -\n";
	cout << "\t   Update Clients Info Screen\n";
	cout << "- - - - - - - - - - - - - - - - - - - - -\n";
	UpDateClientByAccountNumber(ReadAccountNumber(), vClient);
}

void FindClientScreen(vector<sClient>& vClient)
{
	cout << "- - - - - - - - - - - - - - - - - - - - -\n";
	cout << "\t   Find Clients Screen\n";
	cout << "- - - - - - - - - - - - - - - - - - - - -\n";

	DisplayClientByAccountNumber(ReadAccountNumber(), vClient);
}

void ExitScreen()
{
	cout << "==============================================\n";
	cout << "\t Program Ends :-)\n";
	cout << "==============================================\n";
}

void GoBackToMainMenueScrean()
{
	cout << "\n\n\nCliek any Key to go to The Main Manue Screan....";
	system("pause>0");
	system("cls");
	MainMenueScreen();
}

short ReadMainMenueOption()
{
	short Num;
	cout << "Choose What do you want to do? [1 to 6] ";
	cin >> Num;
	return Num;
}

void ShowUserInfoInSerean(vector<sClient>& vClient, eBankClient Result)
{
		switch (Result)
		{

		case eBankClient::ShowClientList:

			system("cls");
			ShowClientListScreen(vClient);
			GoBackToMainMenueScrean();
			break;

		case eBankClient::AddNewClient:

			system("cls");
			AddNewClientScreen(vClient);
			GoBackToMainMenueScrean();

			break;

		case eBankClient::DeleteClient:

			system("cls");
			DeleteClientScreen(vClient);
			GoBackToMainMenueScrean();


			break;

		case eBankClient::UpdateClientInfo:

			system("cls");
			UpdateClientInfoScreen(vClient);
			GoBackToMainMenueScrean();

			break;

		case eBankClient::FindClient:

			system("cls");
			FindClientScreen(vClient);
			GoBackToMainMenueScrean();

			break;

		case eBankClient::Exit:

			system("cls");
			ExitScreen();
			system("pause>0");
			return;
		}
}

void MainMenueScreen()
{
	vector <sClient> vClient = LoadCleintsDataFromFile(FilleClient);

	system("cls");
	cout << "==============================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "==============================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Exit.\n";
	cout << "==============================================\n";
	ShowUserInfoInSerean(vClient, eBankClient(ReadMainMenueOption()));
}

int main()
{
	MainMenueScreen();
	return 0;
}