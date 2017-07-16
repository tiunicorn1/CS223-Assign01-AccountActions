// Assign01-AccountActions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <string>

using namespace std;

char getActionCode();
void displayBalance();
void recordAction(char);
double getActionAmount(char);
void writeAction(char, double);
void listActions();
string getActionLabel(char);
void UseProgram();


int main()
{
	char actionCode;

	cout << fixed << setprecision(2);

	actionCode = getActionCode();
		
	while (actionCode != 'Q')
	{
		switch (actionCode)
		{
		case 'B':
			displayBalance();
			break;
		case 'C':
			recordAction('C');
			break;
		case 'D':
			recordAction('D');
			break;
		case 'W':
			recordAction('W');
			break;
		case 'L':
			listActions();
			break;
		}
		
		actionCode = getActionCode();
	}
	

	cout << endl;
	system("pause");
    return 0;
}

void UseProgram()
{
	cout << "Enter B  show Balance \t ... " << endl;
	cout << "Enter C  record Check \t ... " << endl;
	cout << "Enter D  make Deposit \t ... " << endl;
	cout << "Enter W  Withdrawal \t ... " << endl;
	cout << "Enter L  List actions \t ... " << endl;
	cout << "Enter Q  Quit Program: \t";
}

char getActionCode()	
{
	char bankTransaction;
	
	UseProgram();

	cin >> right >> setw(3) >> bankTransaction;

	bankTransaction = toupper(bankTransaction);

	switch (bankTransaction)
		{
		case 'B':
		case 'C':
		case 'D':
		case 'W':
		case 'L':
		case 'Q':
			return bankTransaction;
			break;
		default:
			UseProgram();
		}

		
}

void displayBalance()
{
	double balance = 0.00;
	char actCode;
	double actAmt;
	ifstream inputFile;
	
	inputFile.open("AccountActions.txt");

	if (!inputFile)
	{
		cout << endl << endl << "BALANCE of account \t $ \t" << balance << endl << endl;
	}
	if (inputFile)
	{
		inputFile >> actCode >> actAmt;

		while (!inputFile.eof())
		{
			if (actCode == 'D')
				balance = actAmt + balance;
			else
				balance = balance - actAmt;

			inputFile >> actCode >> actAmt;
		}

		cout << endl << endl << "BALANCE of account \t $" << right << setw(10) << balance << endl << endl;
	}

		inputFile.close();
}

 void recordAction(char action)
 {
	double recordAmount = 0.00;
	
	cout << endl;
	
	recordAmount = getActionAmount(action);

	writeAction(action, recordAmount);	
	
	cout << endl;

}

double getActionAmount(char actionType)
{
	double amt = 0.00;

	cout << "Amount of " << getActionLabel(actionType) << '\t' << "$ ";

	cin >> amt;

	return amt;

}

void writeAction(char transType, double transAmt)
{
	ofstream outputFile;

	outputFile << fixed << setprecision(2);

	outputFile.open("AccountActions.txt", ios::app);

	outputFile << transType << right << setw(10) << transAmt << endl;

	outputFile.close();

}

void listActions()
{
	ifstream inputFile;
	char actType;
	double actnAmt;

	cout << fixed << setprecision(2);

	inputFile.open("AccountActions.txt");
	
	if (!inputFile)		//open output File initial creation
	{
		cout << endl << "Action file not found. Please make initial deposit." << endl;
	}
	
	if (inputFile)
	{
		inputFile >> actType >> actnAmt;

		while (!inputFile.eof())
		{
			cout << endl << endl << getActionLabel(actType) << '\t' << '\t';
			if (actType == 'D')
				cout << "\t +";
			else if (actType == 'C')
				cout << "\t -";
			else
				cout << " -";

			cout << right << setw(10) << actnAmt;

			inputFile >> actType >> actnAmt;
		}
	}

	displayBalance();

	inputFile.close();
}

string getActionLabel(char label)
{
	string transactionType;

	if (label == 'D')
		transactionType = "deposit";
	else if (label == 'C')
		transactionType = "check";
	else
		transactionType = "withdrawal";
	
	return transactionType;
}