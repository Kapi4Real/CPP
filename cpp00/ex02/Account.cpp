#include "Account.hpp"
#include <iostream>
#include <ctime>
#include <iomanip>

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

int Account::getNbAccounts() { return _nbAccounts; }
int Account::getTotalAmount() { return _totalAmount; }

void Account::_displayTimestamp()
{
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    char result[20];
    strftime(result, sizeof(result), "[%Y%m%d_%H%M%S] ", timeinfo);
    std::cout << result;
}

Account::Account(int initial_deposit)
{
	_accountIndex = _nbAccounts;
	_amount = initial_deposit;
	_nbDeposits = 0;
	_nbWithdrawals = 0;
	_nbAccounts++;
	_totalAmount += initial_deposit;

	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";"
		<< "amount:" << _amount << ";"
		<< "created" << std::endl;
}


void Account::makeDeposit(int deposit)
{
	int prev_amount = _amount;

	_amount += deposit;

	_nbDeposits += 1;

	_totalAmount += deposit;

	_totalNbDeposits += 1;

	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";" 
		  << "p_amount:" << prev_amount << ";" 
		  <<"deposit:"<< deposit << ";" 
		  << "amount:" << _amount << ";" 
		  << "nb_deposits:"<< _nbDeposits << std::endl;
}

bool Account::makeWithdrawal(int withdrawal)
{
	int prev_amount = _amount;

	if (_amount >= withdrawal)
	{
		_totalAmount -= withdrawal;
		_amount -= withdrawal;
		_nbWithdrawals++;
		_totalNbWithdrawals++;

		_displayTimestamp();
        	std::cout << "index:" << _accountIndex << ";"
                  	<< "p_amount:" << prev_amount << ";"
                  	<<"withdrawal:"<< withdrawal << ";"
                  	<< "amount:" << _amount << ";"
                  	<< "nb_withdrawals:"<< _nbWithdrawals << std::endl;
		return true;
	}

	else
	{
		_displayTimestamp();
                std::cout << "index:" << _accountIndex << ";"
                        << "p_amount:" << prev_amount << ";"
                        <<"withdrawal:refused" << std::endl;
		return false;
	}
}

int Account::getNbDeposits()
{
    return _totalNbDeposits;
}

int Account::getNbWithdrawals()
{
    return _totalNbWithdrawals;
}

int Account::checkAmount() const 
{
    return _amount;
}


void Account::displayAccountsInfos() 
{
    _displayTimestamp();
    std::cout << "accounts:" << getNbAccounts() << ";"
              << "total:" << getTotalAmount() << ";"
              << "deposits:" << getNbDeposits() << ";"
              << "withdrawals:" << getNbWithdrawals() << std::endl;
}

void Account::displayStatus() const 
{
    _displayTimestamp();
    std::cout << "index:" << _accountIndex << ";"
              << "amount:" << _amount << ";"
              << "deposits:" << _nbDeposits << ";"
              << "withdrawals:" << _nbWithdrawals << std::endl;
}

Account::~Account()
{
    _nbAccounts--;
    _totalAmount -= _amount;

    _displayTimestamp();
    std::cout << "index:" << _accountIndex << ";"
              << "amount:" << _amount << ";"
              << "closed" << std::endl;
}
