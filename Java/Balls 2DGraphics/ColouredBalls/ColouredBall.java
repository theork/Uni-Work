package ColouredBalls;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.util.Random;

import javax.swing.JComponent;

public class ColouredBall extends JComponent{
	
	private int xPos, yPos;
	private boolean colour;

	public ColouredBall(int x, int y) {
		xPos = x;
		yPos = y;

	}
	
	public void paintComponent(Graphics g) {
		Graphics2D g2 = (Graphics2D) g;
		this.draw(g2);
	}
	
	public void draw(Graphics2D g2) {
		
		System.out.println("draw");
		
		if(colour == true) {
			g2.setColor(Color.RED);
		}
		else {
			g2.setColor(Color.BLUE);
		}
		colour = !colour;
		
		g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		g2.fillOval(xPos, yPos, 100, 100);
	}

}
