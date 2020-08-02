

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Random;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class RandomFactServlet
 */
public class RandomFactServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
	
	private int siteCounter = 0;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public RandomFactServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		siteCounter++;
		Random rand = new Random();
		int factNum = rand.nextInt(10);
		String[] facts = {"Computers are good at maths",
						  "The first electronic computer ENIAC weighed more than 27 tons and took up 1800 square feet.",
						  "Only about 10% of the world’s currency is physical money, the rest only exists on computers.",
						  "TYPEWRITER is the longest word that you can write using the letters only on one row of the keyboard of your computer.",
						  "Doug Engelbart invented the first computer mouse in around 1964 which was made of wood.",
						  "There are more than 5000 new computer viruses are released every month.",
						  "Around 50% of all Wikipedia vandalism is caught by a single computer program with more than 90% accuracy.",
						  "The password for the computer controls of nuclear tipped missiles of the U.S was 00000000 for eight years.",
						  "Approximately 70% of virus writers are said to work under contract for organized crime syndicates.",
						  "HP, Microsoft and Apple have one very interesting thing in common – they were all started in a garage."};
		
		
		PrintWriter pw = response.getWriter();
		pw.append("<html><head><title>Random Fact</title></head><body>");
		
		pw.append("<h1>Fact of the Day</h1>");
		pw.append("<p>" + facts[factNum] + "</p>");		
		pw.append("<p>Site Hits = " + siteCounter + "</p>");
		
		pw.append("</body></html>");
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

	}

}
