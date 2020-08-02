package BouncingBalls;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Random;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.border.EmptyBorder;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class BouncingBallsFrame extends JFrame {

	private final int FRAME_WIDTH = 700;
	private final int FRAME_HEIGHT = 700;
	private Ball ball;
	private ArrayList<Ball> balls;
	private boolean pause = false;

	/**
	 * 
	 */
	public BouncingBallsFrame() {
		// sets the size of the internal window
		getContentPane().setPreferredSize(new Dimension(FRAME_WIDTH, FRAME_HEIGHT));
		setTitle("Bouncing Balls");

		balls = new ArrayList<Ball>();

		JPanel ballPanel = new BallPanel();
		JPanel functionPanel = new JPanel();

		// creates the slider
		JSlider sSpeed = new JSlider(JSlider.HORIZONTAL, 1, 5, 3);
		sSpeed.setMajorTickSpacing(1);
		sSpeed.setPaintTicks(true);
		sSpeed.setPaintLabels(true);

		sSpeed.addChangeListener(new ChangeListener() {
			@Override
			public void stateChanged(ChangeEvent e) {
				JSlider source = (JSlider) e.getSource();
				if (!source.getValueIsAdjusting()) {
					for (Ball b : balls) {
						b.setSpeed(source.getValue());
					}
				}
			}
		});

		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout(new GridLayout(1, 3, 5, 5));
		buttonPanel.setBorder(new EmptyBorder(15, 15, 15, 60));

		JButton bStart = new JButton("Start");
		JButton bPause = new JButton("Pause");
		JButton bStop = new JButton("Stop");

		buttonPanel.add(bStart);
		buttonPanel.add(bPause);
		buttonPanel.add(bStop);

		bStart.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// creates a new instance of ball with colour, speed and the panel
				ball = new Ball(getRandomColour(), 3, ballPanel);
				balls.add(ball);
			}
		});

		bPause.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				// toggles the button and changes the speed to act like the program has paused
				if (pause == false) {
					for (Ball b : balls) {
						b.setSpeed(0);
					}
					pause = true;
				} else {
					for (Ball b : balls) {
						b.setSpeed(sSpeed.getValue());
					}
					pause = false;
				}
			}
		});

		bStop.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				for (Ball b : balls) {
					// stops each thread
					b.stop();
				}
				try {
					Thread.sleep(5000);
				} catch (InterruptedException e1) {
					e1.printStackTrace();
					Thread.currentThread().interrupt();
				}
				balls.clear();
				ballPanel.repaint();
			}
		});

		// aligns everything nicely
		functionPanel.setLayout(new GridLayout(1, 2));
		functionPanel.add(buttonPanel);
		functionPanel.add(sSpeed);

		add(ballPanel, BorderLayout.CENTER);
		add(functionPanel, BorderLayout.SOUTH);

		pack();
	}

	/**
	 * gets 3 random RGB values to create a colour
	 * 
	 * @return Colour
	 */
	public Color getRandomColour() {
		Random rand = new Random();
		float r = rand.nextFloat();
		float g = rand.nextFloat();
		float b = rand.nextFloat();
		return new Color(r, g, b);
	}

	class BallPanel extends JPanel {

		public BallPanel() {
			// shows the outline of the panel
			setBorder(BorderFactory.createLineBorder(Color.BLACK));
		}

		public void paintComponent(Graphics g) {
			super.paintComponent(g);
			// paints all the balls
			for (Ball ball : balls) {
				ball.draw(g);
			}
		}
	}
}
