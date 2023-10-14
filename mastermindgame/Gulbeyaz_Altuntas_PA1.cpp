#include <iostream>
#include <time.h>
#include <ctype.h>
#include <cstring>
#include <cstdlib>

using namespace std;

int get_rand_number(int n);
bool is_digits(string str);
void for_entered_r(int num, int digit, int check, int iterations);
void for_entered_u(int number, int check, int iterations);


int main(int argc, char * argv[]){

    int check = 0;
    int iterations = 1;

    if (argc > 1 && (strcmp(argv[1],"-r")) == 0){ //  ENTERED "-r"
               if (!isdigit(argv[2][0])) // check to see if the entered is a number
            {
                cout << "E2" << endl;
                exit(0);
            }
            else{
                int digit = stoi(argv[2]);
                if(digit < 1 || digit > 9){  // if it's a number it should be digit 
                    cout << "E1" << endl,
                    exit(0);
                }
                else{
                    int num = get_rand_number(digit);
                     for_entered_r(num, digit, check, iterations); // calling the function for the first time
                        while(check != 1){
                             iterations++;
                             for_entered_r(num, digit, check, iterations);       
                        }
                    }
            }
        }

    if (argc > 1 && (strcmp(argv[1],"-u")) == 0){  // ENTERED "-u"
         if (!isdigit(argv[2][0])) // check to see if the entered is a number
            {
                cout << "E2" << endl;
                exit(0);
            }
            else{
                string number_x = argv[2];
                if(is_digits(number_x) == false){ cout << "E2" << endl; exit(0);  } // if there is any char in it we give an E2 error
                if (number_x[0] == '0') {cout << "E0" << endl; exit(0);} // if it starts with '0'
                int number = atoi(argv[2]);  // assign the input to a number        
                for_entered_u(number, check, iterations);
                while(check != 1){
                             iterations++;
                             for_entered_u(number, check, iterations);   
                        }
            }
        }
       
        return 0;
}

/********************************* WHEN THE USER ENTERS "-r" **********************/

void for_entered_r(int num, int digit, int check, int iterations){

int count = 0;
int apart[digit]; // this apart[digit] devides the given number to its digits

for(int i = digit-1; i >= 0; i--){ apart[i] = num % 10; num = num / 10; }

    string guess; // taking our guess as a string so if user uses any char we can check the errors with is_digits
    cin >> guess;
    is_digits(guess);
    if(is_digits(guess) == false){ cout << "E0" << endl; exit(0);  }

int guess_num = stoi(guess); // turning the char into int using stoi if input is full of digits 
int check_digit = 0; // if the given number doesn't have the same digit as the "N" we entered then it will print an E1 error and exit
int temp; // created a temp to check if they have the same amount of integers
temp = guess_num; 

while (temp > 0) { int mod = temp % 10; temp /= 10; check_digit++; }
    
    if(check_digit != digit){
    cout << "E0" << endl;
        exit(0);
}

// C EXACT - true place numbers

int guess_apart[digit];

for (int i = digit-1; i >= 0; i--){ guess_apart[i] = guess_num % 10; guess_num /= 10;}

for(int i = 0; i < digit; i++){
    for(int j = i+1; j < digit; j++){
         if (guess_apart[i] == guess_apart[j]){
        cout << "E0" << endl;
        exit(0);
          }
    }
}

for(int i = 0; i < digit; i++){ // compare the two arrays and count the number of matching elements
    if (apart[i] == guess_apart[i]){
        count++;
    }
}

if (count == digit){ // if our digits and the count is the same number then it means we found it
    check = 1;
    cout << "FOUND " << iterations << endl;
    exit(0);
}

if(iterations == 100){ 
    cout << "FAILED" << endl;
    exit(0);
}

cout << count << " ";

// C MISPLACED - misplaced numbers

int counter = 0;

    for(int i = 0; i < digit; i++){
        for (int j = 0; j < digit; j++){
             if (apart[i] == guess_apart[j]){ // if they are the same we counter++
                 counter++; 
                }     
            }
            if (apart[i] == guess_apart[i]){ // if it's the exact places we take the counter-- to not count them as misplaced
                counter--;
             } 
     }

    cout << counter << endl;

}



/***************************************  WHEN THE USER ENTERS "-u" ********************************/


void for_entered_u(int number, int check, int iterations){

int k = 0;
int number_array[10] = {0};

while(number > 0) { int mod = number % 10; number_array[k] = mod; k++;  number = number / 10; } // diveding the number and putting it in an array
 
    for(int i = 0; i < k-1; i++){
        for(int j = i+1; j < k; j++){
                if(number_array[i] == number_array[j]){  // if the numbers are not unique we will give error
                cout << "E0" << endl;
                exit(0);
            }
        }
    }

    string guess; //taking the guessed number as a string so if we put any char we can check the errors using is_digits
    cin >> guess;
    is_digits(guess);

    if(is_digits(guess) == false){
         cout << "E0" << endl;
             exit(0);
    }

int guess_num = stoi(guess); // turning the char into int using stoi if input is full of digits 

// if the given number doesn't have the same digit as the "N" we entered then it will print an E1 error and exit
 
int check_digit = 0;
int temp = guess_num; // created a temp to check if they have the same amount of integers

while (temp > 0) { int mod = temp % 10 ; temp /= 10; check_digit++; }

if(check_digit != k){
    cout << "E0" << endl;
    exit(0);
}

// C EXACT - true place numbers

int guess_apart[k]; 
int count = 0;

for (int i = 0; i <k ; i++){  guess_apart[i] = guess_num % 10;  guess_num /= 10;}

    for(int i = 0; i < k; i++){
     for(int j = i+1; j < k; j++){
           if (guess_apart[i] == guess_apart[j]){
         cout << "E0" << endl;
            exit(0);
          }
     }
    }

    for(int i = 0; i < k; i++){ // compare the two arrays and count the number of matching elements
         if ( guess_apart[i] == number_array[i]){
          count++;
         }
        }
        if (count == k){
         cout << "FOUND " << iterations << endl;
         exit(0);
        }
    if (iterations == 100){
    cout << "FAILED " << endl;
    exit(0);
    }
    cout << count << " ";

// C MISPLACED  - misplaced numbers

int counter = 0;
    for(int i = 0; i < k; i++){
          for (int j = 0; j < k; j++)
             {
                   if (number_array[i] == guess_apart[j]){
                         counter++;
                   }
              }
            if (number_array[i]== guess_apart[i]){ // if they are on the same place then we take counter as to not count them 
                         counter--;     
                }
     } 
    cout << counter << endl;

}


int get_rand_number(int n){

    int digits[10] = {0}; // array to keep track of used digits
    int num = 0; 
    srand(time(NULL)); 
    
    int digit = rand() % 9 + 1; // generate the first digit since it can't be 0 
    digits[digit] = 1;
    num += digit;
    
    for (int i = 1; i < n; i++) { // generate the other digits
        digit = rand() % 10;
        while (digits[digit]) {
            digit = rand() % 10;
        }
        digits[digit] = 1;
        num = num * 10 + digit;
    }
    return num;
}

bool is_digits(string str){ //checking if any of our inputs have char in them 
    for (char ch : str) {
        int v = ch; // ASCII values 
        if (!(ch >= 48 && ch <= 57)) {
              return false;
        }
            }
            return true;
}
