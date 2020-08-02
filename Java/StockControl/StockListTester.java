/**
 *
 * @author Theo
 */
public class StockListTester {

    /**
     * Tests all the methods in the StockLinkedList class
     * @param args
     */
    public static void main(String[]args){
        System.out.println("Stock List Tester");
        StockLinkedList list = new StockLinkedList();
        
        System.out.println("\nTesting adding three new items to list");
        StockItem tv = new StockItem("001","32-inch TV",150.0,52,10);
        StockItem monitor = new StockItem("002", "26-inch monitor", 89.99, 35, 10);
        StockItem lamp = new StockItem("003", "a white lamp", 25.50, 48, 30);
        System.out.println("Adding TV... ");
        list.addItem(tv);
        System.out.print("Adding monitor... ");
        list.addItem(monitor);
        System.out.print("Adding lamp...");
        list.addItem(lamp);
        
        System.out.println("\nTesting output and checking items added correctly");
        list.formatStockList();
        
        System.out.println("\nTesting deleting an item");
        list.deleteItem("003");
        System.out.println("Item with ID 003 deleted, outputting list...");
        list.formatStockList();
        
        System.out.println("\nTesting invalid ID number");
        list.deleteItem("999");
        System.out.println("Item with ID 999 has been attempted to be deleted");
        
        System.out.println("\nTesting updating the price");
        list.updateItemPrice("002", 90);
        System.out.println("Price of monitor increased to £90");
        list.formatStockList();
        
        System.out.println("\nTesting updating the quantity (but not below re-order level)");
        list.updateItemQuantity("002", 60);
        System.out.println("Quanity of monitor increased to 60");
        list.formatStockList();
        
        System.out.println("\nTesting updating the re order level (but not above quantity)");
        list.updateReOrderLevel("002", 20);
        System.out.println("Re-order level of monitor increased to 20");
        list.formatStockList();
        
        System.out.println("\nTesting updating the quantity below re-order level");
        list.updateItemQuantity("002", 15);
        System.out.println("Quantity of monitor changed to 15");
        list.formatReOrderList();
        
        System.out.println("\nTesting updating the quantity back above re-order level");
        list.updateItemQuantity("002", 60);
        System.out.println("Quantity of monitor changed back to 60");
        list.formatReOrderList();
        
        System.out.println("\nTesting updating the re-order level to above quantity");
        list.updateReOrderLevel("002", 70);
        System.out.println("Re-order level of monitor changed to 70");
        list.formatReOrderList();
        
        System.out.println("\nTesting updating the re-order level back below quantity");
        list.updateReOrderLevel("002", 20);
        System.out.println("Re-order level of monitor changed back to 20");
        list.formatReOrderList();
        
        System.out.println("\nTesting saving the current list items to file");
        list.saveStockData();
        System.out.println("List items have been saved");
        
        System.out.println("\nTesting loading the list from file");
        System.out.println("Deleting current items in list");
        list.deleteItem("001");
        list.deleteItem("002");
        list.loadStockData("stock.txt");
        
        list.formatStockList();
        
        
        
        
        
        
        
        
    }
}
