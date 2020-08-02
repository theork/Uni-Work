package BouncingBalls;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;

import javax.swing.JPanel;
import javax.swing.Timer;

public class Ball implements Runnable {

	private int speed, x, y, maxHeight, maxWidth, xDir, yDir;
	private Color colour;
	private final int DELAY = 50;
	private JPanel panel;
	private boolean stop = false;

	/**
	 * constructor method
	 * 
	 * @param c
	 * @param s
	 * @param p
	 */
	public Ball(Color c, int s, JPanel p) {
		colour = c;
		speed = s;
		panel = p;

		maxHeight = panel.getHeight();
		maxWidth = panel.getWidth();

		// creates a thread so each ball has its own thread (also triggers run below)
		Thread t = new Thread(this);
		t.start();

		// randomises starting position and directions
		Random rand = new Random();
		x = rand.nextInt(maxWidth);
		y = rand.nextInt(maxHeight);

		boolean xRandDir = rand.nextBoolean();
		if (xRandDir == true) {
			xDir = 1;
		} else {
			xDir = -1;
		}
		boolean yRandDir = rand.nextBoolean();
		if (yRandDir == true) {
			yDir = 1;
		} else {
			yDir = -1;
		}
	}

	/**
	 * instructions to draw itself
	 * 
	 * @param g
	 */
	public void draw(Graphics g) {
		g.setColor(colour);
		g.fillOval(x, y, 20, 20);
	}

	/**
	 * moves each ball checks if the edge has been hit and reveres direction if true
	 */
	public void move() {
		x += speed * xDir;
		y += speed * yDir;

		if (x > maxWidth - 20) {
			xDir = -1;
		} else if (x < 0) {
			xDir = 1;
		}

		if (y > maxHeight - 20) {
			yDir = -1;
		} else if (y < 0) {
			yDir = 1;
		}
	}

	@Override
	public void run() {

		// creates a timer to trigger the timer listener class once every DELAY
		// milliseconds
		Timer t = new Timer(DELAY, new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent event) {
				// moves the current ball
				move();
				// updates the graphics
				panel.repaint();

				if (stop == true) {
					((Timer) event.getSource()).stop();
				}
			}
		});

		t.start();

	}

	/**
	 * @param s
	 */
	public void setSpeed(int s) {
		speed = s;
	}

	/**
	 * stops the thread
	 */
	public void stop() {
		stop = true;
	}

}
