

import graph.*;
import algorithms.*;
import tools.GraphLoader;
import java.io.File;  // Import the File class
import java.io.FileNotFoundException;  // Import this class to handle errors
import java.util.Scanner; // Import the Scanner class to read text files
import java.util.*;

import java.util.List;

public class App
{
	public static void main(String[] args)
	{
		// System.out.println("Running tests ...");
		// tests();

		String filename = "C:/Users/aakas/Desktop/Art_gallery/Art_gallery_problems/problem1-2/VisiLibity1-master/src/data.txt";

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
	public static void tests()
	{
		// TEST 1
		System.out.println("\n\nTest 1: ...");
        Graph test1 = new Graph();
        GraphLoader.loadGraph(test1, "data/small_test_graph.txt");
        System.out.println(test1.exportGraphString());

        List<Node> dominatingSet1 = DominatingSet.findGreedyDominatingSet(test1);
        System.out.print("Greedy Dominating Set: ");
        System.out.println(dominatingSet1);

        List<Node> minDominatingSet1 = DominatingSet.findMinimumDominatingSet(test1);
        System.out.print("Minimum Dominating Set: ");
        System.out.println(minDominatingSet1);


        
        // TEST 2
        System.out.println("\n\nTest 2: ... ");
		Graph test2 = new Graph();
		GraphLoader.loadGraph(test2, "data/dominating_set_test.txt");
		System.out.println(test2.exportGraphString());

		List<Node> dominatingSet2 = DominatingSet.findGreedyDominatingSet(test2);
		System.out.print("Dominating Set: ");
		System.out.println(dominatingSet2);

		List<Node> minDominatingSet2 = DominatingSet.findMinimumDominatingSet(test2);
		System.out.print("Minimum Dominating Set: ");
		System.out.println(minDominatingSet2);



		// TEST 3
		System.out.println("\n\nTest 3: ...");
		Graph test3 = new Graph();
		GraphLoader.loadGraph(test3, "data/greedy_ds_test.txt");
		System.out.println(test3.exportGraphString());

		List<Node> dominatingSet3 = DominatingSet.findGreedyDominatingSet(test3);
		System.out.print("Dominating Set: ");
		System.out.println(dominatingSet3);

		List<Node> minDominatingSet3 = DominatingSet.findMinimumDominatingSet(test3);
		System.out.print("Minimum DominatingSet: ");
		System.out.println(minDominatingSet3);

		// MORE TESTS!
        // Graph aaa = new Graph();
        // GraphLoader.loadGraph(aaa, "data/dominating_set_test.txt");
        // System.out.println(aaa.exportGraphString());
        // System.out.println(findMinimumDominatingSet(aaa));
        // System.out.println(findGreedyDominatingSet(aaa));

        // Graph bbb = new Graph();
        // GraphLoader.loadGraph(bbb, "data/dominating_set_test_2.txt");
        // System.out.println(bbb.exportGraphString());
        // System.out.println(findMinimumDominatingSet(bbb));
        // System.out.println(findGreedyDominatingSet(bbb));

        // Graph ccc = new Graph();
        // GraphLoader.loadGraph(ccc, "data/super_small_test.txt");
        // System.out.println(ccc.exportGraphString());
        // System.out.println(findMinimumDominatingSet(ccc));
        // System.out.println(findGreedyDominatingSet(ccc));

        // Graph ddd = new Graph();
        // GraphLoader.loadGraph(ddd, "data/greedy_ds_test.txt");
        // System.out.println(ddd.exportGraphString());
        // System.out.println(findMinimumDominatingSet(ddd));
        // System.out.println(findGreedyDominatingSet(ddd));

        // Graph eee = new Graph();
        // GraphLoader.loadGraph(eee, "data/small_test_graph.txt");
        // System.out.println(eee.exportGraphString());
        // System.out.println("Minimum DS: " + findMinimumDominatingSet(eee));
        // System.out.println("Greedy DS: " + findGreedyDominatingSet(eee));

	}
}