#include <bits/stdc++.h>
using namespace std;

/* ================= ENUMS ================= */

enum class collisionMode
{
    Chaining,
    DoubleHashing,
    CustomProbing
};

enum class HashType
{
    Hash1,
    Hash2
};

/* ================= NODE ================= */

template <class K, class V>
struct Node
{
    K key;
    V value;
    bool occupied = false;
    bool deleted = false;

    Node() {}
    Node(K k, V v) : key(k), value(v), occupied(true), deleted(false) {}
};

/* ================= HASH TABLE ================= */

template <class Key, class Value>
class HashTable
{

private:
    /* ---------- PARAMETERS ---------- */
    int initialsize = 13;
    int tableSize;
    int elementCount;
    int countAtResize; // Element count at time of last resize
    bool isRehashing;  // Flag to prevent recursive resize

    collisionMode mode;
    HashType hashType;

    vector<list<pair<Key, Value>>> chainTable;
    vector<Node<Key, Value>> openTable;

    long long totalHits = 0;
    long long totalCollisions = 0;

    int insertSinceResize = 0;
    int deleteSinceResize = 0;

    /* ---------- PRIME UTIL ---------- */

    bool isPrime(int n)
    {
        if (n <= 1)
            return false;
        for (int i = 2; i * i <= n; i++)
            if (n % i == 0)
                return false;
        return true;
    }

    int nextPrime(int n)
    {
        while (!isPrime(n))
            n++;
        return n;
    }

    int prevPrime(int n)
    {
        while (n > 13)
        {
            if (isPrime(n))
                return n;
            n--;
        }
        return 13;
    }

    /* ---------- HASH FUNCTIONS ---------- */

    // Helper to convert key to string
    template <typename T>
    string keyToString(const T &k)
    {
        return to_string(k);
    }

    string keyToString(const string &k)
    {
        return k;
    }

    int hash1(const Key &key)
    {
        int h = 0;
        string s = keyToString(key);
        for (char c : s)
            h = (h * 31 + c) % tableSize;
        return h;
    }

    int hash2(const Key &key)
    {
        int h = 0;
        string s = keyToString(key);
        for (char c : s)
            h = ((h << 5) + h + c) % tableSize; // FNV-1a style: h*33+c
        return h;
    }

    int primaryHash(const Key &key)
    {
        return (hashType == HashType::Hash1 ? hash1(key) : hash2(key));
    }

    int auxHash(const Key &key)
    {
        int h = hash2(key);
        return 1 + (h % (tableSize - 1));
    }

    /* ---------- LOAD FACTOR ---------- */

    double loadFactor()
    {
        return (double)elementCount / tableSize;
    }

    /* ---------- RESIZE ---------- */

    void resize(bool expand)
    {
        isRehashing = true; // Prevent recursive resize and collision counting

        int newSize;
        if (expand)
            newSize = nextPrime(tableSize * 2);
        else
            newSize = prevPrime(tableSize / 2);

        vector<pair<Key, Value>> old;

        if (mode == collisionMode::Chaining)
        {
            for (auto &lst : chainTable)
                for (auto &p : lst)
                    old.push_back(p);
        }
        else
        {
            for (auto &node : openTable)
                if (node.occupied && !node.deleted)
                    old.push_back({node.key, node.value});
        }

        tableSize = newSize;
        countAtResize = elementCount; // Save current element count
        elementCount = 0;

        chainTable.clear();
        openTable.clear();

        chainTable.resize(tableSize);
        openTable.resize(tableSize);

        long long oldHits = totalHits;
        long long oldCollisions = totalCollisions;

        for (auto &p : old)
        {
            if (mode == collisionMode::Chaining)
                chainInsert(p.first, p.second, false);
            else if (mode == collisionMode::DoubleHashing)
                doubleInsert(p.first, p.second, false);
            else
                customInsert(p.first, p.second, false);
            elementCount++;
        }

        totalHits = oldHits;
        totalCollisions = oldCollisions;

        insertSinceResize = 0;
        deleteSinceResize = 0;
        isRehashing = false; // Re-enable resize checking
    }

    /* ---------- INSERT HELPERS ---------- */

    void chainInsert(const Key &key, const Value &value, bool countElement = true)
    {

        int idx = primaryHash(key) % tableSize;

        for (auto &p : chainTable[idx])
        {
            if (p.first == key)
            {
                p.second = value;
                return;
            }
        }

        if (!isRehashing && !chainTable[idx].empty())
            totalCollisions++;
        chainTable[idx].push_back({key, value});
        if (countElement)
            elementCount++;
    }

    void doubleInsert(const Key &key, const Value &value, bool countElement = true)
    {

        int start = primaryHash(key) % tableSize;
        int step = auxHash(key);

        for (int i = 0; i < tableSize; i++)
        {

            int idx = (start + i * step) % tableSize;

            // Count collision on every probe after the first
            if (!isRehashing && i > 0)
            {
                totalCollisions++;
            }

            if (!openTable[idx].occupied || openTable[idx].deleted)
            {
                openTable[idx] = Node<Key, Value>(key, value);
                if (countElement)
                    elementCount++;
                return;
            }

            if (openTable[idx].key == key)
            {
                openTable[idx].value = value;
                return;
            }
        }
    }

    void customInsert(const Key &key, const Value &value, bool countElement = true)
    {

        int c1 = 3, c2 = 7;
        int start = primaryHash(key) % tableSize;
        int step = auxHash(key);

        for (int i = 0; i < tableSize; i++)
        {

            int idx = (start + c1 * i * step + c2 * i * i) % tableSize;

            // Count collision on every probe after the first
            if (!isRehashing && i > 0)
            {
                totalCollisions++;
            }

            if (!openTable[idx].occupied || openTable[idx].deleted)
            {
                openTable[idx] = Node<Key, Value>(key, value);
                if (countElement)
                    elementCount++;
                return;
            }

            if (openTable[idx].key == key)
            {
                openTable[idx].value = value;
                return;
            }
        }
    }

public:
    /* ---------- CONSTRUCTOR ---------- */

    HashTable(collisionMode m, HashType h)
    {

        mode = m;
        hashType = h;
        tableSize = initialsize;
        elementCount = 0;
        countAtResize = 0;
        isRehashing = false;

        chainTable.resize(tableSize);
        openTable.resize(tableSize);
    }

    /* ---------- INSERT ---------- */

    void insert(const Key &key, const Value &value)
    {
        // Check if resize needed BEFORE inserting
        if (!isRehashing)
        {
            double lf = (double)(elementCount + 1) / tableSize;
            if (lf > 0.5 && insertSinceResize >= countAtResize / 2)
            {
                resize(true);
            }
        }

        int oldCount = elementCount;

        if (mode == collisionMode::Chaining)
            chainInsert(key, value);
        else if (mode == collisionMode::DoubleHashing)
            doubleInsert(key, value);
        else
            customInsert(key, value);

        // Only count as insertion if it was a new key (not an update)
        if (!isRehashing && elementCount > oldCount)
            insertSinceResize++;
    }
    
    void printProbeSequence(const string &key)
    {   
     if(mode==collisionMode::CustomProbing) {
        int c1 = 3, c2 = 7;
        int start = primaryHash(key) % tableSize;
        int step = auxHash(key);

        for (int i = 0; i < tableSize; i++)
        {
            int idx = (start + c1 * i * step + c2 * i * i) % tableSize;
            
            if (i > 0) cout << " -> ";
            cout << idx;

            if (!openTable[idx].occupied || openTable[idx].deleted)
            {
                return;
            }

            if (openTable[idx].key == key)
            {
                return;
            }
        }
     } 
     else if(mode==collisionMode::DoubleHashing){
        int start = primaryHash(key) % tableSize;
        int step = auxHash(key);

        for (int i = 0; i < tableSize; i++)
        {
            int idx = (start + i * step) % tableSize;
            
            if (i > 0) cout << " -> ";
            cout << idx;

            if (!openTable[idx].occupied || openTable[idx].deleted)
            {
                return;
            }

            if (openTable[idx].key == key)
            {
                return;
            }
        }
     }
    }
    /* ---------- SEARCH ---------- */

    bool search(const Key &key, Value &out)
    {

        int hits = 0;

        if (mode == collisionMode::Chaining)
        {

            int idx = primaryHash(key) % tableSize;

            for (auto &p : chainTable[idx])
            {
                hits++;
                if (p.first == key)
                {
                    totalHits += hits;
                    out = p.second;
                    return true;
                }
            }
            totalHits += hits;
            return false;
        }

        int start = primaryHash(key) % tableSize;
        int step = auxHash(key);

        for (int i = 0; i < tableSize; i++)
        {

            int idx;
            if (mode == collisionMode::DoubleHashing)
                idx = (start + i * step) % tableSize;
            else
            {
                int c1 = 3, c2 = 7;
                idx = (start + c1 * i * step + c2 * i * i) % tableSize;
            }

            hits++;

            if (!openTable[idx].occupied)
            {
                totalHits += hits;
                return false;
            }

            if (openTable[idx].occupied && !openTable[idx].deleted && openTable[idx].key == key)
            {
                totalHits += hits;
                out = openTable[idx].value;
                return true;
            }
        }

        totalHits += hits;
        return false;
    }

    /* ---------- REMOVE ---------- */

    void remove(const Key &key)
    {

        if (mode == collisionMode::Chaining)
        {

            int idx = primaryHash(key) % tableSize;

            for (auto it = chainTable[idx].begin(); it != chainTable[idx].end(); ++it)
            {
                if (it->first == key)
                {
                    chainTable[idx].erase(it);
                    elementCount--;
                    if (!isRehashing)
                        deleteSinceResize++;
                    break;
                }
            }
        }
        else
        {

            int start = primaryHash(key) % tableSize;
            int step = auxHash(key);

            for (int i = 0; i < tableSize; i++)
            {

                int idx;
                if (mode == collisionMode::DoubleHashing)
                    idx = (start + i * step) % tableSize;
                else
                {
                    int c1 = 3, c2 = 7;
                    idx = (start + c1 * i * step + c2 * i * i) % tableSize;
                }

                if (!openTable[idx].occupied)
                    return;

                if (openTable[idx].key == key && !openTable[idx].deleted)
                {
                    openTable[idx].deleted = true;
                    elementCount--;
                    if (!isRehashing)
                        deleteSinceResize++;
                    break;
                }
            }
        }

        if (!isRehashing && loadFactor() < 0.25 && tableSize > initialsize && deleteSinceResize >= elementCount / 2)
            resize(false);
    }

    /* ---------- REPORT ---------- */

    long long getCollisions() { return totalCollisions; }
    double getAvgHits(int searches) { return (double)totalHits / searches; }
};

/* ================= RANDOM WORD ================= */

string randomWord(int n)
{
    static const string alpha = "abcdefghijklmnopqrstuvwxyz";
    string s;
    for (int i = 0; i < n; i++)
        s.push_back(alpha[rand() % 26]);
    return s;
}

/* ================= MAIN EXPERIMENT ================= */

int main()
{

    srand(time(0));

    const int WORDS = 10000;
    const int SEARCHES = 1000;

    unordered_set<string> used;
    vector<string> dataset;

    while (dataset.size() < WORDS)
    {
        string w = randomWord(10);
        if (!used.count(w))
        {
            used.insert(w);
            dataset.push_back(w);
        }
    }

    vector<collisionMode> modes = {
        collisionMode::Chaining,
        collisionMode::DoubleHashing,
        collisionMode::CustomProbing};

    vector<HashType> hashes = {
        HashType::Hash1,
        HashType::Hash2};

    string methodNames[] = {"Chaining Method", "Double Hashing", "Custom Probing"};

    // Print table header
    // cout << "\n";
    // cout << left << setw(18) << "Method"
    //      << right << setw(20) << "Hash 1"
    //      << setw(20) << ""
    //      << setw(20) << "Hash 2"
    //      << setw(20) << "" << endl;

    // cout << left << setw(18) << " "
    //      << right << setw(20) << "Collisions"
    //      << setw(20) << "Avg Hits"
    //      << setw(20) << "Collisions"
    //      << setw(20) << "Avg Hits" << endl;

    // cout << endl;
    int n;
        cin >> n;
        vector<string> v;
        for (int i = 0; i < n; i++)
        {
            string s;
            cin >> s;
            v.push_back(s);
        }
    for (int m = 0; m < 3; m++)
    {
        long long coll1 = 0, coll2 = 0;
        double avgHits1 = 0.0, avgHits2 = 0.0;

        // Test with Hash1
        {
            HashTable<string, int> table(modes[m], HashType::Hash1);

            int id = 1;
            for (auto &w : dataset)
                table.insert(w, id++);

            for (int i = 0; i < SEARCHES; i++)
            {
                int val;
                table.search(dataset[rand() % WORDS], val);
            }

            coll1 = table.getCollisions();
            avgHits1 = table.getAvgHits(SEARCHES);
            if(modes[m]==collisionMode::CustomProbing){
                   for(auto &s:v){
                    table.printProbeSequence(s);
                    cout<<"\n";
                   }
            }
        }

        // Test with Hash2
        {
            HashTable<string, int> table(modes[m], HashType::Hash2);

            int id = 1;
            for (auto &w : dataset)
                table.insert(w, id++);

            for (int i = 0; i < SEARCHES; i++)
            {
                int val;
                table.search(dataset[rand() % WORDS], val);
            }

            coll2 = table.getCollisions();
            avgHits2 = table.getAvgHits(SEARCHES);
        }
        

        //     cout << left << setw(18) << methodNames[m]
        //          << right << setw(20) << coll1
        //          << setw(20) << fixed << setprecision(3) << avgHits1
        //          << setw(20) << coll2
        //          << setw(20) << fixed << setprecision(3) << avgHits2 << endl;
        // }

        cout << "\n";
    }
    return 0;
}