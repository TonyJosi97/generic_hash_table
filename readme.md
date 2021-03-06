## Generic Hash Table
_______

[**Documentation**](https://tonyjosi97.github.io/generic_hash_table/generic__hash__table_8h.html)
_______

Hash Table implementation using [Open addressing](https://en.wikipedia.org/wiki/Open_addressing) & [Linear probing](https://en.wikipedia.org/wiki/Linear_probing) method.

> Hash tables are the most commonly used nontrivial data structures, and the most popular implementation on standard hardware uses linear probing, which is both fast and simple.

> **Open addressing**

Open addressing, or closed hashing, is a method of collision resolution in hash tables. With this method a hash collision is resolved by probing, or searching through alternate locations in the array (the probe sequence) until either the target record is found, or an unused array slot is found, which indicates that there is no such key in the table.

> **Linear probing**

Each cell of a hash table stores a single key–value pair. When the hash function causes a collision by mapping a new key to a cell of the hash table that is already occupied by another key, linear probing searches the table for the closest following free location and inserts the new key there. Lookups are performed in the same way, by searching the table sequentially starting at the position given by the hash function, until finding a cell with a matching key or an empty cell.



### Test Status

Tested with 1 million records

#### TO DO:
* Make memcpy to memcpy_s

## NOTES

### [**Amortized analysis**](https://en.wikipedia.org/wiki/Amortized_analysis)

> In computer science, amortized analysis is a method for analyzing a given algorithm's complexity, or how much of a resource, especially time or memory, it takes to execute. The motivation for amortized analysis is that looking at the worst-case run time per operation, rather than per algorithm, can be too pessimistic.

> While certain operations for a given algorithm may have a significant cost in resources, other operations may not be as costly. The amortized analysis considers both the costly and less costly operations together over the whole series of operations of the algorithm. This may include accounting for different types of input, length of the input, and other factors that affect its performance.


### Complexity of Hash Tables

[src](https://stackoverflow.com/a/9214594/6792356)

Hash tables are O(1) average and amortized case complexity, however it suffers from O(n) worst case time complexity. 

Hash tables suffer from O(n) worst time complexity due to two reasons:

* If too many elements were hashed into the same key: looking inside this key may take O(n) time.  
* Once a hash table has passed its load balance - it has to rehash [create a new bigger table, and re-insert each element to the table].

However, it is said to be O(1) average and amortized case because:

* It is very rare that many items will be hashed to the same key [if you chose a good hash function and you don't have too big load balance.

The rehash operation, which is O(n), can at most happen after n/2 ops, which are all assumed O(1): Thus when you sum the average time per op, you get : (n*O(1) + O(n)) / n) = O(1)

### Simple Hash Table Deletion Algorithm

[src](https://stackoverflow.com/a/4396158/6792356)

Find and remove the desired element:
1. Find and remove the desired element.
2. Go to the next bucket
3. If the bucket is empty, quit
4. If the bucket is full, delete the element in that bucket and re-add it to the hash table using the normal means. The item must be removed before re-adding, because it is likely that the item could be added back into its original spot.
5. Repeat step 2.
