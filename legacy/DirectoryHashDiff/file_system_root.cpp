#include "stdafx.h"
#include "file_system_root.h"
using namespace std::string_literals; // https://msdn.microsoft.com/en-CA/library/69ze775t.aspx

file_system_root::file_system_root(boost::filesystem::path root_path)
{
	std::cout << "file_system_root(boost::filesystem::path root_path=" << root_path << ")" << std::endl;
	if (!boost::filesystem::is_directory(root_path))
	{
		std::cerr << "ERROR: directory does not exist." << std::endl;
		getchar();
		// TODO: exception handling
		exit(1);
	}
	G = std::make_shared<FileSystemGraphType>();
	_files = std::make_shared<std::list<hash_path>>();
	// root vertex has current_id = 0
	current_id = -1;
	file_count = 0;
	folder_count = 0;
	hash_map = get(hash_path_property_t(), *G);
	this->root_path = root_path;
	std::cout << "root_path: " << root_path << std::endl;
	this->populate_filesystem_graph(0, this->root_path);
	//std::map<std::string, std::string> graph_attr, vertex_attr, edge_attr;
	//graph_attr["size"] = "3,3";
	//graph_attr["rankdir"] = "LR";
	//graph_attr["ratio"] = "fill";
	//vertex_attr["shape"] = "circle";
	//boost::write_graphviz(std::cout, G,nullptr, nullptr,
	//	//boost::make_label_writer(name),
	//	//boost::make_label_writer(trans_delay),
	//	boost::make_graph_attributes_writer(graph_attr, vertex_attr,
	//	edge_attr));
	//std::list<boost::filesystem::path> *paths = new std::list<boost::filesystem::path>();
	//auto folder_path = "C:/Users/user/Desktop/software"s;
	//hash_path *root = new hash_path(folder_path);
	//boost::filesystem::directory_iterator it = boost::filesystem::directory_iterator(*root), end;
	//
	//int i = 2;
	//while (it != end)
	//{
	//	std::cout << it->path() << std::endl;
	//	boost::add_edge(1,2, *G);
	//	//boost::add_edge(std::make_unique<FileSystemGraph>(it->path()), std::make_unique<FileSystemGraph>(it->path()), *G);
	//	boost::add_vertex(*G);
	//	paths->push_front(it->path());
	//	++it;
	//}
}
void file_system_root::populate_filesystem_graph(const int parent_vertex_id, const hash_path parent_path)
{
	std::cout << "populate_filesystem_graph(parent_vertex_id=" << parent_vertex_id << ",parent_path=" << parent_path << ")" << std::endl;
	current_id = parent_vertex_id + 1;
	// boost directory_iterator seems to return entries in alphabetic order, not ordered by type (ie. not folders then files nor vice versa)
	boost::filesystem::directory_iterator it = boost::filesystem::directory_iterator(parent_path), end;
	bool found_dir = false, found_file = false;
	while (it != end)
	{
		if (boost::filesystem::is_regular_file(it->path()))
		{
			//if (found_dir)
			//{
			//	std::cout << "dir found before file" << std::endl;
			//}
			//found_file = true;
			//std::cout << "regular_file: " << it->path() << std::endl;
			std::cout << "add file vertex: " << parent_path << "->" << it->path() << std::endl;
			std::cout << "\t(" << parent_vertex_id << "->" << current_id << ")" << std::endl;
			std::shared_ptr<hash_path> p = std::make_shared<hash_path>(it->path());
			boost::add_edge(parent_vertex_id, current_id, *G);
			put(hash_map, current_id, *p);
			//std::cout << "\tget_hash... hashing... " << p->get_hash() << std::endl;
			std::cout << "\tfile count: " << file_count << std::endl;
			current_id++;
			file_count++;
		}
		else if (boost::filesystem::is_directory(it->path()))
		{
			//if (found_file)
			//{
			//	std::cout << "file found before dir" << std::endl;
			//}
			//found_dir = true;
			//std::cout << "folder: " << it->path() << std::endl;
			std::cout << "add folder vertex: " << parent_path << "->" << it->path() << std::endl;
			std::cout << "\t(" << parent_vertex_id << "->" << current_id << ")" << std::endl;
			std::shared_ptr<hash_path> p = std::make_shared<hash_path>(it->path());
			boost::add_edge(parent_vertex_id, current_id, *G);
			put(hash_map, current_id, *p);
			std::cout << "\tfolder count: " << folder_count << std::endl;
			folder_count++;
			this->populate_filesystem_graph(current_id, it->path());
		}
		else
		{
			std::cout << "unknown file system type" << it->path();
		}
		it++;
	}
	// set root vertex property
	if (parent_vertex_id == 0)
	{
		std::shared_ptr<hash_path> p = std::make_shared<hash_path>(root_path.string());
		put(hash_map, parent_vertex_id, *p);
	}
}

std::shared_ptr<std::list<hash_path>> file_system_root::get_files()
{
	return _files;
}


file_system_root::~file_system_root()
{
}


// generic edge printer for directed graph
template <class EdgeIter, class Graph>
void who_owes_who(EdgeIter first, EdgeIter last, Graph& G)
{
	// Access the propety acessor type for this graph
	//typedef typename property_map<Graph, hash_path_property_t>
	//	::const_type NamePA;
	//NamePA name = get(vertex_first_name, G);
	//
	//typedef typename boost::property_traits<NamePA>::value_type NameType;

	//NameType src_name, targ_name;

	//while (first != last) {
	//	src_name = boost::get(name, source(*first, G));
	//	targ_name = boost::get(name, target(*first, G));
	//	cout << src_name << " owes "
	//		<< targ_name << " some money" << endl;
	//	++first;
	//}

	typedef typename boost::property_map<FileSystemGraphType, hash_path_property_t>::type hash_map;
	hash_map hash_path_map = get(hash_path_property_t(), G);
	typedef typename boost::property_traits<hash_map>::value_type hash_path_type;
	hash_path_type src_hash_path, dst_hash_path;
	while (first != last) {
		src_hash_path = boost::get(hash_path_map, source(*first, G));
		dst_hash_path = boost::get(hash_path_map, target(*first, G));
		std::cout << src_hash_path << " contains "
			<< dst_hash_path << std::endl;
		++first;
	}
}

std::ostream & operator<<(std::ostream & os, const file_system_root & p)
{
	//who_owes_who(edges(*p.getGraph()).first, edges(*p.getGraph()).second, *p.getGraph());
	//int vertex_id = 1;
	os << "file_system_root: " << p.root_path << std::endl
		<< "vertex count: " << boost::num_vertices(*p.getGraph()) << std::endl
		<< "edge count: " << boost::num_edges(*p.getGraph()) << std::endl
		//<< "example vertex: " << p.getGraph()->m_vertices.at(vertex_id).m_property.m_value.string() << std::endl
		//<< "\thash: " << p.getGraph()->m_vertices.at(vertex_id).m_property.m_value.get_hash_digest() << std::endl
		;
	return os;
}

