import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JProgressBar;
import javax.swing.JLabel;
import javax.swing.JButton;
import java.awt.Font;
import java.awt.event.ActionListener;
import java.util.Arrays;
import java.util.Random;
import java.awt.event.ActionEvent;

/**
 * @author Theo Rook
 * provides a gui and functions to simulate supermarket checkouts
 */
public class QueuesGUI extends JFrame {

	private JPanel contentPane;
	private Queue[] checkouts = new Queue[4];
	private JLabel lblQueue1, lblQueue2, lblQueue3, lblQueue4;
	private JLabel lblCheckout1, lblCheckout2, lblCheckout3, lblCheckout4;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					QueuesGUI frame = new QueuesGUI();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 * gui created by eclipse window builder
	 */
	public QueuesGUI() {
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.setLayout(new BorderLayout(0, 0));
		setContentPane(contentPane);

		JPanel panel = new JPanel();
		contentPane.add(panel, BorderLayout.CENTER);
		panel.setLayout(null);

		lblCheckout1 = new JLabel("Checkout 1");
		lblCheckout1.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblCheckout1.setBounds(21, 11, 169, 14);
		panel.add(lblCheckout1);

		lblQueue1 = new JLabel("");
		lblQueue1.setBounds(21, 32, 393, 14);
		panel.add(lblQueue1);

		lblCheckout2 = new JLabel("Checkout 2");
		lblCheckout2.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblCheckout2.setBounds(21, 51, 169, 14);
		panel.add(lblCheckout2);

		lblQueue2 = new JLabel("");
		lblQueue2.setBounds(21, 72, 393, 14);
		panel.add(lblQueue2);

		lblCheckout3 = new JLabel("Checkout 3");
		lblCheckout3.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblCheckout3.setBounds(21, 95, 169, 14);
		panel.add(lblCheckout3);

		lblQueue3 = new JLabel("");
		lblQueue3.setBounds(21, 116, 393, 14);
		panel.add(lblQueue3);

		lblCheckout4 = new JLabel("Checkout 4");
		lblCheckout4.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblCheckout4.setBounds(21, 139, 169, 14);
		panel.add(lblCheckout4);

		lblQueue4 = new JLabel("");
		lblQueue4.setBounds(21, 160, 393, 14);
		panel.add(lblQueue4);

		JButton btnCustomer = new JButton("Customer");
		btnCustomer.addActionListener(new ActionListener() {
			/* (non-Javadoc)
			 * @see java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
			 * adds a new customer with a random amount of items
			 */
			public void actionPerformed(ActionEvent e) {
				//gets the random items between 1 and 10
				Random rand = new Random();
				int items = rand.nextInt(10) + 1;

				//calculates the smallest queue
				Queue minQueue = checkouts[0];
				for (int i = 0; i < checkouts.length; i++) {
					if (checkouts[i].getSize() < minQueue.getSize()) {
						minQueue = checkouts[i];
					}
				}
				minQueue.Add(items);

				UpdateQueues();
			}
		});
		btnCustomer.setBounds(163, 217, 105, 23);
		panel.add(btnCustomer);

		JButton btnTime = new JButton("Time");
		btnTime.addActionListener(new ActionListener() {
			/* (non-Javadoc)
			 * @see java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
			 * simulates time by items going through checkout
			 */
			public void actionPerformed(ActionEvent e) {
				for (int i = 0; i < checkouts.length; i++) {

					if (checkouts[i].getFront() <= 1) {
						checkouts[i].Remove();
					}
					checkouts[i].setStartValue(checkouts[i].getFront() - 1);
				}
				UpdateQueues();
			}
		});
		btnTime.setBounds(325, 217, 89, 23);
		panel.add(btnTime);

		//initialises checkouts array
		for (int i = 0; i < checkouts.length; i++) {
			Queue checkout = new Queue();
			checkouts[i] = checkout;
		}

	}

	/**
	 * updates gui to display the checkout lines and length
	 */
	public void UpdateQueues() {		
		lblCheckout1.setText("Checkout 1 - Length = " + checkouts[0].getSize());
		lblCheckout2.setText("Checkout 2 - Length = " + checkouts[1].getSize());
		lblCheckout3.setText("Checkout 3 - Length = " + checkouts[2].getSize());
		lblCheckout4.setText("Checkout 4 - Length = " + checkouts[3].getSize());
		
		lblQueue1.setText(FormatQueue(0));
		lblQueue2.setText(FormatQueue(1));
		lblQueue3.setText(FormatQueue(2));
		lblQueue4.setText(FormatQueue(3));
	}

	/**
	 * @param checkout
	 * @return formatted array
	 * formats the array into a string and removes deleted values 
	 */
	public String FormatQueue(int checkout) {
		int[] queue = checkouts[checkout].getOrderedQueue();
		String formattedQueue = "";
		for (int i = 0; i < queue.length; i++) {
			//decides whether there should be commas
			if (queue[i] > 0 && i == 0) {
				formattedQueue += queue[i];
			} else if (queue[i] > 0) {
				formattedQueue += ", " + queue[i];
			}
		}
		
		//removes any leading commas
		if(formattedQueue.length() > 2 && formattedQueue.substring(0, 2).equals(", ")) {
			
			formattedQueue = formattedQueue.substring(2);
		}
			
		return formattedQueue;
	}
}
