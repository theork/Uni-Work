package BouncingBalls;

import java.awt.EventQueue;

import javax.swing.JFrame;

public class BouncingBallsMain {

	/**
	 * starts the program
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				JFrame frame = new BouncingBallsFrame();
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				frame.setVisible(true);
			}
		});
	}

}
