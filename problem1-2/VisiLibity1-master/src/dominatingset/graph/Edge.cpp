


class Edge
{
	private:
    Node v1;
	Node v2;
	int isCovered; 

	public:
    Edge (Node node1, Node node2)
	{	
		// make sure lower value name is always stored in v1
		Node val1;
		Node val2;

		if      ( node1.getName() < node2.getName() )  { val1 = node1; val2 = node2; }
		else if ( node1.getName() > node2.getName() )  { val2 = node1; val1 = node2; }
		

		this.v1 = val1;
		this.v2 = val2;
		this.isCovered = -1;
	}


	
	public String toString() 
	{ 	
		return v1.getName() + "---" + v2.getName();
	}
	

	
	public Node getOtherNode(Node node)
	{
		if (node.name==v1.name) 
			return v2;
		else if (node.name==v2.name)
			return v1;
	
	}


	public Node getNodev1() { return this.v1; }


	public Node getNodev2() { return this.v2; }


	public boolean isEqualTo(Edge edge)
	{
		if ( this.v1.name==edge.getNodev1().name && this.v2.name==edge.getNodev2().name )
			return true;
		return false;
	}


	public int isCovered() { return this.isCovered; }


	public void setIsCovered(int newState) 
	{ 
		if (newState == -1 || newState == 0 || newState == 1)
			this.isCovered = newState;
	}

}