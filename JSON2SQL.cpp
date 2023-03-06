/*
    Copyright(C) 2022 Tyler Crockett | Macdaddy4sure.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissionsand
    limitations under the License.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <mysql.h>

using namespace std;

string ParseThesaurus(string input_file);
void Thesaurus2SQL(string word, string pos, string* synonyms);
void QueryDatabase(string thesaurus_word, string thesaurus_pos, string thesaurus_synonyms);
//bool wordExists(string word);

int main()
{
    string input;

    while (true)
    {
        cout << endl;
        cout << "Input File: ";
        getline(cin, input);

        if (input != "")
        {
            ParseThesaurus(input);
        }
        else
        {
            cout << endl;
        }
    }

    return 0;
}

string ParseThesaurus(string input_file)
{
    string word;
    string pos;
    string synonyms;
    string synonyms_temp;
    string input;
    int num_synonyms = 0;
    fstream file;

    file.open(input_file.c_str());

    if (file.is_open())
    {
        while (getline(file, input))
        {
            for (int a = 0; a <= input.length(); a++)
            {
                // Get the word
                if (input[a] == '{' && input[a + 1] == '\"' && input[a + 2] == 'w' && input[a + 3] == 'o' && input[a + 4] == 'r' && input[a + 5] == 'd' && input[a + 6] == '\"' && input[a + 7] == ':' && input[a + 8] == ' ' && input[a + 9] == '\"')
                {
                    int b = 0;

                    for (b = a + 1; input[b] != '\"'; b++)
                    {
                        word += input[b];
                    }

                    for (int c = b + 1; input.length(); c++)
                    {
                        if (input[c] == '\"' && input[c + 1] == 'p' && input[c + 2] == 'o' && input[c + 3] == 's' && input[c + 4] == '\"' && input[c + 5] == ':' && input[c + 6] == ' ' && input[c + 7] == '\"')
                        {
                            for (int d = c + 1; input[d] != '\"'; d++)
                            {
                                pos += input[d];
                            }
                        }
                        if (input[c] == '\"' && input[c + 1] == 's' && input[c + 2] == 'y' && input[c + 3] == 'n' && input[c + 4] == 'o' && input[c + 5] == 'n' && input[c + 6] == 'y' && input[c + 7] == 'm' && input[c + 8] == 's' && input[c + 9] == '\"' && input[c + 10] == ':' && input[c + 11] == ' ' && input[c + 12] == '[' && input[c + 13] == '\"')
                        {
                            for (int d = c + 1; input.length(); d++)
                            {
                                if (input[d] != ']' && input[d + 1] != '}')
                                {
                                    synonyms_temp += input[d];
                                }
                            }
                        }
                    }
                }
            }

            cout << endl;
            cout << "word: " << word << endl;
            cout << "pos: " << pos << endl;
            cout << "synonyms_temp: " << synonyms_temp << endl;
            //Thesaurus2SQL(word, pos, synonyms);
            QueryDatabase(word, pos, synonyms_temp);
            word.clear();
            pos.clear();
            synonyms_temp.clear();
        }
    }
}

// Purpose: Add one line from the thesaurus to the dictionary database
// 1. Print the line from the thesaurus
//      a. Word
//      b. Part of Speech
//      c. Synonyms
// 2. Get identical lines from the dictionary
//      a. Display all information from the dictionary for a given word
// 3. Based on the current line of the thesaurus and the number of dictionary definitions, make slections for each dictionary definition
void Thesaurus2SQL(string word, string pos, string* synonyms)
{
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* result;
    //string mysql_username = "root";
    //string mysql_password = "Anaheim228%";
    //string mysql_database = "dictionary";
    //string dictionary_table = "entries3";
    //string dictionary_word[5];
    //string dictionary_pos[5];
    //string dictionary_definition[5];
    string table;
    string thesaurus_word;
    string thesaurus_pos;
    string thesaurus_synonyms[5];
    string input;
    bool found = false;
    int number_selection = 1;
    string sql1;

    //conn = mysql_init(0);
    //conn = mysql_real_connect(conn, "127.0.0.1", mysql_username.c_str(), mysql_password.c_str(), mysql_database.c_str(), 3306, NULL, 0);

    //QueryDatabase(thesaurus_word, thesaurus_pos, thesaurus_synonyms);

    //if (conn)
    //{
    //    //sql1 = "SELECT * FROM ";
    //    //sql1 += dictionary_table;
    //    ///*cout << "SQL1: " << sql1 << endl;*/
    //    //mysql_query(conn, sql1.c_str());
    //    //result = mysql_store_result(conn);
    //}
}

//void CreateTable()
//{
//    MYSQL* conn;
//    MYSQL_ROW row;
//    string mysql_database = "dictionary";
//    string mysql_username = "root";
//    string mysql_password = "Anaheim228%";
//    string table = "thesaurus";
//    string input;
//    string sql1;
//
//    conn = mysql_init(0);
//    conn = mysql_real_connect(conn, "127.0.0.1", mysql_username.c_str(), mysql_password.c_str(), mysql_database.c_str(), 3306, NULL, 0);
//
//    if (conn)
//    {
//        sql1 = "CREATE TABLE ";
//        sql1 += table;
//        sql1 += "(word TEXT, wordtype TEXT, definition TEXT, synonyms TEXT);\"";
//        mysql_query(conn, sql1.c_str());
//    }
//}

void QueryDatabase(string thesaurus_word, string thesaurus_pos, string thesaurus_synonyms)
{
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* result;
    string mysql_database = "dictionary";
    string mysql_username = "root";
    string mysql_password = "Anaheim92801%";
    string mysql_table = "thesaurus";
    string input;
    string sql1;
    string word;
    string wordtype;
    //string definition;
    //string synonyms;

    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "127.0.0.1", mysql_username.c_str(), mysql_password.c_str(), mysql_database.c_str(), 3306, NULL, 0);

    if (conn)
    {
        sql1.clear();

        sql1 = "INSERT INTO ";
        sql1 += mysql_table;
        sql1 += "(word, wordtype, synonyms) VALUES(\"";
        sql1 += thesaurus_word;
        sql1 += "\", \"";
        sql1 += thesaurus_pos;
        sql1 += "\", \"";
        sql1 += thesaurus_synonyms;
        sql1 += "\");\"";

        cout << "SQL1: " << sql1 << endl;
        /*mysql_query(conn, sql1.c_str());*/
        cout << mysql_error(conn) << endl;
    }
}

//bool wordExists(string word)
//{
//    MYSQL* conn;
//    MYSQL_ROW row;
//    MYSQL_RES* result;
//    string mysql_database = "dictionary";
//    string mysql_username = "root";
//    string mysql_password = "Anaheim228%";
//    string dictionary_table = "entries";
//    string sql1;
//    string word_temp;
//
//    conn = mysql_init(0);
//    conn = mysql_real_connect(conn, "127.0.0.1", mysql_username.c_str(), mysql_password.c_str(), mysql_database.c_str(), 3306, NULL, 0);
//
//    if (conn)
//    {
//        sql1 = "SELECT * FROM ";
//        sql1 += dictionary_table;
//        /*cout << "SQL1: " << sql1 << endl;*/
//        mysql_query(conn, sql1.c_str());
//        result = mysql_store_result(conn);
//
//        while (row = mysql_fetch_row(result))
//        {
//            word_temp = toLowerWord(row[0]);
//            word = toLowerWord(word);
//
//            if (word == word_temp)
//            {
//                return true;
//            }
//        }
//    }
//}

string toLowerWord(string word)
{
    string temp;

    for (int x = 0; x <= word.length(); x++)
    {
        temp += tolower(word[x]);
    }

    return temp;
}