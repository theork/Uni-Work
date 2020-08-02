using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Health : MonoBehaviour {

    public int startingHealth;
    public int currentHealth;

    void Start()
    {
        currentHealth = startingHealth;
    }

    public void DamageHealth(int damage)
    {
        currentHealth -= damage;
        if (currentHealth <= 0)
        {
            Destroy(gameObject);
        }
    }


}
