


#include <bits/stdc++.h> 
using namespace std; 



class Graph:
{
    private:
    map<int,Node>nodes;
    set<Edge>edges;
    
    public:
    Graph()
    {

    }

    void addNode(int key)
	{
		if ( nodes.find(key) == nodes.end())
		{
			Node newNode = new Node(key);
			nodes[key]= newNode;
		}
		return;
	}

    void removeNode(int nodeToRemove)
	{
		Node node = nodes[nodeToRemove];
		removeNodesEdges(node);
		//nodes.put(nodeToRemove, NULL);
	}

	
	
	void removeNode(Node nodeToRemove)
	{
		removeNodesEdges(nodeToRemove);
		//nodes.put(nodeToRemove.getName(), NULL);
	}

	

	 void removeNodeEdges(int nodeToRemove)
	{
		Node node = nodes[nodeToRemove];
		removeNodesEdges(node);

	}


	
	void removeNodesEdges(Node nodeToRemove)
	{
		for (Edge edge : nodeToRemove.getEdges())
			edges.erase(edge);
	}

	
	
	int addEdge(int v1, int v2)
	{	
		// ensure that the from and to nodes are in the Graph
		if (nodes.find(v1)==nodes.end())	
           return 0;    
		if (nodes.find(v2)==nodes.end())
            return 0;
		// extract Node objects from Graph and construct new Edge object
		Node node1 = nodes[v1];
		Node node2 = nodes[v2];
		Edge newEdge = new Edge(node1, node2);

        // do not add new edge if already contained in graph
        for (Edge edge : node1.getEdges() )
        {
            if (edge.isEqualTo(newEdge)) { return 1; }
        }

		// if Edge is not in the Graph; add it
        edges.add(newEdge);
        node1.addEdge(newEdge);
        node2.addEdge(newEdge);
        return 1;
        
	}


	 void addEdge(Edge newEdge)
	{
		edges.add(newEdge);
		Node v1 = newEdge.getNodev1();
		Node v2 = newEdge.getNodev2();
		v1.addEdge(newEdge);
		v2.addEdge(newEdge);
	}


	//check
	public vector<Node> getNodes()
	{	
        vector<Node>t;
        for(auto i:nodes)
            t.push_back(i.second);
        return t;
        	
    }


   
    public int getNumNodes()
    {   return nodes.size(); }


    /**
     *
     */
    vector<Edge> getEdges()
    {	
        vector<Edge>d;
        for(auto i:edges)
          d.push_back(i);
        return d; }


	
    public int getNumEdges()
    {	return edges.size(); }


	public String exportGraphString()
    {
    	string s = "";
        for (int key : nodes.keySet() )
        {
            s += "\n" + key + "--> [";
            Node node = nodes[key];
            
            for (Edge edge : node.getEdges())
            {
            	s += " " + str(edge.getOtherNode(node));
            }
            s += " ]";
        }
        return s;
    }


    /**
     * Resets all Nodes and Edges in graph to uncovered.
     * Runs in O(|V| + |E|).
     */
    public void resetGraph()
    {
        for (auto node= nodes.begin();node!=nodes.end();node++ )
            node->second=secondsetAssignment(-1);

        for (Edge edge : edges)
        	edge.setIsCovered(-1);
        
        return;
    }
};