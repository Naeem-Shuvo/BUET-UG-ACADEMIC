#include<bits/stdc++.h>
using namespace std;

const int INITIAL_SIZE = 13;
const double MAX_LOAD=0.5;
const double MIN_LOAD=0.25;
const int WORD_SIZE=10;

bool isPrime(int n){
    if(n<=1) return false;
    if(n<=3) return true;
    if(n%2==0 || n%3==0) return false;
    for(int i=5;i*i<=n;i+=6){
        if(n%i==0 || n%(i+2)==0) return false;
    }
    return true;
}

int nextPrime(int n){
    while(true){
        if(isPrime(n)) return n;
        n++;
    }
}

int prevPrime(int n){
    if(n <= 2) return 2;
    n--;
    while(n > 1){
        if(isPrime(n)) return n;
        n--;
    }
    return 2;
}

string randomWord(){
    string word="";
    for(int i=0;i<WORD_SIZE;i++){
        char ch='a'+rand()%26;
        word+=ch;
    }
    return word;
}

enum ResolutionMethod{CHAINING,DOUBLE_HASHING,CUSTOM_HASHING};
enum HashFuncType{HASH1,HASH2};

template<typename K, typename V>
class HashTable{
    private:
    struct Node{
        K key;
        V value;
        bool isDeleted;
        Node(K k,V v):key(k),value(v),isDeleted(false){}
    };
    
    vector<list<Node>> table; 
    vector<Node*> buckets;
    
    int currentSize;
    int elementCount;
    int initialSize;
    int countAtResize;
    int insertionsSinceResize;
    int deletionsSinceCompaction;
    bool isRehashing;

    ResolutionMethod method;
    HashFuncType funcType;

    const int c1 = 1;
    const int c2 = 3;
    
    long long totalCollisions;

    public:
    HashTable(int size=INITIAL_SIZE,ResolutionMethod m=CHAINING,HashFuncType f=HASH1)
        :currentSize(size),initialSize(size),method(m),funcType(f){
        elementCount=0;
        countAtResize=0;
        insertionsSinceResize=0;
        deletionsSinceCompaction=0;
        totalCollisions=0;
        isRehashing=false;
        
        if(method==CHAINING){
            table.resize(currentSize);
        }
        else{
            buckets.resize(currentSize,nullptr);
        }
    }
    
    ~HashTable(){
        for(auto p: buckets){
            if(p) delete p;
        }
    }
    
    long long getCollisions() const{
        return totalCollisions;
    }
    
    int getSize() const{
        return currentSize;
    }
    
    int getElementCount() const{
        return elementCount;
    }
    
    size_t hash1(const K& key){
        size_t hash = 0;
        size_t p = 31;
        for(char c : key){
            hash = hash * p + (c - 'a' + 1);
        }
        return hash % currentSize;
    }

    size_t hash2(const K& key){
        size_t hash=5381;
        for(char c:key){
            hash=((hash<<5)+hash) +c;
        }
        return hash%currentSize;
    }
    
    size_t auxHash(const K& key){
        size_t hash = 0;
        for(char c : key) hash = hash * 131 + c;
        size_t val = (hash % (currentSize - 1)) + 1;
        return val;
    }

    size_t getIndex(const K& key, int i){
        size_t h=(funcType==HASH1)?hash1(key):hash2(key);
        if(method==CHAINING) return h;
        
        size_t aux=auxHash(key);
        if(method==DOUBLE_HASHING) {
            return (h + i*aux) % currentSize;
        }
        else if(method==CUSTOM_HASHING){
            return (h + c1*i*aux + (long long)c2*i*i) % currentSize;
        }
        return h;
    }
    
    int search(K key){
        int hits=0;
        if(method==CHAINING){
            size_t idx=getIndex(key,0);
            hits=1;
            for(auto& node: table[idx]){
                if(node.key==key) return hits;
            }
        }
        else {
            int i=0;
            while(i<currentSize){
                hits++;
                size_t idx=getIndex(key,i);
                if(buckets[idx]==nullptr) return -1;
                if(!buckets[idx]->isDeleted && buckets[idx]->key==key) return hits;
                i++;
                if(i > currentSize * 2) return -1;
            }
        }
        return -1;
    }

    bool deleteKey(K key){
        if(method==CHAINING){
            size_t idx=getIndex(key,0);
            for(auto it=table[idx].begin(); it!=table[idx].end(); ++it){
                if(it->key==key){
                    table[idx].erase(it);
                    elementCount--;
                    if(!isRehashing) deletionsSinceCompaction++;
                    checkCompaction();
                    return true;
                }
            }
            return false;
        }
        else {
            int i=0;
            while(i<currentSize){
                size_t idx=getIndex(key,i);
                if(buckets[idx]==nullptr) return false;
                if(!buckets[idx]->isDeleted && buckets[idx]->key==key){
                    buckets[idx]->isDeleted=true;
                    elementCount--;
                    if(!isRehashing) deletionsSinceCompaction++;
                    checkCompaction();
                    return true;
                }
                i++;
            }
            return false;
        }
    }

    void checkCompaction(){
        if(isRehashing) return;
        if(currentSize <= initialSize) return;
        
        double loadFactor=(double)(elementCount)/currentSize;
        if(loadFactor < MIN_LOAD){
            if(deletionsSinceCompaction >= elementCount/2){
                int newSize=prevPrime(currentSize/2);
                if(newSize >= initialSize){
                    cout << "  [COMPACTING] Size: " << currentSize << " -> " << newSize 
                         << " (Load factor: " << fixed << setprecision(3) << loadFactor << ")" << endl;
                    rehash(newSize);
                    deletionsSinceCompaction=0;
                }
            }
        }
    }

    void insert(K key, V value){ 
        if(search(key)!=-1) return;
        
        if(!isRehashing){
            double loadFactor=(double)(elementCount)/currentSize;
            if(loadFactor > MAX_LOAD){
                if(insertionsSinceResize >= countAtResize/2){
                    int newsize=nextPrime(currentSize*2);
                    cout << "  [EXPANDING] Size: " << currentSize << " -> " << newsize 
                         << " (Load factor: " << fixed << setprecision(3) << loadFactor << ")" << endl;
                    rehash(newsize);
                }
            }
        }
        
        if(method==CHAINING){
            size_t idx=getIndex(key,0);
            if(!isRehashing && !table[idx].empty()){
                totalCollisions++;
            }
            table[idx].push_back(Node(key,value));
        }
        else {
            int i=0;
            while(i<currentSize){
                size_t idx=getIndex(key,i);
                if(!isRehashing && i==0 && buckets[idx]!=nullptr && !buckets[idx]->isDeleted){
                     totalCollisions++;
                }
                if(buckets[idx]==nullptr || buckets[idx]->isDeleted){ 
                    if(buckets[idx]) delete buckets[idx];
                    buckets[idx]=new Node(key,value);
                    break;
                }
                i++;
            }
        }
        elementCount++;
        if(!isRehashing) insertionsSinceResize++;
    }

    void rehash(int newSize){
        isRehashing = true;
        
        vector<list<Node>> oldTable=table;
        vector<Node*> oldBuckets=buckets;

        currentSize=newSize;
        countAtResize=elementCount;
        insertionsSinceResize=0;
        deletionsSinceCompaction=0;
        
        if(method==CHAINING){
            table.clear();
            table.resize(newSize);
            elementCount=0;
            for(auto& list:oldTable){
                for(auto& node: list){
                    insert(node.key,node.value);
                }
            }
        }
        else{
            buckets.clear();
            buckets.resize(newSize,nullptr);
            elementCount=0;
            for(auto p: oldBuckets){
                if(p && !p->isDeleted){
                    insert(p->key,p->value);
                    delete p;
                }
                else if(p){
                    delete p;
                }
            }
        }
        isRehashing = false;
    }
};

int main(){
    srand(time(0));
    
    cout << "\n========== TESTING DELETE AND COMPACTION FEATURES ==========\n\n";
    
    // Test 1: Expansion
    cout << "Test 1: Dynamic Expansion\n";
    cout << "--------------------------\n";
    HashTable<string,int> table1(13, CHAINING, HASH1);
    cout << "Initial size: " << table1.getSize() << ", Elements: " << table1.getElementCount() << endl;
    
    set<string> words;
    while(words.size() < 20){
        words.insert(randomWord());
    }
    vector<string> wordVec(words.begin(), words.end());
    
    cout << "\nInserting 20 words...\n";
    for(int i=0; i<20; i++){
        table1.insert(wordVec[i], i+1);
    }
    cout << "Final size: " << table1.getSize() << ", Elements: " << table1.getElementCount() << endl;
    
    // Test 2: Delete operation
    cout << "\n\nTest 2: Delete Operation\n";
    cout << "-------------------------\n";
    cout << "Before delete: " << wordVec[0] << " search result: " << table1.search(wordVec[0]) << endl;
    bool deleted = table1.deleteKey(wordVec[0]);
    cout << "Delete " << wordVec[0] << ": " << (deleted ? "Success" : "Failed") << endl;
    cout << "After delete: " << wordVec[0] << " search result: " << table1.search(wordVec[0]) << endl;
    cout << "Elements after delete: " << table1.getElementCount() << endl;
    
    // Test 3: Compaction
    cout << "\n\nTest 3: Table Compaction\n";
    cout << "-------------------------\n";
    HashTable<string,int> table2(13, DOUBLE_HASHING, HASH1);
    
    // Insert enough to trigger expansion
    set<string> words2;
    while(words2.size() < 30){
        words2.insert(randomWord());
    }
    vector<string> wordVec2(words2.begin(), words2.end());
    
    cout << "Inserting 30 words to trigger expansion...\n";
    for(int i=0; i<30; i++){
        table2.insert(wordVec2[i], i+1);
    }
    cout << "Size after insertions: " << table2.getSize() << ", Elements: " << table2.getElementCount() << endl;
    
    cout << "\nDeleting 25 words to trigger compaction...\n";
    for(int i=0; i<25; i++){
        table2.deleteKey(wordVec2[i]);
    }
    cout << "Size after deletions: " << table2.getSize() << ", Elements: " << table2.getElementCount() << endl;
    
    // Test 4: No compaction below initial size
    cout << "\n\nTest 4: No Compaction Below Initial Size\n";
    cout << "-------------------------------------------\n";
    HashTable<string,int> table3(13, CHAINING, HASH2);
    
    for(int i=0; i<5; i++){
        table3.insert(wordVec2[i], i+1);
    }
    cout << "Inserted 5 words. Size: " << table3.getSize() << ", Elements: " << table3.getElementCount() << endl;
    
    cout << "Deleting 4 words (should NOT trigger compaction)...\n";
    for(int i=0; i<4; i++){
        table3.deleteKey(wordVec2[i]);
    }
    cout << "Size after deletions: " << table3.getSize() << " (should still be " << INITIAL_SIZE << ")" << endl;
    cout << "Elements: " << table3.getElementCount() << endl;
    
    cout << "\n========== ALL TESTS COMPLETED ==========\n\n";
    
    return 0;
}
