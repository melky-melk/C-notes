#include<stdio.h> 

void RemoveChars(char *s, char c)
{
    int writer = 0, reader = 0;

    // increments the reader until there is no more until it hits the null character at the end 
    while (s[reader])
    {
        // if the current character is not the character we are looking to remove (the non remove character)
        if (s[reader]!=c) 
        {   
            // makes the index ahead the one that was previously there so
            // {'1', '2', '3', null} {null, '1', '2', '3'}
            s[writer++] = s[reader];
        }
        // if the character is not found then thus

        // then increments which one it is at 
        reader++;
    }

    s[writer]=0;

    //doesnt need to return because it is editing the pointer to the character array so its direct
}

int main(){
    return 0;
}