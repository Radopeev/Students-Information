/**
*
* Solution to course project # 5
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Radoslav Peev
* @idnumber 7MI0600261
* @compiler GCC
*
* <file with helper functions>
*
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;
void addingMember(fstream &myFile, const string& group, const string& name, const string& facultyNumber){
    myFile.open(group,ios::app);
    if(myFile.is_open()){
        myFile<<"Name:"<<name<<" ";
        myFile<<"FN:"<<facultyNumber;
        myFile.close();
    }
}
void addingSubjectsAndGrades(fstream &myFile,const string& group,const string& subjects,const string& grades){
    myFile.open(group,ios::app);
    if(myFile.is_open()){
        myFile<<" "<<"Subject:"<<subjects<<" ";
        myFile<<"Grade:"<<grades;
        myFile.close();
    }
}
void removeMember(fstream &myFile,const string& group,const string& facultyNumberToRemove){
    myFile.open(group,ios::in);
    char *filename = new char[group.length() + 1];
    strcpy(filename, group.c_str());
    string line;
    fstream temp;
    temp.open("temp.txt",ios::out);
    if(myFile.is_open()) {
        while (getline(myFile, line)) {
            if(line.find(facultyNumberToRemove)==string::npos)
            {
                temp << line << endl;
            }
        }
        myFile.close();
        temp.close();
        remove(filename);
        rename("temp.txt", filename);
    }
    delete []filename;
}
void fnNumberAssignment(fstream &myFile,const string& group,vector<string> &fnNumbers){
    myFile.open(group,ios::in);
    string line;
    if(myFile.is_open()){
        while (getline (myFile,line)) {
            string facultyNumber=line.substr(line.find("FN:")+3,10);
            fnNumbers.push_back(facultyNumber);
        }
    }
    myFile.close();
}
void fnNumberSortAscending(vector<string> &fnNumbers){
    for(int i=0;i<fnNumbers.size()-1;i++){
        for(int j=0;j<fnNumbers.size()-i-1;j++) {
            if (fnNumbers[j] > fnNumbers[j+ 1]) {
                string temp;
                temp = fnNumbers[j];
                fnNumbers[j] = fnNumbers[j + 1];
                fnNumbers[j+1] = temp;
            }
        }
    }
}
void fnNumberSortDescending(vector<string> &fnNumbers){
    for(int i=0;i<fnNumbers.size()-1;i++){
        for(int j=0;j<fnNumbers.size()-i-1;j++) {
            if (fnNumbers[j] < fnNumbers[j+ 1]) {
                string temp;
                temp = fnNumbers[j];
                fnNumbers[j] = fnNumbers[j + 1];
                fnNumbers[j+1] = temp;
            }
        }
    }
}
void sortingByFacultyNumber(fstream &myFile,const string& group,int order) {
    char *filename = new char[group.length() + 1];
    strcpy(filename, group.c_str());\
    string line,lineForPrint;
    fstream temp;
    vector<string> fnNumbers;
    fnNumberAssignment(myFile,group,fnNumbers);
    temp.open("temp",ios::out);
    if(order==1){
        fnNumberSortAscending(fnNumbers);
    }
    else if(order==2){
        fnNumberSortDescending(fnNumbers);
    }
    for(auto & fnNumber : fnNumbers){
        myFile.open(group,ios::in);
        if(myFile.is_open()) {
            while (getline(myFile, line)) {
                if (line.find(fnNumber) != string::npos) {
                    temp << line << endl;
                }
            }
            myFile.close();
        }
    }
    temp.close();
    remove(filename);
    rename("temp", filename);
    myFile.open(filename, ios::in);
    if(myFile.is_open()) {
        while (getline(myFile, lineForPrint)) {
            cout << lineForPrint << endl;
        }
        myFile.close();
    }
    cout<<endl;
    delete []filename;
}
double averageScore(string line){
    double avgScore=0,grades=0;
    while (!line.empty()) {
        string line1 = line.substr(line.find("Grade:") + 6, 4);
        avgScore+= stod(line1);
        line = line.substr(line.find(line1) + 4, line.length());
        grades++;
    }
    avgScore= avgScore/grades;
    return ceil(avgScore * 100.0) / 100.0;
}
void avgScoresAssignment(fstream &myFile,const string& group,vector<double> &avgScores){
    myFile.open(group,ios::in);
    string line;
    if(myFile.is_open()){
        while (getline (myFile,line)) {
            double avgScore=averageScore(line);
            avgScores.push_back(avgScore);
        }
    }
    myFile.close();
}
void avgScoresSortAscending(vector<double> &avgScores){
    for(int i=0;i<avgScores.size()-1;i++){
        for(int j=0;j<avgScores.size()-i-1;j++) {
            if (avgScores[j] > avgScores[j+ 1]) {
                double temp;
                temp = avgScores[j];
                avgScores[j] = avgScores[j + 1];
                avgScores[j+1] = temp;
            }
        }
    }
}
void avgScoresSortDescending(vector<double> &avgScores){
    for(int i=0;i<avgScores.size()-1;i++){
        for(int j=0;j<avgScores.size()-i-1;j++) {
            if (avgScores[j] < avgScores[j+ 1]) {
                double temp;
                temp = avgScores[j];
                avgScores[j] = avgScores[j + 1];
                avgScores[j+1] = temp;
            }
        }
    }
}
void sortingByAverageScore(fstream &myFile,const string& group,int order) {
    char *filename = new char[group.length() + 1];
    strcpy(filename, group.c_str());
    string line,lineForPrint;
    fstream temp;
    vector<double> avgScores;
    avgScoresAssignment(myFile,group,avgScores);
    temp.open("temp",ios::out);
    if(order==1){
        avgScoresSortAscending(avgScores);
    }
    else if(order==2){
        avgScoresSortDescending(avgScores);
    }
    for(double i : avgScores){
        myFile.open(group,ios::in);
        if(myFile.is_open()) {
            while (getline(myFile, line)) {
                double avgScore= averageScore(line);
                if (i==avgScore) {
                    temp << line << endl;
                }
            }
            myFile.close();
        }
    }
    temp.close();
    remove(filename);
    rename("temp", filename);
    myFile.open(filename, ios::in);
    if(myFile.is_open()) {
        while (getline(myFile, lineForPrint)) {
            cout << lineForPrint << endl;
        }
        myFile.close();
    }
    cout<<endl;
    delete []filename;
}
void mergedGroup(fstream &mergedGroups,vector<string> groups,int n){
    mergedGroups.open("MergedGroups",ios::app);
    string line;
    while(n>=0){
        fstream temp;
        temp.open(groups[n],ios::in);
        if(temp.is_open()) {
            while (getline(temp, line)) {
                mergedGroups << line << endl;
            }
        }
        temp.close();
        n--;
    }
    mergedGroups.close();
}
void avgScoresAssignmentForMergedGroups(fstream &mergedGroups,vector<double> &avgScores){
    mergedGroups.open("MergedGroups",ios::in);
    string line;
    if(mergedGroups.is_open()){
        while (getline (mergedGroups,line)) {
            double avgScore=averageScore(line);
            avgScores.push_back(avgScore);
        }
    }
    mergedGroups.close();
}
void sortByAverageScoreAndVisualize(fstream &mergedGroups,int order){
    string line,lineForPrint;
    fstream temp;
    vector<double> avgScores;
    avgScoresAssignmentForMergedGroups(mergedGroups,avgScores);
    temp.open("temp",ios::out);
    if(order==1){
        avgScoresSortAscending(avgScores);
    }
    else if(order==2){
        avgScoresSortDescending(avgScores);
    }
    for(double i : avgScores){
        mergedGroups.open("MergedGroups",ios::in);
        if(mergedGroups.is_open()) {
            while (getline(mergedGroups, line)) {
                double avgScore= averageScore(line);
                if (i==avgScore) {
                    temp << line << endl;
                }
            }
            mergedGroups.close();
        }
    }
    temp.close();
    remove("MergedGroups");
    rename("temp", "MergedGroups");
    mergedGroups.open("MergedGroups", ios::in);
    if(mergedGroups.is_open())
    {
        while (getline(mergedGroups, lineForPrint)) {
            cout << lineForPrint << endl;
        }
        mergedGroups.close();
    }
    cout<<endl;
}
void fnNumbersAssignmentForMergedGroups(fstream &mergedGroups,vector<string> &fnNumbers){
    mergedGroups.open("MergedGroups",ios::in);
    string line;
    if(mergedGroups.is_open()) {
        while (getline(mergedGroups, line)) {
            string facultyNumber = line.substr(line.find("FN:") + 3, 10);
            fnNumbers.push_back(facultyNumber);
        }
        mergedGroups.close();
    }
}
void sortByFacultyNumberAndVisualize(fstream &mergedGroups,int order){
    string line,lineForPrint;
    fstream temp;
    vector<string> fnNumbers;
    fnNumbersAssignmentForMergedGroups(mergedGroups,fnNumbers);
    temp.open("temp",ios::out);
    if(order==1){
        fnNumberSortAscending(fnNumbers);
    }
    else if(order==2){
        fnNumberSortDescending(fnNumbers);
    }
    for(auto & fnNumber : fnNumbers){
        mergedGroups.open("MergedGroups",ios::in);
        if(mergedGroups.is_open()) {
            while (getline(mergedGroups, line)) {
                if (line.find(fnNumber) != string::npos) {
                    temp << line << endl;
                }
            }
            mergedGroups.close();
        }
    }
    temp.close();
    remove("MergedGroups");
    rename("temp", "MergedGroups");
    mergedGroups.open("MergedGroups", ios::in);
    if(mergedGroups.is_open()) {
        while (getline(mergedGroups, lineForPrint)) {
            cout << lineForPrint << endl;
        }
        mergedGroups.close();
    }
    cout<<endl;
}
bool facultyNumberValidator(string facultyNumber){
    bool isFirstNumberDigit,isThereMIinIt,AreThereOnlyDigits;
    if(isdigit(facultyNumber[0])){
        isFirstNumberDigit= true;
    }
    if(facultyNumber.find("MI")==1){
        isThereMIinIt= true;
    }
    for(int i=3;i<10;i++){
        if(isdigit(facultyNumber[i])){
            AreThereOnlyDigits= true;
        }else {
            AreThereOnlyDigits= false;
        }
    }
    if(isFirstNumberDigit && isThereMIinIt && AreThereOnlyDigits){
        return true;
    }else {
        return false;
    }
}
bool gradesValidator(string grades){
    if(isdigit(grades[0])== true && grades[1]=='.' && isdigit(grades[2])== true && isdigit(grades[3])== true){
        return true;
    }
    else {
        return false;
    }
}
int main() {
    int options=0,countOfSubjects=0;
    double numOfDisciplines;
    string group;
    string maxGroupNum="8";
    string name,facultyNumber,subjects,grades;
    while(options<=4){
        cout<<"Available operations:\n1)Add new student\n2)Remove student\n3)Sort the students\n4)Print the information of more than one group\n5)Exit\n";
        cin>>options;
        if(options==1){
            fstream myFile;
            cout<<"In which group you want to include new student(1-8)\n"<<flush;
            cin>>group;
            if(!isdigit(group[0]) || (stoi(group)<1 || stoi(group)>8)){
                cout<<"You entered incorrect input! Please try again.\n";
                cout<<endl;
                continue;
            }
            cin.ignore();
            cout<<"Name:";
            getline(cin,name);
            cout<<"Faculty Number(*MI*******):";
            cin>>facultyNumber;
            if(facultyNumber.length()>10){
                cout<<"You entered incorrect input! Please try again.\n";
                cout<<endl;
                continue;
            }
            if(!facultyNumberValidator(facultyNumber)){
                cout<<"You entered incorrect input! Please try again.\n";
                cout<<endl;
                continue;
            }
            cin.ignore();
            cout<<"Number of disciplines you would like to add(1-10):";
            cin>>numOfDisciplines;
            if(numOfDisciplines>10){
                cout<<"You entered incorrect input!Please try again.\n";
                cout<<endl;
                continue;
            }
            addingMember(myFile,group,name,facultyNumber);
            cout<<"Enter your subjects and grades(2-6):\n";
            while(countOfSubjects<numOfDisciplines){
                cin>>subjects;
                cin>>grades;
                bool valid= gradesValidator(grades);
                double grade=stod(grades);
                if(grades.length()!=4 || !valid || (grade<2.00 || grade>6.00)){
                    cout<<"You entered incorrect input!Тhe grades need to be in the format *.**(*-number). Please try again.\n";
                    cout<<endl;
                    continue;
                }
                countOfSubjects++;
                addingSubjectsAndGrades(myFile,group,subjects,grades);
            }
            countOfSubjects=0;
            myFile.open(group,ios::app);
            myFile<<endl;
            myFile.close();
        }
        else if(options==2) {
            string facultyNumberToRemove;
            cout << "From which group is the student you want to remove\n";
            cin >> group;
            if(!isdigit(group[0]) || (stoi(group)<1 || stoi(group)>8)){
                cout<<"You entered incorrect input! Please try again!\n";
                cout<<endl;
                continue;
            }
            cout << "Which student would you like to remove(by FN):\n";
            cin >> facultyNumberToRemove;
            if(!facultyNumberValidator(facultyNumberToRemove)){
                cout<<"You entered incorrect input! Please try again\n";
                cout<<endl;
                continue;
            }
            fstream myFile;
            removeMember(myFile,group,facultyNumberToRemove);
        }
        else if(options==3){
            int order,sortingMethod;
            cout<<"Which group would would you like to sort\n";
            cin>>group;
            if(!isdigit(group[0]) || (stoi(group)<1 || stoi(group)>8)){
                cout<<"You entered incorrect input! Please try again!\n";
                cout<<endl;
                continue;
            }
            cout<<"In what order would you like to be sorted(Ascending[1] | Descending[2])\n";
            cin>>order;
            if(order>2){
                cout<<"You entered incorrect input! Please try again!\n";
                cout<<endl;
                continue;
            }
            cout<<"How would you like to sort(Average score[1] | Faculty number[2])\n";
            cin>>sortingMethod;
            if(sortingMethod>2){
                cout<<"You entered incorrect input! Please try again!\n";
                cout<<endl;
                continue;
            }
            if(sortingMethod==1){
                fstream myFile;
                sortingByAverageScore(myFile,group,order);
            }
            else if(sortingMethod==2){
                fstream myFile;
                sortingByFacultyNumber(myFile,group,order);
            }
        }
        else if(options==4){
            int sortingMethod,numOfGroups,n=0,order;
            string g;
            vector<string> groups;
            cout<<"How many groups would you like to visualize(1-8):\n";
            cin>>numOfGroups;
            if(numOfDisciplines>8){
                cout<<"You entered incorrect input! Please try again!\n";
                cout<<endl;
                continue;
            }
            while(n<numOfGroups){
                cout<<"Enter group:\n";
                cin>>g;
                if(!isdigit(g[0]) || (stoi(g)<1 || stoi(g)>8)){
                    cout<<"You entered incorrect input! Please try again!\n";
                    cout<<endl;
                    continue;
                }
                groups.push_back(g);
                n++;
                g.pop_back();
            }
            cout<<"In what order would you like to sort them(Ascending[1] or Descending[2]):\n";
            cin>>order;
            if(order>2){
                cout<<"You entered incorrect input! Please try again!\n";
                cout<<endl;
                continue;
            }
            cout<<"How would you like to sort and visualize them(AverageScore[1] or Faculty Number[2]):\n";
            cin>>sortingMethod;
            if(sortingMethod>2){
                cout<<"You entered incorrect input! Please try again!\n";
                cout<<endl;
                continue;
            }
            if(sortingMethod==1){
                fstream myFile,mergedGroups;
                mergedGroup(mergedGroups,groups,numOfGroups-1);
                sortByAverageScoreAndVisualize(mergedGroups,order);
            }
            else if(sortingMethod==2){
                fstream mergedGroups;
                mergedGroup(mergedGroups,groups,numOfGroups-1);
                sortByFacultyNumberAndVisualize(mergedGroups,order);
            }
        }
    }
    return 0;
}
