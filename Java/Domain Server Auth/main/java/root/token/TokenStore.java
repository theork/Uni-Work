package root.token;

import java.util.HashMap;
import java.util.Map;
import java.util.UUID;

/**
 * Stores user authentication tokens.
 * @author ivslesser
 */
public class TokenStore
{
    private Map<String, Token> tokenMap = new HashMap<String, Token>();    
    private static TokenStore instance = new TokenStore();
    
    public static TokenStore getInstance()
    {
        return instance;
    }
    private TokenStore(){}
    
    /**
     * Places token into the store.
     * @param username String representation of the user name.
     * @param role Integer representation of user role.
     * @return String authorisation token.
     */
    public String generateToken(String username, int role)
    {
        String token = UUID.randomUUID().toString();
        tokenMap.put(token, new Token(username, role));
        return token;
    }
    
    /**
     * Retrieves the username store in a given token. 
     * @param token
     * @return
     */
    public String getUsername(String token)
    {
        if(tokenIsValid(token))
        {
            return tokenMap.get(token).username;
        }
        return null;
    }
    
    /**
     * Retrieves the role stored in a given token
     * Returns -1 if token not found.
     * @param token Token to check
     * @return role integer
     */
    public int getRole(String token)
    {
        if(tokenIsValid(token))
        {
            return tokenMap.get(token).role;
        }
        return -1;
    }
    
    /**
     * Checks if a token is in the store, will also check validity ie. expiration date 
     * and if expired will remove the token.
     * @param token Token to check 
     * @return boolean true if valid, false otherwise.
     */
    public boolean tokenIsValid(String token)
    {
        if(tokenMap.containsKey(token))
        {
            if(tokenMap.get(token).expires > System.currentTimeMillis())
            {
                return true;
            }
            else
            {
                tokenMap.remove(token);
                return false;
            }
        }
        return false;
    }
    
    /**
     * Invalidates the specified token if it is in the store.
     * @param token Token to check against
     */
    public void invalidate(String token)
    {
        if(tokenMap.containsKey(token))
        {
            tokenMap.remove(token);
        }
    }
    
    /**
     * Token to authenticate a user
     * Stores the username, role and expiry time associated with the token.
     * @author ivslesser
     */
    private static class Token
    {
        String username;
        int role;
        long expires;
        
        private Token(String _username, int _role)
        {
            username = _username;
            role = _role;
            expires = System.currentTimeMillis() + 180 * 60 * 1000; // 180 minutes from now
        }
    }
}