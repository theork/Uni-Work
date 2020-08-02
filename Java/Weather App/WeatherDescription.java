import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.table.DefaultTableModel;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.stream.XMLOutputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.XMLStreamWriter;
import javax.xml.xpath.XPath;
import javax.xml.xpath.XPathConstants;
import javax.xml.xpath.XPathExpression;
import javax.xml.xpath.XPathExpressionException;
import javax.xml.xpath.XPathFactory;

import org.w3c.dom.Document;
import org.xml.sax.SAXException;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JTextArea;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Date;
import java.awt.event.ActionEvent;
import javax.swing.JTable;
import java.awt.Font;

public class WeatherDescription extends JFrame {
	private JTextField textField;
	private JTextArea textArea;
	private URL url;
	private JLabel lblIcon;
	private JTable table;
	private DefaultTableModel model;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					WeatherDescription frame = new WeatherDescription();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	public WeatherDescription() {
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 494, 374);
		getContentPane().setLayout(new BorderLayout(0, 0));

		JPanel panel = new JPanel();
		getContentPane().add(panel, BorderLayout.CENTER);
		panel.setLayout(null);

		textField = new JTextField();
		textField.setBounds(110, 41, 298, 20);
		panel.add(textField);
		textField.setColumns(10);

		lblIcon = new JLabel("");
		lblIcon.setBounds(48, 98, 46, 19);
		panel.add(lblIcon);

		// creating the table with following contents
		String[] tableHeaders = { "Temperature", "Wind Direction", "Wind Speed", "Humidity", "Pressure", "Trend",
				"Visibility" };
		Object[][] test = {
				{ "Temperature", "Wind Direction", "Wind Speed", "Humidity", "Pressure", "Trend", "Visibility" },
				{ "-", "-", "-", "-", "-", "-", "-" } };
		table = new JTable(test, tableHeaders);
		// prevents the user from editing the table
		model = new DefaultTableModel(test, tableHeaders) {
			@Override
			public boolean isCellEditable(int r, int c) {
				return false;
			}
		};
		table.setModel(model);
		table.setFont(new Font("Tahoma", Font.PLAIN, 9));
		//makes the text flow to the next line and splits it on whitespace
		textArea.setLineWrap(true);
		textArea.setWrapStyleWord(true);
		table.setBounds(10, 277, 468, 32);
		panel.add(table);

		JButton btnForecast = new JButton("Forecast");
		btnForecast.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {

				String weatherTitle = null;
				String weatherInfo = null;
				String weatherDesc = null;

				// gets unformatted text from input field
				String search = textField.getText().toLowerCase().trim();
				String geoID = SearchForLocation(search);

				try {
					// gets the bbc weather rss xml
					url = new URL("https://weather-broker-cdn.api.bbci.co.uk/en/observation/rss/" + geoID);

					// opens DOM XML parser
					DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
					DocumentBuilder builder = factory.newDocumentBuilder();
					Document document = builder.parse(url.openStream());

					// creates a path through the xml to get the required data
					XPathFactory xpFactory = XPathFactory.newInstance();
					XPath xpath = xpFactory.newXPath();
					XPathExpression expr = xpath.compile("/rss/channel/item/title");
					weatherTitle = (String) expr.evaluate(document, XPathConstants.STRING);
					textArea.setText(weatherTitle);

					expr = xpath.compile("/rss/channel/item/description");
					weatherDesc = (String) expr.evaluate(document, XPathConstants.STRING);

				// provides relevant error messages
				} catch (MalformedURLException e1) {
					textArea.setText("Error inputting created URL");
					e1.printStackTrace();
				} catch (ParserConfigurationException e1) {
					textArea.setText("Error creating document builder");
					e1.printStackTrace();
				} catch (SAXException | IOException | XPathExpressionException e1) {
					textArea.setText("Error opening xml document - no weather forecast for inputted location?");
					e1.printStackTrace();
				}

				// gets the title from the data
				if (weatherTitle != null) {
					int index1 = 0;
					int index2 = 0;
					for (int i = 0; i < weatherTitle.length(); i++) {
						if (weatherTitle.substring(i, i + 1).equals(":")) {
							index1 = i;
						}

						if (weatherTitle.substring(i, i + 1).equals(",")) {
							index2 = i;
						}
					}
					weatherInfo = weatherTitle.substring(index1 + 1, index2).trim();
				}

				// default - provides error if nothing can be found
				String imgFile = "error.png";

				// rss feed can provide bonus adjectives to the weather so must use a contain
				if (weatherInfo.toLowerCase().contains("cloud"))
					imgFile = "cloud.png";
				if (weatherInfo.toLowerCase().contains("rain"))
					imgFile = "rain.png";

				// handles some other weather titles that i have found
				switch (weatherInfo) {
				case "Hazy":
					imgFile = "cloud.png";
					break;
				case "Sunny":
					imgFile = "sun.png";
					break;
				}

				// places the icon in the window
				ImageIcon image = new ImageIcon(WeatherSerialising.class.getResource(imgFile));
				lblIcon.setIcon(image);

				// puts the detailed weather in an array where the different elements are
				// separated by commas
				String[] weatherDescs = weatherDesc.split(",");
				// iterates through array, removing the headers and adding to table
				for (int i = 0; i < weatherDescs.length; i++) {
					weatherDescs[i] = weatherDescs[i].replaceFirst("(.*):", "").trim();
					model.setValueAt(weatherDescs[i], 1, i);
				}
			}
		});

		btnForecast.setBounds(196, 94, 89, 23);
		panel.add(btnForecast);

		JLabel lblLocation = new JLabel("Location:");
		lblLocation.setBounds(58, 44, 54, 14);
		panel.add(lblLocation);

		textArea = new JTextArea();
		textArea.setBounds(91, 143, 317, 96);
		panel.add(textArea);

	}

	/**
	 * searches for a given location using the geonames api
	 * @param location
	 * @return geoid 
	 */
	public String SearchForLocation(String location) {
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		
		//removes spaces - can't have spaces in URL
		location = location.replaceAll(" ", "");

		try {
			DocumentBuilder builder = factory.newDocumentBuilder();

			//searches the geonames api for the location
			URL searchURL = new URL(
					"http://api.geonames.org/search?q=" + location + "&maxRows=1&lang=en&username=theor");
			Document document = builder.parse(searchURL.openStream());
			//creates a path through the xml
			XPathFactory xpFactory = XPathFactory.newInstance();
			XPath xpath = xpFactory.newXPath();
			XPathExpression expr = xpath.compile("/geonames/totalResultsCount");
			//checks if there has is no results returned
			if ((double) expr.evaluate(document, XPathConstants.NUMBER) == 0) {
				return null;
			}
			expr = xpath.compile("/geonames/geoname/geonameId");
			return (String) expr.evaluate(document, XPathConstants.STRING);

		} catch (ParserConfigurationException e) {
			textArea.setText("Error creating search document builder");
			e.printStackTrace();
			return null;
		} catch (MalformedURLException e) {
			textArea.setText("Error inputting search URL");
			e.printStackTrace();
			return null;
		} catch (SAXException | IOException | XPathExpressionException e) {
			textArea.setText("Error opening xml search document");
			e.printStackTrace();
			return null;
		}

	}


}
