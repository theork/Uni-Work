using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyOffensiveDetector : MonoBehaviour {

    private string allegiance;
    
	void Start () {
        if (transform.root.gameObject.tag == "EnemyDrone")
        {
            allegiance = "enemy";
        }
        else if (transform.root.gameObject.tag == "AllyDrone")
        {
            allegiance = "ally";
        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(allegiance == "ally")
        {
            if(collision.gameObject.tag == "EnemyDrone")
            {
                transform.root.GetComponent<CommandoMovement>().Attack(collision.gameObject);
            }
        }
        else if(allegiance == "enemy")
        {
            if(collision.gameObject.tag == "AllyDrone")
            {
                transform.root.GetComponent<CommandoMovement>().Attack(collision.gameObject);
            }
        }
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        if (allegiance == "ally")
        {
            if (collision.gameObject.tag == "EnemyDrone")
            {
                transform.root.GetComponent<CommandoMovement>().Move();
            }
        }
        else if (allegiance == "enemy")
        {
            if (collision.gameObject.tag == "AllyDrone")
            {
                transform.root.GetComponent<CommandoMovement>().Move();
            }
        }
    }
}
