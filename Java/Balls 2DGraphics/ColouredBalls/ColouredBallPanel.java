package ColouredBalls;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridLayout;

import javax.swing.BorderFactory;
import javax.swing.JPanel;

public class ColouredBallPanel extends JPanel{
	
	
	public ColouredBallPanel() {
		//JPanel panel = new JPanel();
		//panel.setBackground(Color.BLACK);
		//setBorder(BorderFactory.createLineBorder(Color.black));
		setLayout(new GridLayout(1,2));
		//ColouredBall ball = new ColouredBall(0 , 0);
		//add(ball);
	}
	
}
