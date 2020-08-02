using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SkirmishMovement : MonoBehaviour {

    public float speed, fireRate;
    public GameObject target, shot;
    public Transform shotSpawn;
    private bool attack, flee, gameOver, turnToFlee;
    private float nextFire;
    private int fleeCount;

    void Start () {
        attack = true;
        flee = false;
        target = GetComponent<DroneTargetClosest>().Target();
    }
	
	void Update () {
        if(target == null)
        {
            target = GetComponent<DroneTargetClosest>().Target();
        }
        else if(target != null)
        {
            if(attack == true)
            {           
                Attack(target);
            }
            else if(flee == true)
            {
                Flee(target);
                fleeCount++;
            }     
        }

		   
	}



    public void Flee(GameObject newTarget)
    {
        attack = false;
        flee = true;

        float tempSpeed = 3.75f;

        if (turnToFlee)
        {
            float startTime = Time.time;
            for(int i = 0; i < 20; i++)
            {
                TurnAway(target);
            }
            turnToFlee = false;
        }
        else
        {
            TurnAway(target);
        }

        GetComponent<Rigidbody2D>().velocity = transform.right * tempSpeed;
        
        if(GetComponentInChildren<EnemyDetector>().getColliderCount() <= 0)
        {
            flee = false;
            attack = true;
        }
    }

    private void TurnTowards(GameObject newTarget)
    {
        Vector3 targetDirection = newTarget.transform.position - transform.position;
        float step = speed * Time.deltaTime * 10;
        float angle = Mathf.Atan2(targetDirection.y, targetDirection.x) * Mathf.Rad2Deg;
        Quaternion q = Quaternion.AngleAxis(angle, Vector3.forward);
        transform.rotation = Quaternion.Slerp(transform.rotation, q, step);
    }

    private void TurnAway(GameObject newTarget)
    {
        Vector3 targetDirection = newTarget.transform.position - transform.position;
        float step = speed * Time.deltaTime * 10;
        float angle = Mathf.Atan2(targetDirection.y, targetDirection.x) * -Mathf.Rad2Deg;
        Quaternion q = Quaternion.AngleAxis(angle, Vector3.forward);
        transform.rotation = Quaternion.Slerp(transform.rotation, q, step);
    }

    public void Attack(GameObject newTarget)
    {
        attack = true;
        flee = false;
        turnToFlee = true;

        GetComponent<Rigidbody2D>().velocity = transform.right * 0;
        target = GetComponent<DroneTargetClosest>().Target();

        TurnTowards(target);

        Shoot();

    }

    private void Shoot()
    {
        if(Time.time > nextFire)
        {
            nextFire = Time.time + fireRate;

           // Quaternion bulletRotation = shotSpawn.rotation;
            Vector3 angles = shotSpawn.rotation.eulerAngles;

            float zMax, zMin;
            zMin = angles.z - 10f;
            zMax = angles.z + 10f;

            if(zMin < 0)
            {
                zMin = zMin + 360;
            }
            if(zMax > 360)
            {
                zMax = zMax - 360;
            }
            angles.z = Random.Range(zMin, zMax);

            Quaternion bulletRotation = Quaternion.Euler(angles);

            GameObject instShot = Instantiate(shot, shotSpawn.position, bulletRotation);
            int shotDamage = Random.Range(15, 25);
            instShot.SendMessage("SetDamage", shotDamage);
            
            if(gameObject.tag == "AllyDrone")
            {
                instShot.SendMessage("SentFrom", "a");
                
            }
            else
            {
                instShot.SendMessage("SentFrom", "e");
            }
            
        }
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.gameObject.tag != "AllyDrone" && collision.gameObject.tag != "EnemyDrone")
        {
            Flee(collision.gameObject);
        }
    }





}
