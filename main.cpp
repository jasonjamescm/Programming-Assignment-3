//Program Name : Programming Assignment 3
//Created by Jason Morales

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

//Prototypes
double getTotalExemption (char, int);
double getPension (double, double);
double getTaxableIncome (double, double, double);
double getTaxObligation (double);
void closeFile (ifstream&, ofstream&, ofstream&);
void display (string, double, double, double, double, double, ofstream&);
int openFile(string, ifstream&, ofstream&, ofstream&);
int showError();
void readData (ifstream&, string, char, int, double, double, double, ofstream&, double, double, double, ofstream&);



int main() {
    
    //Variable Declaration
    string inputFile;
    string lastName;
    int numberOfChild = 0;
    double grossIncome = 0.0;
    double percentOfIncome = 0.0;
    double totalExemption = 0.0;
    double pension = 0.0;
    double taxableIncome = 0.0;
    double taxObligation = 0.0;
    char maritalStatus = '\0';
    
    ifstream inFile;
    ofstream outFile;
    ofstream outFileError;
    
    
    openFile(lastName, inFile, outFile, outFileError);
    
    readData (inFile, lastName, maritalStatus, numberOfChild, grossIncome, percentOfIncome, totalExemption, outFileError, pension, taxableIncome, taxObligation, outFile);
        
    closeFile(inFile, outFile, outFileError);
}


// ~~~~~~~~~~~~~~FUNCTIONS~~~~~~~~~~~~~~~~

//Function to get total exemption amount
double getTotalExemption(char maritalStatus, int numberOfChild){
    double totalExemption;
    switch (maritalStatus) {
        case 'S': case 's':
            totalExemption = 2500.00 + (650 * ( numberOfChild + 1) );
                    break;
                case 'M': case 'm':
                    totalExemption = 5500.00 + (650 * ( numberOfChild + 2) );
                    break;
                default:
                    totalExemption = 0;
                    break;
    }
    return totalExemption;
}

//Funciton to Get Pension
double getPension(double grossIncome, double percentOfIncome){
    double pension = grossIncome * percentOfIncome;
    return pension;
}

//Function to get Taxable income
double getTaxableIncome(double pension, double grossIncome, double totalExemption){
    double taxableIncome = grossIncome - pension - totalExemption;
    return taxableIncome;
}

//Function to get Tax Obligation
double getTaxObligation(double taxableIncome){
    double taxObligation;
    if(taxableIncome < 20001){
        taxObligation = taxableIncome * 0.15;
    }else if(taxableIncome > 20000 && taxableIncome < 50001){
        taxObligation = ((taxableIncome - 20000) * 0.25) + 2000;
    }else{
        taxObligation = ((taxableIncome - 50000) * 0.35) + 8000;
    }
    return taxObligation;
}

//Function to open files
int openFile(string inputFile, ifstream& inFile, ofstream& outFile, ofstream& outFileError){
    // File Name Input
    cout << "File Name: ";
    cin >> inputFile;
    
    //Open inputFile
    inFile.open(inputFile.c_str());        // Open Input File
    outFile.open("RESULT SUCCESS.txt");        // Create Output File
    outFileError.open("RESULT ERRORS.txt");    // Create Error Output File
    return 0;
}

//Function to read data
void readData (ifstream& inFile, string lastName, char maritalStatus, int numberOfChild, double grossIncome, double percentOfIncome, double totalExemption, ofstream& outFileError, double pension, double taxableIncome, double taxObligation, ofstream& outFile){
    
    if (inFile.is_open()) {
    cout << setw(10) << "Last Name" << setw(25) << "Gross Income" << setw(25) << "TotalExemption" << setw(20) << "Pension Ded" << setw(25) << "Taxable Income" << setw(25) << "Tax Obligation" << endl;
    
    while (inFile >> lastName >> maritalStatus >> numberOfChild >> grossIncome >> percentOfIncome) {

        totalExemption = getTotalExemption(maritalStatus, numberOfChild);

        if(percentOfIncome > .04 || percentOfIncome < 0.00){
            outFileError << setw(10) << lastName << setw(20) << maritalStatus << setw(20) << numberOfChild << setw(27) << grossIncome << setw(20)
            << percentOfIncome << setw(40) << "INVALID PERCENT OF INCOME" << endl;
        }else if(totalExemption == 0){
            outFileError << setw(10) << lastName << setw(20) << maritalStatus << setw(20) << numberOfChild << setw(27) << grossIncome << setw(20)
            << percentOfIncome << setw(40) << "INVALID MARITAL STATUS" << endl;
        }else{

            pension = getPension(grossIncome, percentOfIncome);
            taxableIncome = getTaxableIncome(pension, grossIncome, totalExemption);
            taxObligation = getTaxObligation(taxableIncome);

display(lastName, grossIncome, totalExemption, pension, taxableIncome, taxObligation, outFile);
        }
    }

}else{
    showError();
}
        }
        

//Function to close files
void closeFile (ifstream& inFile, ofstream& outFile, ofstream& outFileError){
    inFile.close();
    outFile.close();
    outFileError.close();
}

//Function to display in console and output file
void display (string lastName, double grossIncome, double totalExemption, double pension, double taxableIncome, double taxObligation, ofstream& outFile){
    cout << setw(10) << lastName << setw(20) << grossIncome << setw(20) << totalExemption
    << setw(27) << pension << setw(20) << taxableIncome << setw(20) << taxObligation << endl;

    outFile << setw(10) << lastName << setw(20) << grossIncome<< setw(20) << totalExemption
    << setw(27) << pension << setw(20) << taxableIncome << setw(20) << taxObligation << endl;
}

//Function for error
int showError (){
    cout << "Unable to open file" << endl;
    return 0;
}
