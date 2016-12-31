# Directory Diff
Determine the delta between the two directories and suggest move operations to resync.
- [`boost graph library`](http://www.boost.org/doc/libs/1_62_0/libs/graph/doc/index.html) directed graph used to model file systems
- [`boost::filesystem`](http://www.boost.org/doc/libs/1_62_0/libs/filesystem/doc/index.htm) to iterate over files and subdirectories
    - Custom class `hash_file` inherets `boost::filesystem::path` is an [custom internal vertex property](http://www.boost.org/doc/libs/1_62_0/libs/graph/doc/using_adjacency_list.html#sec:adjacency-list-properties) of graph
    - adds `std::string get_hash(void)` function that returns SHA512 file hash for file pathes and hash of hashes for directories.
- [`OpenSSL`](https://slproweb.com/products/Win32OpenSSL.html) to hash files and folders
  - folder hashes are string hashes (the string is a concatinatino of the hashes of the contained files and subfolders)

## Process root

### 1. crawl folder structure

Model file system as a directed graph with Boost Graph Library:
#### Graph Theory model
Files and Folders are vertices; each edge points out from a parent folder into contained file or subfolder.
- root folder has in-degree 0 (source vertex)
- files and empty folders are leaf nodes (aka pendant vertex)
- non-empty folders have out-degree > 0
- acyclic

#### populate tree data structure
Use recursive iterator to build tree data structure with lazy initialization of `file_hash` objects

### 2. process file hashes
Generate SHA512 hashes for each file in parrellel (todo) with openssl library.


## Binaries

- [boost]()
- [openssl]()