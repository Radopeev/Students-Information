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
    while(getline(myFile,lineForPrint)){
        cout<<lineForPrint<<endl;
    }
    cout<<endl;
    delete []filename;
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
            if(group>"8"){
                cout<<"You entered incorrect input! Please try again!\n";
                continue;
            }
            cin.ignore();
            cout<<"Name:";
            getline(cin,name);
            cout<<"Faculty Number:";
            cin>>facultyNumber;
            cin.ignore();
            cout<<"Number of disciplines you would like to add(1-10):";
            cin>>numOfDisciplines;
            if(numOfDisciplines>10){
                cout<<"You entered incorrect input!Please try again\n";
                continue;
            }
            addingMember(myFile,group,name,facultyNumber);
            while(countOfSubjects<numOfDisciplines){
                cin>>subjects;
                cin>>grades;
                if(grades.length()!=4){
                    cout<<"You entered incorrect input! Please try again.\n";
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
            if(group>"8"){
                cout<<"You entered incorrect input! Please try again!\n";
                continue;
            }
            cout << "Which student would you like to remove(by FN):\n";
            cin >> facultyNumberToRemove;
            fstream myFile;
            removeMember(myFile,group,facultyNumberToRemove);
        }
        else if(options==3){
            int order,sortingMethod;
            cout<<"Which group would would you like to sort\n";
            cin>>group;
            if(group>"8"){
                cout<<"You entered incorrect input! Please try again!\n";
                continue;
            }
            cout<<"In what order would you like to be sorted(Ascending[1] | Descending[2])\n";
            cin>>order;
            if(order>2){
                cout<<"You entered incorrect input! Please try again!\n";
                continue;
            }
            cout<<"How would you like to sort(Average score[1] | Faculty number[2])\n";
            cin>>sortingMethod;
            if(sortingMethod>2){
                cout<<"You entered incorrect input! Please try again!\n";
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
                continue;
            }
            while(n<numOfGroups){
                cout<<"Enter group:\n";
                cin>>g;
                if(g>"8"){
                    cout<<"You entered incorrect input! Please try again!\n";
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
                continue;
            }
            cout<<"How would you like to sort and visualize them(AverageScore[1] or Faculty Number[2]):\n";
            cin>>sortingMethod;
            if(sortingMethod>2){
                cout<<"You entered incorrect input! Please try again!\n";
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