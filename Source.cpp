#include<iostream>
#include<stack>
#include<string>

using namespace std;

void printStack(std::stack<int> s)
{
    cout << "current stack: ";
    while (!s.empty())
    {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;
}

int CurrentSymbolFunction(char currentsymbolvar)
{
    int currentSymbolIndex = 0;
    switch (currentsymbolvar) {
    case 'i':
        currentSymbolIndex = 0;
        break;
    case '+':
        currentSymbolIndex = 1;
        break;
    case '-':
        currentSymbolIndex = 2;
        break;
    case '*':
        currentSymbolIndex = 3;
        break;
    case '/':
        currentSymbolIndex = 4;
        break;
    case '(':
        currentSymbolIndex = 5;
        break;
    case ')':
        currentSymbolIndex = 6;
        break;
    case '$':
        currentSymbolIndex = 7;
        break;
    case 'E':
        currentSymbolIndex = 8;
        break;
    case 'T':
        currentSymbolIndex = 9;
        break;
    case 'F':
        currentSymbolIndex = 10;
        break;
    default:
        cout << "Invalid input symbol: " << currentsymbolvar << endl;
        return false;
    }
    return currentSymbolIndex;
}



const int Parsing_Table[][11] = {

    //Current Symbol i =0, + =1, - =2, * =3 , / =4, ( =5, ) =6, $ =7 , E = 8 , T = 9 , F = 10

    {5,-10,-10,-10,-10,4,-10,-10,1,2,3},			//State 0

    {-10,6,7,-10,-10,-10,-10,100,-10,-10,-10},	    	//State 1

    {-10,-2,-2,8,9,-10,-2,-2,-10,-10,-10},		//State 2

    {-10,-2,-2,-2,-2,-10,-2,-2,-10,-10,-10},	    //State 3

    {5,-10,-10,-10,-10,4,-10,-10,10,2,3},			//state 4	

    {-10,-2,-2,-2,-2,-10,-2,-2,-10,-10,-10},  	//State 5

    {5,-10,-10,-10,-10,4,-10,-10,-10,11,3},			//State 6

    {5,-10,-10,-10,-10,4,-10,-10,-10,12,3},			//State 7

    {5,-10,-10,-10,-10,4,-10,-10,-10,-10,13},			//State 8

    {5,-10,-10,-10,-10,4,-10,-10,-10,-10,14},			//State 9

    {-10,6,7,-10,-10,-10,15,-10,-10,-10,-10},			//State 10

    {-10,-6,-6,8,9,-10,-6,-6,-10,-10,-10},		//State 11

    {0,-6,-6,8,9,0,-6,-6,0,0,0},		//State 12

    {0,-6,-6,-6,-6,0,-6,-6,0,0,0},	    //State 13

    {0,-6,-6,-6,-6,0,-6,-6,0,0,0},	    //State 14

    {0,-6,-6,-6,-6,0,-6,-6,0,0,0},	    //State 15

};


bool ParsingString(const string& inputString) {

    stack<int> stateStack;
    //stack<char> symbolStack;
    int index = 0;
    int currentState = 0;
    stateStack.push(currentState);

    char currentSymbol = inputString[index];
    int currentSymbolIndex = -1;

    currentSymbolIndex = CurrentSymbolFunction(currentSymbol);
    int action = Parsing_Table[currentState][currentSymbolIndex];

    while (index < inputString.length()) {

        cout << "current cordinets are x: " << currentState << " y: " << currentSymbolIndex << endl << endl;
        //Determind if the action is a shift or a reduction
        if (currentState == 1 && currentSymbolIndex == 7) {
            cout << "This string is valid!";
            return true;
        }
        if (-1 < currentState < 16)
        {
            //push values into stack
            stateStack.pop();
            stateStack.push(currentState);
            stateStack.push(currentSymbolIndex);
            stateStack.push(action);
            cout << "This is the Stack in the Shift section: ";
            printStack(stateStack);

            //increase index to change the Y cordinate
            index++;
            currentSymbol = inputString[index];
            currentSymbolIndex = CurrentSymbolFunction(currentSymbol);
            currentState = stateStack.top();

            //get next action to determine if action is it a shift or a reduction
            action = Parsing_Table[currentState][currentSymbolIndex];
            cout << "current cordinets are IN SHIFT FUNCTION x: " << currentState << " y: " << currentSymbolIndex << endl;
            cout << "This action at the end of the shift fuction: " << action << endl << endl;
        }
        while (0 > action && action != -10) {        //while action is reduction
            
            stateStack.pop();
            stateStack.push(currentState);
            int production = -action;


            for (int j = 0; j < production; j++) {
                stateStack.pop();
            }
            cout << "This is the Stack in the Reduction section AFTER POP: ";
            printStack(stateStack);
            
            //Check current state and check what rule it is, Change SymbolIndex into E,T,or F 
            if (currentState == 11 || currentState == 12 || currentState == 2)
            {
                currentSymbolIndex = CurrentSymbolFunction('E');
            }
            else if (currentState == 13 || currentState == 14 || currentState == 3)
            {
                currentSymbolIndex = CurrentSymbolFunction('T');
            }
            else if (currentState == 5 || currentState == 15 )
            {
                currentSymbolIndex = CurrentSymbolFunction('F');
            }
            currentState = stateStack.top();
            stateStack.pop();
            cout << "current cordinets in REDUCTION SECTION before action x: " << currentState << " y: " << currentSymbolIndex << endl ;
            action = Parsing_Table[currentState][currentSymbolIndex];
            

            //push values into stack
            stateStack.push(currentState);
            stateStack.push(currentSymbolIndex);
            stateStack.push(action);
            cout << "This is the Stack in the Reduction section AFTER PUSH: ";
            printStack(stateStack);
            
            cout << "Current action before breaking out of loop or going to if statement in reduction: " << action << endl;
            cout << "current cordinets in REDUCTION SECTION x: " << currentState << " y: " << currentSymbolIndex << endl << endl;
            
            //GOTO function
            if (action == 1 || action == 2 || action == 3 ||
                action == 10 || action == 11 || action == 12 ||
                action == 14 || action == 13)
            {
                //Get the action with ETF
                currentState = stateStack.top();
                stateStack.pop();
                currentSymbol = inputString[index];
                currentSymbolIndex = CurrentSymbolFunction(currentSymbol);
                cout << "current cordinets in REDUCTION SECTION(E,T,F section) x: " << currentState << " y: " << currentSymbolIndex << endl << endl;
                

                action = Parsing_Table[action][currentSymbolIndex];
                //Current state is top
                cout << "Current symbol index (y) in GOTO function: " << currentSymbolIndex << endl;
                stateStack.push(currentState);
                cout << "This is the Stack in the Reduction section(E,T,F section): ";
                printStack(stateStack);
                cout << "current cordinets in REDUCTION SECTION(E,T,F section) x: " << currentState << " y: " << currentSymbolIndex << endl << endl;
                
            }



        }

    }
    cout << "This string is NOT valid";
    return false;
}



int main() {

    ParsingString("(i*)$");

    return 0;
}








