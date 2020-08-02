package root.responses;

/**
 * Authentication response to be returned to
 * authenticate user on login.
 * @author ivslesser
 */

public class AuthToken extends Response
{
	String token;
	int uid;
	int role;
	String email;
	String username;
	String password;
	int primary_details;

	// TOKEN
	public String getToken() {
		return token;
	}
	public void setToken(String token) {
		this.token = token;
	}
	
	// UID
	public int getUid() {
		return uid;
	}
	
	public void setUid(int uid) {
		this.uid = uid;
	}
	
	// ROLE
	public int getRole() {
		return role;
	}

	public void setRole(int role) {
		this.role = role;
	}
	
	// EMAIL
	public String getEmail() {
		return email;
	}
	public void setEmail(String email) {
		this.email = email;
	}
	
	// PASSWORD
	public String getPassword() {
		return password;
	}
	
	public void setPassword(String password) {
		this.password = password;
	}
	
	// USERNAME
	public String getUsername() {
		return username;
	}
	public void setUsername(String username) {
		this.username = username;
	}
	
	// PRIMARY DETAILS
	public int getPrimary_details() {
		return primary_details;
	}
	
	public void setPrimary_details(int primary_details) {
		this.primary_details = primary_details;
	}
}
