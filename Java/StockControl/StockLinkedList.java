
import java.io.*;
import java.util.LinkedList;

/**
 * saves multiple StockItems to a linked list and adds functions around this
 * @author eeub22
 */
public class StockLinkedList implements StockList{
    //creates the lists to hold the data
    LinkedList<StockItem> stockList = new LinkedList<>();
    LinkedList<StockItem> reOrderList = new LinkedList<>();

    @Override
    public void addItem(StockItem item){
        stockList.add(item);
    }

    @Override
    public void deleteItem(String itemID) {
        boolean removed = false;
        //iterates through list to see if there are any matches
        for(StockItem s:stockList){
            if(s.getItemID().equals(itemID)){
                stockList.remove(s);
                removed = true;
                break;
            }
        }
        //outputs error if no results are found
        if(removed == false){
            System.out.println("Error - could not find ID");
        }
    }

    @Override
    public void updateItemPrice(String itemID, double price) {
        boolean updated = false;
        //iterates through list to see if there are any matches
        for(StockItem s : stockList){
            if(s.getItemID().equals(itemID)){
                s.setPrice(price);
                updated = true;
            }
        }
        //outputs error if no results are found
        if(updated == false){
            System.out.println("Error - could not find ID");
        }
    }

    @Override
    public void updateItemQuantity(String itemID, int quantity) {
        boolean updated = false;
        //iterates through list to see if there are any matches
        for(StockItem s : stockList){
            if(s.getItemID().equals(itemID)){
                s.setQuantity(quantity);
                updated = true;
                //removes item from reorder list if the quantity is bigger than the re-order level
                if(quantity > s.getReOrderLevel() && reOrderList.contains(s)){
                    reOrderList.remove(s);
                }
                //adds item to reorder list if the quantity is less than the reorder list
                else if(quantity < s.getReOrderLevel()){
                    reOrderList.add(s);
                }
            }
        }
        //outputs error if no results are found
        if(updated == false){
            System.out.println("Error - could not find ID");
        }


    }

    @Override
    public void updateReOrderLevel(String itemID, int reOrderLevel) {
        boolean updated = false;
        //iterates through list to see if there are any matches
        for(StockItem s : stockList){
            if(s.getItemID().equals(itemID)){
                s.setReOrderLevel(reOrderLevel);
                updated = true;
                //removes item from reorder list if the quantity is less than the re-order level
                if(reOrderLevel < s.getQuantity() && reOrderList.contains(s)){
                    reOrderList.remove(s);
                }
                //adds item to reorder list if the quantity is bigger than the reorder list
                else if(reOrderLevel > s.getQuantity()){
                    reOrderList.add(s);
                }
            }
        }
        //outputs error if no results are found
        if(updated == false){
            System.out.println("Error - could not find ID");
        }
    }

    @Override
    public void formatStockList() {
        System.out.println("\nStock List");
        System.out.println("ID\tDescription\tPrice\tQuantity\tRe-Order Level\n");
        //iterates through list, printing each value
        for(StockItem s : stockList){
            System.out.println(s.getItemID()+ "\t" + s.getItemDesc() + "\t£" + s.getPrice() + "\t" + s.getQuantity() + "\t\t" + s.getReOrderLevel());
        }
    }

    @Override
    public void formatReOrderList() {
        System.out.println("\nRe-Order List");
        System.out.println("ID\tDescription\tPrice\tQuantity\tRe-Order Level\n");
        //iterates through list, printing each value
        for(StockItem s : reOrderList){
            System.out.println(s.getItemID()+ "\t" + s.getItemDesc() + "\t£" + s.getPrice() + "\t" + s.getQuantity() + "\t\t" + s.getReOrderLevel());
        }
    }
    
    @Override
    public void loadStockData(String filename){
        //try-with-resources will close file after
        try( ObjectInputStream input  = new ObjectInputStream(new FileInputStream(filename));) {
            //creates loop that throws and catches EOF error when file has been read
            while (true){
                StockItem objectIn = (StockItem) input.readObject();
                //adds objects back into the list
                stockList.add(objectIn);
            }
        } catch (EOFException eof){
            //this error will be thrown every time
            System.out.println("Reached end of file");
        } catch (FileNotFoundException ex) {
            System.out.println("File not found " + ex);
        } catch (IOException ex) {
            System.out.println("File processing error " + ex);
        } catch (ClassNotFoundException ex) {
            System.out.println("Class not found " + ex);
        } 

    }

    @Override
    public void saveStockData(){
        ObjectOutputStream output = null;
        try {
            output = new ObjectOutputStream(new FileOutputStream("stock.txt", true));
            for(StockItem s : stockList){
                output.writeObject(s);
            }
            
        } catch (FileNotFoundException ex) {
            System.out.println("File not found " + ex);
        } catch (IOException ex) {
            System.out.println("File processing error " + ex);
        } finally {
            
            try {
                output.close();
            } catch (IOException ex) {
                System.out.println("Error closing file " + ex);
            }
 
        }
    }
}
