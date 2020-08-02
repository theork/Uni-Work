package ColouredBalls;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.Timer;

public class ColouredBallRunnable implements Runnable {
	
	private ColouredBall b;
	private ColouredBallPanel panel;
	private final int DELAY = 500;

	public ColouredBallRunnable(ColouredBall ball, ColouredBallPanel colouredBallPanel) {
		b = ball;
		panel = colouredBallPanel;
	}

	@Override
	public void run() {
		
		class TimerListener implements ActionListener{
			@Override
			public void actionPerformed(ActionEvent event) {
				b.repaint();
				//panel.repaint();				
			}
		}	
		
		TimerListener listener = new TimerListener();
		Timer t = new Timer(DELAY, listener);
		
		t.start();

	}

}
