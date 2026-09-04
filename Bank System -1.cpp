#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

string fileName = "Clients.txt";

struct stClient {
	string AccountNumber;
	string PinCode;
	string ClientName;
	string Phone;
	double Balance;
	bool MarkForDelete = false;
};

void ShowTransactionMenue();
void ShowMainMenue();

enum enMainMenueOptions {
	eListClients = 1,
	eAddNewClient = 2,
	eDeleteClient = 3,
	eUpdateClient = 4,
	eFindClient = 5,
	eShowTransactionMenue = 6,
	eExit = 7
};

// bank2 
enum enTreansactionMenueOptions {
	eDeposit = 1,
	eWithdraw = 2,
	eTotalBalacne = 3,
	eMainMenu = 4,
};

string readAccountNumber(string msg) {
	string AccountNumber;
	cout << msg;
	cin >> AccountNumber;
	return AccountNumber;
}

short ReadMainMenueOption(string msg) {
	cout << msg;
	short Choice = 0;
	cin >> Choice;
	return Choice;
}

void GoBackToMainMenue() {
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");

	ShowMainMenue();
}
// bank2 
void GoBackToTransactionMenue() {
	cout << "\n\nPress any key to go back to Transaction Menue...";
	system("pause>0");

	ShowTransactionMenue();
}

vector <string> splitString(string s1, string delim = "//##//") {

	string sWord="";
	short pos = 0;
	vector<string>vClients;
	
	while ((pos = s1.find(delim)) != std::string::npos) {
		
		sWord = s1.substr(0, pos);

		if (sWord != ""){
			vClients.push_back(sWord);
		}
		
		s1.erase(0, pos + delim.length());
	}

	if (s1 != "") {
		vClients.push_back(s1);
	}
	return vClients;
}

string convertRecordToLine(const stClient &Client,string delim ="//##//") {

	string line = "";

	line += Client.AccountNumber + delim;
	line += Client.PinCode + delim;
	line += Client.ClientName + delim;
	line += Client.Phone + delim;
	line += to_string(Client.Balance);

	return line;
}

stClient convertLineToRecord(const string &line) {
	vector <string> vClients;
	vClients = splitString(line);
	stClient client;

	client.AccountNumber = vClients[0];
	client.PinCode = vClients[1];
	client.ClientName = vClients[2];
	client.Phone = vClients[3];
	client.Balance = stod(vClients[4]);

	return client;
}

void saveDataToFile(string fileName , const vector <stClient> & vClient) {
	fstream myFile;

	myFile.open(fileName, ios::out);
	string line;
	if (myFile.is_open()) {
		for (const stClient &C : vClient) {
			if (C.MarkForDelete != true) {
				line = convertRecordToLine(C);
				myFile << line << endl;
			}
		}
		myFile.close();
	}
}

void AddDataLineToFile(string fileName, string dataLine) {
	fstream MyFile;

	MyFile.open(fileName, ios::out | ios::app);

	if (MyFile.is_open()){
		MyFile << dataLine << endl;
		MyFile.close();
	}
}

vector <stClient> loadDataFromFile(string fileName) {

	stClient Clients;
	vector <stClient> vClients;
	fstream myFile;
	myFile.open(fileName, ios::in);

	if (myFile.is_open()) {
		string line;

		while (getline(myFile, line)) {

			Clients = convertLineToRecord(line);
			vClients.push_back(Clients);

		}
		myFile.close();
	}
	return vClients;
}

bool ClientExistsByAccountNumber(string AccountNumber, string fileName) {

	fstream MyFile;
	MyFile.open(fileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;
		stClient Client;
		while (getline(MyFile, Line))
		{
			Client = convertLineToRecord(Line);
			if (Client.AccountNumber == AccountNumber){
				MyFile.close();
				return true;
			}
		}
		MyFile.close();
	}
	return false;
}

stClient ReadNewClient() {
	stClient Client;
		cout << "Enter Account Number: ";
		getline(cin >> ws, Client.AccountNumber);

		while (ClientExistsByAccountNumber(Client.AccountNumber, fileName)) {	
			cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number ? ";
			getline(cin >> ws, Client.AccountNumber);
		}

		cout << "Enter Pin Code: ";
		getline(cin, Client.PinCode);

		cout << "Enter Name: ";
		getline(cin, Client.ClientName);

		cout << "Enter a Phone Number: ";
		getline(cin, Client.Phone);

		cout << "Enter Balance: ";
		cin >> Client.Balance;
		
		return Client;
}

void addMoreClients() {
	stClient Client;
	char addMore = 'Y';

	do {
		cout << "\n\n::::| Add New Client |::::" << endl;

		Client = ReadNewClient();

		AddDataLineToFile(fileName, convertRecordToLine(Client));

		cout << "Do You Want To Add More (y/n): ";
		cin >> addMore;
	} while (addMore == 'Y' || addMore == 'y');
}

void ShowAddClientScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tAdd Client Screen";
	cout << "\n-----------------------------------\n";

	addMoreClients();
}

void PrintClientRecord(const stClient& Client) {
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.ClientName;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.Balance;
}

void PrintTotalClientRecord(stClient Client) {
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.ClientName;
	cout << "| " << setw(12) << left << Client.Balance;
}

void showAllClients(const vector <stClient> &vClients) {
	if (vClients.size() == 0) {
		cout << "\t\t\t\tNo Clients Available In the System!";
	}
	else {

	cout << "-----------------------------------|| Show [" << vClients.size() << "] Client's ||------------------------------------\n" << endl;
	cout << "| " << setw(15) << left << "Account Number";
	cout << "| " << setw(10) << left << "PinCode";
	cout << "| " << setw(40) << left << "Client Name";
	cout << "| " << setw(12) << left << "Phone";
	cout << "| " << setw(12) << left << "Balance";
	cout << "\n----------------------------------------------------------------------------------------------\n";

	for (const stClient &C : vClients) {
		PrintClientRecord(C);
		cout << "\n";
	}
	}
}

void ShowAllClientScreen() {

	vector <stClient> vClients = loadDataFromFile(fileName);

	showAllClients(vClients);
}

void PrintClientCard(const stClient& Client) {
	cout << "\nThe following are the client details:\n";
	cout << "-----------------------------------";

	cout << "\nAccount Number: " << Client.AccountNumber;
	cout << "\nPin Code      : " << Client.PinCode;
	cout << "\nName          : " << Client.ClientName;
	cout << "\nPhone         : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.Balance;

	cout << "\n-----------------------------------\n";
}

bool findClientByAccountNumber(string accountNumber,const vector <stClient> &vClients, stClient &Client) {
	for (const stClient &C : vClients) {
		if (C.AccountNumber == accountNumber) {
			Client = C;
			return true;
		}
	}
	return false;
}

stClient UpdateClient(string AccountNumber) {
	stClient Client;
	Client.AccountNumber = AccountNumber;

	cout << "Enter Pin Code: ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name: ";
	getline(cin, Client.ClientName);

	cout << "Enter a Phone Number: ";
	getline(cin, Client.Phone);

	cout << "Enter Your Balance: ";
	cin >> Client.Balance;

	return Client;
}

// bank2
bool DepositBalanceToClientByAccountNumber(string accountNumber, vector <stClient>& vClients, double amount) {
	char answer = 'n';
	cout << "\nAre you sure you want perfrom this transaction(y/n) ";
	cin >> answer;

	if (answer == 'Y' || answer == 'y') {
		for (stClient& C : vClients) {
			if (C.AccountNumber == accountNumber) {
				C.Balance += amount;
				saveDataToFile(fileName, vClients);
				cout << "\n\nDone Successfully. New balance is: " << C.Balance;
				return true;
			}
		}
	}
	return false;
}

stClient WithdrawAction(stClient& Client, double amount) {

	Client.AccountNumber = Client.AccountNumber;
	Client.PinCode = Client.PinCode;
	Client.ClientName = Client.ClientName;
	Client.Phone = Client.Phone;

	while (amount > Client.Balance) {
		cout << "\nAmount Exceeds the balance, you can withdraw up to: " << Client.Balance << endl;
		cout << "Please enter another amount: ";
		cin >> amount;
	}

	Client.Balance = Client.Balance + (amount * -1);
	return Client;
}

bool MarkClientForDelete(string accountNumber, vector <stClient>& vClients) {
	
	for (stClient& C : vClients) {
		if (C.AccountNumber == accountNumber) {
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

bool DeleteDataByAccountNumber(string accountNumber,vector <stClient> &vClient) {
	stClient Client;
	char answer = 'y';
	if (findClientByAccountNumber(accountNumber, vClient, Client)) {
		
		PrintClientCard(Client);
		cout << "\nAre you sure to delete this item (Y/N): ";
		cin >> answer;

		if (answer == 'Y' || answer == 'y') {
			
			MarkClientForDelete(accountNumber, vClient);
			saveDataToFile(fileName, vClient);
			vClient = loadDataFromFile(fileName);

			cout << "Item Delete Succesfully" << endl;
			return true;
		}
		else {
			cout << "Delete Cansled" << endl;
			return false;
		}

	}
	else {
		cout << "Not Found";
		return false;
	}
}

void ShowDeleteClientScreen(){
	cout << "\n-----------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n-----------------------------------\n";

	vector <stClient> vClients = loadDataFromFile(fileName);

	string accountNumber = readAccountNumber("Enter a account number to delete: ");
	DeleteDataByAccountNumber(accountNumber,vClients);
}

void ShowOneClientScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tFind Client Screen";
	cout << "\n-----------------------------------\n";

	vector <stClient> vClients = loadDataFromFile(fileName);

	stClient Client;

	string accountNumber = readAccountNumber("Enter a account number to search: ");

	if (findClientByAccountNumber(accountNumber, vClients, Client))
	{
		PrintClientCard(Client);
	}
	else
	{
		cout << "\nClient with Account Number[" << accountNumber << "] is not found!";
	}
}

bool UpdateDataByAccountNumber(string accountNumber,vector <stClient> &vClient) {
	stClient Client;
	char answer = 'y';
	if (findClientByAccountNumber(accountNumber, vClient, Client)) {

		PrintClientCard(Client);
		cout << "\nAre you sure to update this item (Y/N): ";
		cin >> answer;

		if (answer == 'Y' || answer == 'y') {
			for (stClient &C: vClient) {
				if (C.AccountNumber == accountNumber) {

					C = UpdateClient(accountNumber);
					break;

				}
			}
			saveDataToFile(fileName, vClient);
			cout << "Item Updated Succesfully" << endl;
			return true;
		}
		else {
			cout << "Updated Cansled" << endl;
			return false;
		}
	}
	else {
		cout << "Not Found";
		return false;
	}
}

void ShowUpdateClientScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tUpdate Client Screen";
	cout << "\n-----------------------------------\n";
	vector <stClient> vClients = loadDataFromFile(fileName);

	string accountNumber = readAccountNumber("Enter a account number to update: ");
	UpdateDataByAccountNumber(accountNumber, vClients);
}

void ShowEndScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tProgram Ends :-)";
	cout << "\n-----------------------------------\n";
}

// bank2
void DepositPerformScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tDeposit Perform Screen";
	cout << "\n-----------------------------------\n";

	vector <stClient> vClients = loadDataFromFile(fileName);
	stClient Client;
	string accountNumber = readAccountNumber("Enter a account number: ");

	while (!findClientByAccountNumber(accountNumber, vClients, Client)) {
		cout << "Client with account [ " << accountNumber << " ] is not found\n";
		accountNumber = readAccountNumber("Enter another account number: ");
	}

	PrintClientCard(Client);

	double Ammount = 0;

	cout << "\nEnter Deposit ammount: ";
	cin >> Ammount;

	DepositBalanceToClientByAccountNumber(accountNumber, vClients, Ammount);
}

void WithdrawPerformScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tWithdraw Perform Screen";
	cout << "\n-----------------------------------\n";

	vector <stClient> vClients = loadDataFromFile(fileName);
	stClient Client;
	string accountNumber = readAccountNumber("Enter a account number: ");

	while (!findClientByAccountNumber(accountNumber, vClients, Client)) {
		cout << "Client with account [ " << accountNumber << " ] is not found\n";
		accountNumber = readAccountNumber("Enter another account number: ");
	}

	PrintClientCard(Client);

	double Ammount = 0;
	cout << "\nEnter Withdraw ammount: ";
	cin >> Ammount;
	
	while (Ammount > Client.Balance) {
		cout << "\nAmount Exceeds the balance, you can withdraw up to: " << Client.Balance << endl;
		cout << "Please enter another amount: ";
		cin >> Ammount;
	}
	DepositBalanceToClientByAccountNumber(accountNumber, vClients, Ammount * -1);
}

void showTotalBalancesClients() {

	vector <stClient> vClients = loadDataFromFile(fileName);

	cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	double TotalBalances = 0;
	
	if (vClients.size() == 0) {

		cout << "\t\t\t\tNo Clients Available In the System!";
	}
	else {


		for (stClient Client : vClients)
		{
			PrintTotalClientRecord(Client);
			TotalBalances += Client.Balance;
			cout << endl;
		}
	}
	cout <<	"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "\t\t\t\t\t Total Balances = " << TotalBalances;
}


void ShowTotalBalancesScreen() {

	showTotalBalancesClients();
}

void PerfromTransactionMenueOption(enTreansactionMenueOptions TransactionnMenueOptions) {

	switch (TransactionnMenueOptions) {
	case enTreansactionMenueOptions::eDeposit:
		system("cls");
		DepositPerformScreen();
		GoBackToTransactionMenue();
		break;

	case enTreansactionMenueOptions::eWithdraw:
		system("cls");
		WithdrawPerformScreen();
		GoBackToTransactionMenue();
		break;

	case enTreansactionMenueOptions::eTotalBalacne:
		system("cls");
		ShowTotalBalancesScreen();
		GoBackToTransactionMenue();
		break;

	case enTreansactionMenueOptions::eMainMenu:
		system("cls");
		ShowMainMenue();
		break;

	default:
		cout << "\nInvalid choice, please try again." << endl;
		GoBackToTransactionMenue();
	}
	cout << endl;
}

// bank2 
void ShowTransactionMenue() {
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tTransaction Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balance.\n";
	cout << "\t[4] Back To Main Menue.\n";
	cout << "===========================================\n";
	PerfromTransactionMenueOption((enTreansactionMenueOptions)ReadMainMenueOption("Choose what do you want to do? [1 to 4]? "));
}

void PerfromMainMenueOption(enMainMenueOptions MainMenueOptions) {
	
	switch (MainMenueOptions) {
	case enMainMenueOptions::eListClients:
		system("cls");
		ShowAllClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eAddNewClient:
		system("cls");
		ShowAddClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eDeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eUpdateClient:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eFindClient:
		system("cls");
		ShowOneClientScreen();
		GoBackToMainMenue();
		break;		

	case enMainMenueOptions::eShowTransactionMenue:
		system("cls");
		ShowTransactionMenue();
		break;

	case enMainMenueOptions::eExit:
		system("cls");
		ShowEndScreen();
		break;

	default:
		cout << "\nInvalid choice, please try again." << endl;
		GoBackToMainMenue();
	}
	cout << endl;
}

void ShowMainMenue() {
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Show Transaction Menue.\n";
	cout << "\t[7] Exit.\n";
	cout << "===========================================\n";
	PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption("Choose what do you want to do? [1 to 7]? "));
}

int main(){
	ShowMainMenue();

	return 0;
}