using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyDetector : MonoBehaviour
{
    private string allegiance;
    private int colliderCount;

    void Start()
    {
        colliderCount = 0;
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
        if (allegiance == "ally")
        {
            if (collision.tag == "EnemyDrone")
            {
                transform.root.GetComponent<SkirmishMovement>().Flee(collision.gameObject);
            }
        }
        else if (allegiance == "enemy")
        {
            if (collision.tag == "AllyDrone")
            {
                transform.root.GetComponent<SkirmishMovement>().Flee(collision.gameObject);
            }
        }
        colliderCount++;
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        if (allegiance == "ally")
        {
            if (collision.tag == "EnemyDrone")
            {
                transform.root.GetComponent<SkirmishMovement>().Attack(collision.gameObject);
            }
        }
        else if (allegiance == "enemy")
        {
            if(collision.tag == "AllyDrone")
            {
                transform.root.GetComponent<SkirmishMovement>().Attack(collision.gameObject);
            }
        }
        colliderCount--;
    }

    public int getColliderCount()
    {
        return colliderCount;
    }
}
