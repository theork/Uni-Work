/**
 * 
 * each node makes up a BST. Every node holds a numeric value. Contains methods
 * to interact with each node
 * 
 * @author Theo
 *
 */
public class Node {

	private int value;
	// references the two possible branches that the node has
	private Node left, right;

	public Node(int value) {
		this.value = value;
		left = null;
		right = null;
	}

	/**
	 * @return the value
	 */
	public int getValue() {
		return value;
	}

	/**
	 * @param value the value to set
	 */
	public void setValue(int value) {
		this.value = value;
	}

	/**
	 * @return the left
	 */
	public Node getLeft() {
		return left;
	}

	/**
	 * @param left the left to set
	 */
	public void setLeft(Node left) {
		this.left = left;
	}

	/**
	 * @return the right
	 */
	public Node getRight() {
		return right;
	}

	/**
	 * @param right the right to set
	 */
	public void setRight(Node right) {
		this.right = right;
	}

}
