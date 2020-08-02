package root.login;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import root.token.TokenStore;

public class Logout_Servlet extends HttpServlet {
	private static final long serialVersionUID = 1L;

    public Logout_Servlet() {
        super();
    }

	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    	HttpSession session = request.getSession();
    	if(session.getAttribute("token") != null)
    	{
    		TokenStore.getInstance().invalidate((String) session.getAttribute("token"));
    	}
    	
    	session.invalidate();
    	response.sendRedirect("index.html");	
	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doGet(request, response);
	}

}