#include<iostream>
#include<bits/stdc++.h>

using namespace std;




int  main()
{
    string filename = "C:/Users/aakas/Desktop/Art_gallery/Art_gallery_problems/problem1-2/VisiLibity1-master/src/data.txt";
    Graph g = new Graph();
    tools.GraphLoader.loadGraph(g, filename);
		
		System.out.println("\nAnalyzing " + filename + " ...");
  		System.out.println("The undirected graph has " + g.getNumNodes() + " nodes.");
		System.out.println("Undirected  graph has " + g.getNumEdges() + " edges.");

		
		long start_mds = System.currentTimeMillis();
		List<Node> mds = DominatingSet.findMinimumDominatingSet(g);
		long end_mds = System.currentTimeMillis();

		double seconds_mds = end_mds/1000.0 - start_mds/1000.0;
		System.out.println("\nThe program found a minimum dominating set in " + seconds_mds + " seconds.");
		System.out.println("The minimum dominating set found contains " + mds.size() + " nodes.");
		System.out.print("The minimum dominating set is: ");
		Set<Integer>d=new HashSet<Integer>();
		for(int i=0;i<mds.size();i++)
		   d.add(mds.get(i).getName());
        try 
		{
			filename = "C:/Users/aakas/Desktop/Art_gallery/Art_gallery_problems/problem1-2/VisiLibity1-master/src/map.txt";
			File myObj = new File(filename);
			Scanner myReader = new Scanner(myObj);
			int i=0;
			while (myReader.hasNextLine()) {
		
				 String data = myReader.nextLine();
				if(d.contains(i))
				  System.out.println(data);
				i++;
			}
			System.out.println(mds);
		}
		catch (FileNotFoundException e) {
				System.out.println("An error occurred.");
					e.printStackTrace();
		}
    }
	
	

