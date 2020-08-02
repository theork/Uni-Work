import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.Timer;



public class ThreadedBallsFrame extends JFrame{

	final int DELAY = 20;
	private JPanel ballPanel;
	
	
	public ThreadedBallsFrame() {		
		final int FRAME_WIDTH = 400;
		final int FRAME_HEIGHT = 400;

		// creates the frame
		JFrame frame = new JFrame();
		frame.getContentPane().setPreferredSize(new Dimension(FRAME_WIDTH, FRAME_HEIGHT));
		frame.setTitle("Balls");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		ballPanel = new JPanel();
		frame.add(ballPanel, BorderLayout.CENTER);
		
		JComponent comp = new BallComponent();
		frame.add(comp);
		
		
		class TimerListener implements ActionListener{
			@Override
			public void actionPerformed(ActionEvent event) {
				comp.repaint();
				frame.repaint();				
			}
		}	
		
		TimerListener listener = new TimerListener();
		Timer t = new Timer(DELAY, listener);
		
		t.start();
		
		frame.pack();
		frame.setVisible(true);
		
	}
	
	public void addBall() {
		JComponent b1 = new BallComponent();
		ballPanel.add(b1);
		//Runnable r = new BallRunnable(b1, ballPanel);
		//Thread t = new Thread(r);
		//t.start();
	}
}
