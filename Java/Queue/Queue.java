import java.util.Arrays;

/**
 * @author Theo Rook 
 * a class to simulate a queue data structure using an array
 */
public class Queue {
	private int start, end, size;
	private int[] queue;
	private final int max = 20;
	
	/**
	 * initialises values
	 */
	public Queue() {
		start = 0;
		size = 0;
		end = -1;	//increments to 1 on first addition
		queue = new int[max];
		
	}
	
	/**
	 * @param value
	 * adds a new value to the end of the queue
	 */
	public void Add(int value) {
		//checks if queue is full
		if(size == max) {
			return;
		}
		end++; size++;
		//cycles the array around
		if(end == max) {
			end = 0;
		}
		queue[end] = value;
	}
	
	/**
	 * removes a value from the start of the queue
	 */
	public void Remove() {
		//checks if array is empty
		if(size == 0) {
			return;
		}
		//doesn't remove the value in memory - just changes it to zero
		queue[start] = 0;
		start++; size--;
		//cycles the array around
		if(start == max) {
			start = 0;
		}		
	}
	
	/**
	 * @return value of the element at the front of the queue
	 */
	public int getFront() {
		return queue[start];
	}
	
	/**
	 * @return the size of the queue
	 */
	public int getSize() {
		return size;
	}
	
	
	/* 
	 * @return the queue in string form
	 */
	public String toString() {
		return Arrays.toString(queue);
	}
	
	/**
	 * @param value
	 * allows modification of the start value
	 * (used in checkouts to decrement the items)
	 */
	public void setStartValue(int value) {
		queue[start] = value;
	}
	
	/**
	 * @return array of the ordered queue
	 * sorts the array so that an array with element 0 has the corresponding first element in the queue
	 */
	public int[] getOrderedQueue() {
		int[] orderedQueue = new int[max];
		int j = start;
		for(int i = 0; i < size; i++) {
			if(j == max) {
				j = 0;
			}
			orderedQueue[i] = queue[j];
			j++;
		}
		return orderedQueue;
	}
	
	/**
	 * @param args
	 * TESTING
	 * many values tested for possible bugs with overfill
	 */
/*	public static void main(String[] args) {
		Queue test = new Queue();
		test.Add(1);
		test.Add(2);
		test.Add(3);
		test.Add(4);
		test.Add(5);
		System.out.println(test.toString());
		System.out.println(test.getFront());
		test.Remove();
		test.Remove();
		System.out.println(test.getFront());
		test.Add(1);
		test.Add(2);
		test.Add(3);
		test.Add(4);
		test.Add(5);
		test.Add(1);
		test.Add(2);
		test.Add(3);
		test.Add(4);
		test.Add(5);
		test.Add(1);
		test.Add(2);
		test.Add(3);
		test.Add(4);
		test.Add(5);
		test.Add(1);
		test.Add(2);
		test.Add(3);
		test.Add(4);
		test.Add(5);
		System.out.println(Arrays.toString(test.getOrderedQueue()));
		System.out.println(test.toString());
		test.Remove();
		System.out.println(test.toString());
		test.Remove();
		test.Remove();
		test.Remove();
		test.Remove();
		test.Remove();
		test.Remove();
		test.Remove();
		test.Remove();
		test.Remove();
		test.Remove();
		test.Remove();
		test.Remove();
		test.Remove();
		test.Remove();
		test.Remove();
		test.Remove();
		test.Add(1);
		test.Add(2);
		test.Add(3);
		test.Add(4);
		test.Add(5);
		test.Add(1);


		System.out.println(test.toString());
		System.out.println(Arrays.toString(test.getOrderedQueue()));
		
		
		
	}*/
}
