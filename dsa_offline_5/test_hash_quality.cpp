#include<bits/stdc++.h>
using namespace std;

/* Test hash function quality - should have 60%+ unique values for 10,000 keys */

string randomWord(int n){
    static const string alpha="abcdefghijklmnopqrstuvwxyz";
    string s;
    for(int i=0;i<n;i++)
        s.push_back(alpha[rand()%26]);
    return s;
}

// Hash1 - Polynomial rolling hash (djb2 variant)
size_t hash1(const string& key){
    size_t h=0;
    for(char c:key) h=(h*31+c);
    return h;
}

// Hash2 - FNV-1a style hash
size_t hash2(const string& key){
    size_t h=0;
    for(char c:key) h=((h<<5)+h)+c;  // h*33+c
    return h;
}

int main(){
    srand(time(0));
    
    const int WORDS = 10000;
    const int WORD_LENGTH = 10;
    
    // Generate unique random words
    unordered_set<string> used;
    vector<string> dataset;
    
    while(dataset.size() < WORDS){
        string w = randomWord(WORD_LENGTH);
        if(!used.count(w)){
            used.insert(w);
            dataset.push_back(w);
        }
    }
    
    cout << "\n=== Hash Function Quality Test ===" << endl;
    cout << "Testing with " << WORDS << " unique words of length " << WORD_LENGTH << endl;
    cout << "Requirement: At least 60% unique hash values (>= 6000)\n" << endl;
    
    // Test Hash1
    {
        set<size_t> uniqueHashes;
        for(const auto& word : dataset){
            uniqueHashes.insert(hash1(word));
        }
        
        double percentage = (double)uniqueHashes.size() / WORDS * 100.0;
        cout << "Hash1 (Polynomial Rolling Hash):" << endl;
        cout << "  Unique hash values: " << uniqueHashes.size() << " / " << WORDS << endl;
        cout << "  Percentage: " << fixed << setprecision(2) << percentage << "%" << endl;
        cout << "  Status: " << (percentage >= 60.0 ? "✓ PASS" : "✗ FAIL") << endl;
        cout << endl;
    }
    
    // Test Hash2
    {
        set<size_t> uniqueHashes;
        for(const auto& word : dataset){
            uniqueHashes.insert(hash2(word));
        }
        
        double percentage = (double)uniqueHashes.size() / WORDS * 100.0;
        cout << "Hash2 (FNV-1a Style Hash):" << endl;
        cout << "  Unique hash values: " << uniqueHashes.size() << " / " << WORDS << endl;
        cout << "  Percentage: " << fixed << setprecision(2) << percentage << "%" << endl;
        cout << "  Status: " << (percentage >= 60.0 ? "✓ PASS" : "✗ FAIL") << endl;
        cout << endl;
    }
    
    return 0;
}
