# DSA Offline 3 - MST Implementation

## What I Did

Implemented **Prim's** and **Kruskal's** algorithms for finding Minimum Spanning Trees. 

Both algorithms use priority queues to select minimum weight edges. Kruskal's sorts edges globally while Prim's grows the tree from a root node.

Ran 10 test cases on the provided inputs. Outputs are stored in `kruskalOutputs` and `primOutputs` folders respectively.

## What I Learned

Learned how to implement **Disjoint Set (Union-Find)** data structure with path compression and union by rank optimization while doing Kruskal's MST algorithm. Also understood the difference between edge-based (Kruskal) and vertex-based (Prim) approaches to MST construction.

## Files
- `kruskal.cpp` - Kruskal's algorithm implementation
- `prim.cpp` - Prim's algorithm implementation

