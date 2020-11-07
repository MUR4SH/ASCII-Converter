#include <iostream>
#include <cstdio>
#include <String>
#include <fstream>
#include "Converter.h"


/*
Saving text into .txt file
text: string for saving
Function returns satuses of saving
*/
void saving(string text) {
	string file; //Direction where to save text
	cout << "save?(y/n) ";
	char yes;
	cin >> yes;
	if (yes == 'Y' || yes == 'y') {
		cout << "File direction: ";
		cin >> file;
		ofstream txt;
		txt.open(file);
		if (txt.is_open()) {
			txt << text; 
			cout << "Saved\n";
		}
		else {
			cout << "Error\n";
		}
	}
}

int main() {
	while(true){
		string file="D:\\Downloads\\tenor.gif";
		int resolution=5;		
		system("pause");
		cout << "\nFile direction: ";
		cin >> file;
		ifstream test;
		test.open(file.c_str()); //Does file exist?
		if (!test.is_open()) {
			cout << "error";
			test.close();
		}
		String^ filee = gcnew String(file.c_str()); //Translate into String^ type
		Bitmap^ img = gcnew Bitmap(filee, false); //Bitmap object of picture
		int recom = img->Width/117 + 1;
		cout << "Recomended " << recom;
		cout << "\nScale 1 to : ";
		cin >> resolution;
		if (file[file.length() - 1] == 'f' && file[file.length() - 2] == 'i' && file[file.length() - 3] == 'g' && file[file.length() - 4] == '.') {
			int choose = 0;
			int rep = 0;
			bool check = true;
			while (check) {
				cout << "\n1)Show main picture\n 2)Show all pictures \n";
				cin >> choose;
				string ascii;
				switch (choose) {
				case 1:
					check = false;
					ascii = convert(file, resolution);
					cout << ascii << endl;
					saving(ascii); //saving text to txt file
					break;
				case 2:
					check = false;
					cout << "repeat:";
					cin >> rep;
					if (rep < 1) rep = 1;
					for(int po=0;po<rep;po++) GifConvert(file, resolution);
					break;
				default:
					system("cls");
					break;
				}
			}
		}
		char yes;
		cout << "retry?(y/n) ";
		cin >> yes;
		if (yes != 'Y' && yes != 'y') {
			return 0;
		}
		system("cls");
	}
}