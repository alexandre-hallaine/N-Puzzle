#include <memory>
#include <set>

#include "Heuristic.hpp"
#include "Node.hpp"

class AStarSearch
{
private:
	Heuristic &heuristic;
	Puzzle puzzle;

	struct NodeCompare
	{
		bool operator()(std::shared_ptr<Node> const &a, std::shared_ptr<Node> const &b) const;
	};

	std::multiset<std::shared_ptr<Node>, NodeCompare> frontier;
	std::vector<std::shared_ptr<Node>> closed;

	std::vector<Puzzle> reconstructPath(Node node);
	void expand(const Node &node);

public:
	AStarSearch(Heuristic &heuristic);
	void init(Puzzle puzzle);

	std::vector<Puzzle> solve();
};
