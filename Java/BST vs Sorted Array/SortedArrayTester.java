import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;
import java.util.Random;

/**
 * tests the efficiency of binary search of arrays 
 * 
 * @author Theo
 *
 */
public class SortedArrayTester {

	public static void main(String[] args) {
		// initialises the sizes of the arrays
		final int MAX = 10000, MIN = 100, SIZE = MAX - MIN;
		Random rand = new Random();
		// holds the results before writing to file
		double[][] data = new double[SIZE][2];

		// iterates through all array sizes
		for (int arrSize = MIN; arrSize < MAX; arrSize++) {
			int compSum = 0;

			// tests each size 1000 times
			for (int i = 0; i < 1000; i++) {
				int[] array = RandomArray(arrSize);
				//gets a random value in the array to search for
				int randVal = array[rand.nextInt(arrSize)];
				//searches the array and holds the amount of comparisons
				int comps = BinarySearch(array, randVal);

				//checks if the search was successful
				if (comps != -1)
					compSum += comps;

			}
			double avgComp = compSum / 1000.0;
			System.out.println("Array Size = " + arrSize + " | Average Comparisons = " + avgComp);
			data[arrSize - MIN][0] = arrSize;
			data[arrSize - MIN][1] = avgComp;
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
			fWriter = new FileWriter("arrData.csv");
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
	 * creates an array of random numbers
	 * 
	 * @param length of array
	 * @return random array
	 */
	public static int[] RandomArray(int length) {
		int[] arr = new int[length];
		Random rand = new Random();

		for (int i = 0; i < length; i++) {
			// creates a large range of numbers because the array will be sorted and would
			// all be the same if was only up to the length
			arr[i] = rand.nextInt(length * 5);

			// makes sure that the values are unique for a good comparison with BST. Removed
			// because of inefficiency...
//			for (int j = 0; j < i; j++) {
//				if (arr[i] == arr[j]) {
//					i--;
//					System.out.println("test");
//					break;
//				}
//			}
		}

		Arrays.sort(arr);

		return arr;
	}

	/**
	 * searches an array for a value 
	 *
	 * @param array to search
	 * @param value to search for
	 * @return number of comparisons
	 */
	public static int BinarySearch(int[] arr, int val) {
		int comparisons = 0, bot = 0, top = arr.length, mid = top / 2;

		while (true) {
			mid = bot + (top - bot) / 2;

			comparisons++;
			if (top < bot) {
				System.out.println("ERROR- search failed");
				return -1;
			}
			if (arr[mid] == val)
				return comparisons;
			else if (arr[mid] < val)
				bot = mid + 1;
			else if (arr[mid] > val)
				top = mid - 1;
		}
	}
}
