#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;
const int Cols = 20;
const int Rows = 50;

ofstream fout("sortedByStudentIDs.txt");
ofstream fout2("sortedByTotalPoints.txt");
void initialize(int a[Rows][Cols], const string& filename);
void SortByTotalPoints(int a[Rows][Cols]);
void SortByStudentID(int a[Rows][Cols]);
void swapRow(int a[Rows][Cols], int Row1, int Row2);
string gradeLetter(int Percentage);
int totalPercentage(int a[Rows][Cols], int targetRow);
int totalAssignments(int a[Rows][Cols], int targetRow);
int totalPoints(int a[Rows][Cols], int targetRow);
void printHeader(void);
void printInputData(int a[Rows][Cols]);
void printinTotalPoints(int a[Rows][Cols]);


int main() {
    ifstream infile("input.txt");
    ofstream fout("sortedByStudentIDs.txt");
    ofstream fout2("sortedByTotalPoints.txt");
    if (infile.is_open() && fout.is_open() && fout2.is_open()){
        printHeader();
        int a[Rows][Cols];
        initialize(a, "input.txt");
     infile.close();
    }
    else {
        cout << "Error in opening file";
    }
   
    return 0;

}

void initialize(int a[Rows][Cols], const string& filename){
        ifstream infile(filename);
        int StudentID, Ex, Assign1, Assign2, Assign3, Assign4, Assign5, Assign6, Assign7, Assign8;
        int Assign9, Assign10, Assign11, Total, Midterm, Final, Codelab, Points, Percentage;
        int currRow = 0;
        while(infile >> StudentID >> Ex >> Assign1 >> Assign2 >> Assign3 >> Assign4 >>
        Assign5 >> Assign6 >> Assign7 >> Assign8 >> Assign9 >> Assign10 >> Assign11 >> 
        Midterm >> Final >> Codelab){
            a[currRow][0] = StudentID;
            a[currRow][1] = Ex;
            a[currRow][2] = Assign1;
            a[currRow][3] = Assign2;
            a[currRow][4] = Assign3;
            a[currRow][5] = Assign4;
            a[currRow][6] = Assign5;
            a[currRow][7] = Assign6;
            a[currRow][8] = Assign7;
            a[currRow][9] = Assign8;
            a[currRow][10] = Assign9;
            a[currRow][11] = Assign10;
            a[currRow][12] = Assign11;
            Total = totalAssignments(a, currRow);
            a[currRow][13] = Total;
            a[currRow][14] = Midterm;
            a[currRow][15] = Final;
            a[currRow][16] = Codelab;
            Points = totalPoints(a, currRow);
            a[currRow][17] = Points;
            Percentage = totalPercentage(a, currRow);
            a[currRow][18] = Percentage;
            ++currRow;
        }
        SortByStudentID(a);
        printInputData(a);
        SortByTotalPoints(a);
        printinTotalPoints(a);
}

void SortByTotalPoints(int a[Rows][Cols]){
    for(int i = 0; i < Rows - 1 ; i++)
        for(int j = 0; j < Rows - i - 1; j++){
            if(a[j][17] < a[j+1][17])
                swapRow(a, j, j+1);
        }
}

void SortByStudentID(int a[Rows][Cols]){
    for(int i =0; i < Rows -1; i++)
        for(int j=0; j < Rows - i - 1; j++){
            if(a[j][0] > a[j+1][0])
                swapRow(a, j, j+1);
        }
}

void swapRow(int a[Rows][Cols], int Row1, int Row2){
    int temp[Cols];
    for(int i = 0; i < Cols; ++i) {
        temp[i] = a[Row1][i];
        a[Row1][i] = a[Row2][i];
        a[Row2][i] = temp[i];
    }
}

string gradeLetter(int Percentage){
    string Grade = " ";
    if(Percentage >= 98) {
        Grade = "A+";
    } else if(Percentage >= 92){
        Grade = "A ";
    } else if(Percentage >= 90){
        Grade = "A-";
    } else if(Percentage >= 88){
        Grade = "B+";
    } else if(Percentage >= 82){
        Grade = "B ";
    } else if(Percentage >= 80){
        Grade = "B-";
    } else if(Percentage >= 78){
        Grade = "C+";
    } else if(Percentage >= 72){
        Grade = "C ";
    } else if(Percentage >= 70){
        Grade = "C-";
    } else if(Percentage >= 68){
        Grade = "D+";
    } else if(Percentage >= 62){
        Grade = "D ";
    } else if(Percentage >= 60){
        Grade = "D-";
    } else {
        Grade = "F ";
    }

    return Grade;

}

int totalPercentage(int a[Rows][Cols], int targetRow){
       int Percentage = (int)round((double(a[targetRow][17]) / 500) * 100);
    
    return Percentage;
}

int totalPoints(int a[Rows][Cols], int targetRow){
    int targetIndices[5]={1,13,14,15,16};
    int Points = 0;
    for(int j = 0; j < 5; ++j)
         Points += a[targetRow][targetIndices[j]];
    
    return Points;
}

int totalAssignments(int a[Rows][Cols], int targetRow){
    int Total = 0;
    int indexLowest = 2;
    for(int i = 3; i <= 12; ++i)
        if(a[targetRow][indexLowest] > a[targetRow][i])
            indexLowest = i;
    for(int i = 2; i <=12; ++i)
        if(i != indexLowest)
            Total += a[targetRow][i];
    
    return Total;

}

void printHeader(void){
    cout << "\n" << string(29,'=') << "SORTED BY STUDENT ID" << string(29,'=') << "\n\n";
    cout << setw(10) << left << "Stdnt ID" <<  setw(4) << left << "Ex";
    cout << setw(10) << left << "---------" << left << "Assignments ";
    cout << setw(11) << left << "----------" << setw(5) << left << "Tot"; 
    cout << setw(4) << left << "Mi" << setw(5) << left << "Fin";
    cout << setw(4) << left << "CL" << setw(5) << left << "Pts";
    cout << setw(5) << left << "Pct" << left << "Gr" << endl;
    cout << setw(10) << left << "--------" << setw(4) << left << "--";
    cout << setw(10) << left << "--------------------------------";
    cout << setw(5) << left << " ---" << setw(5) << left << " --";
    cout << setw(5) << left << "---" << setw(4) << left << "--";
    cout << setw(5) << left << "---" << setw(5) << left << "---" << setw(5) << left << "--" << endl;
}

void printInputData(int a[Rows][Cols]){
    for (int i = 0; i < Rows; ++i) {
        cout << internal << setfill('0') << setw(8) << a[i][0] << right << setfill(' ') << setw(4) << a[i][1];
        cout << internal << right << setw(4) << a[i][2] << right << setw(3) << a[i][3];
        cout << internal << right << setw(3) << a[i][4] << right << setw(3) << a[i][5];
        cout << internal << right << setw(3) << a[i][6] << right << setw(3) << a[i][7];
        cout << internal << right << setw(3) << a[i][8] << right << setw(3) << a[i][9];
        cout << internal << right << setw(3) << a[i][10] << right << setw(3) << a[i][11];
        cout << internal << right << setw(3) << a[i][12] << right << setw(4) << a[i][13];
        cout << right << setw(4) << a[i][14];
        cout << internal << right << setw(5) << a[i][15] << right << setw(4) << a[i][16];
        cout << internal << right << setw(5) << a[i][17] << right << setw(5) << a[i][18];
        cout << internal << right << setw(4) << gradeLetter(a[i][18]) << '\n';


       fout << internal << setfill('0') << setw(8) << a[i][0] << right << setfill(' ') << setw(4) << a[i][1];
       fout << internal << right << setw(4) << a[i][2] << right << setw(3) << a[i][3];
       fout << internal << right << setw(3) << a[i][4] << right << setw(3) << a[i][5];
       fout << internal << right << setw(3) << a[i][6] << right << setw(3) << a[i][7];
       fout << internal << right << setw(3) << a[i][8] << right << setw(3) << a[i][9];
       fout << internal << right << setw(3) << a[i][10] << right << setw(3) << a[i][11];
       fout << internal << right << setw(3) << a[i][12] << right << setw(4) << a[i][13];
       fout << right << setw(4) << a[i][14];
       fout << internal << right << setw(5) << a[i][15] << right << setw(4) << a[i][16];
       fout << internal << right << setw(5) << a[i][17] << right << setw(5) << a[i][18];
       fout << internal << right << setw(4) << gradeLetter(a[i][18]) << '\n';
    }
    cout << endl;
    cout << "\n" << string(28,'=') << "SORTED BY TOTAL POINTS" << string(28,'=') << "\n\n";
}

void printinTotalPoints(int a[Rows][Cols]){
    for (int i = 0; i < Rows; ++i) {
        cout << internal << setfill('0') << setw(8) << a[i][0] << right << setfill(' ') << setw(4) << a[i][1];
        cout << internal << right << setw(4) << a[i][2] << right << setw(3) << a[i][3];
        cout << internal << right << setw(3) << a[i][4] << right << setw(3) << a[i][5];
        cout << internal << right << setw(3) << a[i][6] << right << setw(3) << a[i][7];
        cout << internal << right << setw(3) << a[i][8] << right << setw(3) << a[i][9];
        cout << internal << right << setw(3) << a[i][10] << right << setw(3) << a[i][11];
        cout << internal << right << setw(3) << a[i][12] << right << setw(4) << a[i][13];
        cout << right << setw(4) << a[i][14];
        cout << internal << right << setw(5) << a[i][15] << right << setw(4) << a[i][16];
        cout << internal << right << setw(5) << a[i][17] << right << setw(5) << a[i][18];
        cout << internal << right << setw(4) << gradeLetter(a[i][18]) << '\n';

        fout2 << internal << setfill('0') << setw(8) << a[i][0] << right << setfill(' ') << setw(4) << a[i][1];
        fout2 << internal << right << setw(4) << a[i][2] << right << setw(3) << a[i][3];
        fout2 << internal << right << setw(3) << a[i][4] << right << setw(3) << a[i][5];
        fout2 << internal << right << setw(3) << a[i][6] << right << setw(3) << a[i][7];
        fout2 << internal << right << setw(3) << a[i][8] << right << setw(3) << a[i][9];
        fout2 << internal << right << setw(3) << a[i][10] << right << setw(3) << a[i][11];
        fout2 << internal << right << setw(3) << a[i][12] << right << setw(4) << a[i][13];
        fout2 << right << setw(4) << a[i][14];
        fout2 << internal << right << setw(5) << a[i][15] << right << setw(4) << a[i][16];
        fout2 << internal << right << setw(5) << a[i][17] << right << setw(5) << a[i][18];
        fout2 << internal << right << setw(4) << gradeLetter(a[i][18]) << '\n';
    }
}
