

public class Calculator
{
   private double result;        // Holds accumulator value
   private String lastOperator;  // Stores last operator entered
   private boolean start;        // Indicates start of a computation

   public Calculator()
   {
	   
      result = 0;
      lastOperator = "=";
      start = true;
   }
   
   public double getResult()
   {
      return result;
   }
   
   public boolean getStart()
   {
      return start;
   }
   
   public void setStart(boolean start)
   {
      this.start = start;
   }
   
   public String getLastOperator()
   {
      return lastOperator;
   }
   
   public void setLastOperator(String operator)
   {
      lastOperator = operator;
   }
   
   /**
    * Carries out the pending calculation.
    * @param x the value to be accumulated with the prior result.
    */
   public double calculate(double x)
   {
      if (lastOperator.equals("+")) result += x;
      else if (lastOperator.equals("-")) result -= x;
      else if (lastOperator.equals("*")) result *= x;
      else if (lastOperator.equals("/")) result /= x;
      else if (lastOperator.equals("1/x")) result = 1/x;
      else if (lastOperator.equals("=")) result = x;   
      //System.out.println("result = " + result); 
      return result;  
   }  
   
   /**
    * Returns string representation of calculator state.
    * @param return calculator state
    */
   public String toString()
   {
      return getClass().getSimpleName() + 
      "[result = " + result + ", lastOperator = " + lastOperator
         + ", start = " + start + "]";
   }
}

   
    
  