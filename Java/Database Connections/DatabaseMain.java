package uk.ac.bangor.cs.eeub22.project3;

/**
 * A main method for the University of Utopia database
 * 
 * @author Theo Rook
 *
 */
public class DatabaseMain {

	public static void main(String[] args) {
		DatabaseManager manager = new DatabaseManager();
		new DatabaseCLI(manager);

	}

}
