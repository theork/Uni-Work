import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.RenderingHints;

public class Ball {
	
	private int x, y, startX, startY;
	private boolean start = true;
	
	public Ball(int startX, int startY) {
		x += startX;
		y += startY;
	}
	
	public void draw(Graphics2D g2) {
		g2.setColor(Color.RED);
		g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		g2.fillOval(x, y, 20, 20);
	}
	
	public void addX(int change) {
		x += change;
	}
	
	public void addY(int change) {
		y += change;
	}
	
	public void minusX(int change) {
		x -= change;
		
	}
	
	public void minusY(int change) {
		y -= change;
		
	}
	
	public int getX() {
		return x;
	}
	
	public int getY() {
		return y;
	}
}
