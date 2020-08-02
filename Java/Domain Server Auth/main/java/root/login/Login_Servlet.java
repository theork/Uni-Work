package root.login;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StringReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.Base64;

import javax.json.Json;
import javax.json.JsonObject;
import javax.json.JsonReader;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

/**
 * Servlet implementation class Login_Servlet
 */
public class Login_Servlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    public Login_Servlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String in_user = request.getParameter("u_name");
		String in_pass = request.getParameter("p_word");
		
		try {
			URL url = new URL("http://localhost:8080/api/login");
			HttpURLConnection conn = (HttpURLConnection) url.openConnection();
			String basicAuth = "Basic " + new String(Base64.getEncoder().encode((in_user + ":" + in_pass).getBytes()));

			conn.setRequestMethod("POST");
			conn.setRequestProperty("Accept", "application/json");
			conn.setRequestProperty ("Authorization", basicAuth);

			if (conn.getResponseCode() != 200) {
				throw new RuntimeException("Failed : HTTP error code : "
						+ conn.getResponseCode());
			}

			BufferedReader br = new BufferedReader(new InputStreamReader(
				(conn.getInputStream())));
			String output = br.readLine();

	        JsonReader reader = Json.createReader(new StringReader(output));
	        JsonObject t = reader.readObject();	         
	        reader.close();
	        
	        if(t.getInt("id") != 700)
	        {
	        	response.sendRedirect("index.html?err=true");
	        }
	        else
	        {
	        	HttpSession session = request.getSession();
	        	session.setAttribute("token", t.getString("token"));
	        	response.sendRedirect("/dash");
	        }        
			
			conn.disconnect();

		  } catch (MalformedURLException e) {

			e.printStackTrace();

		  } catch (IOException e) {

			e.printStackTrace();

		  }
	}

}
