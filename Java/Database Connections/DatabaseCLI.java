package uk.ac.bangor.cs.eeub22.project3;

import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.util.Arrays;
import java.util.Scanner;

/**
 * A command line interface to interact with a database for the University of
 * Utopia.
 * 
 * @author Theo Rook
 */
public class DatabaseCLI {

	private int option;
	private int subOption;
	private DatabaseManager mgr;
	private Scanner in;
	// defines the table and heading names for use later...
	private final String[] tables = { "Student", "Staff", "Modules", "Registered", "Teaches" };
	private final String[] studentH = { "student_id", "student_name", "degree_scheme" };
	private final String[] staffH = { "staff_id", "staff_name", "staff_grade" };
	private final String[] moduleH = { "module_id", "module_name", "credits" };
	private final String[] registeredH = { "student_id", "module_id" };
	private final String[] teachesH = { "staff_id", "module_id" };
	private final String[][] headings = { studentH, staffH, moduleH, registeredH, teachesH };

	/**
	 * Constructor method. Also has main menu loop
	 * 
	 * @param manager
	 */
	public DatabaseCLI(DatabaseManager manager) {
		mgr = manager;
		in = new Scanner(System.in);
		String input = "";
		while (!input.equals("0")) {
			DisplayMenu();
			input = in.nextLine(); // gets the user's selection
			MainOption(input);
		}
		in.close();
	}

	/**
	 * Displays the main menu to the console
	 */
	public void DisplayMenu() {
		System.out.println("\n\n");
		System.out.println("Main Menu");
		System.out.println("*********");
		System.out.println("1. Student");
		System.out.println("2. Staff");
		System.out.println("3. Modules");
		System.out.println("4. Registrations");
		System.out.println("5. Teaches");
		System.out.println("6. Reports");
		System.out.println("0. Quit");
		System.out.print("\n:> ");

	}

	/**
	 * Displays the sub menu to the console and appends the table name
	 * 
	 * @param table
	 */
	public void DisplaySubMenu(String table) {
		System.out.println("");
		System.out.println(table + " Sub Menu");
		System.out.println("********************");
		System.out.println("1. Display " + table);
		System.out.println("2. Add " + table);
		System.out.println("3. Delete " + table);
		System.out.println("4. Update " + table);
		System.out.println("0. Back ");
		System.out.print("\n:> ");
	}

	/**
	 * Displays the reports sub menu
	 */
	public void DisplayReportMenu() {
		System.out.println("");
		System.out.println("Reports");
		System.out.println("*******");
		System.out.println("1. Modules Taught by");
		System.out.println("2. Students Registered on");
		System.out.println("3. Staff Who Teach Student");
		System.out.println("4. Staff Who Teach More Than One Module");
		System.out.println("0. Back");
		System.out.print("\n:> ");
	}

	/**
	 * Sends SELECT statements to manager and displays the results
	 * 
	 * @param query
	 */
	public void List(String query) {
		ResultSet result = mgr.Execute(query);

		if (result == null) {
			System.out.println("Oh no! Error executing SQL");
			return;
		}

		try {
			// gets the number of columns for the table
			ResultSetMetaData meta = result.getMetaData();
			int columns = meta.getColumnCount();

			// displays column headings in nice format
			for (int i = 1; i < columns + 1; i++)
				System.out.printf("%-50s", meta.getColumnLabel(i));
			System.out.println("");
			for (int i = 0; i < (50 * columns); i++)
				System.out.print("_");
			System.out.println("");

			// displays the output in rows/column format
			while (result.next()) {

				for (int i = 1; i < columns + 1; i++) {
					System.out.printf("%-50s", result.getString(i) + "   ");
				}
				System.out.println("");
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}

		try {
			result.close();
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}

	/**
	 * Gets parameters and sends INSERT statement to manager
	 * 
	 * @param query
	 * @param number of parameters
	 */
	public void AddNew(String query, int params) {
		String[] inputs = new String[params];
		System.out.println("");
		// repeats depending on how many columns in the table
		for (int i = 0; i < params; i++) {
			System.out.print("Please input parameter " + (i + 1) + " :> ");
			inputs[i] = in.nextLine();
		}
		mgr.Update(query, inputs);
	}

	/**
	 * Gets id of record to delete and sends DELETE statement to manager
	 * 
	 * @param query
	 */
	public void Delete(String query) {
		System.out.print("Please input the " + headings[option - 1][0] + " :> ");
		if (option == 4 || option == 5) {
			String inA = in.nextLine();
			System.out.print("Please input the " + headings[option - 1][1] + " :> ");
			String[] delID = { inA, in.nextLine() };
			mgr.Update(query, delID);
		} else {
			String[] delID = { in.nextLine() }; // sends as array so a new method doesn't have to be created
			mgr.Update(query, delID);
		}
	}

	/**
	 * Gets id of record to delete and new fields from user. Sends UPDATE statements
	 * to manager
	 * 
	 * @param query
	 * @param j      - id number
	 * @param number of parameters
	 */
	public void Update(String query, int params, int j) {
		String[] inputs = new String[(params + j)];
		System.out.print("Input current " + headings[option - 1][0] + " :> ");
		inputs[inputs.length - 1] = in.nextLine(); // puts the id at the end of the array

		if (option == 4 | option == 5) {
			System.out.print("Input current " + headings[option - 1][1] + " :> ");
			inputs[inputs.length - 2] = inputs[inputs.length - 1];
			inputs[inputs.length - 1] = in.nextLine();
		}

		for (int i = 0; i < params; i++) {
			System.out.print("Set column " + (i + 1) + " :> ");
			inputs[i] = in.nextLine();
		}
		mgr.Update(query, inputs);

	}

	/**
	 * Runs correct methods for what the user has selected in the main menu
	 * 
	 * @param input
	 */
	public void MainOption(String input) {
		// converts to int to prevent invalid characters and makes it easier to
		// manipulate
		try {
			option = Integer.parseInt(input);
		} catch (NumberFormatException e) {
			System.out.println("Please input a number");
			return;
		}
		System.out.println("");

		switch (option) {
		// the following 5 options do the same thing - sends user to the sub menu
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			String subInput = "";
			while (!subInput.equals("0")) {
				DisplaySubMenu(tables[option - 1]); // finds the name of the selected table to show relevant sub menu
				subInput = in.nextLine();
				SubOption(subInput);
			}
			break;
		case 6:
			String repInput = "";
			while (!repInput.equals("0")) {
				DisplayReportMenu();
				repInput = in.nextLine();
				RepOption(repInput);
			}
			break;
		case 0:
			mgr.close();
			System.out.println("Goodbye!");
			break;
		default:
			System.out.println("Invalid option");
		}
	}

	/**
	 * Creates SQL queries based on the user menu selections
	 * 
	 * @param input
	 */
	public void SubOption(String input) {
		String t = tables[option - 1];
		int len = headings[option - 1].length;
		// converts to int to prevent invalid characters and makes it easier to
		// manipulate
		try {
			subOption = Integer.parseInt(input);
		} catch (NumberFormatException e) {
			System.out.println("Please input a number");
			return;
		}
		System.out.println("");

		switch (subOption) {
		case 1:
			List("SELECT * FROM " + t);
			break;
		case 2:
			// formats the correct number of question marks for the prepared statement
			String qMarks = "";
			for (int i = 0; i < len; i++) {
				if (i == len - 1) { // no comma for last entry
					qMarks += "?";
					break;
				}
				qMarks += "?,";

			}
			AddNew("INSERT INTO " + t + " VALUES(" + qMarks + ")", len);
			break;
		case 3:
			// 'headings[option - 1][x]' finds the id field
			if (option == 4 || option == 5)
				Delete("DELETE FROM " + t + " WHERE " + headings[option - 1][0] + "=? AND " + headings[option - 1][1]
						+ "=?");
			else
				Delete("DELETE FROM " + t + " WHERE " + headings[option - 1][0] + "=?");
			break;
		case 4:
			// formats headings into a string and question marks
			String head = "";
			for (int i = 0; i < len; i++) {
				if (i == len - 1) { // no comma for last entry
					head += headings[option - 1][i] + "=?";
					break;
				}
				head += headings[option - 1][i] + "=?,";
			}
			if (option == 4 || option == 5)
				Update("UPDATE " + t + " SET " + head + " WHERE " + headings[option - 1][0] + "=? AND "
						+ headings[option - 1][1] + "=?", len, 2);
			else
				Update("UPDATE " + t + " SET " + head + " WHERE " + headings[option - 1][0] + "=?", len, 1);
			break;
		case 0:
			// will exit loop
			break;
		default:
			System.out.println("Invalid option");
		}
	}

	/**
	 * Finds the user option and creates complex SQL statements
	 * @param input
	 */
	public void RepOption(String input) {
		// converts to int to prevent invalid characters and makes it easier to
		// manipulate
		int repOption = -1;
		try {
			repOption = Integer.parseInt(input);
		} catch (NumberFormatException e) {
			System.out.println("Please input a number");
			return;
		}

		switch (repOption) {

		case 1:
			System.out.print("Input member of staff :> ");
			String staff = in.nextLine();
			if (checkInput(staff)) {
				List("SELECT m.module_id, m.module_name FROM Teaches t " + 
						"JOIN Modules m ON t.module_id = m.module_id " + 
						"JOIN Staff s ON t.staff_id = s.staff_id " + 
						"WHERE s.staff_name = '" + staff + "'");
			}
			break;
		case 2:
			System.out.print("Input a module name :> ");
			String module = in.nextLine();
			if (checkInput(module)) {
				List("SELECT s.student_id, s.student_name FROM Registered r " + 
						"JOIN Student s ON r.student_id = s.student_id " + 
						"JOIN Modules m ON r.module_id = m.module_id " + 
						"WHERE m.module_name = '" + module + "'");
			}
			break;

		case 3:
			System.out.print("Input a student id :> ");
			String student = in.nextLine();
			if (checkInput(student)) {
				List("SELECT st.staff_id, st.staff_name, m.module_id FROM Registered r " + 
						"JOIN Teaches t ON r.module_id = t.module_id " + 
						"JOIN Student s ON r.student_id = s.student_id " + 
						"JOIN Modules m ON t.module_id = m.module_id " + 
						"JOIN Staff st ON t.staff_id = st.staff_id " + 
						"WHERE s.student_id = '" + student + "'");
			}
			break;
		case 4:
			List("SELECT s.staff_id, s.staff_name FROM Teaches t " + 
					"JOIN Modules m ON t.module_id = m.module_id " + 
					"JOIN Staff s ON t.staff_id = s.staff_id " + 
					"GROUP BY s.staff_id " + 
					"HAVING COUNT(s.staff_id) > 1");

			break;
		case 0:
			// will exit loop
			break;
		default:
			System.out.println("Invalid option");
		}
	}

	/**
	 * checks the user input for invalid characters to prevent SQL injection
	 * 
	 * @param user input
	 * @return true - good input | false - bad input
	 */
	public boolean checkInput(String q) {
		String[] invalidChars = { ";", "(", ")", "'", "=" };
		for (int i = 0; i < invalidChars.length; i++) {
			if (q.contains(invalidChars[i])) {
				System.out.println("Contains invalid character:  " + Arrays.deepToString(invalidChars));
				return false;
			}
		}
		return true;

	}
}
