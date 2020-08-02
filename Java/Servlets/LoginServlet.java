
import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class LoginServlet
 */
public class LoginServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;

	/**
	 * @see HttpServlet#HttpServlet()
	 */
	public LoginServlet() {
		super();
		// TODO Auto-generated constructor stub
	}


	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse
	 *      response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		String username = request.getParameter("username");
		PrintWriter pw = response.getWriter();
		
		pw.append("<html><head><title>Logging in</title></head><body>");
		
		if (username == null || username.equals("")) {
			pw.append("<p>invalid</p>");
		} else {
			pw.append("<p>Hi user " + username + ". You are now logged into the system</p>");
		}
		
		pw.append("</body></html>");
	}

}
