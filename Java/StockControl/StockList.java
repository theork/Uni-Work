/**
 * CODE TAKEN FROM APPENDIX 1
 * 
 */
public interface StockList {
     /**
     * Adds item to stock list
     * @param item
     */
    public void addItem(StockItem item);
    
     /**
     * Removes item identified by productID from stock list
     * @param itemID
     */
    public void deleteItem(String itemID);

    /**
     * Updates price of existing item
     * @param itemID
     * @param price
     */
    public void updateItemPrice(String itemID, double price);

    /**
     * Updates quantity of existing item
     * @param itemID
     * @param quantity
     */
    public void updateItemQuantity(String itemID, int quantity);

    /**
     * Updates re-order level of existing item
     * @param itemID
     * @param reOrderLevel
     */
    public void updateReOrderLevel(String itemID, int reOrderLevel);

    /**
     * returns formatted representation of the stock list
     */
    public void formatStockList();

    /**
     * Returns formatted representation of re-order list
     * Items are on this list if quantity < reOrderLevel
     */
    public void formatReOrderList();
    
    /**
     * Loads data from the stock file into the stock list
     * @param filename
     */
    public void loadStockData(String filename);
    
    /**
     * Saves data from stock list to file
     */
    public void saveStockData();
}
