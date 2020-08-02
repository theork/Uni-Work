/**
 * contains the methods to create a BST using my Node class
 * 
 * @author Theo
 *
 */
public class BinarySearchTree {

	private Node root;
	private int size;
	private int comparisons;

	public BinarySearchTree() {
		root = null;
	}

	/**
	 * adds a node in the corresponding place in the BST
	 * 
	 * @param value of the node
	 * @return true-successful/false-duplicate
	 */
	public boolean insertValue(int value) {
		Node n = new Node(value);

		// if first value in tree, node becomes the root node
		if (root == null) {
			root = n;
			size++;
			return true;
		}

		Node curNode = root, prevNode = root;
		// iterates through the BST finding the correct space for the node
		while (true) {			
			prevNode = curNode;

			// searches left or right depending on the value
			if (value < curNode.getValue()) {
				curNode = curNode.getLeft();
				//insert
				if (curNode == null) {
					prevNode.setLeft(n);
					size++;
					return true;
				}
			} else if (value > curNode.getValue()) {
				curNode = curNode.getRight();
				if (curNode == null) {
					prevNode.setRight(n);
					size++;
					return true;
				}
				// runs if the value is equal to the current node's value - duplicated
			} else {
				return false;
			}
		}
	}

	/**
	 * searches the BST for the specified value
	 * 
	 * @param value to find
	 * @return true-found/false-not found
	 */
	public boolean search(int value) {
		Node curNode = root;
		comparisons = 0;
		// loops until end of tree is reached
		while (curNode != null) {
			// counts how many comparisons have had to be made
			comparisons++;
			if (value == curNode.getValue())
				return true;
			// finds whether to search left or right
			else if (value < curNode.getValue())
				curNode = curNode.getLeft();
			else
				curNode = curNode.getRight();
		}
		// search failed
		return false;
	}

	/**
	 * (only used in testing)
	 * 
	 * @return the size of the BST
	 */
	public int getSize() {
		return size;
	}

	/**
	 * @return number of comparisons the search has made
	 */
	public int getComparisons() {
		return comparisons;
	}
}
