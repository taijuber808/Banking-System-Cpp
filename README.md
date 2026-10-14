# Banking System in C++

## Project Description
This is a simple console-based Banking System project developed in C++. 
It demonstrates the concepts of Object-Oriented Programming like Inheritance, Polymorphism and Encapsulation.

## Features
- Create different types of bank accounts (Savings, Checking, Fixed Deposit)
- Deposit and Withdraw money
- Calculate interest for Savings and Fixed Deposit accounts
- Check overdraft for Checking account
- Display account details
- Menu driven interface

## Class Structure
1. **BankAccount** (Base Class)
   - accountNumber, accountHolderName, balance
   - deposit(), withdraw(), getBalance(), displayAccountDetails()

2. **SavingsAccount** (Derived)
   - interestRate
   - calculateInterest()

3. **CheckingAccount** (Derived)
   - overdraftLimit
   - checkOverdraft()

4. **FixedDepositAccount** (Derived)
   - term (in months)
   - calculateInterest()
