package root.database;

import java.io.IOException;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Calendar;
import java.util.Date;
import java.util.Properties;

import org.mindrot.jbcrypt.BCrypt;

import root.responses.AuthToken;
import root.responses.Response;
import root.responses.UserDetail;

// For ref...
// BCrypt.checkpw(pass, result.getString("user_password")
// BCrypt.hashpw("password", BCrypt.gensalt(12))

/*
 * Return values:
 * * 700: Success.
 * * 701: Database error. SQLException:
 * * 702: Database error: Incorrect Username.
 * * 703: Database error: Incorrect Password.
 */

public class DatabaseManager {
	private static DatabaseManager instance = new DatabaseManager();

	private static String url;
	private static String username;
	private static String password;

	private Connection conn;

	private DatabaseManager() {

		Properties props = new Properties();
		InputStream stream = DatabaseManager.class.getResourceAsStream("/database.properties");
		try {
			props.load(stream);
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		String driver = props.getProperty("jdbc.driver");
		url = props.getProperty("jdbc.url");
		username = props.getProperty("jdbc.user");
		password = props.getProperty("jdbc.pass");

		try {
			// Class.forName("com.mysql.cj.jdbc.Driver");
			Class.forName(driver);
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}

//		try
//		{
//			// WINDOWS: 
//			//connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/domain", "root", "root");
//			// MAC: 
//			//conn = DriverManager.getConnection("jdbc:mysql://localhost:8889/domain", "root", "root");
//			conn = DriverManager.getConnection(url, username, password);
//			
//			if (conn == null)
//			{
//				System.out.println("Failed to make connection!");
//			}
//		}
//		catch (SQLException e)
//		{
//			System.out.println("MySQL Connection Failed!");
//			e.printStackTrace();
//		}
	}

	public static synchronized DatabaseManager getInstance() {
		return instance;
	}

	public Connection getConnection() throws SQLException {
		return DriverManager.getConnection(url, username, password);
	}

	/**
	 * Check if username exists in the database
	 * 
	 * @param user Username to check
	 * @return Response is failure or success.
	 */
	public Response check_user_exists(String user) {
		Connection conn = null;
		Response r = new Response();
		ResultSet rs = null;
		PreparedStatement st = null;

		try {
			conn = DatabaseManager.getInstance().getConnection();
			st = conn.prepareStatement("SELECT * FROM user WHERE username = ?");
			st.setString(1, user);

			rs = st.executeQuery();

			// Check if 0 results...
			if (!rs.isBeforeFirst()) {
				r.setId(700);
				r.setMessage("Success: Username not already in database.");
			} else {
				r.setId(704);
				r.setMessage("Database error: User already exists.");
			}
		} catch (SQLException e) {
			r.setId(701);
			r.setMessage("Database error. SQLException: " + e.getMessage());
		} finally {
			try {
				rs.close();
				st.close();
				conn.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}

		return r;
	}

	/**
	 * Verifies passed username and password exists in the database.
	 * 
	 * @param user Username to check
	 * @param pass Password to check
	 * @return AuthToken with user or error details.
	 */
	public AuthToken verify_user_password(String user, String pass) {
		PreparedStatement st = null;
		ResultSet rs = null;
		Connection conn = null;
		AuthToken auth = new AuthToken();
		auth.setUid(0);
		auth.setRole(0);

		try {
			conn = DatabaseManager.getInstance().getConnection();
			st = conn.prepareStatement("SELECT * FROM User WHERE Username = ?");
			st.setString(1, user);

			rs = st.executeQuery();

			// 1. Check if 0 results...
			if (!rs.isBeforeFirst()) {
				auth.setId(702);
				auth.setMessage("Database error: Incorrect Username.");
			} else {
				rs.next();
				// 2. Check password matches!
				if (BCrypt.checkpw(pass, rs.getString("Password"))) {
					// Match!
					auth.setId(700);
					auth.setUid(rs.getInt("id"));
					auth.setRole(rs.getInt("role"));
					auth.setMessage("Success: User logged in");
				} else {
					// No Match!
					auth.setId(703);
					auth.setMessage("Database error: Incorrect Password.");
				}
			}
		} catch (SQLException e) {
			auth.setId(701);
			auth.setMessage("Database error. SQLException: " + e.getMessage());
		} finally {
			try {
				rs.close();
				st.close();
				conn.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}

		auth.setUsername(user);
		return auth;
	}

	@SuppressWarnings("resource")
	public Response add_user_details(AuthToken user, UserDetail dets) {
		PreparedStatement st = null;
		Connection conn = null;
		Response r = new Response();
		String user_statement = "INSERT INTO `user` (`role`, `email`, `username`, `password`, `details`) VALUES (?, ?, ?, ?, 0)";
		String detail_statement = "INSERT INTO `details` (`UserID`, `fname`, `lname`, `company`, `address1`, `address2`, `town`, `region`, `country`, `postcode`, `landline`, `mobile`) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
		String update_user_statement = "UPDATE user SET details = ? WHERE userid = ?";

		try {
			conn = DatabaseManager.getInstance().getConnection();
			// 1. Add User
			st = conn.prepareStatement(user_statement, Statement.RETURN_GENERATED_KEYS);
			st.setInt(1, user.getRole());
			st.setString(2, user.getEmail());
			st.setString(3, user.getUsername());
			st.setString(4, BCrypt.hashpw(user.getPassword(), BCrypt.gensalt(12)));
			st.executeUpdate();

			// 1.1 Get user id auto generated.
			int user_id = 0;
			ResultSet urs = st.getGeneratedKeys();
			if (urs.next()) {
				user_id = urs.getInt(1);
				user.setUid(user_id);
				System.out.println(user_id);
			} else {
				// HANDLE ERROR!
				r.setId(704);
				r.setMessage("Database error: Cannot get user ID.");
			}

			urs.close();

			// 2. Add Details
			st = conn.prepareStatement(detail_statement, Statement.RETURN_GENERATED_KEYS);
			st.setInt(1, user_id);
			st.setString(2, dets.getFirst_name());
			st.setString(3, dets.getLast_name());
			st.setString(4, dets.getCompany());
			st.setString(5, dets.getAddr_1());
			st.setString(6, dets.getAddr_2());
			st.setString(7, dets.getTown_city());
			st.setString(8, dets.getCounty_state());
			st.setString(9, dets.getCountry());
			st.setString(10, dets.getPostcode());
			st.setString(11, dets.getLandline());
			st.setString(12, dets.getMobile());
			st.executeUpdate();

			// 2.1 Get detail id auto generated.
			int detail_id = 0;
			ResultSet drs = st.getGeneratedKeys();
			if (drs.next()) {
				detail_id = drs.getInt(1);
				user.setPrimary_details(detail_id);
				System.out.println(detail_id);
			} else {
				// HANDLE ERROR!
				r.setId(704);
				r.setMessage("Database error: Cannot get details.");
			}

			drs.close();

			// 3. Update user with primary details.
			st = conn.prepareStatement(update_user_statement);
			st.setInt(1, detail_id);
			st.setInt(2, user_id);
			st.executeUpdate();

			r.setId(700);
			r.setMessage("Success");
		} catch (SQLException e) {
			r.setId(701);
			r.setMessage("Database error. SQLException: " + e.getMessage());
		} finally {
			try {
				st.close();
				conn.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}

		return r;
	}

	/** 
	 * TEMP - should be done with ARP
	 *
	 * @param domain name
	 * @return whether present
	 */
	public Boolean CheckUniqueDomain(String domain) {
		PreparedStatement st = null;
		ResultSet rs = null;

		try {
			conn = DatabaseManager.getInstance().getConnection();
			st = conn.prepareStatement("SELECT COUNT('Name') FROM Domain WHERE 'Name' = ?");
			st.setString(1, domain);
			rs = st.executeQuery();
			rs.next();
			int result = rs.getInt(1);
			if (result == 0)
				return false;

		} catch (SQLException e) {

			e.printStackTrace();
		} finally {
			try {
				if (st != null)
					st.close();
				if (rs != null)
					rs.close();
				if (conn != null)
					conn.close();
			} catch (SQLException e) {
			}
		}
		return true;
	}

	public Response newDomain( int nameservers) {

		PreparedStatement st = null;

		try {
			conn = DatabaseManager.getInstance().getConnection();
//			String qMarks = "", nsName = "";
			java.util.Date jDate = new Date();
			Calendar cal = Calendar.getInstance();
			cal.setTime(jDate);
			cal.add(Calendar.YEAR, 1); // TODO change this so isn't hard coded as 1 year
			java.util.Date jRenewalDate = cal.getTime();
			java.sql.Date sqlTodayDate = new java.sql.Date(jDate.getTime());
			java.sql.Date sqlRenewalDate = new java.sql.Date(jRenewalDate.getTime());

//			for (int i = 0; i < nameservers; i++) {
//				qMarks += "?";
//				nsName += "NS" + (i + 1);
//			}

			st = conn.prepareStatement(
					"INSERT INTO `Domain` (`Name`, `ID`, `Registered`, `Renewal`, `Price`, `AutoRenew`,"
							+ " `NS1`, `NS2`, `NS3`, `NS4`, `NS5`) VALUES (?, 0, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
			
			


		} catch (SQLException e) {

			e.printStackTrace();
		} finally {
			try {
				if (conn != null)
					conn.close();
			} catch (SQLException e) {
			}
		}

		return null;

	}
}
