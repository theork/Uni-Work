//package BouncingBalls;
//
//import java.awt.Color;
//import java.awt.event.ActionEvent;
//import java.awt.event.ActionListener;
//
//import javax.swing.Timer;
//
//
//public class Runnaball implements Runnable {
//	
//	private final int DELAY = 100;
//	private Ball ball;
//	
//	public Runnaball(){
//		ball = new Ball(Color.RED, 3);
//		
//	}
//
//	@Override
//	public void run() {
//		
//		
//		class TimerListener implements ActionListener{
//			@Override
//			public void actionPerformed(ActionEvent event) {
//				System.out.println("RUNNING");
//				ball.move();
//				
//			}
//		}	
//		
//		TimerListener listener = new TimerListener();
//		Timer t = new Timer(DELAY, listener);
//		
//		t.start();
//	}
//}
