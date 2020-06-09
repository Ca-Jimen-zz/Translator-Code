#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//=====================================================
// File scanner.cpp written by: Group Number: 7
//                    member A: Fernando Juarez
//                    member B: Carlos Jimenez
//                    member C: Christopher Still
//=====================================================

// --------- DFAs ---------------------------------

// MYTOKEN DFA to be replaced by the WORD DFA
// ** Done by: CJ and FJ
bool mytoken(string s)
{
  int state = 0;
  int charpos = 0;

  while (s[charpos] != '\0')
    {
      
    // State Q0 - FJ
      if (state == 0 && (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'h' || s[charpos] == 'k' || s[charpos] == 'm' || s[charpos] == 'n' || s[charpos] == 'p' || s[charpos] == 'r') )
        {state = 1;}
      else if(state == 0 && (s[charpos] == 'a' || s[charpos] == 'i' || s[charpos] == 'u' || s[charpos] == 'e' || s[charpos] == 'o' || s[charpos] == 'I' || s[charpos] == 'E'))
        { state = 2;}
      else if(state == 0 && (s[charpos] == 'd' || s[charpos] == 'j' || s[charpos] == 'w' || s[charpos] == 'y' || s[charpos] == 'z'))
        { state = 3;}
      else if(state == 0 && s[charpos] == 's')
        { state = 4;}
      else if(state == 0 && s[charpos] == 't')
        { state = 5;}
      else if(state == 0 && s[charpos] == 'c')
        { state = 6;}
      else
         { // State Qcon1 - FJ
          if (state == 1 && (s[charpos] == 'a' || s[charpos] == 'i' || s[charpos] == 'u' || s[charpos] == 'e' || s[charpos] == 'o' || s[charpos] == 'I' || s[charpos] == 'E'))
          {state = 2;}
          else if(state == 1 && s[charpos] == 'y')
          { state = 3;}
          else
            { // State Q0 - CJ
              if(state == 2 && s[charpos] == 'n')
                { state = 0; }
               else if (state == 2 && (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'h' || s[charpos] == 'k' || s[charpos] == 'm' || s[charpos] == 'n' || s[charpos] == 'p' || s[charpos] == 'r') )
                {state = 3;}
              else if(state == 2 && (s[charpos] == 'a' || s[charpos] == 'i' || s[charpos] == 'u' || s[charpos] == 'e' || s[charpos] == 'o' || s[charpos] == 'I' || s[charpos] == 'E'))
                { state = 2;}
              else if(state == 2 && (s[charpos] == 'd' || s[charpos] == 'j' || s[charpos] == 'w' || s[charpos] == 'y' || s[charpos] == 'z'))
                { state = 3;}
              else if(state == 2 && s[charpos] == 's')
                { state = 4;}
              else if(state == 2 && s[charpos] == 't')
                { state = 5;}
              else if(state == 2 && s[charpos] == 'c')
                { state = 6;}
              else
                { // State Qcon - CJ
                  if(state == 3 && (s[charpos] == 'a' || s[charpos] == 'i' || s[charpos] == 'u' || s[charpos] == 'e' || s[charpos] == 'o' || s[charpos] == 'I' || s[charpos] == 'E'))
                    { state = 2;}
                  else
                    { // State QS - CJ
                      if(state == 4 && (s[charpos] == 'a' || s[charpos] == 'i' || s[charpos] == 'u' || s[charpos] == 'e' || s[charpos] == 'o' || s[charpos] == 'I' || s[charpos] == 'E'))
                      { state = 2;}
                      else if(state == 4 && s[charpos] == 'h')
                      { state = 3;}
                      else
                      { // State QT - CJ
                        if(state == 5 && (s[charpos] == 'a' || s[charpos] == 'i' || s[charpos] == 'u' || s[charpos] == 'e' || s[charpos] == 'o' || s[charpos] == 'I' || s[charpos] == 'E'))
                          { state = 2;}
                        else if(state == 5 && s[charpos] == 's')
                          { state = 3;}
                        else
                          { // State QC - CJ
                            if(state == 6 && s[charpos] == 'h')
                              { state = 3;}
                            else
                              {
                              return false;}
                          }
                      }
                  }
                }
            }
         }
    charpos++;

    }//end of while

  if (state == 0 || state == 2)
  {
      return(true);// return true if states are in the given range
  }
  else return(false);// else return false
}


// ** Add the PERIOD DFA here - CS
bool periodtoken(string s)
{
    int state = 0;
    int charpos = 0;

    //checks each character of the word for a single period "."
    while (s[charpos] != '\0')
    {
        if (state == 0 && s[charpos] == '.')
            state = 1;// given conditions for state to be 1
        else
            return(false);

        ++charpos;
    }

    if (state == 1) return(true);
    else return(false);
}
                                                                                                                                                 
// ** Done by: CS

// -----  Three Tables -------------------------------------
// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, etc.
enum token_type { WORD1, WORD2, PERIOD, ERROR, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR };
//word1, word2, in tokentype enum
string tokenName[30] = { "WORD1", "WORD2", "PERIOD", "ERROR", "VERB", "VERBNEG","VERBPAST","VERBPASTNEG","IS","WAS", "OBJECT", "SUBJECT","DESTINATION", "PRONOUN", "CONNECTOR" };

// ** Need the reservedwords table to be set up here.
// ** Do not require any file input for this.
// ** a.out should work without any additional files.
struct reserved
{
  const char* string;
  token_type tokenT;
}

//reserved table including strings and tokentypes as instructed
reserved[] = {
  { "masu",VERB},
  {"masen",VERBNEG},
  {"mashita",VERBPAST},
  {"masendeshita",VERBPASTNEG},
  {"desu",IS},
  {"deshita",WAS},
  {"o", OBJECT},
  {"wa", SUBJECT},
  {"ni", DESTINATION},
  {"watashi",PRONOUN},
  {"anata",PRONOUN},
  {"kare",PRONOUN},
  {"kanojo", PRONOUN},
  {"sore", PRONOUN},
  {"mata",CONNECTOR},
  {"soshite", CONNECTOR},
  {"shikashi", CONNECTOR},
  { "dakara", CONNECTOR}
};

// ------------ Scaner and Driver -----------------------

ifstream fin;  // global ifstream for reading from the input file

// Scanner handles one word each time it is called
// Then Identifies the token type and the word
// ** Done by: FJ
int scanner(token_type& a, string& w)
{
    // ** Grab the next word from the file via fin
    // 1. If it is eofm, return right now.
    // Grabs next word from the file via fin
    fin >> w;

    /*  **
    2. Call the token functions (word and period)
       one after another (if-then-else).
       Generate a lexical error message if both DFAs failed.
       Let the tokentype be ERROR in that case.

    3. If it was a word,
       check against the reservedwords list.
       If not reserved, tokentype is WORD1 or WORD2
       decided based on the last character.

    4. Return the token type & string  (pass by reference)
    */

    int rowCount = sizeof reserved/ sizeof reserved[0];
        cout<<"\n";

    if(mytoken(w)) //calls for token function one after another
      {
        for (int i = 0; i < rowCount; i++)
        {
          if (w == reserved[i].string) //checks against reservedword list
            {
                a = reserved[i].tokenT;
                return 0;
            }
        }
        
        char lastLetter = ' ';
          lastLetter = w[(w.length()-1)];

          //if not reserved then either word1 or word2
        if (lastLetter == 'I' || lastLetter == 'E')
          {
        a = WORD2;
          }
        else
          {
        a = WORD1;
          }

    }
    else if(periodtoken(w)) //checks step 2, part 2 of code
      {
        a = PERIOD;
      }
    else if(w == "eofm")
      {
      }
    else
      {
        cout << "LEXICAL ERROR: "<< w <<" is not a valid token \n";// DFA's failed
        a = ERROR;
      }


    return 0;
}//the end of scanner



// The temporary test driver to just call the scanner repeatedly
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!!
// Done by:  Rika
/*int main()
{
  tokentype thetype;
  string theword;
  string filename;

  cout << "Enter the input file name: ";
  cin >> filename;

  fin.open(filename.c_str());

  // the loop continues until eofm is returned.
   while (true)
    {
       scanner(thetype, theword);  // call the scanner
       if (theword == "eofm") break;  // stop now

       cout << "Type is:" << tokenName[thetype] << endl;
       cout << "Word is:" << theword << endl;
    }

   cout << "End of file is encountered." << endl;
   fin.close();

}// end
*/
