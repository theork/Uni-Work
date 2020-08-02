using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DamageByCollision : MonoBehaviour
{
    public GameObject drone;
    private int damage;

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if(gameObject.tag == "AllyDrone")
        {
            if(collision.gameObject.tag == "EnemyDrone")
            {
                damage = 10;
            }
            else
            {
                damage = 5;
            }
        }
        else if(gameObject.tag == "EnemyDrone")
        {
            if(collision.gameObject.tag == "AllyDrone")
            {
                damage = 10;
            }
            else
            {
                damage = 5;
            }
        }
        this.GetComponent<Health>().DamageHealth(damage);
    }
}
