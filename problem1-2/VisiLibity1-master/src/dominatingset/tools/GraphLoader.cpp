

#include<bits/stdc++.h>
uding namespace std;

class GraphLoader: 
{
    public:
    static void loadGraph(Graph g, string filename) {
        
        set<int> seen;
        Scanner sc;
        try {
            sc = new Scanner(new File(filename));
        } catch (Exception e) {
            e.printStackTrace();
            return;
        }
        // Iterate over the lines in the file, adding new
        // vertices as they are found and connecting them with edges.
        while (sc.hasNext()) 
        {
        	if (sc.hasNextInt())
        	{
	            int v1 = sc.nextInt();
	            int v2 = sc.nextInt();
	            if (!seen.contains(v1)) {
	                g.addNode(v1);
	                seen.add(v1);
	            }
	            if (!seen.contains(v2)) {
	                g.addNode(v2);
	                seen.add(v2);
	            }
	            g.addEdge(v1, v2);
	        }
	        else
	        {
	        	sc.nextLine();
	        }
        }
        
        sc.close();
    }
}
