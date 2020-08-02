using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShotController : MonoBehaviour {

    private string sentFrom;
    public int shotDamage;
    public float shotSpeed;

	void Start () {
        GetComponent<Rigidbody2D>().velocity = transform.up * shotSpeed;
    }	

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(sentFrom == "a")
        {
            if(collision.gameObject.tag == "EnemyDrone")
            {
                collision.gameObject.GetComponent<Health>().DamageHealth(shotDamage);
                Destroy(gameObject);
            }
        }
        else if(sentFrom == "e")
        {
            if(collision.gameObject.tag == "AllyDrone")
            {
                collision.gameObject.GetComponent<Health>().DamageHealth(shotDamage);
                Destroy(gameObject);
            }
        }

        if(collision.gameObject.tag == "Boundary")
        {
            Destroy(gameObject);
        }        
    }

    public void SentFrom(string type)
    {
        sentFrom = type;
    }

    public void SetDamage(int damage)
    {
        shotDamage = damage;
    }
}
