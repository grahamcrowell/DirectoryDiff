// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define  BOOST_FILESYSTEM_NO_DEPRECATE

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>


/*
 *
 * general includes
 *
 */
#include <iostream>
#include <string>
#include <memory>
// make hash_path::get_hash_digest member function thread safe.
#include <mutex>
#include <algorithm>
#include <vector>
#include <utility>
#include <iterator>
/*
*
*OpenSsl includes
*
*/
#include <openssl/sha.h>

/*
*
*Boost includes
*
*/
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
/*
*
*Boost Graph Library includes
*
*/
#include <boost/config.hpp>
#include <iostream>                         // for std::cout
#include <utility>                          // for std::pair
#include <algorithm>                        // for std::for_each
#include <boost/utility.hpp>                // for boost::tie
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

#include <boost/property_map/property_map.hpp>

/*
* Boost Graph Breadth First Search includes
*/
//#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include <boost/range/irange.hpp>

/*
*
* my headers
*
*/
#include "hash_path.h"
#include "file_system_root.h"

// TODO: reference additional headers your program requires here
