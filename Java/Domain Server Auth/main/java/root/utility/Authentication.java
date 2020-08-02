package root.utility;

import java.util.Base64;

import root.token.TokenStore;

public class Authentication {
	public static String[] decode_two_part_header(String header)
	{
		String[] values_to_return = { null, null };
		// Remove the 'Basic ' part and trim.
		String encoded = header.substring(header.indexOf(' ') + 1).trim();
		// Decode combined string.
		String decoded_combined = new String(Base64.getDecoder().decode(encoded));
		// Split string
		values_to_return[0] = decoded_combined.substring(0, decoded_combined.indexOf(':')).trim();
		values_to_return[1] = decoded_combined.substring(decoded_combined.indexOf(':') + 1).trim();
		// Return
		System.out.println(values_to_return[0] + ". " + values_to_return[1]);
		return values_to_return;
	}
	
	/**
	 * Validates the passed header to ensure authenticated.
	 * @param header_auth Header to validate against
	 * @return boolean true is validated otherwise false.
	 */
	public static boolean validate_token(String header_auth)
	{
		// 1. Check if Authorisation header is present & handle if not
		if(header_auth.equals(""))
		{
			return false;
		}
		
		// 2. Decode encrypted header.
		String[] decoded = Authentication.decode_two_part_header(header_auth);
		
		// 3. Handle Return if null
		if (decoded[0] == null || decoded[1] == null)
		{
			return false;
		}
		
		// 4. Check token validity.
		// 4.1 Valid Token?
		if (!TokenStore.getInstance().tokenIsValid(decoded[1]))
		{
			return false;
		}
		
		// 4.2 User names match?
		String t_uname = TokenStore.getInstance().getUsername(decoded[1]);
		if(!decoded[0].equals(t_uname))
		{
			// Note: Also invalidates the token if details do not match.
			TokenStore.getInstance().invalidate(decoded[1]);
			return false;
		}
		
		return true;
	}
}
