package uk.ac.bangor.cs.eeub22.project3;

import java.io.IOException;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.SQLIntegrityConstraintViolationException;
import java.sql.Statement;
import java.util.Arrays;
import java.util.Properties;

import com.mysql.cj.jdbc.exceptions.MysqlDataTruncation;

/**
 * Handles the database side of the University of Utopia database
 * 
 * @author Theo Rook
 *
 */
public class DatabaseManager {
	private Connection con;
	private ResultSet results;
	private Statement statement;

	/**
	 * Constructor method
	 */
	public DatabaseManager() {
		con = Connect();
	}

	/**
	 * Creates a connection to the database
	 * 
	 * @return connection
	 */
	public Connection Connect() {
		InputStream stream = DatabaseManager.class.getResourceAsStream("/database.properties");
		Properties props = new Properties();
		Connection connection;
		try {
			props.load(stream);

			String driver = props.getProperty("jdbc.driver");
			String url = props.getProperty("jdbc.url");
			String username = props.getProperty("jdbc.username");
			String password = props.getProperty("jdbc.password");

			Class.forName(driver);
			connection = DriverManager.getConnection(url, username, password);
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
			return null;
		} catch (IOException e) {
			e.printStackTrace();
			return null;
		} catch (SQLException e) {
			e.printStackTrace();
			return null;
		}
		return connection;
	}

	/**
	 * Executes retrieval SQL statements (SELECT)
	 * 
	 * @param query
	 * @return results
	 */
	public ResultSet Execute(String query) {
		try {
			statement = con.createStatement();
			results = statement.executeQuery(query);

			return results;			
		} catch (SQLException e) {
			e.printStackTrace();
			return null;
		}
	}

	/**
	 * Executes data manipulation SQL statements (INSERT, UPDATE DELETE)
	 * 
	 * @param query
	 * @param params
	 */
	public void Update(String query, String[] params) {
		try {
			PreparedStatement pStatement = con.prepareStatement(query);
			for (int i = 1; i < params.length +1; i++) {
				// replaces '?' with the correct data
				pStatement.setString(i, params[i-1]);
			}
			int changed = pStatement.executeUpdate();
			if (changed == 0) 
				System.out.println("Error - invalid ID");
			
		} catch (SQLIntegrityConstraintViolationException e) {
			System.out.println("Error updating database - integrity constraint - check primary/foreign keys");
		} catch (MysqlDataTruncation e) {
			System.out.println("Error updating database - Input too long");
		} catch (SQLException e) {
			e.printStackTrace();
		}

	}

	/**
	 * Closes connection when finished
	 */
	public void close() {
		try {
			if (con != null) {
				con.close();
				System.out.println("Connection Closed");
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
}
