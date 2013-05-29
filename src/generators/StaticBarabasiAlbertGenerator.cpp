/*
 * StaticBarabasiAlbertGenerator.cpp
 *
 *  Created on: May 28, 2013
 *      Author: forigem
 */

#include "StaticBarabasiAlbertGenerator.h"


namespace NetworKit {

StaticBarabasiAlbertGenerator::StaticBarabasiAlbertGenerator(count k,
		count nMax, count n0):k(k), nMax(nMax), n0(n0) {
	if (n0 == -1) {
		n0 = k;
	}
}

StaticBarabasiAlbertGenerator::~StaticBarabasiAlbertGenerator() {
	// TODO Auto-generated destructor stub
}

Graph StaticBarabasiAlbertGenerator::generate() {
	Graph G = initializeGraph();
	assert (G.numberOfNodes() >= k);

	for (int i = n0; i < nMax; i++) {
		DEBUG("FOR")
		count degreeSum = G.numberOfEdges() * 2;
		//DEBUG("Random")

		node u = G.addNode();
		std::set<node> targets;
		targets.insert(u);
		int j = 0;
		while (targets.size() - 1 < k) {
			int64_t random = randomInt.generate(0, degreeSum);

			DEBUG("WHILE")
			j++;
			///if (j > k) throw std::runtime_error("Possible infinite loop detected.");
			bool found = false; // break from node iteration when done
			auto notFound = [&](){ return ! found; };

			G.forNodesWhile(notFound, [&](node v) {

				DEBUG("FOR-NODES-WHILE")

				if (random <= G.degree(v)) {
					DEBUG("found a node " << v);
					found = true; // found a node to connect to
					targets.insert(v);
				}
				random -= G.degree(v);
				//if (j >= G.numberOfNodes() && found==false) throw std::runtime_error("Last node, but still nothing happened.");
			});
		}

		targets.erase(u);

		for (node x : targets) {
			G.addEdge(u, x);
		}

	}

	return G;
}

Graph StaticBarabasiAlbertGenerator::initializeGraph() {
	Graph G(0);

	// initialize the graph with n0 connected nodes
	for (int i = 0; i < n0; i++) {
		node v = G.addNode();
		if (i > 0) G.addEdge(v, v - 1);
	}

	return G;
}


} /* namespace NetworKit */

