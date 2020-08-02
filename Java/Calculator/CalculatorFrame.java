import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Desktop;
import java.awt.Dimension;

import java.awt.GridLayout;
import java.awt.Toolkit;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.StringSelection;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.text.DecimalFormat;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.border.EmptyBorder;

/**
 * Title: Calculator Frame *
 * 
 * @author eeub22
 * @version 1.0 Date: 05/11/18
 */
public class CalculatorFrame extends JFrame {

	String currentText = "";
	double currentNum = 0;
	int currentDecimal = 0;
	boolean decimal = false;
	int zeroCount = 0;
	boolean digitGrouping = true;
	double memory = 0;

	public CalculatorFrame() {
		final int FRAME_WIDTH = 350;
		final int FRAME_HEIGHT = 240;

		// creates the frame
		JFrame frame = new JFrame();
		frame.getContentPane().setPreferredSize(new Dimension(FRAME_WIDTH, FRAME_HEIGHT));
		frame.setTitle("Calculator");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		JPanel mainKeys = new JPanel();
		Calculator calc = new Calculator();

		// creates the text field
		JTextField field = new JTextField("0");
		// user can't change the values directly
		field.setEditable(false);
		// right align
		field.setHorizontalAlignment(JTextField.TRAILING);
		field.setBackground(Color.WHITE);

		// creates a layout of 4x6 with 5px padding between buttons
		GridLayout buttonLayout = new GridLayout(4, 6, 5, 5);
		mainKeys.setLayout(buttonLayout);
		// pads the outside of the panel by five pixels
		mainKeys.setBorder(new EmptyBorder(5, 5, 5, 5));

		// creating the buttons
		JButton b0 = new JButton("0");
		JButton b1 = new JButton("1");
		JButton b2 = new JButton("2");
		JButton b3 = new JButton("3");
		JButton b4 = new JButton("4");
		JButton b5 = new JButton("5");
		JButton b6 = new JButton("6");
		JButton b7 = new JButton("7");
		JButton b8 = new JButton("8");
		JButton b9 = new JButton("9");
		JButton bDiv = new JButton("/");
		JButton bMult = new JButton("*");
		JButton bMinus = new JButton("-");
		JButton bPlus = new JButton("+");
		JButton bPnt = new JButton(".");
		JButton bEqls = new JButton("=");

		JButton bSign = new JButton("+/-");
		JButton bSqrt = new JButton("-/");
		JButton bPcent = new JButton("%");
		JButton bRec = new JButton("1/x");

		JButton bMC = new JButton("MC");
		JButton bMR = new JButton("MR");
		JButton bMS = new JButton("MS");
		JButton bMAdd = new JButton("M+");

		JButton bBack = new JButton("BS");
		JButton bCE = new JButton("CE");
		JButton bC = new JButton("C");

		// changes the colour of the buttons to red or blue
		JButton[] blues = { b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, bSign, bSqrt, bPcent, bRec, bPnt };
		JButton[] reds = { bDiv, bMult, bMinus, bPlus, bEqls, bMC, bMR, bMS, bMAdd, bBack, bCE, bC };
		for (int i = 0; i < blues.length; i++) {
			blues[i].setForeground(Color.BLUE);
		}
		for (int i = 0; i < reds.length; i++) {
			reds[i].setForeground(Color.RED);
		}

		// creates a new panel for the buttons at the top with a new grid layout of 1x3
		JPanel topBtns = new JPanel();
		GridLayout inLine = new GridLayout(1, 3, 5, 5);
		topBtns.setLayout(inLine);
		// pads the panel with a large empty space to the left to get the sizing right
		topBtns.setBorder(new EmptyBorder(5, 70, 0, 5));

		topBtns.add(bBack);
		topBtns.add(bCE);
		topBtns.add(bC);

		// adds the buttons to the panel in the right order
		mainKeys.add(bMC);
		mainKeys.add(b7);
		mainKeys.add(b8);
		mainKeys.add(b9);
		mainKeys.add(bDiv);
		mainKeys.add(bSqrt);
		mainKeys.add(bMR);
		mainKeys.add(b4);
		mainKeys.add(b5);
		mainKeys.add(b6);
		mainKeys.add(bMult);
		mainKeys.add(bPcent);
		mainKeys.add(bMS);
		mainKeys.add(b1);
		mainKeys.add(b2);
		mainKeys.add(b3);
		mainKeys.add(bMinus);
		mainKeys.add(bRec);
		mainKeys.add(bMAdd);
		mainKeys.add(b0);
		mainKeys.add(bSign);
		mainKeys.add(bPnt);
		mainKeys.add(bPlus);
		mainKeys.add(bEqls);

		// creates the menu bar
		JMenuBar menuBar = new JMenuBar();

		JMenu mFile = new JMenu("File");
		JMenuItem mCopy = new JMenuItem("Copy");
		mFile.add(mCopy);
		JMenuItem mPaste = new JMenuItem("Paste");
		mFile.add(mPaste);
		menuBar.add(mFile);

		// finds whether the paste button should be enabled or disabled
		String cb = getClipboard();
		if (isDouble(cb) == true && cb != null) {
			mPaste.setEnabled(true);
		} else {
			mPaste.setEnabled(false);
		}

		JMenu mView = new JMenu("View");
		JMenuItem mStandard = new JMenuItem("Standard");
		mView.add(mStandard);
		JMenuItem mScientific = new JMenuItem("Scientific");
		mView.add(mScientific);
		mView.addSeparator();
		JMenuItem mDGroup = new JMenuItem("Digit Grouping");
		mView.add(mDGroup);
		menuBar.add(mView);

		JMenu mHelp = new JMenu("Help");
		JMenuItem mTopics = new JMenuItem("Help Topics");
		mHelp.add(mTopics);
		mHelp.addSeparator();
		JMenuItem mAbout = new JMenuItem("About Calculator");
		mHelp.add(mAbout);
		menuBar.add(mHelp);

		class InsertActionListener implements ActionListener {
			/*
			 * class for inputting numbers (non-Javadoc)
			 * 
			 * @see
			 * java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
			 */
			@Override
			public void actionPerformed(ActionEvent e) {
				// gets the number of the button pressed
				String input = (String) ((JButton) e.getSource()).getText();

				// checks if the input is a decimal point
				if (input.equals(".")) {
					// prevents multiple decimal points
					if (decimal == true) {
						return;
					}
					decimal = true;
				}

				// adds the next inputed number to the screen
				currentText = currentText + input;
				field.setText(currentText);

				if (decimal == false && !input.equals(".")) {
					// adds the inputed number onto the whole number that is currently being typed
					currentNum = Double.parseDouble(input) + (currentNum * 10);
				} else if (decimal == true && !input.equals(".")) {
					// adds the inputed number onto the decimal number that is currently being typed
					currentDecimal = Integer.parseInt(input) + (currentDecimal * 10);

					// adds zeros to the number where it is x.0000x...
					if (input == "0" && currentDecimal == 0) {
						zeroCount++;
					}
				}
				// disables pasting because a number has already been started
				mPaste.setEnabled(false);
			}
		}
		class OperatorActionListener implements ActionListener {
			/*
			 * handles operator buttons such as plus, minus and equals (non-Javadoc)
			 * 
			 * @see
			 * java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
			 */
			@Override
			public void actionPerformed(ActionEvent e) {
				// gets the operator button pressed
				String input = (String) ((JButton) e.getSource()).getText();

				// adds the decimal number to the main number
				if (decimal == true) {
					int divBy = 1;
					// loops through number to make current decimal a double from an integer
					for (int i = 0; i < ((String.valueOf(currentDecimal).length()) + zeroCount); i++) {
						divBy *= 10;
					}
					double currentDoubleDecimal = (double) (currentDecimal) / (double) (divBy);
					currentNum += currentDoubleDecimal;
				}

				if (input.equals("=")) {
					// sends the current number to the calculator class
					calc.calculate(currentNum);
					System.out.println(calc.getResult());
					// sets the text field to the calculated result
					field.setText(formatDouble(calc.getResult(), 0));

					currentNum = calc.getResult();
					currentDecimal = 0;

				} else {
					// updates text field
					currentText = currentText + input;
					field.setText(currentText);
					// sends current number to the calculator
					calc.calculate(currentNum);
					// sends the current operator to the calculator
					calc.setLastOperator(input);

					// resets variables
					currentNum = 0;
					currentDecimal = 0;
					decimal = false;
					zeroCount = 0;
					// allows pasting if current clip-board is double
					if (isDouble(cb)) {
						mPaste.setEnabled(true);
					}
				}
			}
		}
		class ClearActionListener implements ActionListener {
			/*
			 * clears the calculator (non-Javadoc)
			 * 
			 * @see
			 * java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
			 */
			@Override
			public void actionPerformed(ActionEvent e) {
				// resets everything
				calc.setLastOperator("=");
				calc.calculate(0);
				currentText = "";
				field.setText(currentText);
				currentNum = 0;
				currentDecimal = 0;
				decimal = false;
				zeroCount = 0;
				// allows pasting if current clipboard is double
				if (isDouble(cb)) {
					mPaste.setEnabled(true);
				}
			}
		}
		class ClearEntryActionListener implements ActionListener {
			/*
			 * clears what the user is typing (non-Javadoc)
			 * 
			 * @see
			 * java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
			 */
			@Override
			public void actionPerformed(ActionEvent e) {
				// clears whatever is on the screen and reverts it back to the last result
				field.setText(formatDouble(calc.getResult(), 0));
				currentText = "";
				currentNum = 0;
				currentDecimal = 0;
				decimal = false;
			}
		}
		class BackspaceActionListener implements ActionListener {
			/*
			 * removes a character from the end of the current number BUGGY WITH DECIMALS
			 * (non-Javadoc)
			 * 
			 * @see
			 * java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
			 */
			@Override
			public void actionPerformed(ActionEvent e) {
				// converts the current number to a string (which is always without commas)
				String currentNumString = formatDouble(currentNum, 1);
				if (currentNumString.length() > 0 && currentText.length() > 0) {
					// this is very confusing to read
					// checks length is greater than two first so isn't out of range for next check
					// also checks whether the last two characters of the string is .0
					if (currentNumString.length() > 2 && currentNumString
							.substring(currentNumString.length() - 2, currentNumString.length()).equals(".0")) {
						// removes the .0 + the normal character
						currentNumString = currentNumString.substring(0, currentNumString.length() - 3);
					} else {
						// takes a character away from the end of the string
						currentNumString = currentNumString.substring(0, currentNumString.length() - 1);
					}

					if (decimal == true) {
						String currentDecimalString = currentDecimal + "";
						if (currentDecimalString.length() > 0) {
							// checks for points - this should be improved
							for (int i = 0; i < currentDecimalString.length() - 1; i++) {
								if (currentDecimalString.substring(i, i + 1) == ".") {
									break;
								}
							}
							currentDecimal = Integer.parseInt(currentDecimalString);
						}
					}

					// prevents crashes when currentNumString is not a double
					try {
						currentNum = Double.parseDouble(currentNumString);
					} catch (java.lang.NumberFormatException e1) {
						field.setText("0");
						System.out.println("ERROR - couldn't convert to double");
					}

					try {
						currentText = currentText.substring(0, currentText.length() - 1);
						field.setText(currentText);
					} catch (java.lang.StringIndexOutOfBoundsException e1) {
						System.out.println("ERROR - couldn't take away any more characters");
					}

				} else {
					currentNum = 0;
					field.setText("0");
				}
			}
		}

		class MemoryStoreActionListener implements ActionListener {
			/*
			 * stores the current number into the calculator memory (non-Javadoc)
			 * 
			 * @see
			 * java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
			 */
			@Override
			public void actionPerformed(ActionEvent e) {
				if (isDouble(field.getText())) {
					memory = Double.parseDouble(field.getText());
				} else {
					memory = calc.getResult();
				}
			}
		}
		class MemoryRecallActionListener implements ActionListener {
			/*
			 * places the current number in memory onto the screen (non-Javadoc)
			 * 
			 * @see
			 * java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
			 */
			@Override
			public void actionPerformed(ActionEvent e) {
				currentNum = memory;
				currentText += formatDouble(currentNum, 0);
				field.setText(currentText);
			}
		}
		class MemoryAddActionListener implements ActionListener {
			/*
			 * increments the current number on the screen by the number in memory
			 * (non-Javadoc)
			 * 
			 * @see
			 * java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
			 */
			@Override
			public void actionPerformed(ActionEvent arg0) {
				currentNum += memory;
				currentText = formatDouble(currentNum, 0);
			}
		}
		class MemoryClearActionListener implements ActionListener {
			/*
			 * sets memory to zero (non-Javadoc)
			 * 
			 * @see
			 * java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
			 */
			@Override
			public void actionPerformed(ActionEvent e) {
				memory = 0;
			}
		}

		// creates the action listeners
		ActionListener insert = new InsertActionListener();
		ActionListener operate = new OperatorActionListener();
		ActionListener clear = new ClearActionListener();
		ActionListener clearEntry = new ClearEntryActionListener();
		ActionListener back = new BackspaceActionListener();
		ActionListener memStore = new MemoryStoreActionListener();
		ActionListener memRecall = new MemoryRecallActionListener();
		ActionListener memAdd = new MemoryAddActionListener();
		ActionListener memClear = new MemoryClearActionListener();

		// adds action listeners to each button
		b0.addActionListener(insert);
		b1.addActionListener(insert);
		b2.addActionListener(insert);
		b3.addActionListener(insert);
		b4.addActionListener(insert);
		b5.addActionListener(insert);
		b6.addActionListener(insert);
		b7.addActionListener(insert);
		b8.addActionListener(insert);
		b9.addActionListener(insert);
		bPnt.addActionListener(insert);
		// these are currently not implemented
//		bSign.addActionListener(insert);
//		bSqrt.addActionListener(insert);
//		bPcent.addActionListener(insert);
//		bRec.addActionListener(insert);
		bDiv.addActionListener(operate);
		bMult.addActionListener(operate);
		bMinus.addActionListener(operate);
		bPlus.addActionListener(operate);
		bEqls.addActionListener(operate);
		bMC.addActionListener(memClear);
		bMR.addActionListener(memRecall);
		bMS.addActionListener(memStore);
		bMAdd.addActionListener(memAdd);
		bBack.addActionListener(back);
		bCE.addActionListener(clearEntry);
		bC.addActionListener(clear);

		class CopyActionListener implements ActionListener {
			/*
			 * copies current text field to clip board (non-Javadoc)
			 * 
			 * @see
			 * java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
			 */
			@Override
			public void actionPerformed(ActionEvent e) {
				// https://stackoverflow.com/questions/6710350/copying-text-to-the-clipboard-using-java
				StringSelection stringSelection = new StringSelection(field.getText());
				Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
				clipboard.setContents(stringSelection, null);
				mPaste.setEnabled(true);
			}
		}
		class PasteActionListener implements ActionListener {
			/*
			 * pastes current text on clip board onto the text field (non-Javadoc)
			 * 
			 * @see
			 * java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
			 */
			@Override
			public void actionPerformed(ActionEvent e) {
				String clipboard = getClipboard();
				// pastes the number if it is a double
				if (isDouble(clipboard)) {
					currentNum = Double.parseDouble(clipboard);
					currentText += clipboard;
					field.setText(currentText);
				}
			}
		}
		class DigitGroupActionListener implements ActionListener {
			/*
			 * toggles digit grouping (non-Javadoc)
			 * 
			 * @see
			 * java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
			 */
			@Override
			public void actionPerformed(ActionEvent e) {
				digitGrouping = !digitGrouping;
			}
		}
		class ReadmeActionListener implements ActionListener {
			/*
			 * opens the README file (non-Javadoc)
			 * 
			 * @see
			 * java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
			 */
			@Override
			public void actionPerformed(ActionEvent e) {
				// finds the readme file
				File readme = new File("README.txt");

				// checks if it exists
				if (readme.exists()) {
					// checks if current operating system supports desktop commands
					if (Desktop.isDesktopSupported()) {
						try {
							// opens readme in default editor
							Desktop.getDesktop().edit(readme);
						} catch (IOException e1) {
							System.out.println("Couldn't open file");
							e1.printStackTrace();
						}
					} else {
						System.out.println("Couldn't open default editor");
					}
				} else {
					System.out.println("Couldn't find file");
				}
			}
		}
		class AboutActionListener implements ActionListener {
			/*
			 * shows short about message (non-Javadoc)
			 * 
			 * @see
			 * java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
			 */
			@Override
			public void actionPerformed(ActionEvent e) {
				//creates a dialogue box
				JOptionPane.showMessageDialog(frame, "Created by Theo Rook in Java 1.8", "About",
						JOptionPane.INFORMATION_MESSAGE);
			}
		}

		//more action listeners
		ActionListener alCopy = new CopyActionListener();
		ActionListener alPaste = new PasteActionListener();
		ActionListener alGrouping = new DigitGroupActionListener();
		ActionListener alReadme = new ReadmeActionListener();
		ActionListener alAbout = new AboutActionListener();
		mCopy.addActionListener(alCopy);
		mPaste.addActionListener(alPaste);
		mDGroup.addActionListener(alGrouping);
		mTopics.addActionListener(alReadme);
		mAbout.addActionListener(alAbout);

		//creates another panel to hold both the field and the clear buttons
		JPanel topPanel = new JPanel();
		topPanel.setLayout(new BorderLayout());
		topPanel.add(field, BorderLayout.NORTH);
		topPanel.add(topBtns, BorderLayout.SOUTH);

		//organises layout of the main frame
		frame.add(topPanel, BorderLayout.NORTH);
		frame.add(mainKeys, BorderLayout.CENTER);
		frame.setJMenuBar(menuBar);
		frame.pack();
		frame.setVisible(true);
	}

	/**
	 * gets the current contents of the clipboard and returns it as a string
	 * @return clipboard
	 */
	private String getClipboard() {
		// gets what's currently on the clipboard
		Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
		String getClipboard = "";
		if (clipboard != null) {
			//creates a transferable object to allow for more data types
			Transferable transfer = clipboard.getContents(this);
			if (transfer == null) {
				return null;
			}
			//catches errors for things like images and files that have been copied
			try {
				getClipboard = (String) transfer.getTransferData(DataFlavor.stringFlavor);
			} catch (UnsupportedFlavorException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		return getClipboard;
	}

	/**
	 * checks if a string is a double - useful for converting
	 * @param str
	 * @return boolean
	 */
	private boolean isDouble(String str) {
		try {
			Double.parseDouble(str);
			return true;
		} catch (Exception e) {
			return false;
		}
	}

	/**
	 * given a double, will format it depending on current digit grouping criteria
	 * @param num
	 * @param override
	 * @return formatted double as string
	 */
	private String formatDouble(double num, int override) {
		if (digitGrouping == true && override == 0) {
			DecimalFormat commas = new DecimalFormat("#,###.#######");
			return commas.format(num);
		} else {
			DecimalFormat noCommas = new DecimalFormat("#.#######");
			return noCommas.format(num);
		}
	}
}
