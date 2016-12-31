#pragma once
#include "stdafx.h"
//#include "file_system_root.h"

using namespace boost;
using namespace std;
using namespace boost::filesystem;


template < typename TimeMap > class bfs_time_visitor : public default_bfs_visitor {
	typedef typename property_traits < TimeMap >::value_type T;
public:
	bfs_time_visitor(TimeMap tmap, T & t) :m_timemap(tmap), m_time(t) { }
	template < typename Vertex, typename Graph >
	void discover_vertex(Vertex u, const Graph & g) const
	{
		std::cout << "discover_vertex: " << u << endl;
		put(m_timemap, u, m_time++);
	}
	template < typename Edge, typename Graph >
	void examine_edge(Edge e, const Graph &g)
	{
		/*typedef typename boost::property_map<FileSystemGraphType, hash_path_property_t>::type hash_map;
		hash_map hash_path_map = get(hash_path_property_t(), g);
		typedef typename boost::property_traits<hash_map>::value_type hash_path_type;
		hash_path_type src_hash_path, dst_hash_path;*/

		std::cout << "examine_edge: " << e << endl;
		//std::cout << "???: " << boost::edge(e,g) << endl;
	}
	TimeMap m_timemap;
	T & m_time;

};

void test_bfs()
{
	using namespace boost;
	auto folder_path = string(R"(C:\Users\user\Desktop\test)");
	boost::filesystem::path root_path(folder_path);
	unique_ptr<file_system_root> fsr = make_unique<file_system_root>(root_path);
	int root_node_index = 0;
	int N = num_vertices(*fsr->getGraph());

	typedef graph_traits < FileSystemGraphType >::vertices_size_type Size;
	std::vector < Size > dtime(num_vertices(*fsr->getGraph()));
	typedef iterator_property_map<std::vector<Size>::iterator, property_map<FileSystemGraphType, vertex_index_t>::const_type> dtime_pm_type;
	dtime_pm_type dtime_pm(dtime.begin(), get(vertex_index, *fsr->getGraph()));
	Size time = 0;
	bfs_time_visitor < dtime_pm_type > vis(dtime_pm, time);
	breadth_first_search(*fsr->getGraph(), vertex(root_node_index, *fsr->getGraph()), visitor(vis));
	std::vector<graph_traits<FileSystemGraphType>::vertices_size_type > discover_order(N);
	integer_range < int >range(0, N);
	std::copy(range.begin(), range.end(), discover_order.begin());
	std::sort(discover_order.begin(), discover_order.end(), indirect_cmp < dtime_pm_type, std::less < Size > >(dtime_pm));
	std::cout << "order of discovery: ";

	typedef typename boost::property_map<FileSystemGraphType, hash_path_property_t>::type hash_map;
	hash_map hash_path_map = get(hash_path_property_t(), *fsr->getGraph());
	typedef typename boost::property_traits<hash_map>::value_type hash_path_type;
	hash_path_type src_hash_path;
	for each (auto discover_index in discover_order)
	{
		src_hash_path = boost::get(hash_path_map, discover_index);
		std::cout << src_hash_path.string() << std::endl;
	}
	std::cout << std::endl;
}