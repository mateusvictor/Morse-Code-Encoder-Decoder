#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#define LIN 37

using namespace std;

vector<string> alphaLatim = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
					  		 "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",
					         "1", "2", "3", "4", "5", "6", "7", "8", "9", "0"}; 

vector<string> alphaMorse = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--",
							 "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",
							 ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----"}; 

void printMenu();
void printBye();

string decodeMorseCode(string);
string encodeLatimCode(string);

vector<string> split(string, string);
string strip(string);

int main(){

	int option;
	string morseCode, morseDecoded, latimCode, morseEncoded;
	
	while (1) {
		system("cls");

		printMenu();
		
		cin >> option;
		
		cin.ignore();
            		    
		if (option == 1) {	
			cout << setw(62) << "*1 space between chars and 3 spaces between words*" << endl << endl;
			cout << "  Type the morse code: ";
			
			getline(cin, morseCode);

			morseDecoded = decodeMorseCode(strip(morseCode));
			
			if(morseDecoded != "-1"){
				cout << "  Morse decoded: ";
				cout << morseDecoded << endl;
			}

		} else if (option == 2) {
			cout << setw(62) << "*1 space between words (Only numbers and letters)*" << endl << endl;

			cout << "  Type the latim code: ";
			getline(cin, latimCode);

			transform(latimCode.begin(), latimCode.end(), latimCode.begin(), 
				[](unsigned char c){return tolower(c);}); // Convert the string to lower case

			morseEncoded = encodeLatimCode(strip(latimCode));

			if(morseEncoded != "-1") {
				cout << "  Morse code: ";
				cout << morseEncoded << endl;
			}

		} else {
			cout << endl;
			printBye();
			break;
		}

		cout << "\n  ";
		system("pause");
	}

	cout << "\n  ";
	system("pause");
	return 0;
}

void printMenu()
{
	/*
	-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    	                      Morse Decoder/Encoder                       
	=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

  	  [ 1 ] Decode (Morse Code -> Latim Code)
  	  [ 2 ] Encode (Latim Code -> Morse Code)
  	  [ 3 ] Exit

  	  =>>
	*/

	for (int i = 0; i < LIN; i++) 
		cout << "-=";
	cout << "\n" << setw(47) << "Morse Decoder/Encoder" << endl;
	for (int i = 0; i < LIN; i++) 
		cout << "=-";

	cout << endl << endl;		

	cout << "  [ 1 ] Decode (Morse Code -> Latim Code)\n  [ 2 ] Encode (Latim Code -> Morse Code)\n  [ 3 ] Exit\n" << endl;
	cout << "  =>> ";
}
		
void printBye()
{
	/*
	-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    	                                          Thanks for using my program!
    	                                    Follow me on GitHub: @mateusvictor
	*/

	for (int i = 0; i < LIN; i++) cout << "-=";
	cout << endl;
	cout << setw(74) << "Thanks for using my program!" << endl;
	cout << setw(74) << "Follow me on GitHub: @mateusvictor" << endl;
}

string decodeMorseCode(string code)
{	
	// Decode Morse Code returning Latim Code
	int lenWord, index, lenCode;
	string result = ""; 
	

	vector <string> word;
	vector<string> codeSplit;
	vector<string>::iterator it;

	codeSplit = split(code, "   "); // Split the phrase at each triple space (divides the phrase into words)
	
	lenCode = codeSplit.size(); 
	
	for (int words = 0; words < lenCode; words++) { // For each word in the phrase
		word = split(codeSplit[words], " "); 
		lenWord = word.size(); // Split the word at each space (divides the word into letters)

		for (int letters = 0; letters < lenWord; letters++) { // For each letter in the word
			
			it = find(alphaMorse.begin(), alphaMorse.end(), word[letters]); // Iterator that searchs the character 
			index = it - alphaMorse.begin();

			if (index == 36){  // The character wasn't found
				cout << "  ERRO! Please type corectly the morse code!\n";
				return "-1";
			}

			result += alphaLatim[index];	// Add the letter already decoded to the result 
		}
		result += " "; // Add a space between words
	}
	return result;
}

string encodeLatimCode(string phrase)
{	
	// Encode Latim Code returning Morse Code
	int lenWord, index, lenPhrase;
	string line = "";

	vector<string> word;
	vector<string> phraseSplit;
	vector<string>::iterator it;

	phraseSplit = split(phrase, " "); // Split the phrase at each space (divides the phrase into words)
	
	lenPhrase = phraseSplit.size();

	for (int words = 0; words < lenPhrase; words++) { // For each word in the phrase
		word = split(phraseSplit[words], ""); // Split the word in chars
		lenWord = word.size();

		for (int letters = 0; letters < lenWord; letters++) // For each letter in the word
		{
			it = find(alphaLatim.begin(), alphaLatim.end(), word[letters]); // Iterator that searchs the character 
			index = it - alphaLatim.begin();

			if (index == 36){  // The character wasn't found
				cout << "  ERRO! Please type corectly the morse code!\n";
				return "-1";
			}

			line += alphaMorse[index];
			
			if (lenWord - 1 != letters) // If the character isn't the last in the word
				line += " "; // Add a space beween characters
		}
		line += "   ";	
	}
	return line;
}

vector<string> split(string s, string delimiter)
{
	// Splits the string at each delimiter returning a vector 
	// This function allows us to compare letter by letter instead of phrases and words
	// Ex: split("hello.-.world.-.!", ".-.") returns: {"hello", "word", "!"}

	vector<string> str_split;
	string temp; 

	if (delimiter == ""){ //The delimter is a empty string
		int len = s.size();
		for (int i = 0; i < len; i++){
			temp = s[i];
			str_split.push_back(temp);
		}
	}

	else { 
		size_t pos = 0;
		while ((pos = s.find(delimiter)) != string::npos) {
    		str_split.push_back(s.substr(0, pos));
    		s.erase(0, pos + delimiter.length());
		}
		str_split.push_back(s);
	}

	return str_split;
}

string strip(string s)
{
	// Eliminate the space at the begin and at the end of the string
	// This is a treatment input function that prevent future errors

	s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
	s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
	s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());

    return s;
}

/*
	Resources: 
		- split(): https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
		- strip(): https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring		
*/