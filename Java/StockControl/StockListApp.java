/**
 *
 * @author Theo
 */
public class StockListApp{

    /**
     * Creates a main method for the command line interface
     * @param args
     */
    public static void main(String[] args){        
        // Create the stock list object
        StockList stockList= new StockLinkedList();
        //stockList.loadStockData(args[0]);

        // Create an interface
        StockListCLI stockListCLI= new StockListCLI(stockList);

        // Display the menu
        stockListCLI.doMenu();
    }
}