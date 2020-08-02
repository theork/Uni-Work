package root.api.auth;

import java.sql.SQLException;

import javax.ws.rs.DefaultValue;
import javax.ws.rs.HeaderParam;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;

import root.database.DatabaseManager;
import root.responses.AuthToken;
import root.responses.Response;
import root.token.TokenStore;
import root.utility.Authentication;

/**
 * Handle user login
 * @author ivslesser
 * Response types:
 * * 700: Success.
 * * 701: Api/auth error: Missing Authorisation Header.
 * * 702: Api/auth error: Cannot decode Authorisation Header.
 * * 703: Api/auth error: User name or Password mismatch.
 * * 
 */
@Path("/login")
public class UserLogin {
	
	@POST
    @Produces(MediaType.APPLICATION_JSON)
	public Response login(
			@DefaultValue("") @HeaderParam("Authorization") String header_auth
		) throws SQLException
	{	
		// 1. Check if Authorisation header is present & handle if not
		if(header_auth.equals(""))
		{
			return Response.create_response(701, "Api/auth error: Missing Authorisation Header");
		}
		
		// 2. Decode encrypted header.
		String[] decoded = Authentication.decode_two_part_header(header_auth);
		
		// 3. Handle Return if null
		if (decoded[0] == null || decoded[1] == null)
		{
			return Response.create_response(702, "Api/auth error: Cannot Decode Authorisation Header");
		}
		
		// 3. Check user credentials.
			// // WILL BE DB BASED SOME DAY
		AuthToken auth = DatabaseManager.getInstance().verify_user_password(decoded[0], decoded[1]);
		//if (!(decoded[0].equals("test_user") && decoded[1].equals("password")))
		if(auth.getId() != 700)
		{
			// Invalid! Oh my!
			return Response.create_response(703, "Api/auth error: User name or Password mismatch");
		}
		
		// 4. Success - add token and away we go!
		auth.setToken(TokenStore.getInstance().generateToken(decoded[0], 2));
		return auth;
	}
}
