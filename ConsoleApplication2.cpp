#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <cctype>
#include <fstream>
#include <ctime>
using namespace std;
const string ClientsFileName = "Clients.txt";



void ShowTransactionsMenue();
void ShowMainMenue();






void GoBackToTranactionsMenue()
{
	cout << "\n\nPress in any key to go Main Menue...";
	system("pause>0");
	ShowTransactionsMenue();
}

void GoBackToMainMenue()
{
	cout << "\n\nPress in any key to go Main Menue...";
	system("pause>0");
	ShowMainMenue();
}





 
struct InfoCl
{
	string AcountNumber;
	string Pincode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;

};




vector<string>SplitString(string stt, string delim)
{
	vector<string> VString;
	size_t pos = 0;
	string Word;

	// Use find() function to get the position of the delimiters
	while ((pos = stt.find(delim)) != string::npos) {
		Word = stt.substr(0, pos); // Store the word
		if (!Word.empty()) { // Avoid adding empty words (spaces)
			VString.push_back(Word);
		}                                                  
		stt.erase(0, pos + delim.length()); // Erase until the delimiter position
	}
	 
	if (!stt.empty()) { // Add any remaining content after the last delimiter
		VString.push_back(stt);
	}

	return VString;
}

InfoCl ConvertLineToRecord(string line, string Seperator = "#//#")
{
	InfoCl Client;
	vector<string>vClientData;
	vClientData = SplitString(line, Seperator);

	Client.AcountNumber = vClientData[0];
	Client.Phone = vClientData[1];
	Client.Name = vClientData[2];
	Client.Pincode = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);


	return Client;
}

string ConvertRecordToLine(InfoCl Client, string Seperator = "#//#")
{

	string stClientRecord = "";

	stClientRecord += Client.AcountNumber + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += Client.Name + Seperator;

	stClientRecord += Client.Pincode + Seperator;
	stClientRecord += to_string(Client.AccountBalance);


	return stClientRecord;
}


bool ClientsExistsByAccountNumber(string AccountNumer, string FileName)
{
	vector<InfoCl>vClients;

	fstream my1;
	my1.open(FileName, ios::in);


	if (my1.is_open())
	{
		string Line;
		InfoCl Client;

		while (getline(my1, Line))
		{
			Client = ConvertLineToRecord(Line);
			if (Client.AcountNumber== AccountNumer)
			{
				my1.close();
				return true;
			}
			vClients.push_back(Client);
		}

		my1.close();

	}
	return false;
}




InfoCl ReadInfo()
{
	InfoCl Client;
	cout << "Pleas enter your AccountNumber? ";
	getline(cin >> ws, Client.AcountNumber);
	while (ClientsExistsByAccountNumber(Client.AcountNumber, ClientsFileName))
	{
		cout << "\nClient With [" << Client.AcountNumber << "] already  exists    , Enter another Account";
		getline(cin >> ws, Client.AcountNumber);

	}
	cout << "Please enter your pincode?";
	getline(cin, Client.Pincode);

	cout << " Please enter your Name?";
	getline(cin, Client.Name);

	cout << " Please enter your phone?";
	getline(cin, Client.Phone);

	cout << "  Please enter your AccountBalance?";
	cin >> Client.AccountBalance;
	return Client;
}



vector< InfoCl>LoudClientDataFromFile(string FileName)
{
	vector<InfoCl>vClients;

	fstream my1;
	my1.open(FileName, ios::in);
	 


	if (my1.is_open())
	{
		string Line;
		InfoCl Client;

		while (getline(my1, Line))
		{
			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}

		my1.close();

	}
	return vClients;
}

void ClientRecordBalanceLine(InfoCl Client)
{
	cout << "| " << left << setw(15) << Client.AcountNumber;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(12) << Client.AccountBalance;

}

void PrintClientRecord(InfoCl Client)
{
	cout << "| " << left << setw(15) << Client.AcountNumber;
	cout << "| " << left << setw(10) << Client.Pincode;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(12) << Client.Phone;
	cout << "| " << left << setw(12) << Client.AccountBalance;
}



void ShowAllClientData()
{
	vector<InfoCl>vClients = LoudClientDataFromFile(ClientsFileName);

	cout << "\n\n\t\t\t\t\t\t Client List (" << vClients.size() << ") Client(s)";
	cout << "\t";

	cout << "\n_________________________________________________________________________________________________________________\n";

	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_________________________________________________________________________________________________________________\n";


	if (vClients.size() == 0)
	{
		cout << "\t\t\tNo Client Available  In the System";
	}
	else
		for (InfoCl Client : vClients)
		{
			PrintClientRecord(Client);
			cout << endl;
		}
	cout << "\n_________________________________________________________________________________________________________________\n";

}

void PrintClientCard(InfoCl Client)
{
	cout << "\nThe folloeing are the client details:\n";
	cout << "\nAccount Number  = " << Client.AcountNumber;
	cout << "\nPin Code    =   " << Client.Pincode;
	cout << "\nName        =     " << Client.Name;
	cout << "\nPhone       = " << Client.Phone;
	cout << "\nAccount Balance     =  " << Client.AccountBalance;

}

bool FindAccountNumber(string AccountNumber, vector<InfoCl>vClients, InfoCl& Client)
{


	for (InfoCl c : vClients)
	{
		if (c.AcountNumber == AccountNumber)
		{
			Client = c;
			return true;
		}
	}
	return false;
}

InfoCl ChangeClientRecord(string AccountNumber)
{
	InfoCl Client;
	Client.AcountNumber == AccountNumber;


	cout << "Please enter your pincode?";
	getline(cin >> ws, Client.Pincode);

	cout << " Please enter your Name?";
	getline(cin, Client.Name);

	cout << " Please enter your phone?";
	getline(cin, Client.Phone);

	cout << "  Please enter your AccountBalance?";
	cin >> Client.AccountBalance;

	return Client;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<InfoCl>& vClients)
{
	for (InfoCl& c : vClients)
	{
		if (c.AcountNumber == AccountNumber)
		{
			c.MarkForDelete = true;
			return true;
		}
	}
	return false;
}


vector<InfoCl>SaveClientsDataToFile(string FileName, vector<InfoCl>vClients)
{

	fstream my1;
	my1.open(FileName, ios::out);


	if (my1.is_open())
	{
		string DataLine;

		for (InfoCl c : vClients)
		{
			if (c.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLine(c);
				my1 << DataLine << endl;
			}
		}

		my1.close();

	}
	return vClients;
}




void AddDataToLine(string FileName, string stDataLine) 
{

	fstream my1;

	my1.open(FileName, ios::out | ios::app);

	if (my1.is_open())
	{
		my1 << stDataLine << endl;
		my1.close();
	}

}

void AddNewClient()
{
	InfoCl Client;
	Client = ReadInfo();
	AddDataToLine(ClientsFileName, ConvertRecordToLine(Client));
}
void AddClients()
{

	char Addmore = 'Y';
	do
	{
		system("cls");
		cout << "Adding New Client:\n\n ";

		AddNewClient();
		cout << "\n Client Added Successsfully !, Do you Want add More ?\n";
		cin >> Addmore;
		GoBackToMainMenue();
	} while  (toupper(Addmore) == 'Y');




}



bool  DeleteClientByAccountNumber(string AccountNumber, vector<InfoCl>& vClients)
{

	InfoCl Client;

	char answer = 'n';

	if (FindAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);

		cout << "\n\nAre you sure you want delete thiss Client ? y/n";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveClientsDataToFile(ClientsFileName, vClients);

			//Refresh Clients
			vClients = LoudClientDataFromFile(ClientsFileName);

			cout << "\n\nClient Deleted Successfully.";
			return true;
		}


		else
		{
			cout << "\n\nClient with  Account Number (" << AccountNumber << ") is not Found!";

		}

	}


	return false;


}


bool  UpdateClientByAccountNumber(string AccountNumber, vector<InfoCl>& vClients)
{

	InfoCl Client;

	char answer = 'n';


	if (FindAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);

		cout << "\n\nAre you sure you want Update thiss Client ? y/n";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{

			for (InfoCl& c : vClients)
			{
				if (c.AcountNumber == AccountNumber)
				{
					c = ChangeClientRecord(AccountNumber);
					break;
				}


			}




			SaveClientsDataToFile(ClientsFileName, vClients);


			cout << "\n\nClient Updeted Successfully.";
			return true;
		}





	}

}


string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "\nplease  Enter AccountNumber? ";
	cin >> AccountNumber;
	return AccountNumber;
}









//Find
bool FindAcountNumber(string AccountNumber, InfoCl& Client)
{
	vector<InfoCl>vClients = LoudClientDataFromFile(ClientsFileName);


	for (InfoCl c : vClients)
	{
		if (c.AcountNumber == AccountNumber)
		{
			Client = c;
			return true;
		} 
	}
	return false;
}







//void ShowTransactioonsScreen()


void ShowFindScreen()
{
	cout << "\n----------------------------\n";
	cout << "Find Clients Screen";
	cout << "\n----------------------------\n";
	vector<InfoCl>vClients = LoudClientDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	InfoCl Client;

	if (FindAccountNumber(AccountNumber, vClients, Client))

		PrintClientCard(Client);
	else
		cout << "\n\nClient with  Account Number (" << AccountNumber << ") is not Found!";


}

void ShowUpdateClientsScreen()
{

	cout << "\n---------------------------\n";
	cout << "Update Client Screen";
	cout << "\n----------------------------\n";


    vector<InfoCl>vClients = LoudClientDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);
	
}

void ShowDeleteClientsScreen()
{
	cout << "\n----------------------------\n";
	cout << "Delete Client Screen";
	cout << "\n----------------------------\n";


	vector<InfoCl>vClients = LoudClientDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);
}

void AddNewClientsScreen() {
	cout << "\n----------------------------\n";
	cout << "Add New Clients Screen";
	cout << "\n----------------------------\n";
	AddClients();

};












void ShowTotalBalances()
{
	vector<InfoCl>vClients = LoudClientDataFromFile(ClientsFileName);
	cout << "\n\t\t\t\t\t\tBalance List (" << vClients.size() << ")  Client(s).\n";
	cout << "\n_________________________________________________________________________________________________________________\n";

	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_________________________________________________________________________________________________________________\n";

	double TotalBalance = 0;

	if (vClients.size() ==    0)
	{
		cout << "\t\t\t\t\tNo Client Available In the System !";

	}
	else
	{
		for (InfoCl Client : vClients)
		{
			ClientRecordBalanceLine(Client);
			TotalBalance += Client.AccountBalance;
			cout << endl;
		}
		cout << "\n_________________________________________________________________________________________________________________\n";
		cout << "\t\t\t\t  Ttal Blance =" << TotalBalance;

	}
}


bool DepositBalanceToClientByAcountNumber(string AccountNumber, double Amount,vector<InfoCl>vClients)
{
	char Choice = 'n';
	

	cout << "Are you sure you want perfrom this transactions?";
	cin >> Choice;
	if (Choice == 'Y' || Choice =='y')
	{
		for (InfoCl& c : vClients)
		{
			if (c.AcountNumber == AccountNumber)
			{
				c.AccountBalance += Amount;
				SaveClientsDataToFile(ClientsFileName, vClients);
				cout << "\n\Done  Successfully New Balance = " << c.AccountBalance;

				return true;
			}
		}

	}
	return false;
}

void ShowTotalBalancesScreen()
{
	ShowTotalBalances();
}

// Show withdraw screen
void ShowWithdrowScreen()
{

	cout << "\n----------------------------\n";
	cout << "Withdrow Screen  (:";
	cout << "\n----------------------------\n";




	vector<InfoCl>vClients = LoudClientDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	InfoCl Client;

	while (!FindAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\n\nClient with  Account Number (" << AccountNumber << ") is not Found!\n";
		AccountNumber = ReadClientAccountNumber();
	}

	PrintClientCard(Client);
    cout << endl;
	cout << endl;


	double Amount=0;
	cout << "Please enter deposit Number?";
	cin >> Amount;
	
	while (Amount>Client.AccountBalance)
	{
		cout << "Amount Exceeds the balance, you can withdrow up to : "<<Client.AccountBalance <<endl;
		cout << "Please enter deposit Number ? ";
		cin >> Amount;

	}
	DepositBalanceToClientByAcountNumber(AccountNumber, Amount * -1, vClients);
}


// Show deposit screen
void ShowDepositScreen()
{

	cout << "\n----------------------------\n";
	cout << "Deposit Screen  (:";
	cout << "\n----------------------------\n";




	vector<InfoCl>vClients = LoudClientDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	InfoCl Client;

	while (!FindAccountNumber(AccountNumber, vClients, Client))
	{
          cout << "\n\nClient with  Account Number (" << AccountNumber << ") is not Found!\n";
		  AccountNumber=ReadClientAccountNumber();
	}	
	
			PrintClientCard(Client);
			cout << endl;
			cout << endl;

	double Amount=0;
	cout << "Please enter deposit Number?";
	cin >> Amount;
	DepositBalanceToClientByAcountNumber(AccountNumber, Amount, vClients);
}























// Read transactions menu options from user
void  ShowEndScreen()
{
	cout << "\n----------------------------\n";
	cout << "Program Ends  (:";
	cout << "\n----------------------------\n";
}





enum enTransactionsMenueOptions
{
	enDeposit=1, enWithdraw=2 ,enTotalBalances=3, enMainMenue=4
};  



enum enMainMenueOptions
{
	enListClient = 1, enAddNewClient=2,enDeleteClient=3
	, enUpdateeClient=4, enFindClient=5, enTransactions=6 ,Exit=7 

};




// Read transactions menu options from user
short ReadTransactionsMenueOptions()
{
	short Choice;
	cout << "Choce what do you want to do ? ";
	cin >> Choice;
	return Choice;
}

// Handle transactions menu
void TransactionMenue(enTransactionsMenueOptions Transaction)
{
	switch (Transaction)
	{
	case enTransactionsMenueOptions::enDeposit:
		system("cls");
		ShowDepositScreen();
		GoBackToTranactionsMenue();
		break;
	case enTransactionsMenueOptions::enWithdraw:
		system("cls");
		ShowWithdrowScreen();
		GoBackToTranactionsMenue();
		break;
	case enTransactionsMenueOptions::enTotalBalances:
		system("cls");
		ShowTotalBalancesScreen();
		GoBackToTranactionsMenue();
		break;
	case enTransactionsMenueOptions::enMainMenue:
		GoBackToMainMenue();
		break;
	}
}

// Show transactions menu
void ShowTransactionsMenue()
{
	cout << "=====================================================================================\n";
	cout << "\t\t\t TransactionsMenue Menue Scren\n";
	cout << "=====================================================================================\n";
	cout << "[1] Deposit." << endl;
	cout << "[2] Withdraw." << endl;
	cout << "[3] Total Balances." << endl;
	cout << "[4] Main Menue." << endl;

	TransactionMenue((enTransactionsMenueOptions)ReadTransactionsMenueOptions());
}














// Read main menu options from user

short ReadMainMenueOption()
{
short Choice;  
	cout << "Choce what do you want to do ? ";
	cin >> Choice;
	return Choice;
}


// Handle main menu

void MainMenue(enMainMenueOptions MainMenueOption)
{



	switch (MainMenueOption)
	{
	case enMainMenueOptions::enListClient:
		system("cls");
		ShowAllClientData();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::enAddNewClient:
		system("cls");
		AddNewClientsScreen();
		GoBackToMainMenue();

		break;

	case enMainMenueOptions::enDeleteClient:
		system("cls");
		ShowDeleteClientsScreen();
		GoBackToMainMenue();
		break;


	case enMainMenueOptions::enUpdateeClient:
		system("cls");
		ShowUpdateClientsScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::enFindClient:
		system("cls");
		ShowFindScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOptions::enTransactions:
		system("cls");
		ShowTransactionsMenue();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::Exit :
		system("cls");
		ShowEndScreen();

		break;
	}




}










// Show main menu

void ShowMainMenue()
{
	cout << "=====================================================================================\n";
	cout << "\t\t\t Main Menue Scren\n";
	cout << "=====================================================================================\n";
	cout << "[1] Show Client List." << endl;
	cout << "[2] Add New Client." << endl;
	cout << "[3] Delete Client." << endl;
	cout << "[4] Update Client." << endl;
	cout << "[5] Find Client." << endl;
	cout << "[6] Transactiosns." << endl;
	cout << "[7] Exit." << endl;
	MainMenue((enMainMenueOptions)ReadMainMenueOption());
	ShowTransactionsMenue();

}
int main()
{















	ShowMainMenue();

		return 0;
}




















