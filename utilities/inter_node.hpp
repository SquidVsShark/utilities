#include "varient.hpp"

namespace Util {

/*
	This is a generic tree contanier.
*/
template<typename... Ts>
class Node
{
public:

	explicit Node()
	{}



private:

	Node 							*m_parent_node;
	std::string				m_node_name;
	std::vector<Node> m_child_nodes;
	varient<Ts> 			m_data;

};


} // ns