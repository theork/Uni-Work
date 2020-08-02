import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JLabel;
import java.awt.Font;
import java.awt.GridLayout;
import javax.swing.JButton;
import javax.swing.JTextField;
import java.awt.FlowLayout;
import javax.swing.BoxLayout;
import java.awt.event.ActionListener;
import java.sql.SQLException;
import java.awt.event.ActionEvent;

public class BankAccountViewer extends JFrame {

	private JPanel contentPane;
	private JTextField txtDeposit;
	private JTextField txtWithdraw;
	private BankAccount b;
	private JLabel lblBalance;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					BankAccountViewer frame = new BankAccountViewer();
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
	public BankAccountViewer() {
		b = new BankAccount(1);
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 369, 302);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.setLayout(new BorderLayout(0, 0));
		setContentPane(contentPane);
		
		JPanel panel = new JPanel();
		contentPane.add(panel, BorderLayout.NORTH);
		
		JLabel lblBankOfUtopia = new JLabel("Bank Of Utopia");
		panel.add(lblBankOfUtopia);
		lblBankOfUtopia.setFont(new Font("Tahoma", Font.BOLD, 30));
		
		JPanel panel_1 = new JPanel();
		contentPane.add(panel_1, BorderLayout.CENTER);
		panel_1.setLayout(null);		
		
		txtDeposit = new JTextField();
		txtDeposit.setBounds(203, 28, 103, 20);
		panel_1.add(txtDeposit);
		txtDeposit.setColumns(10);		
		
		txtWithdraw = new JTextField();
		txtWithdraw.setBounds(203, 90, 103, 20);
		panel_1.add(txtWithdraw);
		txtWithdraw.setColumns(10);
		
		lblBalance = new JLabel("Balance: ");
		lblBalance.setBounds(129, 181, 95, 14);
		panel_1.add(lblBalance);
		
		JButton btnDeposit = new JButton("Deposit");
		btnDeposit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {				
				try {
					Double amount = Double.parseDouble(txtDeposit.getText());
					b.deposit(amount);
				} catch(NumberFormatException ex) {
					System.out.println("INVALID");
				} catch (SQLException ex1) {
					// TODO Auto-generated catch block
					ex1.printStackTrace();
				}				
			}
		});
		btnDeposit.setBounds(38, 27, 95, 23);
		panel_1.add(btnDeposit);
		
		JButton btnWithdraw = new JButton("Withdraw");
		btnWithdraw.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					Double amount = Double.parseDouble(txtWithdraw.getText());
					b.withdraw(amount);
				} catch(NumberFormatException ex) {
					System.out.println("INVALID");
				} catch (SQLException ex1) {
					// TODO Auto-generated catch block
					ex1.printStackTrace();
				}
			}
		});
		btnWithdraw.setBounds(38, 89, 95, 23);
		panel_1.add(btnWithdraw);
		

		JButton btnShowBalance = new JButton("Show Balance");
		btnShowBalance.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					String currBalance = String.format("%.2f", b.getBalance());
					
					lblBalance.setText("Balance: " + currBalance);
				} catch (SQLException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}
		});
		btnShowBalance.setBounds(117, 147, 125, 23);
		panel_1.add(btnShowBalance);
	}
}
