import java.awt.Graphics;
import java.awt.Graphics2D;
import java.util.Random;

import javax.swing.JComponent;

public class BallComponent extends JComponent{
	
	final int DELAY = 200;
	Ball b1 = new Ball(getRandom(), getRandom());
	boolean xPos = true;
	boolean yPos = true;
		
	public void paintComponent(Graphics g) {
		
		if(xPos == true) {
			b1.addX(1);
		}
		else {
			b1.minusX(1);
		}
		
		if(yPos == true) {
			b1.addY(1);
		}
		else {
			b1.minusY(1);
		}
		
		
		if(b1.getX() > 380) {
			xPos = false;
		}
		else if(b1.getX() < 0) {
			xPos = true;
		}
		
		if(b1.getY() > 380) {
			yPos = false;
		}
		else if(b1.getY() < 0) {
			yPos = true;
		}
	
		Graphics2D g2 = (Graphics2D) g;
		b1.draw(g2);
	}
	
	private int getRandom() {
		Random rand = new Random();
		return rand.nextInt(400) + 0;
		
	}
	

}
