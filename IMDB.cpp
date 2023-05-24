/**********************************************************
 * Program 4: IMDB
 * 
 * Course: CS 141, Fall 2022
 * System: MacOS using VSCode
 * Starter Code Author: Dr. Sara Riazi
 * Student Author: Albert Huynh
 **********************************************************/

#include <iostream>   
#include <cctype>     
#include <vector>     
#include <sstream>    
#include <fstream>
#include <unistd.h>
#include <iomanip>
#include <cstring>

using namespace std;

struct TitleRecord{
    string titleId;
    string primaryTitle;
    string startYear;
    string genre;
};

struct NameRecord{
    string nameId;
    string primaryName;
    string birthYear;
    string deathYear;
    string primaryProfession;
};

struct PrincipalRecord{
    string titleId;
    string nameId;
    string character;
};

/*********************************************** Helper functions ***************************************/
//The splitString function takes a line and split it on the delimiter and push the parts into items
void splitString(string line, char delimiter, vector<string>& items ) {
	stringstream s_stream(line);
	while (s_stream.good()) {
		string item;
		getline(s_stream, item, delimiter);
		items.push_back(item);
	}
}
/**********************************************************************************************************/

void listOfTitleIds(vector<TitleRecord> &listOfTitleRecords){
    string line;
    TitleRecord tempRecord;
	ifstream Records("movie.titles.tsv");
	if(Records.is_open()){
		while(getline(Records, line)){
            vector<string> TitleRecords;
            splitString(line, '\t', TitleRecords);

            tempRecord.titleId = TitleRecords.at(0);
            tempRecord.primaryTitle = TitleRecords.at(2);
            tempRecord.startYear = TitleRecords.at(5);
            tempRecord.genre = TitleRecords.at(8);

            listOfTitleRecords.push_back(tempRecord);
		}
	}
	Records.close();
}

void listOfNameIds(vector<NameRecord> &listOfPrincipals){
    string line;
    NameRecord tempName;
	ifstream Records("movie.names.tsv");
	if(Records.is_open()){

		while(getline(Records, line)){
            vector<string> nameRecords;
            splitString(line, '\t', nameRecords);

            tempName.nameId = nameRecords.at(0);
            tempName.primaryName = nameRecords.at(1);
            tempName.birthYear = nameRecords.at(2);
            tempName.deathYear = nameRecords.at(3);
            tempName.primaryProfession = nameRecords.at(4);
            
			listOfPrincipals.push_back(tempName);
		}
	}
	Records.close();
}

void listOfPrincipalIds(vector<PrincipalRecord> &listOfRecords){
    string line;
	
	ifstream Records("movie.principals.tsv");
	if(Records.is_open()){
		while(getline(Records, line)){
            vector<string> principalRecords;
            splitString(line, '\t', principalRecords);
            PrincipalRecord tempRecord;

            tempRecord.titleId = principalRecords.at(0);
            tempRecord.nameId = principalRecords.at(2);
            tempRecord.character = principalRecords.at(5);
            
			listOfRecords.push_back(tempRecord);
		}
	}
	Records.close();
}

vector<TitleRecord> linearSearch(vector<string> words, vector<TitleRecord> &listofMovie){
    bool matched = false;
    vector<TitleRecord> records;
    for(int i = 0; i < listofMovie.size(); i++){
        matched = false;
        //making movie lowercase
            string lowercaseMovie = "";
            for(int j = 0; j < listofMovie.at(i).primaryTitle.length(); j++){
                lowercaseMovie += tolower(listofMovie.at(i).primaryTitle.at(j));
            }
            for(int j = 0; j < words.size(); j++){
                if(lowercaseMovie.find(words.at(j)) != -1){
                    matched = true;
                }
                else{
                    matched = false;
                    break;              
                }
        }
        if(matched){
            records.push_back(listofMovie.at(i));
        }
    }
    if(records.size() == 0){
        cout << "No match found" << endl;
    }
    return records;
}

vector<NameRecord> linearSearch2(vector<string> words, vector<NameRecord> &listOfActors){
    bool matched = false;
    vector<NameRecord> records;
    for(int i = 0; i < listOfActors.size(); i++){
        matched = false;
        string lowercaseActor = "";
        for(int j = 0; j < listOfActors.at(i).primaryName.length(); j++){
            lowercaseActor += tolower(listOfActors.at(i).primaryName.at(j));
        }
        for(int j = 0; j < words.size(); j++){
            if(lowercaseActor.find(words.at(j)) != -1){
                matched = true;
            }
            else{
                matched = false;
                break;
            }
        }
        if(matched){
            records.push_back(listOfActors.at(i));
        }
    }
    if(records.size() == 0){
        cout << "No match found" << endl;
    }
    return records;
}

void MenuOption1(string title, vector<TitleRecord> &titles, vector<NameRecord> &names,vector<PrincipalRecord> &principals){
    vector<string> origTitleRecord;
    vector<string> lowercaseTitleRecords;
    vector<TitleRecord> matches;
    matches.clear();
    origTitleRecord.clear();

    //Creating the userinput lowercase titles
    splitString(title, '+', origTitleRecord);
    for(int i = 0; i < origTitleRecord.size(); i++){
        string lowercaseTitle = "";
        for(int j = 0; j < origTitleRecord.at(i).length(); j++){
            lowercaseTitle += tolower(origTitleRecord.at(i).at(j));
        }
        lowercaseTitleRecords.push_back(lowercaseTitle);
    }

    //creating the matches
    matches = linearSearch(lowercaseTitleRecords, titles);

    //seperating the genre cases
    vector<string> genres;
    for(int i = 0; i < matches.size(); i++){
        splitString(matches.at(i).genre , ',' , genres);
    }
    //printing the sets
    cout << endl;
    for(int i = 0; i < matches.size(); i++){
        cout << i << ":" << endl;
        cout << "Title: " << matches.at(i).primaryTitle << endl;
        cout << "Year: " << matches.at(i).startYear << endl;
        for(int j = 0; j < matches.size(); j+=2){
            cout << "Genre: " << genres.at(j) << " " << genres.at(j + 1) << endl;
        }
        cout << "---------------" << endl;
    }

    //finding the actors to the movie
    int movieSelection = -2;
    while (movieSelection != -1) {
        vector<string> actors;
        cout << "Select a movie to see its actors/actresses (-1 to go back to the previous menu): ";
        cin >> movieSelection;
        if (cin.fail() ) {
            break;
        }

        if(movieSelection != -1){
            string movieSelectionId = matches.at(movieSelection).titleId;
            vector<PrincipalRecord> listOfActors;
            vector<string> listOfCharacters;
            vector<string> listOfRealActors;

            //getting the matched principals
            for(int i = 0; i < principals.size(); i++){
                if(principals.at(i).titleId == movieSelectionId && principals.at(i).character != "\\N"){
                    listOfActors.push_back(principals.at(i));
                }
            }

            //putting the names inside a vector
            for(int i = 0; i < names.size(); i++){
                for(int j = 0; j < listOfActors.size(); j++){
                    if(names.at(i).nameId == listOfActors.at(j).nameId){
                        listOfRealActors.push_back(names.at(i).primaryName);
                        cout << names.at(i).primaryName << " " << listOfActors.at(j).character << endl;
                    }
                }
            }
        }
    }
}

void MenuOption2(string actor, vector<NameRecord> &listOfActors, vector<TitleRecord> &titles, vector<PrincipalRecord> &principals){
        vector<string> originalActors;
        vector<string> lowercaseActors;
        vector<NameRecord> matches;

        //creating the userinput lowercase
        splitString(actor, '+', originalActors);
        for(int i = 0; i < originalActors.size(); i++){
            string lowercaseActor = "";
            for(int j = 0; j < originalActors.at(i).length(); j++){
                lowercaseActor += tolower(originalActors.at(i).at(j));
            }
            lowercaseActors.push_back(lowercaseActor);
        }

        //creating matches for actors
        matches = linearSearch2(lowercaseActors, listOfActors);

        //printing the results of the matches
        cout << "---------------" << endl;
        for(int i = 0; i < matches.size(); i++){
            cout << i << ":" << endl;
            cout << matches.at(i).primaryName << endl;
            cout << matches.at(i).primaryProfession << endl;
            cout << "(" << matches.at(i).birthYear << "-" << matches.at(i).deathYear << ")" << endl;
            cout << "---------------" << endl;
        }

        //Second part of menu 2
        int actorSelection;
        cout << "Select and actor/actress to see movies (-1 to go back to the previous menu): ";
        cin >> actorSelection;

        while(actorSelection != -1 && actor != "done"){
            string actorSelectionId = matches.at(actorSelection).nameId;
            vector<PrincipalRecord> listOfMovies;
            vector<string> listOfRealMovies;
            vector<string> listOfCharacters;
            vector<string> listOfYears;

            //Finding the principals with the actor
            for(int i = 0; i < principals.size(); i++){
                if(principals.at(i).nameId == actorSelectionId){
                    listOfMovies.push_back(principals.at(i));
                }
            }

            //finding the movies with the actor
            for(int i = 0; i < titles.size(); i++){
                for(int j = 0; j < listOfMovies.size(); j++){
                    if(titles.at(i).titleId == listOfMovies.at(j).titleId){
                        listOfRealMovies.push_back(titles.at(i).primaryTitle);
                    }
                }
            }

            //finding the characters with the actor
            for(int i = 0; i < listOfMovies.size(); i++){
                listOfCharacters.push_back(listOfMovies.at(i).character);
            }

            //finding the years with the actor
            for(int i = 0; i < titles.size(); i++){
                for(int j = 0; j < listOfMovies.size(); j++){
                    if(titles.at(i).titleId == listOfMovies.at(j).titleId){
                        listOfYears.push_back(titles.at(i).startYear);
                    }
                }
            }

            //printing the movie, year, and character
            for(int i = 0; i < listOfMovies.size(); i++){
                cout << listOfRealMovies.at(i) << " " << listOfYears.at(i) << " " << listOfCharacters.at(i) << endl;
            }

            cout << "Enter search phrase (type done to go back to the previous menu): ";
            cin >> actor;
            if (cin.fail() ) {
                break;
            }
        }
    }

int run(string titlesFile, string namesFile, string principalsFile) {
    vector<TitleRecord> titles;
    vector<NameRecord> names;
    vector<PrincipalRecord> principals;
    int choice = -2;
    string phrase;

    listOfNameIds(names);
    listOfPrincipalIds(principals);
    listOfTitleIds(titles);

    while(true){
        cout << "Select a menu option:" << endl;
        cout << "   1. Search for movies" << endl;
        cout << "   2. Search for actors/actresses" << endl;
        cout << "   3. Exit" << endl;
        cout << "Your choice --> ";
        cin >> choice;
        if (cin.fail() ) {
            break;
        }
        if (choice == 3) {
            break;
        }
        cout << "Enter search phrase: ";
        cin >> phrase;
        if (cin.fail() ) {
            break;
        }
        if(choice == 1){
            MenuOption1(phrase, titles, names, principals);
        }
        else if(choice == 2){
            MenuOption2(phrase, names, titles, principals);
        }
        
    }
	return 0;	
}

int main() {
	//Change these addresses according to your local machine
	string titlesFile =	"/Users/albert/Desktop/C:C++ Projects/Project 4/movie.titles.tsv";
	string namesFile = "/Users/albert/Desktop/C:C++ Projects/Project 4/movie.names.tsv";
	string principalsFile = "/Users/albert/Desktop/C:C++ Projects/Project 4/movie.principals.tsv";

	//DO NOT change the main function. The main function will be removed by the autograder
	run(titlesFile, namesFile, principalsFile);
	return 0;
}
