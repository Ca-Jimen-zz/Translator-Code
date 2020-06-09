#include<iostream>
#include<fstream>
#include<string>
#include "scanner.cpp"
#include <stdlib.h>
#include <vector>
using namespace std;

/* INSTRUCTION:  copy your parser.cpp here
      cp ../ParserFiles/parser.cpp .
   Then, insert or append its contents into this file and edit.
   Complete all ** parts.
*/

//=================================================
// File translator.cpp written by Group Number: 7
//=================================================

// ----- Additions to the parser.cpp ---------------------

// ** Declare Lexicon (i.e. dictionary) that will hold the content of lexicon.txt
// Make sure it is easy and fast to look up the translation.
// Do not change the format or content of lexicon.txt 
//  Done by: ** 
void s();
void afterSubject();
void afterNoun();
void afterObject();
void noun();
void verb();
void be();
void tense();

ofstream outFile;

token_type saved_token;
string saved_lexeme;
bool  token_available = false;
bool set_trace = true;

string savedEword;
// table for translation
vector<string> wordJ ;
vector <string> wordE ;

// Tracing function - turns or or off tracing messages if user desires
// Done by: CJ
void tracing()
{
    string trace;
    cout << "Would you like tracing messages on or off? (type on or off) ";
    cin >> trace;
    while (trace != "on" && trace != "off")
    {
     cout << "\n Error: only on or off are accepted, try again. ";
     cin >> trace;
    }
    if (trace == "on")
    {
        set_trace = true;
    }
    else
    {
        set_trace = false;
    }
    return;
}

// ** Additions to parser.cpp here:
//    getEword() - using the current saved_lexeme, look up the English word
//                 in Lexicon if it is there -- save the result   
//                 in saved_E_word
void getEword()
{
  //outFile<< "GETTING EWORD USING:   "<< saved_lexeme <<endl;
  bool found = false;
  for(int a =0;a< wordJ.size(); a++)
    {
      if(wordJ[a]==saved_lexeme)
    {
      savedEword = wordE[a];
      found = true;
    }
    }
  if(found == false)
    {savedEword = saved_lexeme;}
  //outFile<<"new saved E word  "<< savedEword <<endl;
}
//  Done by: ** 
//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)
void gen(string line_type)
{
  if(line_type == "TENSE")
    {
        cout<< line_type<< "  "<< tokenName[saved_token] <<endl;
        outFile<< line_type<< "  "<< tokenName[saved_token] <<endl;
    

    }
  else{
      cout<< line_type<< "  "<< savedEword <<endl;
      outFile<< line_type<< "  "<< savedEword <<endl;
  }
}
//  Done by: ** 

// ----- Changes to the parser.cpp content ---------------------

// ** Comment update: Be sure to put the corresponding grammar 
//    rule with semantic routine calls
//    above each non-terminal function 

// ** Each non-terminal function should be calling
//    getEword and/or gen now.
//  Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.

// Done by: FJ
void syntax_error1(token_type expected, string saved_lexeme)
{
    cout<<"SYNTAX ERROR: expected "<< tokenName[expected]  << " but found "<<  saved_lexeme <<endl;
    exit (1);
}

// Done by: FJ
void syntax_error2(string saved_lexeme, string parserFunct)
{
    cout<<"SYNTAX ERROR: unexpected "<< saved_lexeme << " found in "<< parserFunct <<endl;
    exit (1);
}

//  Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme
// Done by: CJ
token_type next_token()
{
    if (!token_available)   // if there is no saved token
    {
      scanner(saved_token, saved_lexeme);  // calls scanner to grab new token
      cout<<"Scanner called using word: "<< saved_lexeme <<endl;
      token_available = true;
    }
    return saved_token;
}

// Done by: CJ
bool match(token_type expected)
{
    if (next_token() != expected)  // mismatch occurs with following token
      {
        syntax_error1(expected, saved_lexeme);// generates syntax error message
       

      }
    else  // match has occurred
      {
          token_available = false;
          if (set_trace == true)
           {
            cout<<"Matched "<< tokenName[expected] <<endl; //prints matched token type, if successful
           }
          return true;
      }
    return 0;
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: <story> ::= <s>{<s>}
// Done by: FJ
void story()
{
  if (set_trace == true)
  {
    cout<<"Processing <story>"<<endl;
  }
  s();
  //while()  call more s()
  while (true && (saved_lexeme != "eofm"))
    {
      //outFile<<endl;
      s();
    }
  cout<<"\nSuccessfully parsed <story>"<<endl;
}

// Grammar: <noun> ::= WORD1|PRONOUN
// Done by: FJ
void noun()
{
  if (set_trace == true)
  {
    cout<<"Processing <noun>"<<endl;
  }
  switch(next_token())  // looks ahead at next token
    {
    case  WORD1:
      match(WORD1);
      getEword();
      break;
    case  PRONOUN:
      match(PRONOUN);
      getEword();
      break;
    default:
      syntax_error2(saved_lexeme, "noun");
    }
}

// Grammar: <s> ::= [CONNECTOR]<noun>SUBJECT<after subject>
// Done by: FJ
void s()
{
  next_token();
  if(saved_lexeme != "eofm")
    {

      if (set_trace == true)
        {
         cout<<"Processing <s>"<<endl;
        }
  

  if(next_token() == CONNECTOR)
    {
      match(CONNECTOR);
      getEword();
      gen("CONNECTOR");
    }
  

  noun();
  match(SUBJECT);
  gen("ACTOR");
  afterSubject();

    }

}
// Grammar: <after subject> ::= <verb> <tense> PERIOD | <noun> <after noun>
// Done by: CJ
void afterSubject()
{
  if (set_trace == true)
  {
  cout<<"Processing <afterSubject>"<<endl;
  }
  switch(next_token())  // looks at next token
      {
    case  WORD2:
      verb();
      tense();
      match(PERIOD);
      break;
    case  WORD1:
      noun();
      afterNoun();
      break;
    case PRONOUN:
      noun();
      afterNoun();
      break;
    default:
      syntax_error2(saved_lexeme, "afterSubject");  // none found
      }
}

// Grammar: <verb> ::= WORD2
// Done by: CJ
void verb()
{
  if (set_trace == true)
  {
  cout<<"Processing <verb>"<<endl;
  }
  switch(next_token())  // look ahead at next token
    {
    case  WORD2:
      match(WORD2);
      getEword();
      gen("ACTION");
      break;
    default:
      syntax_error2(saved_lexeme, "verb");  // none found
    }
}

// Grammar: <be> ::= IS | WAS
// Done by: CS
void be()
{
  if (set_trace == true)
  {
  cout<<"Processing <be>"<<endl;
  gen("DESCRIPTION");
  }
  switch(next_token())  // looks at next token
    {
    case  IS:
      match(IS);
      gen("TENSE");
      break;
    case  WAS:
      match(WAS);
      gen("TENSE");
      break;
    default:
      syntax_error2(saved_lexeme, "be");  // none found
    }
}

// Grammar: <after noun> ::= <be> PERIOD  | DESTINATION <verb> <tense> PERIOD | OBJECT  <after object>
// Done by: CS
void afterNoun()
{
  if (set_trace == true)
  {
  cout<<"Processing <afterNoun>"<<endl;
  }
  

  switch(next_token())  // looks at next token
    {
    case  IS:
      be();
      match(PERIOD);
      break;
    case  WAS:
      be();
      match(PERIOD);
      break;
    case DESTINATION:
      match(DESTINATION);
      gen("TO");
      verb();
      tense();
      match(PERIOD);
      break;
    case OBJECT:
      match(OBJECT);
      gen("OBJECT");
      afterObject();
      break;
    default:
      syntax_error2(saved_lexeme, "afterNoun");  // none found
    }
  

}
// Grammar: <after object> ::= <verb><tense> PERIOD | <noun>DESTINATION <verb> <tense> PERIOD
// Done by: CS
void afterObject()
{
  if (set_trace == true)
  {
  cout<<"Processing <afterObject>"<<endl;
  }
  switch(next_token())
    {
    case WORD2:
      verb();
      tense();
      match(PERIOD);
      break;
    case WORD1:
      noun();
      match(DESTINATION);
      gen("TO");
      verb();
      tense();
      match(PERIOD);
      break;
    case PRONOUN:
      noun();
      match(DESTINATION);
      gen("TO");
      verb();
      tense();
      match(PERIOD);
      break;
    default:
      syntax_error2(saved_lexeme, "afterObject");  // none found
    }
}

// Grammar: <tense> ::= VERBPAST | VERBPASTNEG | VERB | VERBNEG
// Done by: CS
void tense()
{
  if (set_trace == true)
  {
  cout<<"Processing <tense>"<<endl;
  }
  switch(next_token())  // look ahead at next token
    {
    case  VERBPAST:
      match(VERBPAST);
      gen("TENSE");
      break;
    case  VERBPASTNEG:
      match(VERBPASTNEG);
      gen("TENSE");
      break;
    case  VERB:
      match(VERB);
      gen("TENSE");
      break;
    case  VERBNEG:
      match(VERBNEG);
      gen("TENSE");
      break;
    default:
      syntax_error2(saved_lexeme, "tense");  // none found
    }
}
//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by:  CS
int main()
{
  string filename;
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());
  tracing();

  // calls the <story> to start parsing
    story();
  // closes the input file
    fin.close();

}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
