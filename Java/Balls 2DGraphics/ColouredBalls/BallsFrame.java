package ColouredBalls;
import java.awt.BorderLayout;
import java.awt.Dimension;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class BallsFrame extends JFrame{

	private ColouredBallPanel colouredBallPanel;
	private final int FRAME_WIDTH = 600;
	private final int FRAME_HEIGHT = 500;
	
	public BallsFrame() {
		getContentPane().setPreferredSize(new Dimension(FRAME_WIDTH, FRAME_HEIGHT));
		setTitle("Coloured Balls");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		colouredBallPanel = new ColouredBallPanel();
		
		add(colouredBallPanel, BorderLayout.CENTER);
		
		addBall((FRAME_WIDTH / 2) - 150 , (FRAME_HEIGHT / 2) - 75);
		addBall((FRAME_WIDTH / 2) + 50, (FRAME_HEIGHT / 2) - 75);
				
		pack();
	}

	public void addBall(int x, int y) {
		ColouredBall ball = new ColouredBall(x, y);
		colouredBallPanel.add(ball);
		
		Runnable r = new ColouredBallRunnable(ball, colouredBallPanel);
		Thread t = new Thread(r);
		t.start();		
	}
}
