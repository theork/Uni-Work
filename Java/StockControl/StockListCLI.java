
import java.util.Scanner;

/**
 * Creates a console based interface for the user to use
 * @author Theo
 */
public class StockListCLI {
    private StockList stock = null;

    /**
     * constructor method
     * @param stock
     */
    public StockListCLI(StockList stock){
        this.stock = stock;
    }

    // Displays main menu andgets valid option from user

    /**
     * Creates a menu, gets the user choice and runs the relevant helper method
     * Repeats until exit is chosen
     */
    public void doMenu() {

        int userInput = 0;
        while(userInput != 8){
            System.out.println("\nStock List Main Menu");
            System.out.println("********************\n");
            System.out.println("1. Add an item");
            System.out.println("2. Delete an item");
            System.out.println("3. Update item price");
            System.out.println("4. Update item quantity");
            System.out.println("5. Update re-order level");
            System.out.println("6. Print stock list");
            System.out.println("7. Print re-order list");
            System.out.println("8. Exit");

            System.out.print("\nPlease input your menu option: ");
            Scanner in = new Scanner(System.in);
            userInput = in.nextInt();

            switch(userInput){
                case 1:
                    doAddItem();
                    break;
                case 2:
                    doDeleteItem();
                    break;
                case 3:
                    doUpdateItemPrice();
                    break;
                case 4:
                    doUpdateItemQuantity();
                    break;
                case 5:
                    doUpdateReOrderLevel();
                    break;
                case 6:
                    doPrintStockList();
                    break;
                case 7:
                    doPrintReOrderList();
                    break;
                case 8:
                    System.out.println("Bye!");
                    break;
                default:
                    System.out.println("Invalid input, try a number between 1 and 8");

            }
        }


    }

    // Obtain input for stock list operation
    // and invoke operation
    private void doAddItem() {
        while(true){
            Scanner in = new Scanner(System.in);
            System.out.println("\nAdd New Item");
            System.out.println("************\n");
            System.out.print("Enter ID: ");
            String stockID = in.nextLine();
            System.out.print("Enter Description: ");
            String stockDesc = in.nextLine();
            System.out.print("Enter Price: ");
            double stockPrice = in.nextDouble();
            System.out.print("Enter Quantity: ");
            int stockQuantity = in.nextInt();
            System.out.print("Enter Re-Order Level: ");
            int stockReOrder = in.nextInt();
            
            //creates a new stock item with the inputted data and adds it to the stock linked list
            StockItem newStock = new StockItem(stockID, stockDesc, stockPrice, stockQuantity, stockReOrder);
            stock.addItem(newStock);
                        
            
            System.out.print("Add another? (Y/N): ");
            //gets the first character of the input and capitalises as to allow yes/no or any version of them
            char again = Character.toUpperCase(in.next().charAt(0));
            if(again == 'N'){
                break;
            }
            else if(again != 'Y'){
                System.out.println("Invalid input, taken as n");
                break;
            }
        }
    }

    private void doDeleteItem() {
        System.out.println("\nDelete an Item");
        System.out.println("**************");
        System.out.print("\nPlease input the ID of the item that you wish to delete: ");
        Scanner in = new Scanner(System.in);
        String id = in.nextLine();
        stock.deleteItem(id);
    }

    private void doUpdateItemPrice() {
        System.out.println("\nUpdate Item Price");
        System.out.println("*****************");
        System.out.print("\nPlease input the ID of the item that you wish to update: ");
        Scanner in = new Scanner(System.in);
        String id = in.nextLine();
        System.out.print("Please input the new value you wish to update the item to: ");
        double price = in.nextDouble();
        stock.updateItemPrice(id, price);
    }
    private void doUpdateItemQuantity(){
        System.out.println("\nUpdate Item Quantity");
        System.out.println("********************");
        System.out.print("\nPlease input the ID of the item that you wish to update: ");
        Scanner in = new Scanner(System.in);
        String id = in.nextLine();
        System.out.print("Please input the new value you wish to update the item to: ");
        int quantity = in.nextInt();
        stock.updateItemQuantity(id, quantity);
    }

    private void doUpdateReOrderLevel() {
        System.out.println("\nUpdate Re-Order Level");
        System.out.println("********************");
        System.out.print("\nPlease input the ID of the item that you wish to update: ");
        Scanner in = new Scanner(System.in);
        String id = in.nextLine();
        System.out.print("Please input the new value you wish to update the item to: ");
        int reorderLevel = in.nextInt();
        stock.updateReOrderLevel(id, reorderLevel);
    }

    // Display contents of stock list
    private void doPrintStockList() {
        stock.formatStockList();
    }

    // Display contents of re-order list
    private void doPrintReOrderList() {
        stock.formatReOrderList();
    }


}
