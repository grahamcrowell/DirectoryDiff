#pragma once
#include "stdafx.h"

// create custom vertex property tag
struct hash_path_property_t {
	typedef boost::vertex_property_tag kind;
};
//use the new tag in the property class and use that in the assembly of a graph type
typedef boost::property<hash_path_property_t, hash_path> HashPathProperty;
// adjacency list as container for graph
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, HashPathProperty, boost::no_property> FileSystemGraphType;

typedef std::pair<hash_path, hash_path> Edge;

class file_system_root
{
	std::shared_ptr<FileSystemGraphType> G;
	boost::property_map<FileSystemGraphType, hash_path_property_t>::type hash_map;
	//HashPathProperty vertex_property;
	boost::filesystem::path root_path;
	int current_id;
	int file_count;
	int folder_count;
	std::shared_ptr<std::list<hash_path>> _files;

public:

	file_system_root(boost::filesystem::path root_path);
	void populate_filesystem_graph(int parent_vertex_id, hash_path parent_path);
	//void populate_filesystem_graph(int parent_vertex_id, hash_path parent_path);
	std::shared_ptr<FileSystemGraphType> getGraph() const
	{
		return G;
	}

	std::shared_ptr<std::list<hash_path>> get_files();
	//HashPathProperty getVertexProperty()
	//{
	//	return vertex_property;
	//}
	
	int Count()
	{
		return this->current_id;
	}
	//std::pair<boost::range_detail::integer_iterator<size_t>, boost::range_detail::integer_iterator<size_t>> get_file_iterator()
	//{
	//	std::pair<boost::range_detail::integer_iterator<size_t>, boost::range_detail::integer_iterator<size_t>> itpr = boost::vertices(*G);
	//	boost::vertex(7, *G);
	//	
	//	struct is_file {
	//		hash_map = get(hash_path_property_t(), *G);
	//		bool operator()(size_t &x) { return boost::filesystem::is_regular_file(hash_map(boost::vertex(7, *G))); }
	//	};
	//	
	//	boost::filesystem::is_regular_file(hash_map(boost::vertex(7, *G)));
	//	//typedef boost::range_detail::integer_iterator<size_t> base_iterator;
	//	//// Example using filter_iterator
	//	//typedef boost::filter_iterator<is_file, base_iterator> FilterIter;

	//	//is_file predicate;
	//	//FilterIter filter_iter_first(predicate, numbers, numbers + N);
	//	return itpr;
	//}
	~file_system_root();
private:
	friend std::ostream & operator<<(std::ostream &os, const file_system_root& p);

};

