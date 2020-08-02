
/**
 *
 * @author eeub22
 */
public class StockItemTester {

    /**
     * Tests all the methods in the StockItem class
     * @param args
     */
    public static void main(String[]args){
        System.out.println("Stock Item Tester\n\n");
        System.out.println("Creating new item");
        StockItem tv = new StockItem("001","32-inch tele",150.0,52,10);
        System.out.println("Testing toString and testing constructor");
        System.out.println("tv=" + tv.toString());
        
        System.out.println("\nTesting setting price, quantity and reorder level");
        tv.setPrice(140.0);
        tv.setQuantity(62);
        tv.setReOrderLevel(15);
        System.out.println("tv after setting=" + tv.toString());
        
        System.out.println("\nTesting getters");
        System.out.println("tv.toString=" + tv.toString());
        System.out.println("getItemID = " + tv.getItemID());
        System.out.println("getItemDesc = " + tv.getItemDesc());
        System.out.println("getPrice = " + tv.getPrice());
        System.out.println("getQuantity = " + tv.getQuantity());
        System.out.println("getReOrderLevel = " +tv.getReOrderLevel());
        
        System.out.println("\nTesting format");
        StockItem monitor = new StockItem("002", "26-inch monitor", 89.99, 35, 10);
        System.out.println(tv.format() + monitor.format());
        
       
        
    }
}
