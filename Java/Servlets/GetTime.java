
import java.io.IOException;
import java.io.PrintWriter;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class GetTime
 */
public class GetTime extends HttpServlet {
	private static final long serialVersionUID = 1L;

	/**
	 * @see HttpServlet#HttpServlet()
	 */
	public GetTime() {
		super();
		// TODO Auto-generated constructor stub
	}

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse
	 *      response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		// gets the selected name from the drop down
		String zone = request.getParameter("TimeZones");
		PrintWriter pw = response.getWriter();
		pw.append("<html><head><title>Time in UTC" + zone + "</title></head><body>");
		// back button
		pw.append("<form action=\"TimeZones.html\" method=\"get\"><input type=\"submit\" value=\"Back\"></form>");

		DateFormat dFormat = new SimpleDateFormat("HH:mm:ss");
		Calendar calTime = Calendar.getInstance();

		double hDifference = 0;
		int mDifference = 0;
		try {
			// removes +/- and gets the time zone difference
			hDifference = Double.parseDouble(zone.substring(1, zone.length()));
			// gets the minutes if needed
			if (zone.contains("."))
				mDifference = Integer.parseInt(zone.replaceFirst("(.*)[.]", ""));
		} catch (NumberFormatException e) {
			pw.append("<p>SOMETHING WENT WRONG CONVERTING TO INT</p>");
		}

		if (zone.startsWith("-")) {
			hDifference = -hDifference;
			mDifference = -mDifference;
		}

		//calculates current time in set time zone
		calTime.add(Calendar.HOUR, (int) hDifference);
		calTime.add(Calendar.MINUTE, mDifference);
		String time = dFormat.format(calTime.getTime());

		pw.append("<h1>Time in UTC" + zone + " is " + time + "</h1>");

		pw.append("</body></html>");
	}

}
