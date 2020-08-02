package root.responses;

/**
 * Generic response message
 * @author ivslesser
 */
public class Response {
	int id;
	String message;
	
	// CODE
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	
	
	// MESSAGE
	public String getMessage() {
		return message;
	}
	public void setMessage(String message) {
		this.message = message;
	}
	
	public static Response create_response(int _id, String _msg)
	{
		Response to_return = new Response();
		to_return.setId(_id);
		to_return.setMessage(_msg);
		return to_return;
	}
}
