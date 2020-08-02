package root.login;


import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import root.database.DatabaseManager;
import root.responses.AuthToken;
import root.responses.Response;
import root.responses.UserDetail;
import root.token.TokenStore;

/**
 * Servlet implementation class Signup_Servlet
 */
public class Signup_Servlet extends HttpServlet {
	private static final long serialVersionUID = 1L;

	public Signup_Servlet() {
        super();
    }

	protected void doPost(HttpServletRequest request, HttpServletResponse response) 
			throws ServletException, IOException 
	{	
    	HttpSession session = request.getSession();
    	String forward_to = "/dash";
    	
		String in_user = request.getParameter("u_name");
		String in_pass = request.getParameter("p_word");
		String in_cpass = request.getParameter("conf_p_word");	

		System.out.println(in_user);
		// 1. Check username not in DB
		Response username_check = DatabaseManager.getInstance().check_user_exists(in_user);
		if(username_check.getId() != 700)
		{
			// TODO: Error, already exists in db.
			forward_to = "signup.html?exist=true";
		}		
		
		// 2. Check passwords match.
		if(!in_pass.equals(in_cpass))
		{
			// TODO: Error, passwords don't match
			forward_to = "signup.html?pass_mismatch=true";
		}
		
		// 3. Get remaining details.
		String in_email = request.getParameter("e_mail");
		String in_fname = request.getParameter("f_name");
		String in_lname = request.getParameter("l_name");	
		String in_add1 = request.getParameter("add_1");
		String in_add2 = request.getParameter("add_2");
		String in_towncity = request.getParameter("town_city");	
		String in_county = request.getParameter("county_state");
		String in_country = request.getParameter("country");
		String in_landline = request.getParameter("landline");	
		String in_postcode = request.getParameter("post_code");		
		String in_company = request.getParameter("o_company");
		String in_mobile = request.getParameter("o_mobile");
		
		// 4. Make the User Object
		AuthToken user = new AuthToken();
		user.setRole(3);
		user.setEmail(in_email);
		user.setUsername(in_user);
		user.setPassword(in_pass);
		
		// 5. Make the User Details Object
		UserDetail details = new UserDetail();
		details.setFirst_name(in_fname);
		details.setLast_name(in_lname);
		details.setCompany(in_company);
		details.setAddr_1(in_add1);
		details.setAddr_2(in_add2);
		details.setTown_city(in_towncity);
		details.setCounty_state(in_county);
		details.setCountry(in_country);
		details.setPostcode(in_postcode);
		details.setLandline(in_landline);
		details.setMobile(in_mobile);
		
		// 6. Pass to database and await reply!
		Response from_db = DatabaseManager.getInstance().add_user_details(user, details);
		
		if(from_db.getId() != 700)
		{
			// TODO: Error, something went wrong
			forward_to = "signup.html?error=true";
		}
		
		System.out.println(from_db.getMessage());
		
		String token = TokenStore.getInstance().generateToken(user.getUsername(), user.getRole());

    	session.setAttribute("token", token);
    	response.sendRedirect(forward_to);
	}

}
