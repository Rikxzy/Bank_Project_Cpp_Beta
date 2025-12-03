#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include <iomanip>
#include <fstream>

using namespace std;

const string ClientsFileName = "CLIENT.txt";

void BankMainMenu();

void TransactionMenu();


struct stClientData
{
	string PinCode;
	string AccountNumber;
	string FULLName;
	string PhoneNumber;
	double AccountBalance = 0;
	bool MarkForDeleted = false;

};

vector<string> splitString(const string& str, const string& delim) {

	vector<string> result;
	size_t start = 0;
	size_t end = str.find(delim);

	while (end != string::npos) {
		result.push_back(str.substr(start, end - start));
		start = end + delim.length();
		end = str.find(delim, start);
	}

	result.push_back(str.substr(start));
	return result;
}

stClientData ConvertLineToRecord(string Line, string Separator = "#//#")
{
	stClientData Client;
	vector <string> vClienData;
	vClienData = splitString(Line, Separator);

	Client.AccountNumber = vClienData[0];
	Client.PinCode = vClienData[1];
	Client.FULLName = vClienData[2];
	Client.PhoneNumber = vClienData[3];
	Client.AccountBalance = stod(vClienData[4]);

	return Client;

}

string ConvertRecordToLine(stClientData ClientData, string Separator = "#//#")
{
	string StClientRecord = "";

	StClientRecord += ClientData.AccountNumber + Separator;
	StClientRecord += ClientData.PinCode + Separator;
	StClientRecord += ClientData.FULLName + Separator;
	StClientRecord += ClientData.PhoneNumber + Separator;
	StClientRecord += to_string(ClientData.AccountBalance);

	return StClientRecord;
}

bool DoesClientExistsWithAccountNumber(string FileName, string AccountNumber)
{
	vector<stClientData> vClients;
	fstream Myfile;

	Myfile.open(FileName, ios::in);

	if (Myfile.is_open())
	{
		string Line;
		stClientData Clients;
		while (getline(Myfile, Line))
		{
			Clients = ConvertLineToRecord(Line);
			if (Clients.AccountNumber == AccountNumber)
			{
				Myfile.close();
				return 1;
			}
			vClients.push_back(Clients);

		}

		Myfile.close();

	}

	return false;

}

stClientData ReadNewClientData()
{
	stClientData ClientData;

	cout << "------------ Please Enter Client Data ------------ \n";

	cout << "Enter Account Number : ";
	getline(cin >> ws, ClientData.AccountNumber);

	while (DoesClientExistsWithAccountNumber(ClientsFileName, ClientData.AccountNumber))
	{
		cout << "Clients Already exists , Enter Another Account Number : ";
		getline(cin >> ws, ClientData.AccountNumber);

	}

	cout << "Enter PinCode : ";
	getline(cin, ClientData.PinCode);

	cout << "Enter Full Name : ";
	getline(cin, ClientData.FULLName);

	cout << "Enter Phone Number : ";
	getline(cin, ClientData.PhoneNumber);

	cout << "Enter Account Balance : ";
	cin >> ClientData.AccountBalance;

	cout << "___________________________\n";

	return ClientData;
}

void AddClientDataToFile(string FileName, string strClientLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open())
	{
		MyFile << strClientLine << endl;
		MyFile.close();
	}
}

void PrintRecord(stClientData ClientRecord)
{
	cout << "| " << setw(15) << left << ClientRecord.AccountNumber;
	cout << "| " << setw(10) << left << ClientRecord.PinCode;
	cout << "| " << setw(40) << left << ClientRecord.FULLName;
	cout << "| " << setw(12) << left << ClientRecord.PhoneNumber;
	cout << "| " << setw(15) << right << ClientRecord.AccountBalance << " $";

}

void ShowClientDataList(vector<stClientData> vClients)
{
	cout << "\n\t\t\t\t List Of (" << vClients.size() << ") Client(s) ";
	cout << "\n__________________________________________________";
	cout << "____________________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "PinCode";
	cout << "| " << left << setw(40) << "Name";
	cout << "| " << left << setw(12) << "Phone Number";
	cout << "| " << left << setw(15) << "Account Balance";
	cout << "\n__________________________________________________";
	cout << "____________________________________________________\n" << endl;

	for (stClientData Client : vClients)
	{
		PrintRecord(Client);
		cout << endl;
	}
	cout << "\n__________________________________________________";
	cout << "____________________________________________________\n" << endl;

}

void PrintOneClientRecord(stClientData ClientRecord)
{
	cout << "\n\t\t The Following Are The Client Details : \n\n";
	cout << " Account Number : " << ClientRecord.AccountNumber << endl;
	cout << " Pin Code       : " << ClientRecord.PinCode << endl;
	cout << " Name           : " << ClientRecord.FULLName << endl;
	cout << " Phone          : " << ClientRecord.PhoneNumber << endl;
	cout << " Balance        : " << ClientRecord.AccountBalance << "$";

}

bool SearchClientNumber(string AccountNumber, vector<stClientData> vClientInfo, stClientData& Client)
{

	for (stClientData C : vClientInfo)
	{
		if (C.AccountNumber == AccountNumber)
		{

			Client = C;
			return 1;

		}
	}return 0;
}

stClientData UpdateClientData(string AccountNumber)
{
	stClientData ClientData;

	cout << "\n------------ Please Enter The Modification ------------ \n";
	ClientData.AccountNumber = AccountNumber;
	cout << "Enter PinCode : ";
	getline(cin >> ws, ClientData.PinCode);

	cout << "Enter Full Name : ";
	getline(cin, ClientData.FULLName);

	cout << "Enter Phone Number : ";
	getline(cin, ClientData.PhoneNumber);

	cout << "Enter Account Balance : ";
	cin >> ClientData.AccountBalance;

	cout << "_______________________________________________________\n";

	return ClientData;
}

void AddNewClient()
{
	stClientData ClientData;
	ClientData = ReadNewClientData();
	AddClientDataToFile(ClientsFileName, ConvertRecordToLine(ClientData, "#//#"));
}

void AddClients()
{
	char AddMore = 'Y';

	do
	{
		cout << "Adding New Client :\n\n";
		AddNewClient();
		cout << "Client Added Successfully , Do You Want to add More ? : ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}

vector<stClientData> LoadClientDataFromFile(string FileName )
{
	vector<stClientData> vClients;

	fstream Myfile;
	Myfile.open(FileName, ios::in);
	if(Myfile.is_open())
	{
		stClientData ClientData;
		string Line;
		while(getline(Myfile,Line))
		{
			ClientData = ConvertLineToRecord(Line, "#//#");
			vClients.push_back(ClientData);
	
		}
		Myfile.close();
	}
	return vClients;
}

string ReadAccountNumber()
{
	string AccountNumber = "";
	cout << "Please Enter Client Number : ";
	cin >> AccountNumber;
	return AccountNumber;
}

bool MarkClienAccountNumberForDelete(string AccountNumber, vector<stClientData> &vClients)
{
	for(stClientData &c : vClients)
	{
		if(c.AccountNumber == AccountNumber)
		{
			c.MarkForDeleted = true;
			return true;
		}
	}
	return false;
}

vector<stClientData> SaveClientDataToFile(string FileName , vector<stClientData> vClients)
{
	fstream Myfile;
	Myfile.open(FileName, ios::out);
	string DataLine; 

	if(Myfile.is_open())
	{
		for(stClientData c : vClients)
		{
			if (c.MarkForDeleted == false)
			{
				DataLine = ConvertRecordToLine(c);
				Myfile << DataLine << endl;
			
			}
		}
		Myfile.close();
	}

	return vClients;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<stClientData>& vClients)
{
	stClientData Client;
	char Check = 'n';

	if (SearchClientNumber(AccountNumber, vClients, Client))
	{
		PrintOneClientRecord(Client);
		cout << "\n\t Are You Sure To Update This Client ? Y/n : ";
		cin >> Check;
		if (Check == 'y' || Check == 'Y')
		{
			for(stClientData &c : vClients)
			{
				if(c.AccountNumber == AccountNumber)
				{
					c = UpdateClientData(AccountNumber);
					break;
				}
			}

			SaveClientDataToFile(ClientsFileName, vClients);
			cout << "\n\t Client Updated Succesfuly";
			return true;
		}
	}
	else
	{
		cout << " \n\t !!! CLIENT WITH NUMBER (" << AccountNumber << ") IS NOT FOUND\t\n";
		return false;
	}
}

bool DeleteClientByAccountNumber(string AccountNumber , vector<stClientData> &vClients)
{
	stClientData Client;
	char Check = 'n';

	if (SearchClientNumber(AccountNumber, vClients, Client))
	{
		PrintOneClientRecord(Client);
		cout << "\n\t Are You Sure To Delete This Client ? Y/n : ";
		cin >> Check;
		if(Check == 'y' || Check=='Y') 
		{
			MarkClienAccountNumberForDelete(AccountNumber , vClients);
			SaveClientDataToFile(ClientsFileName, vClients);

			vClients = LoadClientDataFromFile(ClientsFileName);
			cout << "\n\t Client Deleted Succesfuly";
			return true;
		}
	} 
	else 
	{
		cout << " \n\t !!! CLIENT WITH NUMBER (" << AccountNumber << ") IS NOT FOUND\t\n";
		return false;
	}
}

void AddingNewClientScreen()
{
	cout << "==================================================\n";
	cout << "                Add New Client List               \n";
	cout << "==================================================\n";

	AddClients();
}

void DeleteClientScreen()
{
	vector<stClientData> vClients =LoadClientDataFromFile(ClientsFileName) ;
	cout << "==================================================\n";
	cout << "                DELETE CLIENT SCREEN              \n";
	cout << "==================================================\n";
	string AccountNumber = ReadAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);
}

void UpdateClientScreen()
{
	vector<stClientData> vClients = LoadClientDataFromFile(ClientsFileName);
	cout << "==================================================\n";
	cout << "                UPDATE CLIENT SCREEN              \n";
	cout << "==================================================\n";
	string AccountNumber = ReadAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);
}

void FindClientScreen()
{
	vector<stClientData> vClients = LoadClientDataFromFile(ClientsFileName);
	stClientData Client;
	cout << "==================================================\n";
	cout << "                Find CLIENT SCREEN              \n";
	cout << "==================================================\n";
	string AccountNumber = ReadAccountNumber();
	Client.AccountNumber = AccountNumber;
	if(!SearchClientNumber(AccountNumber,vClients,Client))
	{
		cout << " \n\t !!! CLIENT WITH NUMBER (" << AccountNumber << ") IS NOT FOUND\t\n";

	} else if(SearchClientNumber(AccountNumber, vClients, Client))
	{
		PrintOneClientRecord(Client);
	}
}

void ShowEndScreen()
{
	cout << "==================================================\n";
	cout << "                    PROGRAM ENDS                  \n";
	cout << "          Thank you for using our system!         \n";
	cout << "==================================================\n";
}

enum enMenuChoice { ShowClients = 1, NewClient = 2, DeleteClient = 3, UpdateClient = 4, FindClient = 5, Transaction = 6 ,Exit = 7 };

enum enTransaMenu { eDeposit = 1 , eWithdraw = 2 , eTotalBalances = 3 , eMainMenu = 4 };

enMenuChoice  ReadMenuChoice()
{
	short int Choice;
	cout << "Choose What do you want to do ? [1 to 6] : ";
	cin >> Choice;
	while (cin.fail())
	{
		cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid Number, Enter a valid one : "; cin >> Choice;
	}
	while(Choice < 1 || Choice > 7)
	{
		cout << "ERROR !!!!! , Try Again \n"; cout << "Choice from 1 to 7 : ";
		cin >> Choice;
	}

	return (enMenuChoice) Choice;
}

enTransaMenu ReadTransaChoice()
{
	short int Choice;
	cout << "Choose What do you want to do ? [1 to 4] : ";
	cin >> Choice;
	while (cin.fail())
	{
		cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid Number, Enter a valid one : "; cin >> Choice;
	}
	while (Choice < 1 || Choice > 4)
	{
		cout << "ERROR !!!!! , Try Again \n"; cout << "Choice from 1 to 6 : ";
		cin >> Choice;
	}

	return (enTransaMenu)Choice;
}

void GoBackToTransaMenu()
{
	cout << "\n\nPress any key to go back...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
	TransactionMenu();
}

void GoBackToMainMenu()
{
	cout << "\n\nPress any key to go back...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
	BankMainMenu();
}


void UserTransaChoice(enTransaMenu UserTransaMenuChoice)
{
	switch (UserTransaMenuChoice)
	{
	case enTransaMenu::eDeposit :
		GoBackToTransaMenu();
		break;

	case enTransaMenu::eWithdraw:
		GoBackToTransaMenu();
		break;

	case enTransaMenu::eTotalBalances:
		GoBackToTransaMenu();
		break;

		case enTransaMenu::eMainMenu :
			GoBackToMainMenu();
		break;
	}
}

void TransactionMenu()
{
	
		system("cls");
		cout << "==================================================\n";
		cout << "             Transaction Menu Screen              \n";
		cout << "==================================================\n";
		cout << "\t    [1] Deposit.\n";
		cout << "\t    [2] Withdraw.\n";
		cout << "\t    [3] Total Balances.\n";
		cout << "\t    [4] Main Menu.\n";
		cout << "==================================================\n";

		UserTransaChoice(ReadTransaChoice());
	
}

void UserMenuChoice(enMenuChoice UserMenuChoice)
{
	vector<stClientData> vClients = LoadClientDataFromFile(ClientsFileName);

	switch (UserMenuChoice)
	{
	case enMenuChoice::ShowClients:
		system("cls");
		ShowClientDataList(vClients);
		GoBackToMainMenu();
		break;

	case enMenuChoice::NewClient:
		system("cls");
		AddingNewClientScreen();
		GoBackToMainMenu();
		break;

	case enMenuChoice::DeleteClient:
		system("cls");
		DeleteClientScreen();
		GoBackToMainMenu();
		break;

	case enMenuChoice::UpdateClient:
		system("cls");
		UpdateClientScreen();
		GoBackToMainMenu();
		break;

	case enMenuChoice::FindClient:
		system("cls");
		FindClientScreen();
		break;

	case enMenuChoice::Transaction :
		system("cls");
		TransactionMenu();
		break;
		
		break;
	case enMenuChoice::Exit:
		ShowEndScreen();
		break;

	}
}

void BankMainMenu()
{
	
		system("cls");
		cout << "==================================================\n";
		cout << "                  Main Menu Screen                \n";
		cout << "==================================================\n";
		cout << "\t    [1] Show Client List.\n";
		cout << "\t    [2] Add New Client.\n";
		cout << "\t    [3] Delete Client.\n";
		cout << "\t    [4] Update Client Data.\n";
		cout << "\t    [5] Find Client.\n";
		cout << "\t    [6] Transaction.\n";
		cout << "\t    [7] Exit.\n";
		cout << "==================================================\n";
		UserMenuChoice(ReadMenuChoice());
	
}


int main()
{

	BankMainMenu();

	system("pause>0");
	return 0;
}
