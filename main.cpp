#include <map>
#include <cstdio>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

const int MINUTESPERHOUR = 60;
const int HOURESPERDAY   = 24;
const int DAYSPERWEEK    =  7;
const int MONTHSPERYEAR  = 12;
const int DAYSPERMONTH   = 31;

vector< string > split( const string& value, const char delimiter )
{
	vector< string > result;

	string token = "";

	stringstream stream( value );

    while( getline( stream, token, delimiter ) )
    {
        result.push_back( token );
    }

    return result;
}

string expand( const string& expression )
{
	string result = "";

    if ( expression.find( "-" ) not_eq string::npos )
    {
		vector< string > rangearray = split( expression, '-' );

		int start = stoi( rangearray[ 0 ] );
		int stop = stoi( rangearray[ 1 ] );

	    for(int index = start; index <= stop; index++ )
	    {
	        result.append( to_string( index ) + "," );
	    }
	}
	else
	{
        result = expression + ",";
	}

    return result;
}

vector< string > parse(string expression, int maximum, int minimum)
{
	vector< string > subexpressions;

	if ( expression.find( "," ) not_eq string::npos )
	{
		subexpressions = split( expression, ',' );
	}
	else
	{
	    subexpressions.push_back(expression);
	}

	string rangeitems;

	for (const auto& subexpression : subexpressions)
	{
	    if (subexpression.find("/") not_eq string::npos) // handle */N syntax
	    {
	        for (int a = 1; a <= maximum; a++)
	        {
	            if (a % stoi(subexpression.substr(subexpression.find("/")+1)) == 0)
	            {
	                if(a == maximum)
	                {
	                    rangeitems.append(to_string(minimum));
	                }
	                else
	                {
	                    rangeitems.append(to_string(a));
	                }

	                rangeitems.append(",");
	            }
	        }
	    }
	    else
	    {
	        if(subexpression == "*")
	        {
	        	rangeitems.append(expand(to_string(minimum) + "-" + to_string(maximum)));
	        } 
	        else
	        {
	            rangeitems.append(expand(subexpression));
	        }
	    }
	}

   return split( rangeitems, ',' );
}

int main( int argc, char** argv )
{
	//bug: 3-59/15

	auto result = parse("3-59/15", MINUTESPERHOUR, 0);

	cout << "size: " << result.size( ) << endl;

	for (auto item : result)
	{
		cout << "first: " << item << endl;
	}

	return EXIT_SUCCESS;
}