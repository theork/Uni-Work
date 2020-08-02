using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CommandoMovement : MonoBehaviour {

    public GameObject target, shot;
    public Transform shotSpawn;
    public float speed, fireRate;
    private float nextFire;
    private bool attack;
    
	void Start () {
        target = GetComponent<DroneTargetClosest>().Target();
        Move();
    }	

	void Update () {
		if(target == null)
        {
            target = GetComponent<DroneTargetClosest>().Target();
        }
        else if(target != null)
        {
            //turns the drone towards the target
            Vector3 targetDirection = target.transform.position - transform.position;
            float step = speed * Time.deltaTime;
            float angle = Mathf.Atan2(targetDirection.y, targetDirection.x) * Mathf.Rad2Deg;
            Quaternion q = Quaternion.AngleAxis(angle, Vector3.forward);
            transform.rotation = Quaternion.Slerp(transform.rotation, q, step);

            if(attack == true)
            {
                Attack(target);
            }
            else
            {
                Move();
            }
        }
	}

    public void Move()
    {
        GetComponent<Rigidbody2D>().velocity = transform.right * speed;
        attack = false;
    }

    public void Attack(GameObject newTarget)
    {
        target = newTarget;
        GetComponent<Rigidbody2D>().velocity = transform.right * 0;
        Shoot();
        attack = true;
    }

    private void Shoot()
    {
        if (Time.time > nextFire)
        {
            nextFire = Time.time + fireRate;
            Vector3 angles = shotSpawn.rotation.eulerAngles;

            float zMax, zMin;
            zMin = angles.z - 30f;
            zMax = angles.z + 30f;

            if (zMin < 0)
            {
                zMin = zMin + 360;
            }
            if (zMax > 360)
            {
                zMax = zMax - 360;
            }
            angles.z = Random.Range(zMin, zMax);

            Quaternion bulletRotation = Quaternion.Euler(angles);

            GameObject instShot = Instantiate(shot, shotSpawn.position, bulletRotation);

            int shotDamage = Random.Range(6, 12);
            instShot.SendMessage("SetDamage", shotDamage);

            if (gameObject.tag == "AllyDrone")
            {
                instShot.SendMessage("SentFrom", "a");
            }
            else
            {
                instShot.SendMessage("SentFrom", "e");
            }
        }
    }
}
