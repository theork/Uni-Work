import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

/**
 * Finds the average number of comparisons to find a value in a BST
 * 
 * @author Theo
 *
 */
public class BSTTester {

	public static void main(String[] args) {
		Random rand = new Random();
		// sets the min and max sizes of the tree
		final int MAXTREE = 10000, START = 100, SIZE = MAXTREE - START;
		// where the results are saved before going into a file
		double[][] data = new double[SIZE][2];

		// iterates through every possible tree size
		for (int treeSize = START; treeSize < MAXTREE; treeSize++) {
			int sum = 0;
			// creates a permutation to fill random data into the BST which saves a bit of
			// time rather than randomising every value
			int[] perm = Permutation(0, treeSize);
			// provides 1000 results per tree size
			for (int i = 0; i < 1000; i++) {
				BinarySearchTree tree = new BinarySearchTree();				
				perm = Shuffle(perm);
				// iterates through every node in the tree, adding values
				for (int j = 0; j < treeSize; j++) {
					// checks for any duplicates
					while (!tree.insertValue(perm[j])) {
						// this shouldn't happen when using permutations
						System.out.println("dupe");
					}
				}

				// finds the value if it exists
				if (tree.search(rand.nextInt(treeSize)))
					// calculates a running total of the number of comparisons for the tree size
					sum += tree.getComparisons();
				else
					System.out.println("FAIL");
			}
			// calculates the average comparisons
			double comps = sum / 1000.0;
			data[treeSize - START][0] = treeSize;
			data[treeSize - START][1] = comps;
			System.out.println("Tree Size = " + treeSize + " | Average Comparisons = " + comps);
		}

		// at the end of the program, the tree sizes and their corresponding number of
		// comparisons are saved to a CSV file
		StringBuilder sizeCSV = new StringBuilder(SIZE);
		StringBuilder compCSV = new StringBuilder(SIZE);
		for (int i = 0; i < SIZE; i++) {
			sizeCSV.append(data[i][0]);
			compCSV.append(data[i][1]);
			if (i != SIZE - 1) {
				sizeCSV.append(", ");
				compCSV.append(", ");
			}
		}

		FileWriter fWriter = null;
		try {
			fWriter = new FileWriter("data.csv");
			fWriter.write(sizeCSV.toString() + "\n");
			fWriter.write(compCSV.toString());
		} catch (IOException e) {
			System.out.println("FAILURE WRITING TO CSV");
			e.printStackTrace();
		} finally {
			if (fWriter != null) {
				try {
					fWriter.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
	}

	/**
	 * @param start of the permutation range
	 * @param end   of the permutation range
	 * @return array of randomly shuffled values
	 */
	public static int[] Permutation(int start, int end) {
		int length = end - start;
		int[] perm = new int[length];
		int incr = start;

		// adds the values into the array
		for (int i = 0; i < length; i++) {
			perm[i] = incr;
			incr++;
		}
		
		perm = Shuffle(perm);
		return perm;
	}

	/**
	 * randomly shuffles the values in the array using a Fisher–Yates algorithm
	 *
	 * @param arr
	 * @return
	 */
	public static int[] Shuffle(int[] arr) {
		Random rand = new Random();
		for (int i = arr.length - 1; i > 0; i--) {
			int randi = rand.nextInt(i + 1);
			int temp = arr[randi];
			arr[randi] = arr[i];
			arr[i] = temp;
		}
		return arr;
	}	
}
