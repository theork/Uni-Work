
import java.io.Serializable;

/**
 * Date created: 16/04/18
 * @author eeub22
 * @version 1.0
 * 
 * implements serializable to allow save and loading to file
 */
public class StockItem implements Serializable{
    private String itemID, itemDesc;
    private double price;
    private int quantity, reOrderLevel;
    
    /**
     * The StockItem constructor with parameters initialising the instance variables 
     * @param sItemID
     * @param sItemDesc
     * @param sPrice
     * @param sQuantity
     * @param sReOrderLevel
     */
    public StockItem(String sItemID, String sItemDesc, double sPrice, int sQuantity, int sReOrderLevel){
        itemID = sItemID;
        itemDesc = sItemDesc;
        setPrice(sPrice);
        setQuantity(sQuantity);
        setReOrderLevel(sReOrderLevel);
    }
    
    /**
     * getter for itemID instance variable
     * @return itemID 
     */
    public String getItemID(){
        return(itemID);
    }
    
    /**
     * getter for itemDesc instance variable
     * @return itemDesc
     */
    public String getItemDesc(){
        return(itemDesc);
    }
    
    /**
     * setter for price instance variable
     * @param sPrice sets price
     */
    public void setPrice(double sPrice){
        price = sPrice;
    }

    /**
     * getter for price instance variable
     * @return price
     */
    public double getPrice(){
        return(price);
    }
    
    /**
     * setter for quantity instance variable
     * @param sQuantity sets quantity
     */
    public void setQuantity(int sQuantity){
        quantity = sQuantity;
    }

    /**
     * getter for quantity instance variable
     * @return quantity
     */
    public int getQuantity(){
        return(quantity);
    }
    
    /**
     * setter for reOrderLevel instance variable
     * @param sReOrderLevel sets reOrderLevel
     */
    public void setReOrderLevel(int sReOrderLevel){
        reOrderLevel = sReOrderLevel;
    }

    /**
     * getter for reOrderLevel instance variable
     * @return reOrderLevel
     */
    public int getReOrderLevel(){
        return(reOrderLevel);
    }
    
    /**
     *
     * @return provides all instance variables for that instance
     */
    @Override
    public String toString(){
        return("[itemID=" + itemID + ",itemDesc=" + itemDesc + ",price=" + price + ",quantity=" + quantity + ",reOrderLevel=" + reOrderLevel + "]");
    }
    
    /**
     *
     * @return provides all instance variables in an easily readable and comparable format
     */
    public String format(){
        return(String.format("\n%s %s £%.2f %d %d", itemID, itemDesc, price, quantity, reOrderLevel));
    }
}
