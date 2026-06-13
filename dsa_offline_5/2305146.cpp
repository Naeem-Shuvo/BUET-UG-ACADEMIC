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
            for(auto& node: table[idx]){
                hits++;
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
        if(currentSize <= initialSize) return;  // Don't compact below initial size
        
        double loadFactor=(double)(elementCount)/currentSize;
        if(loadFactor < MIN_LOAD){
            if(deletionsSinceCompaction >= elementCount/2){
                int newSize=prevPrime(currentSize/2);
                if(newSize >= initialSize){
                    rehash(newSize);
                    deletionsSinceCompaction=0;
                }
            }
        }
    }

    void insert(K key, V value){ 
        if(search(key)!=-1) return;
        
        
        if(!isRehashing){
            double loadFactor=(double)(elementCount + 1)/currentSize;
            if(loadFactor > MAX_LOAD){
                if(insertionsSinceResize >= countAtResize/2){
                    int newsize=nextPrime(currentSize*2);
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
                
                if(!isRehashing && i > 0){
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
    int N=10000; 

    
    set<string> uniqueWords;
    while(uniqueWords.size() < N){
        string word = randomWord();
        uniqueWords.insert(word);
    }
    vector<string> words(uniqueWords.begin(), uniqueWords.end());
    
    vector<string> searchWords;
    for(int i=0; i<1000; i++){
        searchWords.push_back(words[rand() % N]);
    }

    
    const int nameWidth = 20; 
    const int colWidth = 15; 
    const int hitWidth = 15; 
    const string sep = "    ";

    
    cout << "\n";
    cout << left << setw(nameWidth) << " " 
         << sep << right << setw(colWidth + hitWidth + sep.length()) << "Hash 1" 
         << sep << right << setw(colWidth + hitWidth + sep.length()) << "Hash 2" << endl;

    
    cout << left << setw(nameWidth) << "Method" 
         << sep << right << setw(colWidth) << "Collisions" << sep << setw(hitWidth) << "Avg Hits"
         << sep << right << setw(colWidth) << "Collisions" << sep << setw(hitWidth) << "Avg Hits" << endl;
    cout << endl; 
    
    ResolutionMethod methods[] = {CHAINING, DOUBLE_HASHING, CUSTOM_HASHING};
    string methodNames[] = {"Chaining Method", "Double Hashing", "Custom Probing"};

    for(int m=0; m<3; m++){
        long long coll1 = 0, coll2 = 0;
        double avgHits1 = 0.0, avgHits2 = 0.0;
        
        {
            HashTable<string,int> table(13, methods[m], HASH1);
            for(int i=0; i<N; i++) table.insert(words[i], i+1);
            
            long long totalHits = 0;
            for(auto& word : searchWords){
                int h = table.search(word);
                if(h != -1) totalHits += h;
            }
            coll1 = table.getCollisions();
            avgHits1 = (double)totalHits / searchWords.size();
        }

        {
            HashTable<string,int> table(13, methods[m], HASH2);
            for(int i=0; i<N; i++) table.insert(words[i], i+1);
            
            long long totalHits = 0;
            for(auto& word : searchWords){
                int h = table.search(word);
                if(h != -1) totalHits += h;
            }
            coll2 = table.getCollisions();
            avgHits2 = (double)totalHits / searchWords.size();
        }
        
        cout << left << setw(nameWidth) << methodNames[m]
             << sep << right << setw(colWidth) << coll1 << sep << setw(hitWidth) << fixed << setprecision(3) << avgHits1
             << sep << right << setw(colWidth) << coll2 << sep << setw(hitWidth) << fixed << setprecision(3) << avgHits2
             << endl;
    }
    cout << "\n";
    return 0;
}