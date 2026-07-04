# Hash Table Implementation
## BANGLADESH UNIVERSITY OF ENGINEERING AND TECHNOLOGY
## CSE208 - Data Structures and Algorithm Sessional

This is a comprehensive implementation of hash table data structures with dynamic resizing, multiple collision resolution techniques, and performance evaluation capabilities.

## Features

### 1. Dynamic Resizing
- **Initial table size:** 13 (prime number)
- **Load factor thresholds:**
  - Expansion when load factor > 0.5
  - Compaction when load factor < 0.25
- **Resizing policy:**
  - Expansion: smallest prime > 2 × current_size
  - Compaction: largest prime < current_size / 2
  - No compaction below initial size
  - Expansion only after n/2 insertions since last expansion
  - Compaction only after n/2 deletions since last compaction

### 2. Hash Functions
Two primary hash functions are implemented:
- **Hash1:** Polynomial rolling hash (djb2 variant)
- **Hash2:** FNV-1a hash algorithm
- **Auxiliary Hash:** Used for double hashing and custom probing

Both hash functions are designed to minimize collisions and achieve at least 60% unique hash values.

### 3. Collision Resolution Techniques

#### Chaining Method
- Each slot contains a linked list of elements
- All elements hashing to the same index stored in the list
- NULL pointer if no elements

#### Double Hashing
- Probe sequence: `(Hash(k) + i × auxHash(k)) mod N`
- Uses auxiliary hash function for probing

#### Custom Probing
- Probe sequence: `(Hash(k) + C1 × i × auxHash(k) + C2 × i²) mod N`
- Constants: C1 = 1, C2 = 3
- Combines linear and quadratic probing with auxiliary hash

### 4. Random Word Generator
- Generates unique random words of specified length
- Maintains sequence numbers for values
- Automatically discards duplicates

### 5. Performance Evaluation
- Tests all combinations of hash functions and collision resolution methods
- Measures:
  - Number of collisions during insertion
  - Average number of hits per search operation
- Default test: 10,000 words of length 10, with 1,000 search operations

## File Structure

```
dsa_offline_5/
├── prime_utils.py                    # Prime number utilities
├── word_generator.py                 # Random word generator
├── hash_functions.py                 # Hash function implementations
├── hash_table_chaining.py           # Chaining collision resolution
├── hash_table_double_hashing.py     # Double hashing collision resolution
├── hash_table_custom_probing.py     # Custom probing collision resolution
├── performance_tester.py            # Performance testing framework
├── main.py                          # Main program with user interface
├── README.md                        # This file
└── hashing_offline.pdf              # Assignment specification
```

## Usage

### Running the Program

```bash
python main.py
```

### Main Menu Options

1. **Run Performance Evaluation (10,000 words)**
   - Executes the default performance test as specified in the assignment
   - Generates 10,000 unique words of length 10
   - Tests all 6 combinations (3 methods × 2 hash functions)
   - Searches for 1,000 randomly selected words
   - Displays results in tabular format

2. **Interactive Hash Table Demo**
   - Choose collision resolution method and hash function
   - Perform manual insert, search, and delete operations
   - Generate random words for testing
   - View real-time statistics

3. **Custom Performance Test**
   - Specify custom parameters:
     - Number of words
     - Word length
     - Number of search operations
   - Run full performance evaluation with custom settings

4. **Exit**
   - Exit the program

## Performance Report Format

The program generates a report in the following format:

```
Method                    | Hash1                               | Hash2
                         | Collisions      Avg Hits           | Collisions      Avg Hits
----------------------------------------------------------------------------------------------------
Chaining Method          | XXXX            X.XXXX             | XXXX            X.XXXX
Double Hashing           | XXXX            X.XXXX             | XXXX            X.XXXX
Custom Probing           | XXXX            X.XXXX             | XXXX            X.XXXX
```

## Implementation Details

### Configuration Parameters

All configuration parameters are defined as single-source class variables for easy modification:

```python
INITIAL_SIZE = 13              # Initial table size
LOAD_FACTOR_UPPER = 0.5       # Upper threshold for expansion
LOAD_FACTOR_LOWER = 0.25      # Lower threshold for compaction
C1 = 1                        # Custom probing constant 1
C2 = 3                        # Custom probing constant 2
```

### Key Operations

#### Insert
- Checks if key exists (updates if found)
- Inserts new key-value pair
- Tracks collisions
- Triggers resize if needed based on load factor and insertion count

#### Search
- Returns value and number of hits (table accesses)
- Follows probe sequence until found or empty slot reached

#### Delete
- Marks slot as deleted (for open addressing methods)
- Removes from linked list (for chaining)
- Triggers resize if needed based on load factor and deletion count

### Dynamic Resizing Logic

The implementation strictly follows the assignment requirements:
- Resize only when appropriate threshold reached AND
- Sufficient operations performed (n/2 insertions/deletions)
- Table size always remains prime
- No compaction below initial size

## Testing

The implementation has been designed to handle:
- Large datasets (tested with 10,000+ entries)
- Various word lengths
- All collision scenarios
- Dynamic resizing edge cases
- Prime number calculations

## Requirements

- Python 3.6 or higher
- No external dependencies (uses only standard library)

## Assignment Compliance

This implementation strictly adheres to all requirements specified in the assignment:
- ✓ Dynamic resizing with prime table sizes
- ✓ Load factor thresholds (0.5 and 0.25)
- ✓ Controlled expansion/compaction with n/2 operation requirement
- ✓ Three collision resolution techniques
- ✓ Two primary hash functions
- ✓ Random word generator with duplicate handling
- ✓ Performance evaluation with 10,000 words
- ✓ Search testing with 1,000 sample words
- ✓ Tabular report format
- ✓ Single-source configuration variables

## Author

Implemented for CSE208 - Data Structures and Algorithm Sessional
Department of Computer Science and Engineering
Bangladesh University of Engineering and Technology

## Submission Deadline

11:59 PM on 1 February 2025 (Sunday)
