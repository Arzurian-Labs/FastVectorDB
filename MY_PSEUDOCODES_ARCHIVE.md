# 📝 Hazushiro's Raw Pseudocode Archive
**Project:** FastVectorDB (C++20 Engine)  
**Date:** July 24–25, 2026  

---

## 🌟 The Message for Future Computer Scientists & Engineers

> *"Never be afraid to write unorganized, messy, or 'broken' pseudocode. Staring at a blank editor waiting for perfect syntax is the biggest obstacle in programming. Drafting your thoughts—no matter how rough—gets your mental model out of your head and into motion. Every working line of production code starts from a rough draft."*

---

## 📜 Raw Pseudocode Entries & Translations

### 1. VectorStore Constructor & Guard Clause
**User's Original Raw Draft:**
```cpp
... VectorStore::VectorStore(std::size_t dimension, ... (same std declare at three dots) initial_capacity);
... dimension::dimension_(Declare anything that needs to be written here );
Using a if-else statement to check:
if(dimension_ == 0) { std::invalid_argument;
std::cout << "Vector dimension must be greater than zero." << std::endl;
 }
else {
This is where dimension creation would be created so long as it is above 0 (not below 0)
}
```

* **Why It Worked:** Even though syntax details like member initializer lists (`: dimension_(dimension)`) and namespace scoping were missing, the **core engineering logic** (checking `dimension == 0` first, throwing an error, and reserving valid creation for `> 0`) was 100% sound. This naturally derived the industry-standard **Guard Clause Pattern**.

---

### 2. Class Members, Getters & Insert Method
**User's Original Raw Draft:**
```cpp
Right after the VectorStore::VectorStore(...) section:
size_t dimension() const;
Size_t size() const;

These two would stay out, meanwhile:
std::vector<float> data_;
std:vector<uint64_t> ids_; or std::vector<std::string>

After these two lines, the third one (either outside or next part within the namespace:
insert(id, vector<float>)
{
vector.size() = dimension_;
}
```

* **Why It Worked:** This raw draft laid out the exact architecture of Phase 2: separating `public` getters (`dimension()`, `size()`) from `private` storage buffers (`data_`, `ids_`), and defining the vector validation requirement during `insert()`.

---

### 3. CLI Test Harness (`main.cpp`)
**User's Original Raw Draft:**
```cpp
fastvectordb::VectorStore store (3, 10);

// Initial Status (though I am considering the possibility of using a for loop for this)
std::cout << ID << values << std::endl;

// Verify the size
std::cout << store.size() << std::endl;

// Test dimension validation
try {...} catch (const std::exception& e)

return 0;
```

* **Why It Worked:** This draft defined a complete integration test harness: initializing a 3D store, logging initial state, verifying vector counts, and testing exception handling with `try-catch`. When implemented, it compiled and ran cleanly on the very first try.

---

## 🏆 Takeaway
Drafting pseudocode is the bridge between human thought and hardware execution. Keep writing rough drafts!
