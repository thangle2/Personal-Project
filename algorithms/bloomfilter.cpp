
// Copyright Tiffany Lukmantara 2021 tiffaluk@bu.edu
// Copyright Thang Le 2021 thangle2@bu.edu

/* To take advantage of all memory, instead of using just 2 characters 'T' and 'F' to indicate presence
   of string item, this bloom filter sets one bit per hash function within the character (8 bits/ char). 
   This allows for a bloom filter with larger length, hence reducing collision and the probability of false positives. The
   hash functions created were inspired by: https://cp-algorithms.com/string/string-hashing.html. However,
   instead of using powers, we multiplied the ascii value by i and a prime number constant. This is because the
   running sum of powers was generating too large of numbers to fit in long long int. A prime number constant was
   selected because a prime number is only divisible by itself and 1. This makes the distribution of hash values
   more uniform. The number of hash functions used was determined through trial and error. (A formula was found 
   online for the optimal number of hash functions but it requires knowledge of the size of the input set.)
*/

#include "BloomFilter.h"

// #include <iostream> this was used for cout and debugging code

const int p = 13;    // Prime number used for hash function 

// Constructor
BloomFilter::BloomFilter(int len){
    this->length = len*8;           //8 bits per 1 byte, 1 char = 1 byte
    char * temp = new char;         //dynamically allocating memory for bloom filter
    this->bf = temp;
    for (int i = 0; i < len; i++) 
    {
        *temp = (char)0;            //set all characters in bloom filter to null
        temp++;
    }
}

// Defining the 3 hash functions used for the bloom filter
int hash1(string s, int slen, int bflen){ 
    long long int h = 0;

    for (int i = 0; i < slen; i++)
    {
        h += (int)s[i] * p * (i+1); //take ascii value of each character in the string item 
                                    //and multiply by prime constant p = 13 and i to give different
                                    //weights to characters depending on order
        //h += (int)s[i] * pow(this->p, i+1);
    }

    h = h%bflen;                    //take modulo bloom filter length
    return h;
}

int hash2(string s, int slen, int bflen){
    long long int h = 0;

    for (int i = 0; i < slen; i++)
    {
        h += (int)s[i] * p * (i +1);
        //h += (int)s[i] * pow(this->p, i+1);
    }
    h = (11 + h)%bflen;         // add 11 to avoid collision
    return h;
}

int hash3(string s, int slen, int bflen){
    long long int h = 0;

    for (int i = 0; i < slen; i++)
    {
        h += (int)s[i] * p * (i+1);
        //h += (int)s[i] * pow(this->p, i+1);
    }
    h = (17 + h)%bflen;         // add 17 to differ from previous hash
    return h;
}

// Insert item into bloom filter
void BloomFilter::insert(string item) {
    int len = item.length();
    // cout<<len<<endl;

    // Calculating hashes for string item
    int h1 = hash1(item, len, this->length); 
    int h2 = hash2(item, len, this->length);
    int h3 = hash3(item, len, this->length);
     // cout<<h1<<" "<<h2<<" "<<h3<<endl;

    // Finding corresponding characters in bloom filter
    unsigned int c1 = this->bf[h1/8];
    unsigned int c2 = this->bf[h2/8];
    unsigned int c3 = this->bf[h3/8];
    // cout<<this->bf[h1/8]<<" "<<this->bf[h2/8]<<" "<<this->bf[h3/8]<<endl;
    // cout<<c1<<" "<<c2<<" "<<c3<<endl;

    // Checking if hashes fall under the same character 
    if (h1/8 == h2/8 && h1/8 == h3/8)
    {
        c1 |= 1 << (h1%8);
        c1 |= 1 << (h2%8);
        c1 |= 1 << (h3%8); 

        this->bf[h1/8] = (char)c1;

    }
    else if (h1/8 == h2/8)
    {
        c1 |= 1 << (h1%8);
        c1 |= 1 << (h2%8);
        c3 |= 1 << (h3%8);

        this->bf[h1/8] = (char)c1;
        this->bf[h3/8] = (char)c3;
    }
    else if (h1/8 == h3/8)
    {
        c1 |= 1 << (h1%8);
        c2 |= 1 << (h2%8);
        c1 |= 1 << (h3%8);

        this->bf[h1/8] = (char)c1;
        this->bf[h2/8] = (char)c2;
    }
    else if (h2/8 == h3/8)
    {
        c1 |= 1 << (h1%8);
        c2 |= 1 << (h2%8);
        c2 |= 1 << (h3%8);

        this->bf[h1/8] = (char)c1;
        this->bf[h2/8] = (char)c2;
    }
    else
    {
        c1 |= 1 << (h1%8);
        c2 |= 1 << (h2%8);
        c3 |= 1 << (h3%8);

        this->bf[h1/8] = (char)c1;
        this->bf[h2/8] = (char)c2;
        this->bf[h3/8] = (char)c3;
    }

    // cout<<c1<<" "<<c2<<" "<<c3<<endl;


}

// Check if item exists in bloom filter
bool BloomFilter::exists(string item){
    int len = item.length();

    // Calculating hashes for string item
    int h1 = hash1(item, len, this->length);
    int h2 = hash2(item, len, this->length);
    int h3 = hash3(item, len, this->length);

    // cout<<h1<<" "<<h2<<" "<<h3<<endl;

    // Finding corresponding characters in bloom filter 
    unsigned int c1 = this->bf[h1/8];
    unsigned int c2 = this->bf[h2/8];
    unsigned int c3 = this->bf[h3/8];

    // cout<<c1<<" "<<c2<<" "<<c3<<endl;

    // Checking if bits are set in corresponding characters
    if ((c1 & (1 << (h1%8))) && (c2 & (1 << (h2%8))) && (c3 & (1 << (h3%8))))
        return true; // item may be in bloom filter
    else
        return false; // item is not in bloom filter
}

// Return string version of bloom filter
string BloomFilter::output(){
     string s ="";
    for (int i = 0; i < this->length/8; i++)
    {
        s = s + *(this->bf + i);
    }
    return s;
}
