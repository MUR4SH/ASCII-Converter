#pragma once
#pragma managed
#include <String> //to return string
#include <fstream> //Check existing of file
#include <iostream>
#using <System.dll>
#using <System.Drawing.Dll> //Dll for Bitmap and Color classes
#using <mscorlib.dll>
#using <WindowsBase.dll>
#using <PresentationCore.dll> //Dll for Bitmap array from gif

using namespace System;
using namespace System::Windows::Media::Imaging; 
using namespace System::Drawing; 
using namespace System::Runtime::InteropServices;
using namespace System::IO;
using namespace std;

/*
Fil: String^ type string - directory of picture
Resolution: subdividing original height and width of file to resolution number
Function returns string - to ascii converted picture
*/
string convert(string fil,int resolution){
	if (resolution < 1) { resolution = 1; }
	ifstream test;
	test.open(fil.c_str()); //Does file exist?
	if (!test.is_open()) {
		return "error";
		test.close();
	}
	String^ file = gcnew String(fil.c_str()); //Translate into String^ type
	Bitmap^ img = gcnew Bitmap(file, false); //Bitmap object of picture
	string ascii = "";
	int x = img->Width, y = img->Height;
	cout << "x: " << x << " y: " << y << endl;
	for (int i = 0; i < y; i += resolution) {
		for (int j = 0; j < x; j += resolution) {
			Color pixel = img->GetPixel(j, i);
			double br = pixel.GetBrightness();
			if (br > 0.8) { //Very bright && White
				ascii += '@';
			}
			else if (br > 0.6) { //Bright
				ascii += '#';
			}
			else if (br > 0.4) { //Normal
				ascii += '*';
			}
			else if (br > 0.2) { //Dark
				ascii += '^';
			}
			else { //Very Dark && Black
				ascii += ' ';
			}
		}
		ascii += '\n';
	}
	delete img;
	return ascii;
}
/*
Fil: String^ type string - directory of picture
Resolution: subdividing original height and width of file to resolution number
Function converts frames into ascii text and demonstrates them
*/
void GifConvert(string fil, int resolution) {
	if (resolution < 1) { resolution = 1; }
	ifstream test;
	test.open(fil.c_str()); //Does file exist?
	if (!test.is_open()) {
		cout << "error";
		test.close();
	}
	String^ file = gcnew String(fil.c_str()); //Translate into String^ type
	GifBitmapDecoder^ gif_file = gcnew GifBitmapDecoder( //Creating special Gif Decoder
		gcnew Uri(file), //Direction of our .gif file
		BitmapCreateOptions::PreservePixelFormat, //Default options for function
		BitmapCacheOption::Default
	);
	for (int it = 0; it < gif_file->Frames->Count; it++) {
		BitmapFrame^ bs = gif_file->Frames[it]; //Creating BitmapFrame of one direct Frame of gif
		BitmapEncoder^ bm_enc = gcnew BmpBitmapEncoder(); //Creating special encoder 
		bm_enc->Frames->Add(BitmapFrame::Create(bs)); //Adding BitmapFrame to bm_enc frames (encoder has only one frame)
		MemoryStream^ memory = gcnew MemoryStream(); //Making new memory stream (could use buffer stream or file stream but we will remember it in memory)
		bm_enc->Save(memory); //Saving encoded Bitmap Frame in memory stream (only one frame)
		Bitmap^ img = gcnew Bitmap(memory); //Bitmap object of picture from memory stream
		string ascii = "";
		int x = img->Width, y = img->Height;
		//cout << "x: " << x << " y: " << y << endl;
		for (int i = 0; i < y; i += resolution) {
			for (int j = 0; j < x; j += resolution) {
				Color pixel = img->GetPixel(j, i);
				double br = pixel.GetBrightness();
				if (br > 0.8) { //Very bright && White
					ascii += '@';
				}
				else if (br > 0.6) { //Bright
					ascii += '#';
				}
				else if (br > 0.4) { //Normal
					ascii += '*';
				}
				else if (br > 0.2) { //Dark
					ascii += '^';
				}
				else { //Very Dark && Black
					ascii += ' ';
				}
			}
			ascii += '\n';
		}
		system("cls");
		cout << ascii;
		delete img;		
		delete memory;
		delete bm_enc;
		delete bs;		
		delete gif_file;
	}
}