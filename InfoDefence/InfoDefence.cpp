// InfoDefence.cpp : Defines the entry point for the console application.
//
#pragma once
#include "stdafx.h"
#include <vector>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <algorithm>
#include <windows.h>

using namespace std;

string toLower(string s) {
	std::transform(s.begin(), s.end(), s.begin(),
		[](unsigned char c) { return tolower(c); }
	);
	return s;
}
template<class c>
bool contains(const c str, char key)
{
	for (int i = 0; i < string(str).length();i++) {
		if (str[i] == key)
		{
			return true;
		}
	}
	return false;
}

template<class s>
vector<string> deleteChar(vector<string> str, const s key)
{
	vector<string> result = str;
	 
	for (int i = 0; i < result.size(); i++) {
		if (result.at(i) == string(key))
		{
			result.erase(result.begin() +i);
		}
	}
	return result;
}
int findIndex(vector<string> vec, string elem) {
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec.at(i) == elem) { return i; }
	}
	return -1;
}
bool checkKeyWord(string keyword) {
	if (keyword.length() > 33) { return false; }
	string check = "";
	for (auto c : keyword) {
		if (contains(check, c)) {
			return false;
		}
		check += c;

	}
	return true;
}
string MakeEncryption(string text, string keyword, int key) {
//	vector<string> pureAlpha = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z" };
//	vector<string> alpha = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z" };
//	vector<string> newAlpha = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z" };
	vector<string> pureAlpha = { "א", "ב", "ג", "ד", "ה", "ו", "¸", "ז", "ח", "ט", "י", "ך", "כ", "ל", "ם", "מ", "ן", "נ", "ס", "ע", "ף", "פ", "ץ", "צ", "ק", "ר","ש","ת","û","ü","‎","‏","ÿ"};
	vector<string> alpha = { "א", "ב", "ג", "ד", "ה", "ו", "¸", "ז", "ח", "ט", "י", "ך", "כ", "ל", "ם", "מ", "ן", "נ", "ס", "ע", "ף", "פ", "ץ", "צ", "ק", "ר","ש","ת","û","ü","‎","‏","ÿ" };
	vector<string> newAlpha = { "א", "ב", "ג", "ד", "ה", "ו", "¸", "ז", "ח", "ט", "י", "ך", "כ", "ל", "ם", "מ", "ן", "נ", "ס", "ע", "ף", "פ", "ץ", "צ", "ק", "ר","ש","ת","û","ü","‎","‏","ÿ" };
	string result = "";

	for (int i = 0; i < keyword.length(); i++) {
		newAlpha[(i+key)%33] = keyword[i];
		alpha = deleteChar(alpha, newAlpha[(i+key)%33]);
	}
	for (int i = keyword.length()+key; i%33 != key ; i++) {
		sort(alpha.begin(), alpha.end());
		newAlpha[i%33] = alpha[0];
		alpha = deleteChar(alpha, alpha[0]);

	}
	for (int i = 0; i < text.length(); i++) {
		if (contains("אבגדהו¸זחטיךכלםמןנסעףפץצקרשתûü‎‏ÿ", text[i])) {
			result += newAlpha.at(findIndex(pureAlpha, { text[i] }));
		}
		else { result += text[i]; }

	}
	return result;
}
string readFromFile(string filename) {
	string text = "";
	string line;

	ifstream in(filename);
	if (in.is_open())
	{
		while (getline(in, line))
		{
			text += line;
		}
	}
	else {
		cout << "File error";
		return "";
	}
	in.close();
	return text;

}
void writeToFile(string text) {
	ofstream out;
	out.open("result.txt");
	
	if (out.is_open()) {
		out << text;
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	setlocale(LC_ALL, "Russian");
	string text;
	string keyword;
	int n;
	//vector<string> test = deleteChar( vector<string>{ "1","2","4","d" }, "1");
	text = readFromFile("text.txt");
	if (text == "") { return 0 ; }
	cout << "Âגוהטעו ךכ‏קוגמו סכמגמ"<<endl;
	cin >> keyword;
	cout << "Âגוהטעו ךכ‏ק N"<<endl;
	cin >> n;
	if (checkKeyWord(keyword) && n < 33 && n >= 0) {
		writeToFile(MakeEncryption(toLower(text), keyword, n));
	}
	else { cout << "Not valid keyword or key"; }
	cin >> n;


    return 0;
}



	




