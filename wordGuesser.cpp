/*
WordGuesser 2.0:
    Guesses your word more precisely.
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class WordsFilter
{
    public:
        //Vector to store the 
        WordsFilter(const vector<string>& wordList) : wordList_(wordList)
        {
        }
        //Function to store the filtered-in words (returns a value):
        vector<string> filterWords(char firstLetter, char lastLetter, char recurring, char consonant, int numLetters)
        {
            int counter = 0;
            //Creating an empty container/vector to hold strings:
            vector<string> filteredWords;
            //Loop: For each word in the referenced list:
            for (const string& word : wordList_)
            {
                    counter++;
                    // Skip words that don't start with the specified first letter:
                    if (word.front() < firstLetter)
                        // ASCII Univode comparison.
                        // "Does first letter of current word occur before the specified first letter?"
                        continue; // Skip to the next word.
                    else if (word.front() > firstLetter)
                        break; // No need to check further if the first letter exceeds the specified letter.
                    
                    //Check if the word meets all filtering requirements:
                        // List is not sorted by length or last letters,
                        // so this check is done together & w/o breaks.
                    if (word.length() == numLetters && word.back() == lastLetter)
                    {
                        if (word.find(recurring) != string::npos && count(word.begin(), word.end(), recurring) >= 2 && word.find(consonant) != string::npos)
                            //If word matches filtering requirements, it is inserted into the back of list:
                            filteredWords.push_back(word);
                    }
            }
            
            cout << "Filtered " << to_string(counter) << " words.\n";
                // to_string converts counter integer to a string.
            //If no words found:
            if (filteredWords.empty())
                cout << "No words found!";
            else
                cout << "Is your word [";
            return filteredWords;
        }

    private:
        //Private member variable. Can be accessed by any member function of the entire class/file.
            // Tied to "wordList" object. Exists to reference wordList OUTSIDE of the main class.
        const vector<string>& wordList_; // reference to a constant vector of strings.
            // & - reference, const - constant or unchanging.
};

/**
 * Main class
*/
int main()
{
    ifstream inputFile("words_alpha.txt"); // opens the text file.
    if(!inputFile)
    {
        cerr << "Error loading file for program. Retry.\n";
            // cerr used instead of cout for immediate error message, no buffer from message storage.
        return 1; // 1 instead of 0 for 'error while executing.
    }

    //Read words from the file and store them in a container/vector:
    vector<string> wordList;
        // local variable, holds list of words read from file. Limited to main function.
    string word;
        // each word
    // While there's still words to be read, keep doing:
    while (inputFile >> word)
    {
        wordList.push_back(word); // inserts the current word to the end of the vector.
    }

    //User interactions and main screen:
    char firstLetter, lastLetter, recurring, consonants;
    int numLetters;
    cout << "____________________________________\n\n";
    cout << "Welcome to Wordo the Word Guesser!\n";
    cout << "Let's guess your word...\n";
    cout << "What is the first letter? > ";
        cin >> firstLetter;
    cout << "What is the last letter? > ";
        cin >> lastLetter;
    cout << "How many letters? > ";
        cin >> numLetters;
    cout << "Any recurring characters? > ";
        cin >> recurring;
    cout << "Any unique characters (consonants)? > ";
        cin >> consonants;
    cout << "____________________________________\n\n";
    if(!firstLetter || !lastLetter || !numLetters || !recurring || !consonants)
    {
        cout << "Invalid inputs!! Ending...";
    }

    
    //Computer guesses:
    // Call the WordsFilter class:
    WordsFilter wordFilter(wordList);
    // Call the filterWords function:
    vector<string> filteredWords = wordFilter.filterWords(firstLetter, lastLetter, recurring, consonants, numLetters);
    for(size_t i = 0; i < filteredWords.size(); i++)
        // size_t is a variable type like int but for ARRAY INDEXING and LOOP COUNTING.
    {
        cout << filteredWords[i] << "]??" << "\n";
    }


    inputFile.close(); // closes the text file.
    return 0; // successful execution.
}

/*
SAMPLE OUTPUT:
____________________________________

Welcome to Wordo the Word Guesser!
Let's guess your word...
What is the first letter? > a
What is the last letter? > e
How many letters? > 5
Any recurring characters? > p
Any unique characters (consonants)? > l
____________________________________

Filtered 25418 words.
Is your word [apple]??
*/
