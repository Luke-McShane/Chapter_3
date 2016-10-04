// Accelerated CPP - Chapter 3 Exercises.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <ios>
#include <string>
#include <vector>
#include <algorithm>
#include <map>;
using namespace std;
void userGrade();
void quartiles();
void countWords();
void multipleStudents();

int main() {
	//userGrade();
	//quartiles();
	//countWords();
	multipleStudents();
	return 0;
}

void userGrade() {

	//ask for and read student's name
	cout << "Please enter your first name: ";
	string name;
	cin >> name;
	cout << "Hello, " << name << "!" << endl;

	//ask for and read the midterm and final grades
	cout << "Please enter your midterm and final exam grades: ";
	double midterm, finalGrade;
	cin >> midterm >> finalGrade;

	//ask for and read the homework grades
	cout << "Enter all of your homework grades, "
		"followed by end-of-file: ";

	vector<double> homework;
	double x;
	//invariant: homework contains all the homework grades read so far
	while (cin >> x)
		homework.push_back(x);

	//check that the student entered some homework grades
	typedef vector<double>::size_type vec_sz;
	vec_sz size = homework.size();
	if (size == 0) {
		cout << endl << "You must enter your grades. "
			"Please try again." << endl;
		return;
	}

	//sort the grades
	sort(homework.begin(), homework.end());

	//compute the median homework grade
	vec_sz mid = size / 2;
	double median;
	median = size % 2 == 0 ? (homework[mid] + homework[mid - 1]) / 2
		: homework[mid];

	//compute and write the final grade
	//Here we find out the standard floating-point precision the standard output uses. We find this out so we can reset the precision
	//after we alter it to 3.
	streamsize prec = cout.precision();
	cout << "Your final grade is " << setprecision(3) << 0.2 * midterm + 0.4 * finalGrade + 0.4 * median
		<< setprecision(prec) << endl;
	return;
}

/*3.1
If we have a data set '1, 3, 5, 7, 9', the current median is 5. If we discard the 5, and continue reading
values, of which are '2, 3, 6, 8, 10', then we distort the median as we move from a data set that would have
been '1, 2, 3, 4, 5, 6, 7, 8, 9, 10' to '1, 2, 3, 4, 6, 7, 8, 9', meaning the median shifts from the true
mediagn (5.5), to a distorted median (5).
*/

//3.2
void quartiles() {
	cout << "Please enter at least 4 numbers, separated by a \" \" and ending with an end-of-file: ";
	typedef vector<double>::size_type vec_size;
	vector<double> myVector;
	double x;
	while (cin >> x)
		myVector.push_back(x);
	vec_size size = myVector.size();

	if (size == 0) {
		cout << "Please enter some values.." << endl;
		return;
	}
	else if (size == 1) {
		cout << "All quartiles equate to the input.." << endl;
		return;
	}


	sort(myVector.begin(), myVector.end());
	//If the data set's length is odd, then when dividing to find the mid & lower, the compiler will truncate the result.
	//Therefore, if we have data set '1, 2, 3, 4, 5', then the lower quartile value will be 1 and the middle will be 2.
	//Since 5/2 = 2.5, the '0.5' is discarded so we are left with 2.

	vec_size M, ML, MU;
	double m, ml, mu;
	string dataDistribution = "";

	vec_size pattern = size % 4;
	/* The data distribution signifies whether the lower quartile, median and upper quartile are included in the data set or not.
	0 indicates that the value lies between two numbers, 1 indicates that the value is within the data set.
	For example, if we have a data set of length 9, then the pattern is 1 because the remainder of 9/4 is 1. This indicates a pattern
	of 0 1 0 because the median is 5, whereas the lower quartile is 2.5 and the upper quartile is 7.5
	Another example would be if the had a data set of length 4. The data distribution would be 0 0 0 since the median would lie between
	the second and third values, the lower quartile would lie between the first and second values, and the upper quartile would lie
	between the third and fourth numbers.*/ 
	if (pattern == 0) {
		dataDistribution = "[0 0 0]";
		M = size / 2;
		ML = M / 2;
		MU = M + ML;

		m = (myVector[M] + myVector[M - 1]) / 2;
		ml = (myVector[ML] + myVector[ML - 1]) / 2;
		mu = (myVector[MU] + myVector[MU - 1]) / 2;
	}

	else if (pattern == 1) {
		dataDistribution = "[0 1 0]";
		M = size / 2;
		ML = M / 2;
		MU = M + ML + 1;

		m = myVector[M];
		ml = (myVector[ML] + myVector[ML - 1]) / 2;
		mu = (myVector[MU] + myVector[MU - 1]) / 2;
	}

	else if (pattern == 2) {
		dataDistribution = "[1 0 1]";
		M = size / 2;
		ML = M / 2;
		MU = M + ML;

		m = (myVector[M] + myVector[M-1]) / 2;
		ml = myVector[ML];
		mu = myVector[MU];
	}

	else if (pattern == 3) {
		dataDistribution = "[1 1 1]";
		M = size / 2;
		ML = M / 2;
		MU = M + ML + 1;

		m = (myVector[M] + myVector[M - 1]) / 2;
		ml = myVector[ML];
		mu = myVector[MU];
	}

	/*int mid = size / 2;
	int lower = mid / 2;
	int upper = mid + lower;
	//cout << lower << " " << mid << " " << upper << endl;
	double lowerQuartile = size % 2 == 0 ? (myVector[lower] + myVector[lower - 1]) / 2
		: (myVector[lower]);
	double upperQuartile = size % 2 == 0 ? (myVector[upper] + myVector[upper - 1]) / 2
		: (myVector[upper]);
	double median = size % 2 == 0 ? (myVector[mid] + myVector[mid - 1]) / 2
		: (myVector[mid]);

	cout << "Lower Quartile: " << lowerQuartile << endl
		<< "Median: " << median << endl
		<< "Upper Quartile: " << upperQuartile << endl;
		*/
	cout << "The ordered data set is as follows: " << flush;
	for (int i = 0; i < size; i++)
		cout << myVector[i] << " " << flush;
	cout << endl;
	cout << "Data distibution: " << dataDistribution << endl << "Lower Quartile: " << ml << endl
			<< "Median: " << m << endl << "Upper Quartile: " << mu << endl;
	
	return;
}

//3.3
void countWords(){
	typedef map<string, int> wordMap;
	//Here we create a variable myMap with type map<string, int>
	//Think of this as a dictionary, where the 'string' is the key that holds a value 'int'.
	wordMap myMap;
	string currentVal;
	//This means that until there is an invalid input or an EOF, the input stream will continue reading into currentVal
	while (cin >> currentVal) {
		//This tries to find the key currentVal in the map, if the returned value is the end of the map, then this key is not present.
		if (myMap.find(currentVal) == myMap.end()) 
			//Here we insert a pair (a key then a value) into the map with correct data types in the pair.
			myMap.insert(pair<string, int>(currentVal, 1));
		else //If we find the key, we increase it's value by 1.
			myMap[currentVal] += 1;
	}
	//it is simply an iterator that points to a position in the map. We can dereference the value(s) the iterator points to by using ->
	//as we would for any pointer. Because the pointer points to a pair, we can use 'first' and 'second' to dereference the pointer and access the values.
	for (wordMap::iterator it = myMap.begin(); it != myMap.end(); it++)
		cout << "Name: " << it->first << endl << "Occurences: " << it->second << endl << endl;

	//3.4
	int sStringLen = 0;
	int lStringLen = 0;
	string sString = "";
	string lString = "";
	for (wordMap::iterator it = myMap.begin(); it != myMap.end(); it++) {
		//Here we check if this is the first item being checked of if it is a new shortest item.
		if ((sStringLen == 0) || (it->first.length() < sStringLen)) {
			//If so, we reset the sString value and append the new value, and also change the length to the new shortest length so we can compare values to it in future iterations
			sString = "";
			sStringLen = it->first.length();
			sString.append(it->first);
		}
		//If however, we come across a value of the same length, we simply append it to the sString string. 
		else if (it->first.length() == sStringLen) {
			sString.append(" " + it->first);
		}
		if (lStringLen == 0 || it->first.length() > lStringLen) {
			lString = "";
			lStringLen = it->first.length();
			lString.append(it->first);
		}
		else if (it->first.length() == lStringLen) {
			lString.append(" " + it->first);
		}
	}
	cout << "Shortest Name: " << sString << endl << "Longest Name: " << lString << endl;
}

void multipleStudents() {
	const int H_GRADES = 5;
	vector<string> students;
	vector<double> meanGrades;
	double currentGrade;
	string currentStudent;

	cout << "Please enter the name of the current student, or type EOF (uppercase 'Z' and 'Enter') to exit the program: " << flush;
	while (cin >> currentStudent) {
		int totalGrade = 0;
		students.push_back(currentStudent);
		cout << "Please enter the students grades: " << flush;
		for (int i = 0; i < H_GRADES; i++) {
			cin >> currentGrade;
			totalGrade += currentGrade;
		}
		meanGrades.push_back(totalGrade / H_GRADES);
		totalGrade = 0;
		cout << "\nPlease enter the next student's name: " << flush;
	}
	for (int i = 0; i < students.size(); i++)
		cout << "Name: " << students[i] << endl << "Average Grade: " << meanGrades[i] << endl << endl;
}