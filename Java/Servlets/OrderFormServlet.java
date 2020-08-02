

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class OrderFormServlet
 */
public class OrderFormServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public OrderFormServlet() {
        super();
        // TODO Auto-generated constructor stub
    }


	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		PrintWriter pw = response.getWriter();
		pw.append("<html><head><title>Order Confirm</title></head><body>");
		
		pw.append("<h1>Testing doPost</h1>");
		pw.append("<p>Description = " + request.getParameter("description") + "<br>");
		pw.append("Product Code = " + request.getParameter("code") + "<br>");
		pw.append("Quantity = " + request.getParameter("quantity") + "<br>");
		pw.append("Delivery Mode = " + request.getParameter("delivery") + "<br>");
		pw.append("Customer Number = " + request.getParameter("customer") + "</p>");
		
		pw.append("</body></html>");
		
	}

}
