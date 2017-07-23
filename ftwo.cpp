//
// SPROG File Stream Sample
// ftwo.cpp
//
// Created by elviskason.lin on 17 July 2017
//

// NOTE To-do list
// Save data from avg & stdD into a struct. Use this data for file output.
// Declare structs.
// Finish up averages
// Finish up file output

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

// ---------- VAR Global Variables ----------
vector <string> subjects;
int totalStudents, totalSubj;
bool isFileLoaded = false;

// ---------- CLASS Student ----------
class student {
  // VAR
  string name;
  vector <float> marks;
  float average;

public:
  // GETTER
  string getName(void) { return name; }
  float getMark(int index) { return marks[index]; }
  float getAverage(void) { return average;}

  // SETTER
  void setName(string input_name) { name = input_name; }
  void addMark(float input_mark) { marks.push_back(input_mark); }
  void editMark(float input_mark, unsigned int index) { marks[index] = input_mark; }
  void processAverage(void) {
    float sum = 0;
    for (int x = 0; x < (int)marks.size(); x++) { sum += getMark(x); }
    average = sum / marks.size();
  }
};

// ---------- STRUCT DATAS ----------

struct stdD {
  
};

struct avg {
  
};

// ---------- FUNC MISC ----------

// --- GET INPUT <unsigned short int> ---
unsigned short int getMenuChoice(string argcs) {
  unsigned short int choice;
  cout << argcs ; cin >> choice;
  return choice;
}

// --- GET INPUT <string> ---
string getInputString(string argcs) {
  string input;
  cout << argcs; cin >> input;
  return input;
}

// ---------- FUNC FILE STREAM ----------

// NOTE
// REMEMBER TO ADD PROMPT TO ASK WHETHER USER WISHES TO LOAD/OVERWRITE DATASETS

// --- FILE LOADING ---
void loadFile(vector <student> &data) {
  // Initial User Greetings
  cout << "\n ---------- \nFILE LOADING\n ---------- \n" << endl;

  // Get file name
  string fileName;
  cout << "\nEnter file name for input : ";
  cin >> fileName;
  cin.clear();
  cout << "***** Trying to find : \"" << fileName << "\"" << endl;

  // Initialise file stream
  ifstream fin;
  fin.open(fileName.c_str());

  // IF Statement to check whether file exists.
  if (fin.fail()) {
    cout << "***** ERROR. No such file or directory." << endl;
    cin.clear();
    // A small prompt to check whether user wish to try to load again.
    char choice;
    cout << "Do you wish to load another file? Y to Load." << endl << "Your choice : "; cin >> choice;
    if (choice == 'y' || choice == 'Y') { loadFile(data); } else { return; }

  } else {
    // Set isFileLoaded boolean to true
    isFileLoaded = true;

    // Get variables for total number of Students & Subjects
    fin >> totalStudents >> totalSubj;
    fin.ignore(); // Ignores extra characters left from previous input.

    // Iteration construct to get subject names.
    for (int ia = 0; ia < totalSubj; ia++) {
      string temp; getline(fin, temp);
      subjects.push_back(temp);
    }
    fin.ignore();

    // Iteration construct to get marks & names for each student.
    for (int ib = 0; ib < totalStudents; ib++) {
      student buffer; // Create a temporary object called buffer that uses student construct.
      string name; float temp;

      // Get student name
      getline(fin, name);
      buffer.setName(name);

      // Get student marks
      for (int ic = 0; ic < totalSubj; ic++) {
        fin >> temp;
        buffer.addMark(temp); // Push back to internal vector.
      }

      buffer.processAverage(); // Processes the average for the person.
      data.push_back(buffer); // Adds the buffer (student n) object to the vector.
      fin.ignore();
    }

    cout << "***** File \"" << fileName << "\" loaded successfully!" << endl;
    cout << "Total number of students : " << data.size() << endl << endl;
  }
  fin.close();
}

// --- FILE OUTPUT ---
void outputFile(vector <student> &data, string fileName, struct stdD, struct avg) {
  ofstream fout;
  fout.open(fileName.c_str());

  if (fout.is_open()) {
    // Start output
    

    cout << "***** Output to \" " << fileName << "\" successful!" << endl;
  } else {
    cout << "***** Error Opening \"" << fileName << "\".\n\n";
  }

  fout.close();
}

// ---------- FUNC Data Processing ----------

// --- STANDARD DEVIATION ---
void calcStdD(vector <student> &data, unsigned short int choice, bool shouldCout) {
  if (choice == 1) {
    cout << "\n ----- 2.2.1 Overall Standard Deviation ----- \n";

    // DATA PROCESSING
    float sum = 0.0, mean = 0.0, stdD = 0.0, top = 0.0;
    for (int i = 0; i < totalStudents; i++) { sum += data[i].getAverage(); }
    mean = sum/totalStudents;
    for (int ib = 0; ib < totalStudents; ib++) { top += pow((data[ib].getAverage() - mean), 2); }
    stdD = sqrt(top/totalStudents);

    if (shouldCout == true) {
      // COUT stdD value if bool shouldCout is TRUE
      cout << "\n Standard Deviation : " << stdD << endl;
    } else {
      // Save data to struct. & Return.
    }

  } else if (choice == 2) {
    cout << "\n ----- 2.2.2 Standard Deviation per Subject ----- \n";

    // Getting user's choice of subject for analysis.
    string toShow = "Available subjects for analysis :\n";
    for (int i = 0; i < totalSubj; i++ ) {
      toShow += ("[" + to_string(i) + "] " + subjects[i] + "\n");
    }
    toShow += "Enter your choice : ";
    int subjChoice = getMenuChoice(toShow); // Gets and Returns user choice.
    subjChoice -= 1; // Minus one to choice so that counting starts from zero.

    // Data Processing
    float sum = 0.0, mean = 0.0, stdD = 0.0, top = 0.0;
    for (int i = 0; i < totalStudents; i++) { sum += data[i].getMark(subjChoice); }
    mean = sum/totalStudents;
    for (int ib = 0; ib < totalStudents; ib++) { top += pow((data[ib].getMark(subjChoice) - mean), 2); }
    stdD = sqrt(top/totalStudents);

    if (shouldCout == true) {
      // COUT stdD value if bool shouldCout is TRUE
      cout << "\n Standard Deviation : " << stdD << endl;
    } else {
      // Save data to struct. & Return.
    }

  } else {
    cout << "\n\n***** Invalid Input!\n\n";
  }
}

// --- AVERAGES > PASSES/FAILURES/DISTINCTIONS ---
void calcAvg(vector <student> &data, unsigned short int choice, bool shouldCout) {
  if (choice == 1) {
    cout << "\n ----- 2.1.1 Overall Averages ----- \n";

    // Variable Declaration
    unsigned int counterPasses = 0, counterFailures = 0, counterDistinctions = 0;
    vector <string> namesPasses, namesFailures, namesDistinctions;

    // Data Processing
    for (int ia = 0; ia < totalStudents; ia++) {
      float temp = data[ia].getAverage();
      string tempName = data[ia].getName();
      if (temp >= 50.0) {
        counterPasses++; namesPasses.push_back(tempName);
        if (temp >= 75.0) { counterDistinctions++; namesDistinctions.push_back(tempName); }
      }
      else if (temp < 50.0) { counterFailures++; namesFailures.push_back(tempName); }
    }

    if (shouldCout == true) {
      // Only COUT if shouldCout is TRUE
      cout << "\nNumber of Passes : " << counterPasses << "\nNumber of Failures : " << counterFailures << "\nNumber of Distinctions : " << counterDistinctions << endl;
    } else {
      // Else save data to struct and return.
    }

    // Return data to a struct.

  } else if (choice == 2) {
    cout << "\n ----- 2.2.2 Averages per Subject ----- ";



  } else {
    cout << "\n\n***** Invalid Input!\n\n";
  }
}

// --------- FUNC DISPLAY ----------

// --- MAIN MENU ---
void displayMenu() {
  cout << "\n ---------- \nAVAILABLE FUNCTIONS\n ---------- \n" << endl;
  cout << "1. Load Student Data File\n2. Display Statistics ...\n3. Raw Data Dump\n0. EXIT PROGRAM\n";
}

// --- STATS ---
void displayStats(vector <student> &data) {
  unsigned short int choice, choiceType;
  cout << "\n ---------- 2. DISPLAY STATISTICS ---------- \n1. Averages...\n2. Standard Deviation...\n0. << BACK\nEnter your choice : ";
  cin >> choice;
  switch(choice) {
  case 1 : choiceType = getMenuChoice("\n ----- 2.1. Averages ----- \nBased on :\n1. Overall Average Marks\n2. Per Subject\nEnter your choice : "); calcAvg(data, choiceType, 1); break;
  case 2 : choiceType = getMenuChoice("\n ----- 2.2. Standard Deviation ----- \nBased on :\n1. Overall Average Marks\n2. Per Subject\nEnter your choice : "); calcStdD(data, choiceType, 1); break;
  default : break;
  }
}

// --- DEBUG DATA DUMP ---
void debug_displayData(vector <student> &data) {
  cout << "\n ---------- \nDATA DUMP\n ---------- \n" << endl;
  cout << "Total num of Students : " << totalStudents << " Total num of Subjects : " << totalSubj << endl;

  for (int i = 0; i < totalStudents; i++) {
    cout << left <<  setw(15) << data[i].getName() << setw(2) << " " << left << setw(4) << (float)data[i].getAverage();
    for (int ib = 0; ib < totalSubj; ib++) {
      cout << setw(subjects[ib].length() + 2) << subjects[ib] << " : " << left << setw(4) << (float)data[i].getMark((unsigned int)ib);
    }
    cout << endl;
  }
}

// ---------- PROGRAM ENTRY ----------
int main() {
  vector <student> data;
  unsigned short int menuChoice = 1;

  cout << endl << "DATA ANALYSIS PROGRAMME V1.0.0a" << endl << "Written by Py." << endl << "-------------------------------\n\n";

  while (menuChoice != 0) {
    displayMenu();
    menuChoice = getMenuChoice("Enter your choice : ");
    switch (menuChoice) {
      case 0 : cout << "/!\\ EXITING PROGRAM" << endl; break;
      case 1 : loadFile(data); break;
      case 2 : displayStats(data); break;
      case 3 : debug_displayData(data); break;
      default : break;
    }
  }

  return 0;
}
