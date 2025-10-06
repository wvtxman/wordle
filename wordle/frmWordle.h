#pragma once

#include "pch.h" ;
#include "ClassPublic.h"; //class containing multiple functions;
#include "ClassConvert.h"; //class to covnert strings and more;
#include "Wordle.h" //class containing game logic;


using namespace System;
using namespace System::IO;

namespace wordle {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	/// <summary>
	/// Summary for frmWordle
	/// </summary>
	public ref class frmWordle : public System::Windows::Forms::Form
	{
	private:

		void disableBoxes() {

			if (WordGuessed) {  // reset the labels to match the correct word
				for (int j = 0; j < 25; j++) {
					 
					label[j]->Text = textBox[j]->Text;
					label[j]->ForeColor = textBox[j]->ForeColor;
					label[j]->BackColor = textBox[j]->BackColor;
					label[j]->Visible = true;

				}
			}
			//change the colors of labels for correct and incorrect words
			if (NumberOfRowsFilled == 1) {
				for (int j = 0; j < 5; j++) {
					label[j]->Text = textBox[j]->Text;
					label[j]->BackColor = textBox[j]->BackColor;
					label[j]->ForeColor = textBox[j]->ForeColor;

					label[j]->Visible = true;

				}

			}
			//change the colors of labels for correct and incorrect words
			else if (NumberOfRowsFilled == 2) {
				for (int j = 5; j < 10; j++) {
					label[j]->Text = textBox[j]->Text;
					label[j]->BackColor = textBox[j]->BackColor;
					label[j]->ForeColor = textBox[j]->ForeColor;

					label[j]->Visible = true;
				}

			}
			//change the colors of labels for correct and incorrect words
			else if (NumberOfRowsFilled == 3) {
				for (int j = 10; j < 15; j++) {
					label[j]->Text = textBox[j]->Text;
					label[j]->BackColor = textBox[j]->BackColor;
					label[j]->ForeColor = textBox[j]->ForeColor;

					label[j]->Visible = true;
				}

			}
			//change the colors of labels for correct and incorrect words
			else if (NumberOfRowsFilled == 4) {
				for (int j = 15; j < 20; j++) {
					label[j]->Text = textBox[j]->Text;
					label[j]->BackColor = textBox[j]->BackColor;
					label[j]->ForeColor = textBox[j]->ForeColor;

					label[j]->Visible = true;
				}

			}
			//change the colors of labels for correct and incorrect words
			else if (NumberOfRowsFilled == 5) {
				for (int j = 20; j < 25; j++) {
					label[j]->Text = textBox[j]->Text;
					label[j]->BackColor = textBox[j]->BackColor;
					label[j]->ForeColor = textBox[j]->ForeColor;

					label[j]->Visible = true;
				}

			}
		}
		/*
		Utility function. Converts the string input to all uppercase
		*/
		string convertToUppercase(string str)
		{
			//convert string to all uppercase
			for (int i = 0; i < str.length(); i++)
			{
				str[i] = toupper(str[i]);
			}
			return str;
		} //end convertToUppercase

		/*
		Utility function. Converts the string input to all lowercase
		*/
		string convertToLowercase(string str)
		{
			//convert string to all uppercase
			for (int i = 0; i < str.length(); i++)
			{
				str[i] = tolower(str[i]);
			}
			return str;
		} //end convertToUppercase


		/*
		open inputFile, picks 5-letter words, writes them to output file, and adds the words to the vector array.
		Returns the vector array
		*/
		vector<string> importDictionary()
		{
			string inFile = "ListOfWords.txt";
			string outFile = "FilteredWords.txt";

			fstream inputFile(inFile, ios::in);
			fstream outputFile(outFile, ios::out);

			const int WORD_LENGTH = 5; //5 letters per word

			string str; //string to store in individual words read from file 
			vector<string> arrayToReturn; //vector array to return

			// int vector.capacity() //returns total capacity of vector
			// int vector.size() //returns size (occupied space) of vector

			while (!inputFile.eof()) //end of file function
			{
				inputFile >> str; //read line/word and assign it to str; will ignore whitespaces

				for (int i = 0; i < str.length(); i++)
				{
					if (!isalpha(str[i]))
					{
						str.erase(i, 1);
					}
				}

				if (str.length() == WORD_LENGTH)
				{
					outputFile << str << endl; //output to writing file
					arrayToReturn.push_back(str); //add to vector array
				}
			} //end while

			sort(arrayToReturn.begin(), arrayToReturn.end()); //using algorithm library

			for (int i = 0; i < arrayToReturn.size(); i++)
				outputFile << arrayToReturn[i] << endl; //output to writing file

			inputFile.close();
			outputFile.close();

			return arrayToReturn; //array containing all 'eligible' words
		} //end importDictionary

		/*
		generates random number, returns a word (the SECRET word, converted to uppercase) selected from the dictionary
		*/
		string pickWord(vector<string> arrayOfWords)
		{
			std::string randomWord = "";
			//seeding random generator
			unsigned seed = time(0);
			srand(seed);

			//generating random number
			int minValue = 1, maxValue = arrayOfWords.size();
			int randomNumber = (rand() % (maxValue - minValue + 1)) + minValue;

			//retrieving word from file
			randomWord = arrayOfWords[randomNumber - 1];

			//convert word to Uppercase
			randomWord = convertToUppercase(randomWord);

			return randomWord;
		} //end pickWord

		 
		/*
		function that converts the array output by the Wordle class (which has 1's, 2's, and 3's) to a visual output
		of 'G' (for Green letter), 'Y' (for Yellow letter), and '-' (for Gray letter)
		*/
		void displayResult(int* numArray, int round, int index)
		{

			for (int i = 0; i < 5; i++)
			{
				int in1 = numArray[i];

				if (in1 == 1) {
					cout << 'G';
					setColor(1, i + index);

				}


				else if (in1 == 2) {
					cout << 'Y';
					setColor(2, i + index);

				}
				else if (in1 == 3) {
					cout << '-';
					setColor(3, i + index);

				}
				FirstIndex = -1;
			}



		} //end displayResult
	 
		 /*sets the colors of the labels and textboxes for each letter*/
		void setColor(int index, int j) {

			ClassConvert* convert = new ClassConvert();
			int letterLocation = -1;
			if (index == 1) {
				
				textBox[j]->BackColor = System::Drawing::Color::LimeGreen;
				textBox[j]->ForeColor = System::Drawing::Color::White;
				letterLocation = GuessedWord->IndexOf(textBox[j]->Text);
				if (letterLocation != -1) {//change letter label colors
					for (int i = 0; i < 26; i++) {
						if(letters[i]->Text == textBox[j]->Text)
						letters[i]->ForeColor = System::Drawing::Color::LimeGreen;
					}
				}
			}
			if (index == 2) {


				textBox[j]->BackColor = System::Drawing::Color::Yellow;
				textBox[j]->ForeColor = System::Drawing::Color::White;
				letterLocation = GuessedWord->IndexOf(textBox[j]->Text);
				if (letterLocation != -1) {
					for (int i = 0; i < 26; i++) {//change letter label colors
						if (letters[i]->Text == textBox[j]->Text)
							letters[i]->ForeColor = System::Drawing::Color::Yellow;
					}
				}
			}
			if (index == 3) {
				textBox[j]->BackColor = System::Drawing::Color::DarkGray;
				textBox[j]->ForeColor = System::Drawing::Color::White;
				letterLocation = GuessedWord->IndexOf(textBox[j]->Text);
				if (letterLocation != -1) {
					for (int i = 0; i < 26; i++) {//change letter label colors
						if (letters[i]->Text == textBox[j]->Text)
							letters[i]->ForeColor = System::Drawing::Color::Black;
					}
				}
				 
			}
		 
		}

		/*sets the label postion to center of form*/
		void setLabelPosition() {

			frmWordle^ v = gcnew  frmWordle();
			int formWidth = v->Width;
			int labelWidth = lblCorrect->Width;

			// Calculate the x position for centering
			int xPosition = (formWidth - labelWidth) / 2;
			// Set the label's location
			lblCorrect->Location = System::Drawing::Point(xPosition, lblCorrect->Location.Y);
		}

		/*submit the word to check if it is correct and in dictionary*/
		void submit(String^ GuessedWord, int index, String^ secretWord) {

			ClassConvert* convert = new ClassConvert();
			ClassPublic* info = new ClassPublic();

			String^ wordCheck;
			NumberOfRowsFilled++;

			btnSubmitWord->BackColor = System::Drawing::Color::Gray;
			btnSubmitWord->ForeColor = System::Drawing::Color::Black;

			string input = convert->ConvertSystemStringToStandardString(GuessedWord);
			int* outputArray;

			std::string secret = convert->ConvertSystemStringToStandardString(secretWord);
			Wordle theGame(secret);


			if (theGame.canAttempt() && !(theGame.isSolved())) //still can attempt
			{
				//show the word for testing
				lblCorrect->Text = secretWord;


				setLabelPosition();
				numIterations++;

				if (!theGame.wordIsInDictionary(info->dictionaryArray, convertToLowercase(input))) //invalid word
				{
					lblCorrect->Text = "This word is not in the dictionary!";
					setLabelPosition();
					if(index != -1)textBox[index]->Focus();
					NumberOfRowsFilled = 0;
					CheckWord = 0;
					NumberOfTrys -= 1;
					btnSubmitWord->Enabled = false;
					FirstIndex = -1;
					numIterations -= 1;
					WordNotInDictionary = true;
					return;
				}

				theGame.updateAttempts(input); //adds input to list of attempts
				outputArray = theGame.compareWord(input); //checks every letter of input

				displayResult(outputArray, NumberOfRowsFilled, index); //displays result for every input
				disableBoxes();
				if (index + 4 != 24) textBox[index + 5]->Focus();
			}

			//post game results
			if (theGame.isSolved()) {
				lblCorrect->Text = "You guessed the word " + secretWord;
				NumberOfRowsFilled = 0;
				btnSubmitWord->Enabled = false;
				FirstIndex = -1;
				GuessedWord = "";
				secretWord = "";
				WordGuessed = true;
				disableBoxes();
				setLabelPosition();
				btnNew->BackColor = System::Drawing::Color::LimeGreen;
				btnNew->ForeColor = System::Drawing::Color::White;


			}
			else if (!theGame.canAttempt()) {
				String^ word = secretWord;
				lblCorrect->Text = "No more turns: The word was " + word;
				GuessedWord = "";
				secretWord = "";
				FirstIndex = -1;
				NumberOfRowsFilled = 0;
				setLabelPosition();
				 
			}



			delete info;
			delete convert;
			info = nullptr;
			convert = nullptr;
		}


//game labels and textboxes and buttons
	private: System::Windows::Forms::Button^ btnNew;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::Label^ label19;
	private: System::Windows::Forms::Label^ label20;
	private: System::Windows::Forms::Label^ label21;
	private: System::Windows::Forms::Label^ label22;
	private: System::Windows::Forms::Label^ label23;
	private: System::Windows::Forms::Label^ label24;
	private: System::Windows::Forms::Label^ label25;
	private: System::Windows::Forms::Label^ label26;
	private: System::Windows::Forms::Label^ label27;
	private: System::Windows::Forms::Label^ label28;
	private: System::Windows::Forms::Label^ label29;
	private: System::Windows::Forms::Label^ label30;
	private: System::Windows::Forms::Label^ label31;
	private: System::Windows::Forms::Label^ label32;
	private: System::Windows::Forms::Label^ label33;
	private: System::Windows::Forms::Label^ label34;
	private: System::Windows::Forms::Label^ label35;
	private: System::Windows::Forms::Label^ label36;
	private: System::Windows::Forms::Label^ label37;
	private: System::Windows::Forms::Label^ label38;
	private: System::Windows::Forms::Label^ label39;
	private: System::Windows::Forms::Label^ label40;
	private: System::Windows::Forms::Label^ label41;
	private: System::Windows::Forms::Label^ label42;
	private: System::Windows::Forms::Label^ label43;
	private: System::Windows::Forms::Label^ label44;
	private: System::Windows::Forms::Label^ label45;
	private: System::Windows::Forms::Label^ label46;
	private: System::Windows::Forms::Label^ label47;
	private: System::Windows::Forms::Label^ label48;
	private: System::Windows::Forms::Label^ label49;
	private: System::Windows::Forms::Label^ label50;
	private: System::Windows::Forms::Label^ label51;

	public:

		cli::array<TextBox^>^ textBox;//textboxes for letters
		cli::array<Label^>^ label; //labels for the letters after they are checked
		cli::array<Label^>^ letters; // the alphabet


		String^ GuessedWord; //word user guessed
		String^ secretWord; // random word that was chosen
		 
		 
		int FirstIndex = -1; //used for each row of letters to get the correct first index in row
		int numIterations = 0; //number of guesses
		int NumberOfRowsFilled = 0; //number of rows that have been filled
		int CheckWord; //used to keep tab index from cycling two times
		int NumberOfTrys; //number of tries user guessed
		int IndexBeforeBackSpace; // used if user uses the backspace to erase a letter
		int textboxIndex; //used to keep track of the previous index with backspace
		bool NewGame; // if word was correct new game 
		bool WordGuessed; //if user got word correct to reset the labels and textboxes
		bool WordNotInDictionary; // check if word is in dictionary
		bool BackSpaceUsed;//if user uses backspace to keep track of index
		bool dragging;//used to move form on screen
	  
	public:
	

		   frmWordle(void)
		   {
			   InitializeComponent();
			   textBox = gcnew cli::array<TextBox^>(25);//all the textboxes
			   label = gcnew cli::array<Label^>(25);// labels for the guessed letters
			   letters = gcnew cli::array<Label^>(26);// alphabet letters

			   //labels to cover text boxes
			   label[0] = this->label1;
			   label[1] = this->label2;
			   label[2] = this->label3;
			   label[3] = this->label4;
			   label[4] = this->label5;
			   label[5] = this->label6;
			   label[6] = this->label7;
			   label[7] = this->label8;
			   label[8] = this->label9;
			   label[9] = this->label10;
			   label[10] = this->label11;
			   label[11] = this->label12;
			   label[12] = this->label13;
			   label[13] = this->label14;
			   label[14] = this->label15;
			   label[15] = this->label16;
			   label[16] = this->label17;
			   label[17] = this->label18;
			   label[18] = this->label19;
			   label[19] = this->label20;
			   label[20] = this->label21;
			   label[21] = this->label22;
			   label[22] = this->label23;
			   label[23] = this->label24;
			   label[24] = this->label25;

			   //labels for letters
			   letters[0] = this->label26;
			   letters[1] = this->label27;
			   letters[2] = this->label28;
			   letters[3] = this->label29;
			   letters[4] = this->label30;
			   letters[5] = this->label31;
			   letters[6] = this->label32;
			   letters[7] = this->label33;
			   letters[8] = this->label34;
			   letters[9] = this->label35;
			   letters[10] = this->label36;
			   letters[11] = this->label37;
			   letters[12] = this->label38;
			   letters[13] = this->label39;
			   letters[14] = this->label40;
			   letters[15] = this->label41;
			   letters[16] = this->label42;
			   letters[17] = this->label43;
			   letters[18] = this->label44;
			   letters[19] = this->label45;
			   letters[20] = this->label46;
			   letters[21] = this->label47;
			   letters[22] = this->label48;
			   letters[23] = this->label49;
			   letters[24] = this->label50;
			   letters[25] = this->label51;



			   // all the text boxes
			   textBox[0] = this->textBox1;
			   textBox[1] = this->textBox2;
			   textBox[2] = this->textBox3;
			   textBox[3] = this->textBox4;
			   textBox[4] = this->textBox5;
			   textBox[5] = this->textBox6;
			   textBox[6] = this->textBox7;
			   textBox[7] = this->textBox8;
			   textBox[8] = this->textBox9;
			   textBox[9] = this->textBox10;
			   textBox[10] = this->textBox11;
			   textBox[11] = this->textBox12;
			   textBox[12] = this->textBox13;
			   textBox[13] = this->textBox14;
			   textBox[14] = this->textBox15;
			   textBox[15] = this->textBox16;
			   textBox[16] = this->textBox17;
			   textBox[17] = this->textBox18;
			   textBox[18] = this->textBox19;
			   textBox[19] = this->textBox20;
			   textBox[20] = this->textBox21;
			   textBox[21] = this->textBox22;
			   textBox[22] = this->textBox23;
			   textBox[23] = this->textBox24;
			   textBox[24] = this->textBox25;

			   for (int i = 0; i < 25; i++) {
				   textBox[i]->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &frmWordle::textBox_KeyPress);
				   textBox[i]->TextChanged += gcnew System::EventHandler(this, &frmWordle::textBox_TextChanged);
				   textBox[i]->MaxLength = 1;
                   textBox[i]->MouseClick += gcnew MouseEventHandler(this, &frmWordle::textBox_MouseClick);
				   //textBox[i]->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &frmWordle::textBox_KeyUp);
			   }
			   //
			   //TODO: Add the constructor code here
			   //
		   }

	protected:

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~frmWordle()
		{
			if (components)
			{
				delete components;
			}
		}
		protected:
	private: System::Windows::Forms::Button^ btnQuit;
	private: System::Drawing::Point offset;
	private: System::Windows::Forms::Button^ btnSubmitWord;
	public: System::Windows::Forms::Label^ lblCorrect;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::TextBox^ textBox7;
	private: System::Windows::Forms::TextBox^ textBox8;
	private: System::Windows::Forms::TextBox^ textBox9;
	private: System::Windows::Forms::TextBox^ textBox10;
	private: System::Windows::Forms::TextBox^ textBox11;
	private: System::Windows::Forms::TextBox^ textBox12;
	private: System::Windows::Forms::TextBox^ textBox13;
	private: System::Windows::Forms::TextBox^ textBox14;
	private: System::Windows::Forms::TextBox^ textBox15;
	private: System::Windows::Forms::TextBox^ textBox16;
	private: System::Windows::Forms::TextBox^ textBox17;
	private: System::Windows::Forms::TextBox^ textBox18;
	private: System::Windows::Forms::TextBox^ textBox19;
	private: System::Windows::Forms::TextBox^ textBox20;
	private: System::Windows::Forms::TextBox^ textBox21;
	private: System::Windows::Forms::TextBox^ textBox22;
	private: System::Windows::Forms::TextBox^ textBox23;
	private: System::Windows::Forms::TextBox^ textBox24;
	private: System::Windows::Forms::TextBox^ textBox25;
	 
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;
	public:




#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(frmWordle::typeid));
			this->btnQuit = (gcnew System::Windows::Forms::Button());
			this->btnSubmitWord = (gcnew System::Windows::Forms::Button());
			this->lblCorrect = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->textBox12 = (gcnew System::Windows::Forms::TextBox());
			this->textBox13 = (gcnew System::Windows::Forms::TextBox());
			this->textBox14 = (gcnew System::Windows::Forms::TextBox());
			this->textBox15 = (gcnew System::Windows::Forms::TextBox());
			this->textBox16 = (gcnew System::Windows::Forms::TextBox());
			this->textBox17 = (gcnew System::Windows::Forms::TextBox());
			this->textBox18 = (gcnew System::Windows::Forms::TextBox());
			this->textBox19 = (gcnew System::Windows::Forms::TextBox());
			this->textBox20 = (gcnew System::Windows::Forms::TextBox());
			this->textBox21 = (gcnew System::Windows::Forms::TextBox());
			this->textBox22 = (gcnew System::Windows::Forms::TextBox());
			this->textBox23 = (gcnew System::Windows::Forms::TextBox());
			this->textBox24 = (gcnew System::Windows::Forms::TextBox());
			this->textBox25 = (gcnew System::Windows::Forms::TextBox());
			this->btnNew = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->label40 = (gcnew System::Windows::Forms::Label());
			this->label41 = (gcnew System::Windows::Forms::Label());
			this->label42 = (gcnew System::Windows::Forms::Label());
			this->label43 = (gcnew System::Windows::Forms::Label());
			this->label44 = (gcnew System::Windows::Forms::Label());
			this->label45 = (gcnew System::Windows::Forms::Label());
			this->label46 = (gcnew System::Windows::Forms::Label());
			this->label47 = (gcnew System::Windows::Forms::Label());
			this->label48 = (gcnew System::Windows::Forms::Label());
			this->label49 = (gcnew System::Windows::Forms::Label());
			this->label50 = (gcnew System::Windows::Forms::Label());
			this->label51 = (gcnew System::Windows::Forms::Label());
 
			this->SuspendLayout();
			// 
			// btnQuit
			// 

			this->btnQuit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnQuit->Location = System::Drawing::Point(274, 597);
			this->btnQuit->Name = L"btnQuit";
			this->btnQuit->Size = System::Drawing::Size(126, 36);
			this->btnQuit->TabIndex = 27;
			this->btnQuit->Text = L"Quit";
			this->btnQuit->UseVisualStyleBackColor = true;
			this->btnQuit->Click += gcnew System::EventHandler(this, &frmWordle::btnQuit_Click);
			// 
			// btnSubmitWord
			// 
			this->btnSubmitWord->Enabled = false;
			this->btnSubmitWord->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnSubmitWord->Location = System::Drawing::Point(274, 511);
			this->btnSubmitWord->Name = L"btnSubmitWord";
			this->btnSubmitWord->Size = System::Drawing::Size(126, 36);
			this->btnSubmitWord->TabIndex = 26;
			this->btnSubmitWord->Text = L"Submit Word";
			this->btnSubmitWord->UseVisualStyleBackColor = true;
			this->btnSubmitWord->Click += gcnew System::EventHandler(this, &frmWordle::btnSubmitWord_Click);
			// 
			// lblCorrect
			// 
			this->lblCorrect->AutoSize = true;
			this->lblCorrect->Font = (gcnew System::Drawing::Font(L"Cooper Black", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblCorrect->Location = System::Drawing::Point(234, 9);
			this->lblCorrect->Name = L"lblCorrect";
			this->lblCorrect->Size = System::Drawing::Size(90, 20);
			this->lblCorrect->TabIndex = 4;
			this->lblCorrect->Text = L"WORDLE";
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::LemonChiffon;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(60, 43);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 45);
			this->textBox1->TabIndex = 1;
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &frmWordle::textBox_KeyPress);
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::Color::LemonChiffon;
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox2->Location = System::Drawing::Point(173, 43);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 45);
			this->textBox2->TabIndex = 2;
			this->textBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox3
			// 
			this->textBox3->BackColor = System::Drawing::Color::LemonChiffon;
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox3->Location = System::Drawing::Point(286, 43);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(100, 45);
			this->textBox3->TabIndex = 3;
			this->textBox3->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox4
			// 
			this->textBox4->BackColor = System::Drawing::Color::LemonChiffon;
			this->textBox4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox4->Location = System::Drawing::Point(399, 43);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(100, 45);
			this->textBox4->TabIndex = 4;
			this->textBox4->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox5
			// 
			this->textBox5->BackColor = System::Drawing::Color::LemonChiffon;
			this->textBox5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox5->Location = System::Drawing::Point(512, 43);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(100, 45);
			this->textBox5->TabIndex = 5;
			this->textBox5->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox6
			// 
			this->textBox6->BackColor = System::Drawing::Color::LemonChiffon;
			this->textBox6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox6->Location = System::Drawing::Point(60, 112);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(100, 45);
			this->textBox6->TabIndex = 10;
			this->textBox6->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox7
			// 
			this->textBox7->BackColor = System::Drawing::Color::LemonChiffon;
			this->textBox7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox7->Location = System::Drawing::Point(173, 112);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(100, 45);
			this->textBox7->TabIndex = 9;
			this->textBox7->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox8
			// 
			this->textBox8->BackColor = System::Drawing::Color::LemonChiffon;
			this->textBox8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox8->Location = System::Drawing::Point(286, 112);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(100, 45);
			this->textBox8->TabIndex = 8;
			this->textBox8->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox9
			// 
			this->textBox9->BackColor = System::Drawing::Color::LemonChiffon;
			this->textBox9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox9->Location = System::Drawing::Point(399, 112);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(100, 45);
			this->textBox9->TabIndex = 7;
			this->textBox9->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox10
			// 
			this->textBox10->BackColor = System::Drawing::Color::LemonChiffon;
			this->textBox10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox10->Location = System::Drawing::Point(512, 112);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(100, 45);
			this->textBox10->TabIndex = 6;
			this->textBox10->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox11
			// 
			this->textBox11->BackColor = System::Drawing::Color::LemonChiffon;
			this->textBox11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox11->Location = System::Drawing::Point(60, 181);
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(100, 45);
			this->textBox11->TabIndex = 15;
			this->textBox11->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox12
			// 
			this->textBox12->BackColor = System::Drawing::Color::LemonChiffon;
			this->textBox12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox12->Location = System::Drawing::Point(173, 181);
			this->textBox12->Name = L"textBox12";
			this->textBox12->Size = System::Drawing::Size(100, 45);
			this->textBox12->TabIndex = 14;
			this->textBox12->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox13
			// 
			this->textBox13->BackColor = System::Drawing::Color::LemonChiffon;
			this->textBox13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox13->Location = System::Drawing::Point(286, 181);
			this->textBox13->Name = L"textBox13";
			this->textBox13->Size = System::Drawing::Size(100, 45);
			this->textBox13->TabIndex = 13;
			this->textBox13->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox14
			// 
			this->textBox14->BackColor = System::Drawing::Color::LemonChiffon;
			this->textBox14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox14->Location = System::Drawing::Point(399, 181);
			this->textBox14->Name = L"textBox14";
			this->textBox14->Size = System::Drawing::Size(100, 45);
			this->textBox14->TabIndex = 12;
			this->textBox14->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox15
			// 
			this->textBox15->BackColor = System::Drawing::Color::LemonChiffon;
			this->textBox15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox15->Location = System::Drawing::Point(512, 181);
			this->textBox15->Name = L"textBox15";
			this->textBox15->Size = System::Drawing::Size(100, 45);
			this->textBox15->TabIndex = 11;
			this->textBox15->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox16
			// 
			this->textBox16->BackColor = System::Drawing::Color::LemonChiffon;
			this->textBox16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox16->Location = System::Drawing::Point(61, 250);
			this->textBox16->Name = L"textBox16";
			this->textBox16->Size = System::Drawing::Size(100, 45);
			this->textBox16->TabIndex = 20;
			this->textBox16->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox17
			// 
			this->textBox17->BackColor = System::Drawing::Color::LemonChiffon;
			this->textBox17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox17->Location = System::Drawing::Point(173, 250);
			this->textBox17->Name = L"textBox17";
			this->textBox17->Size = System::Drawing::Size(100, 45);
			this->textBox17->TabIndex = 19;
			this->textBox17->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox18
			// 
			this->textBox18->BackColor = System::Drawing::Color::LemonChiffon;
			this->textBox18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox18->Location = System::Drawing::Point(285, 250);
			this->textBox18->Name = L"textBox18";
			this->textBox18->Size = System::Drawing::Size(100, 45);
			this->textBox18->TabIndex = 18;
			this->textBox18->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox19
			// 
			this->textBox19->BackColor = System::Drawing::Color::LemonChiffon;
			this->textBox19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox19->Location = System::Drawing::Point(397, 250);
			this->textBox19->Name = L"textBox19";
			this->textBox19->Size = System::Drawing::Size(100, 45);
			this->textBox19->TabIndex = 17;
			this->textBox19->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox20
			// 
			this->textBox20->BackColor = System::Drawing::Color::LemonChiffon;
			this->textBox20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox20->Location = System::Drawing::Point(509, 250);
			this->textBox20->Name = L"textBox20";
			this->textBox20->Size = System::Drawing::Size(100, 45);
			this->textBox20->TabIndex = 16;
			this->textBox20->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox21
			// 
			this->textBox21->BackColor = System::Drawing::Color::LemonChiffon;
			this->textBox21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox21->Location = System::Drawing::Point(60, 319);
			this->textBox21->Name = L"textBox21";
			this->textBox21->Size = System::Drawing::Size(100, 45);
			this->textBox21->TabIndex = 25;
			this->textBox21->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox22
			// 
			this->textBox22->BackColor = System::Drawing::Color::LemonChiffon;
			this->textBox22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox22->Location = System::Drawing::Point(173, 319);
			this->textBox22->Name = L"textBox22";
			this->textBox22->Size = System::Drawing::Size(100, 45);
			this->textBox22->TabIndex = 24;
			this->textBox22->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox23
			// 
			this->textBox23->BackColor = System::Drawing::Color::LemonChiffon;
			this->textBox23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox23->Location = System::Drawing::Point(286, 319);
			this->textBox23->Name = L"textBox23";
			this->textBox23->Size = System::Drawing::Size(100, 45);
			this->textBox23->TabIndex = 23;
			this->textBox23->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox24
			// 
			this->textBox24->BackColor = System::Drawing::Color::LemonChiffon;
			this->textBox24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox24->Location = System::Drawing::Point(399, 319);
			this->textBox24->Name = L"textBox24";
			this->textBox24->Size = System::Drawing::Size(100, 45);
			this->textBox24->TabIndex = 22;
			this->textBox24->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox25
			// 
			this->textBox25->BackColor = System::Drawing::Color::LemonChiffon;
			this->textBox25->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox25->Location = System::Drawing::Point(512, 319);
			this->textBox25->Name = L"textBox25";
			this->textBox25->Size = System::Drawing::Size(100, 45);
			this->textBox25->TabIndex = 21;
			this->textBox25->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// btnNew
			// 
			this->btnNew->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnNew->Location = System::Drawing::Point(274, 554);
			this->btnNew->Name = L"btnNew";
			this->btnNew->Size = System::Drawing::Size(126, 36);
			this->btnNew->TabIndex = 28;
			this->btnNew->Text = L"New ";
			this->btnNew->UseVisualStyleBackColor = true;
			this->btnNew->Click += gcnew System::EventHandler(this, &frmWordle::btnNew_Click);
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::LemonChiffon;
			this->label1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(61, 43);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(104, 45);
			this->label1->TabIndex = 29;
			this->label1->Text = L"label1";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label1->Visible = false;
			// 
			// label2
			// 
			this->label2->BackColor = System::Drawing::Color::LemonChiffon;
			this->label2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(173, 43);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(104, 45);
			this->label2->TabIndex = 30;
			this->label2->Text = L"label2";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label2->Visible = false;
			// 
			// label3
			// 
			this->label3->BackColor = System::Drawing::Color::LemonChiffon;
			this->label3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(285, 43);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(104, 45);
			this->label3->TabIndex = 31;
			this->label3->Text = L"label3";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label3->Visible = false;
			// 
			// label4
			// 
			this->label4->BackColor = System::Drawing::Color::LemonChiffon;
			this->label4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(397, 43);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(104, 45);
			this->label4->TabIndex = 32;
			this->label4->Text = L"label4";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label4->Visible = false;
			// 
			// label5
			// 
			this->label5->BackColor = System::Drawing::Color::LemonChiffon;
			this->label5->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(509, 43);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(104, 45);
			this->label5->TabIndex = 33;
			this->label5->Text = L"label5";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label5->Visible = false;
			// 
			// label6
			// 
			this->label6->BackColor = System::Drawing::Color::LemonChiffon;
			this->label6->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(61, 112);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(104, 45);
			this->label6->TabIndex = 34;
			this->label6->Text = L"label6";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label6->Visible = false;
			// 
			// label7
			// 
			this->label7->BackColor = System::Drawing::Color::LemonChiffon;
			this->label7->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(173, 112);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(104, 45);
			this->label7->TabIndex = 35;
			this->label7->Text = L"label7";
			this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label7->Visible = false;
			// 
			// label8
			// 
			this->label8->BackColor = System::Drawing::Color::LemonChiffon;
			this->label8->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(283, 112);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(104, 45);
			this->label8->TabIndex = 36;
			this->label8->Text = L"label8";
			this->label8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label8->Visible = false;
			// 
			// label9
			// 
			this->label9->BackColor = System::Drawing::Color::LemonChiffon;
			this->label9->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->Location = System::Drawing::Point(397, 112);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(104, 45);
			this->label9->TabIndex = 37;
			this->label9->Text = L"label9";
			this->label9->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label9->Visible = false;
			// 
			// label10
			// 
			this->label10->BackColor = System::Drawing::Color::LemonChiffon;
			this->label10->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(509, 112);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(104, 45);
			this->label10->TabIndex = 38;
			this->label10->Text = L"label10";
			this->label10->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label10->Visible = false;
			// 
			// label11
			// 
			this->label11->BackColor = System::Drawing::Color::LemonChiffon;
			this->label11->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->Location = System::Drawing::Point(61, 181);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(104, 45);
			this->label11->TabIndex = 39;
			this->label11->Text = L"label11";
			this->label11->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label11->Visible = false;
			// 
			// label12
			// 
			this->label12->BackColor = System::Drawing::Color::LemonChiffon;
			this->label12->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label12->Location = System::Drawing::Point(174, 181);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(104, 45);
			this->label12->TabIndex = 40;
			this->label12->Text = L"label12";
			this->label12->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label12->Visible = false;
			// 
			// label13
			// 
			this->label13->BackColor = System::Drawing::Color::LemonChiffon;
			this->label13->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label13->Location = System::Drawing::Point(285, 181);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(104, 45);
			this->label13->TabIndex = 41;
			this->label13->Text = L"label13";
			this->label13->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label13->Visible = false;
			// 
			// label14
			// 
			this->label14->BackColor = System::Drawing::Color::LemonChiffon;
			this->label14->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label14->Location = System::Drawing::Point(397, 181);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(104, 45);
			this->label14->TabIndex = 42;
			this->label14->Text = L"label14";
			this->label14->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label14->Visible = false;
			// 
			// label15
			// 
			this->label15->BackColor = System::Drawing::Color::LemonChiffon;
			this->label15->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label15->Location = System::Drawing::Point(509, 181);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(104, 45);
			this->label15->TabIndex = 43;
			this->label15->Text = L"label15";
			this->label15->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label15->Visible = false;
			// 
			// label16
			// 
			this->label16->BackColor = System::Drawing::Color::LemonChiffon;
			this->label16->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label16->Location = System::Drawing::Point(61, 250);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(104, 45);
			this->label16->TabIndex = 44;
			this->label16->Text = L"label16";
			this->label16->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label16->Visible = false;
			// 
			// label17
			// 
			this->label17->BackColor = System::Drawing::Color::LemonChiffon;
			this->label17->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label17->Location = System::Drawing::Point(174, 250);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(104, 45);
			this->label17->TabIndex = 45;
			this->label17->Text = L"label17";
			this->label17->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label17->Visible = false;
			// 
			// label18
			// 
			this->label18->BackColor = System::Drawing::Color::LemonChiffon;
			this->label18->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label18->Location = System::Drawing::Point(283, 250);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(104, 45);
			this->label18->TabIndex = 46;
			this->label18->Text = L"label18";
			this->label18->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label18->Visible = false;
			// 
			// label19
			// 
			this->label19->BackColor = System::Drawing::Color::LemonChiffon;
			this->label19->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label19->Location = System::Drawing::Point(397, 250);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(104, 45);
			this->label19->TabIndex = 47;
			this->label19->Text = L"label19";
			this->label19->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label19->Visible = false;
			// 
			// label20
			// 
			this->label20->BackColor = System::Drawing::Color::LemonChiffon;
			this->label20->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label20->Location = System::Drawing::Point(509, 250);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(104, 45);
			this->label20->TabIndex = 48;
			this->label20->Text = L"label20";
			this->label20->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label20->Visible = false;
			// 
			// label21
			// 
			this->label21->BackColor = System::Drawing::Color::LemonChiffon;
			this->label21->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label21->Location = System::Drawing::Point(61, 319);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(104, 45);
			this->label21->TabIndex = 49;
			this->label21->Text = L"label21";
			this->label21->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label21->Visible = false;
			// 
			// label22
			// 
			this->label22->BackColor = System::Drawing::Color::LemonChiffon;
			this->label22->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label22->Location = System::Drawing::Point(174, 319);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(104, 45);
			this->label22->TabIndex = 50;
			this->label22->Text = L"label22";
			this->label22->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label22->Visible = false;
			// 
			// label23
			// 
			this->label23->BackColor = System::Drawing::Color::LemonChiffon;
			this->label23->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label23->Location = System::Drawing::Point(283, 319);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(104, 45);
			this->label23->TabIndex = 51;
			this->label23->Text = L"label23";
			this->label23->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label23->Visible = false;
			// 
			// label24
			// 
			this->label24->BackColor = System::Drawing::Color::LemonChiffon;
			this->label24->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label24->Location = System::Drawing::Point(397, 319);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(104, 45);
			this->label24->TabIndex = 52;
			this->label24->Text = L"label24";
			this->label24->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label24->Visible = false;
			// 
			// label25
			// 
			this->label25->BackColor = System::Drawing::Color::LemonChiffon;
			this->label25->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label25->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label25->Location = System::Drawing::Point(510, 319);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(104, 45);
			this->label25->TabIndex = 53;
			this->label25->Text = L"label25";
			this->label25->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label25->Visible = false;
			// 
			// label26
			// 
			this->label26->BackColor = System::Drawing::Color::LemonChiffon;
			this->label26->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label26->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label26->Location = System::Drawing::Point(105, 379);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(41, 34);
			this->label26->TabIndex = 54;
			this->label26->Text = L"Q";
			this->label26->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label26->Visible = false;
			// 
			// label27
			// 
			this->label27->BackColor = System::Drawing::Color::LemonChiffon;
			this->label27->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label27->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label27->Location = System::Drawing::Point(152, 379);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(41, 34);
			this->label27->TabIndex = 55;
			this->label27->Text = L"W";
			this->label27->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label27->Visible = false;
			// 
			// label28
			// 
			this->label28->BackColor = System::Drawing::Color::LemonChiffon;
			this->label28->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label28->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label28->Location = System::Drawing::Point(199, 379);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(41, 34);
			this->label28->TabIndex = 56;
			this->label28->Text = L"E";
			this->label28->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label28->Visible = false;
			// 
			// label29
			// 
			this->label29->BackColor = System::Drawing::Color::LemonChiffon;
			this->label29->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label29->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label29->Location = System::Drawing::Point(246, 379);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(41, 34);
			this->label29->TabIndex = 57;
			this->label29->Text = L"R";
			this->label29->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label29->Visible = false;
			// 
			// label30
			// 
			this->label30->BackColor = System::Drawing::Color::LemonChiffon;
			this->label30->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label30->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label30->Location = System::Drawing::Point(293, 379);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(41, 34);
			this->label30->TabIndex = 58;
			this->label30->Text = L"T";
			this->label30->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label30->Visible = false;
			// 
			// label31
			// 
			this->label31->BackColor = System::Drawing::Color::LemonChiffon;
			this->label31->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label31->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label31->Location = System::Drawing::Point(340, 379);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(41, 34);
			this->label31->TabIndex = 59;
			this->label31->Text = L"Y";
			this->label31->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label31->Visible = false;
			// 
			// label32
			// 
			this->label32->BackColor = System::Drawing::Color::LemonChiffon;
			this->label32->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label32->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label32->Location = System::Drawing::Point(387, 379);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(41, 34);
			this->label32->TabIndex = 60;
			this->label32->Text = L"U";
			this->label32->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label32->Visible = false;
			// 
			// label33
			// 
			this->label33->BackColor = System::Drawing::Color::LemonChiffon;
			this->label33->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label33->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label33->Location = System::Drawing::Point(434, 379);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(41, 34);
			this->label33->TabIndex = 61;
			this->label33->Text = L"I";
			this->label33->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label33->Visible = false;
			// 
			// label34
			// 
			this->label34->BackColor = System::Drawing::Color::LemonChiffon;
			this->label34->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label34->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label34->Location = System::Drawing::Point(481, 379);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(41, 34);
			this->label34->TabIndex = 62;
			this->label34->Text = L"O";
			this->label34->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label34->Visible = false;
			// 
			// label35
			// 
			this->label35->BackColor = System::Drawing::Color::LemonChiffon;
			this->label35->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label35->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label35->Location = System::Drawing::Point(528, 379);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(41, 34);
			this->label35->TabIndex = 63;
			this->label35->Text = L"P";
			this->label35->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label35->Visible = false;
			// 
			// label36
			// 
			this->label36->BackColor = System::Drawing::Color::LemonChiffon;
			this->label36->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label36->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label36->Location = System::Drawing::Point(133, 421);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(41, 34);
			this->label36->TabIndex = 64;
			this->label36->Text = L"A";
			this->label36->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label36->Visible = false;
			// 
			// label37
			// 
			this->label37->BackColor = System::Drawing::Color::LemonChiffon;
			this->label37->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label37->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label37->Location = System::Drawing::Point(179, 421);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(41, 34);
			this->label37->TabIndex = 65;
			this->label37->Text = L"S";
			this->label37->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label37->Visible = false;
			// 
			// label38
			// 
			this->label38->BackColor = System::Drawing::Color::LemonChiffon;
			this->label38->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label38->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label38->Location = System::Drawing::Point(225, 421);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(41, 34);
			this->label38->TabIndex = 66;
			this->label38->Text = L"D";
			this->label38->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label38->Visible = false;
			// 
			// label39
			// 
			this->label39->BackColor = System::Drawing::Color::LemonChiffon;
			this->label39->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label39->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label39->Location = System::Drawing::Point(271, 421);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(41, 34);
			this->label39->TabIndex = 67;
			this->label39->Text = L"F";
			this->label39->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label39->Visible = false;
			// 
			// label40
			// 
			this->label40->BackColor = System::Drawing::Color::LemonChiffon;
			this->label40->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label40->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label40->Location = System::Drawing::Point(317, 421);
			this->label40->Name = L"label40";
			this->label40->Size = System::Drawing::Size(41, 34);
			this->label40->TabIndex = 68;
			this->label40->Text = L"G";
			this->label40->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label40->Visible = false;
			// 
			// label41
			// 
			this->label41->BackColor = System::Drawing::Color::LemonChiffon;
			this->label41->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label41->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label41->Location = System::Drawing::Point(363, 421);
			this->label41->Name = L"label41";
			this->label41->Size = System::Drawing::Size(41, 34);
			this->label41->TabIndex = 69;
			this->label41->Text = L"H";
			this->label41->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label41->Visible = false;
			// 
			// label42
			// 
			this->label42->BackColor = System::Drawing::Color::LemonChiffon;
			this->label42->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label42->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label42->Location = System::Drawing::Point(409, 421);
			this->label42->Name = L"label42";
			this->label42->Size = System::Drawing::Size(41, 34);
			this->label42->TabIndex = 70;
			this->label42->Text = L"J";
			this->label42->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label42->Visible = false;
			// 
			// label43
			// 
			this->label43->BackColor = System::Drawing::Color::LemonChiffon;
			this->label43->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label43->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label43->Location = System::Drawing::Point(455, 421);
			this->label43->Name = L"label43";
			this->label43->Size = System::Drawing::Size(41, 34);
			this->label43->TabIndex = 71;
			this->label43->Text = L"K";
			this->label43->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label43->Visible = false;
			// 
			// label44
			// 
			this->label44->BackColor = System::Drawing::Color::LemonChiffon;
			this->label44->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label44->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label44->Location = System::Drawing::Point(501, 421);
			this->label44->Name = L"label44";
			this->label44->Size = System::Drawing::Size(41, 34);
			this->label44->TabIndex = 72;
			this->label44->Text = L"L";
			this->label44->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label44->Visible = false;
			// 
			// label45
			// 
			this->label45->BackColor = System::Drawing::Color::LemonChiffon;
			this->label45->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label45->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label45->Location = System::Drawing::Point(179, 465);
			this->label45->Name = L"label45";
			this->label45->Size = System::Drawing::Size(41, 34);
			this->label45->TabIndex = 73;
			this->label45->Text = L"Z";
			this->label45->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label45->Visible = false;
			// 
			// label46
			// 
			this->label46->BackColor = System::Drawing::Color::LemonChiffon;
			this->label46->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label46->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label46->Location = System::Drawing::Point(225, 465);
			this->label46->Name = L"label46";
			this->label46->Size = System::Drawing::Size(41, 34);
			this->label46->TabIndex = 74;
			this->label46->Text = L"X";
			this->label46->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label46->Visible = false;
			// 
			// label47
			// 
			this->label47->BackColor = System::Drawing::Color::LemonChiffon;
			this->label47->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label47->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label47->Location = System::Drawing::Point(271, 465);
			this->label47->Name = L"label47";
			this->label47->Size = System::Drawing::Size(41, 34);
			this->label47->TabIndex = 75;
			this->label47->Text = L"C";
			this->label47->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label47->Visible = false;
			// 
			// label48
			// 
			this->label48->BackColor = System::Drawing::Color::LemonChiffon;
			this->label48->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label48->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label48->Location = System::Drawing::Point(317, 465);
			this->label48->Name = L"label48";
			this->label48->Size = System::Drawing::Size(41, 34);
			this->label48->TabIndex = 76;
			this->label48->Text = L"V";
			this->label48->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label48->Visible = false;
			// 
			// label49
			// 
			this->label49->BackColor = System::Drawing::Color::LemonChiffon;
			this->label49->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label49->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label49->Location = System::Drawing::Point(363, 465);
			this->label49->Name = L"label49";
			this->label49->Size = System::Drawing::Size(41, 34);
			this->label49->TabIndex = 77;
			this->label49->Text = L"B";
			this->label49->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label49->Visible = false;
			// 
			// label50
			// 
			this->label50->BackColor = System::Drawing::Color::LemonChiffon;
			this->label50->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label50->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label50->Location = System::Drawing::Point(409, 465);
			this->label50->Name = L"label50";
			this->label50->Size = System::Drawing::Size(41, 34);
			this->label50->TabIndex = 78;
			this->label50->Text = L"N";
			this->label50->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label50->Visible = false;
			// 
			// label51
			// 
			this->label51->BackColor = System::Drawing::Color::LemonChiffon;
			this->label51->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label51->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label51->Location = System::Drawing::Point(455, 465);
			this->label51->Name = L"label51";
			this->label51->Size = System::Drawing::Size(41, 34);
			this->label51->TabIndex = 79;
			this->label51->Text = L"M";
			this->label51->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label51->Visible = false;
			// 
			// frmWordle
			// 
			
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::LemonChiffon;
			this->ClientSize = System::Drawing::Size(674, 640);
			this->Controls->Add(this->label51);
			this->Controls->Add(this->label50);
			this->Controls->Add(this->label49);
			this->Controls->Add(this->label48);
			this->Controls->Add(this->label47);
			this->Controls->Add(this->label46);
			this->Controls->Add(this->label45);
			this->Controls->Add(this->label44);
			this->Controls->Add(this->label43);
			this->Controls->Add(this->label42);
			this->Controls->Add(this->label41);
			this->Controls->Add(this->label40);
			this->Controls->Add(this->label39);
			this->Controls->Add(this->label38);
			this->Controls->Add(this->label37);
			this->Controls->Add(this->label36);
			this->Controls->Add(this->label35);
			this->Controls->Add(this->label34);
			this->Controls->Add(this->label33);
			this->Controls->Add(this->label32);
			this->Controls->Add(this->label31);
			this->Controls->Add(this->label30);
			this->Controls->Add(this->label29);
			this->Controls->Add(this->label28);
			this->Controls->Add(this->label27);
			this->Controls->Add(this->label26);
			this->Controls->Add(this->label25);
			this->Controls->Add(this->label24);
			this->Controls->Add(this->label23);
			this->Controls->Add(this->label22);
			this->Controls->Add(this->label21);
			this->Controls->Add(this->label20);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->label18);
			this->Controls->Add(this->label17);
			this->Controls->Add(this->label16);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox21);
			this->Controls->Add(this->textBox22);
			this->Controls->Add(this->textBox23);
			this->Controls->Add(this->textBox24);
			this->Controls->Add(this->textBox25);
			this->Controls->Add(this->textBox16);
			this->Controls->Add(this->textBox17);
			this->Controls->Add(this->textBox18);
			this->Controls->Add(this->textBox19);
			this->Controls->Add(this->textBox20);
			this->Controls->Add(this->textBox11);
			this->Controls->Add(this->textBox12);
			this->Controls->Add(this->textBox13);
			this->Controls->Add(this->textBox14);
			this->Controls->Add(this->textBox15);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->textBox7);
			this->Controls->Add(this->textBox8);
			this->Controls->Add(this->textBox9);
			this->Controls->Add(this->textBox10);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->lblCorrect);
			this->Controls->Add(this->btnNew);
			this->Controls->Add(this->btnSubmitWord);
			this->Controls->Add(this->btnQuit);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = gcnew System::Drawing::Icon(L"C:\\cplus\\Wordle Game - NEW WAY\\wordle\\alphabet.ico");
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"frmWordle";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Wordle";
			this->Load += gcnew System::EventHandler(this, &frmWordle::frmWordle_Load);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &frmWordle::frmWordle_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &frmWordle::frmWordle_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &frmWordle::frmWordle_MouseUp);
			this->ResumeLayout(false);
			this->PerformLayout();

		}


#pragma endregion

		//quit the game
	private: System::Void btnQuit_Click(System::Object^ sender, System::EventArgs^ e) {

		this->Close();


	}

	   //play a new game reset everything
	private: System::Void btnNew_Click(System::Object^ sender, System::EventArgs^ e) {

		WordGuessed = false;
		NumberOfRowsFilled = 0;
		CheckWord = -2;
		NumberOfTrys = 0;
		btnSubmitWord->Enabled = false;
		FirstIndex = -1;
		 
		numIterations = 0;
		NewGame = true;
		for (int j = 0; j < 26; j++) {
			letters[j]->BackColor = System::Drawing::Color::Gray;
			letters[j]->ForeColor = System::Drawing::Color::White;
			letters[j]->Visible = true;
		}
		for (int j = 0; j < 25; j++) {
			if (textBox[j]->Enabled == false) {
				textBox[j]->Enabled = true;
			}
			textBox[j]->Text = "";
			textBox[0]->Focus();
			textBox[j]->ForeColor = System::Drawing::Color::Black;
			textBox[j]->BackColor = System::Drawing::Color::White;
			CheckWord = 0;

			if (label[j]->Visible == true) {
				label[j]->Text = "";
				label[j]->Visible = false;
			}
		}
		ClassPublic* info = new ClassPublic();
		ClassConvert* convert = new ClassConvert();


		secretWord = convert->ConvertStandardStringToSystem(pickWord(info->dictionaryArray)); //selects secret word
		lblCorrect->Text = secretWord;
		setLabelPosition();
		delete convert;
		delete info;
		info = nullptr;
		convert = nullptr;
	}

	private: System::Void textBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {

	 
		int index = Array::IndexOf(textBox, sender);//get index of textbox of letter entered


		GuessedWord = "";
		 
		//keep the first letter of each row to check the word
		if (FirstIndex == -1) { 
			FirstIndex = index;
			IndexBeforeBackSpace = FirstIndex;
		}
		 
		 
		if (BackSpaceUsed) {
			FirstIndex = IndexBeforeBackSpace;

		}
		 
		//show the word for testing
		lblCorrect->Text = secretWord;


		setLabelPosition();

		textBox[index]->Text = textBox[index]->Text->ToUpper();
		textBox[index]->SelectionStart = textBox[index]->Text->Length; // Keep the cursor at 
		GuessedWord = "";
		//save the guessed word
		for (int i = FirstIndex; i < FirstIndex + 5; i++) {
			textBox[i]->Text = textBox[i]->Text->Replace(" ", ""); // Replace spaces with an empty string
			GuessedWord = GuessedWord += textBox[i]->Text;

		}
		 

		 
		if (BackSpaceUsed) {
			BackSpaceUsed = false;
		if(index != 0)	textBox[index - 1]->Focus();
		}
		else {
			switch (index) {

			case 4:
				// Code to execute if expression == value1

				btnSubmitWord->Enabled = true;
				//btnSubmitWord->Focus();
				break;
			case 9:
				// Code to execute if expression == value2

				btnSubmitWord->Enabled = true;
			//	btnSubmitWord->Focus();
				break;
			case 14:
				// Code to execute if expression == value1

				btnSubmitWord->Enabled = true;
			//	btnSubmitWord->Focus();
				break;
			case 19:
				// Code to execute if expression == value2

				btnSubmitWord->Enabled = true;
			//	btnSubmitWord->Focus();
				break;
			case 24:
				// Code to execute if expression == value1

				btnSubmitWord->Enabled = true;
			//	btnSubmitWord->Focus();
				break;

			default:
				// Code to execute if expression does not match any case 
					textBox[index + 1]->Focus(); 
				break;
			}
		}
		textboxIndex = index;
		CheckWord++;
		if (CheckWord == 2) { CheckWord = 0; return; } //used to stop tab running second round
		 
		 
		 
		// wordGuessed = (char*)(void*)Marshal::StringToHGlobalAnsi(GuessedWord);

		if (GuessedWord->Length == 5) {
			btnSubmitWord->Enabled = true;

			btnSubmitWord->BackColor = System::Drawing::Color::LightGreen;
			btnSubmitWord->ForeColor = System::Drawing::Color::White;
 
 
		}
 
	}

	private: System::Void textBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {


		int index = Array::IndexOf(textBox, sender);

		if (e->KeyChar == (Char)Keys::Enter) {
			if (GuessedWord != nullptr) {
				if (GuessedWord->Length == 5 && WordGuessed == false) {
					e->Handled = true;
					submit(GuessedWord, FirstIndex, secretWord);
					GuessedWord = "";
					return;
				}
			}
			else {
			}
			e->Handled = true;
			return;
			 
		}
		//if backspace is hit go back one square
		if (e->KeyChar == 8 && index != 0) {

			if (index != 0) {
				textBox[index - 1]->Text = "";
				textBox[index - 1]->Focus();
			}
			e->Handled = false;
			BackSpaceUsed = true;

		}
		else if (index == 0 && e->KeyChar == 8) {
			textBox[index]->Focus();
			e->Handled = false;
			BackSpaceUsed = true;
		}

		if (Char::IsLetter(e->KeyChar) || e->KeyChar == (Char)Keys::Back || e->KeyChar == (Char)Keys::Enter)
		{
			int index = Array::IndexOf(textBox, sender);
			if (textBox[index]->Text->Length > 1) {
				textBox[index]->Text = "";
			}
			else {
				//letters entered
				e->Handled = false;

			}
		}
		else {
			MessageBox::Show(L"Only letters are allowed!", "Letters Only", MessageBoxButtons::OK);
			e->Handled = true;

		}


	}

	private: System::Void btnSubmitWord_Click(System::Object^ sender, System::EventArgs^ e) {
		CheckWord = 0;
		btnSubmitWord->Enabled = false;
		submit(GuessedWord, FirstIndex, secretWord);


	}

	private: System::Void frmWordle_Load(System::Object^ sender, System::EventArgs^ e) {

		ClassPublic* info = new ClassPublic();
		ClassConvert* convert = new ClassConvert();

		 
		      
		btnSubmitWord->Enabled = false;
		 
		for (int j = 0; j < 26; j++) {
			letters[j]->BackColor = System::Drawing::Color::Gray;
			letters[j]->ForeColor = System::Drawing::Color::White;
			letters[j]->Visible = true;
			 
		}
		//get the word to guess
		secretWord = convert->ConvertStandardStringToSystem(pickWord(info->dictionaryArray)); //selects secret word

		//show the word for testing
		lblCorrect->Text = secretWord;


		setLabelPosition();
		 

		delete convert;
		delete info;
		info = nullptr;
		convert = nullptr;
		 
	}

	private: System::Void frmWordle_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		dragging = true;
		offset = System::Drawing::Point(e->X, e->Y);
	}

	private: System::Void frmWordle_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (dragging) {
			System::Drawing::Point currentScreenPos = PointToScreen(e->Location);
			Location = System::Drawing::Point(currentScreenPos.X - offset.X, currentScreenPos.Y - offset.Y);
		}
	}

	private: System::Void frmWordle_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		dragging = false;
	}



	private: System::Void textBox_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {

		int index = Array::IndexOf(textBox, sender);
		MessageBox::Show(L"Please use the back space!", L"Use Back Space", MessageBoxButtons::OK, MessageBoxIcon::Information);
		textBox[textboxIndex]->Focus();
		return;
		 
		 
	}
};
}
