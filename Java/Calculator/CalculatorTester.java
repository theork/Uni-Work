
public class CalculatorTester {

	public static void main(String[] args) {
		
		Calculator calc = new Calculator();
		
		System.out.println("Calculate 1 + 2");		
		calc.calculate(1);
		calc.setLastOperator("+");
		calc.calculate(2);
		System.out.println("result = " + calc.getResult());
		
		System.out.println("1 + 2 + 3");
		calc.calculate(3);
		System.out.println("result = " + calc.getResult());
		
		System.out.println("1 + 2 * 3");
		calc.setLastOperator("=");
		calc.calculate(1);
		calc.setLastOperator("+");
		calc.calculate(2);
		calc.setLastOperator("*");
		calc.calculate(3);
		System.out.println("result = " + calc.getResult());
		
		System.out.println("8 / 2");
		calc.setLastOperator("=");
		calc.calculate(8);
		calc.setLastOperator("/");
		calc.calculate(2);
		System.out.println("result = " + calc.getResult());
		
		System.out.println("4 - 2");
		calc.setLastOperator("=");
		calc.calculate(4);
		calc.setLastOperator("-");
		calc.calculate(2);
		System.out.println("result = " + calc.getResult());
		
		System.out.println("-2 + 2");
		calc.setLastOperator("=");
		calc.calculate(0);
		calc.setLastOperator("-");
		calc.calculate(2);
		calc.setLastOperator("+");
		System.out.println("result = " + calc.getResult());
		System.out.println(calc.toString());
		
	}

}
