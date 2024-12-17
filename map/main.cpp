#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

char ToLower(char ch) 
{
    if (ch >= 'A' && ch <= 'Z') 
    {
        return ch + ('a' - 'A');
    }
    return ch;
}

bool CheckChar(char ch) 
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9');
}

string ToLowerWord(const string& word) 
{
    string result;
    for (char ch : word) 
    {
        if (CheckChar(ch)) 
        {
            result += ToLower(ch);
        }
    }
    return result;
}

void SplitLineIntoWords(const string& line, map<string, int>& dictionary)
{
    string word;
    for (char ch : line) 
    {
        if (CheckChar(ch)) 
        {
            word += ch;
        }
        else if (!word.empty()) 
        {
            word = ToLowerWord(word);
            if (!word.empty()) 
            {
                dictionary[word]++;
            }
            word.clear();
        }
    }
    if (!word.empty()) 
    {
        word = ToLowerWord(word);
        if (!word.empty()) 
        {
            dictionary[word]++;
        }
    }
}

int main() 
{
    string input_file_name = "input.txt";
    string output_file_name = "output.txt";

    ifstream input_file(input_file_name);
    if (!input_file)
    {
        cout << "Error: can not open the file " << input_file_name << endl;
        return 1;
    }

    map<string, int> dictionary;

    string line;
    while (getline(input_file, line))
    {
        SplitLineIntoWords(line, dictionary);
    }
    input_file.close();

    string most_frequent_word;
    int max_frequency = 0;
    for (const auto& entry : dictionary)
    {
        if (entry.second > max_frequency)
        {
            most_frequent_word = entry.first;
            max_frequency = entry.second;
        }
    }


    cout << "Frequency dictionary:\n";
    for (const auto& entry : dictionary)
    {
        cout << entry.first << ": " << entry.second << endl;
    }
    cout << "\nMost common word: " << most_frequent_word << " (occurs " << max_frequency << " times)\n";



    ofstream outputFile(output_file_name);
    if (!outputFile) 
    {
        cout << "Error: can not open the file " << output_file_name << endl;
        return 1;
    }
    outputFile << "Most common word:\n";
    for (const auto& entry : dictionary)
    {
        outputFile << entry.first << ": " << entry.second << endl;
    }
    outputFile << "\nMost common word: " << most_frequent_word << " (occurs " << max_frequency << " times)\n";
    outputFile.close();


    cout << "The results are written to a file " << output_file_name << endl;

    return 0;
}
