#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cmath>
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