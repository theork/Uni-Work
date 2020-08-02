using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MeleeMovement : MonoBehaviour {

    public float speed;
    public GameObject target;
    private bool gameOver = false;

	void Start() {
        InvokeRepeating("Move", 0, 0.8f);
        target = GetComponent<DroneTargetClosest>().Target();
    }

    private void Update()
    {
        if(target == null && !gameOver)
        {
            target = GetComponent<DroneTargetClosest>().Target();
        }
        else if (target != null)
        {
            //turns the drone towards the target
            Vector3 targetDirection = target.transform.position - transform.position;
            float step = speed * Time.deltaTime;
            float angle = Mathf.Atan2(targetDirection.y, targetDirection.x) * Mathf.Rad2Deg;
            Quaternion q = Quaternion.AngleAxis(angle, Vector3.forward);
            transform.rotation = Quaternion.Slerp(transform.rotation, q, step);
        }
    }

    void Move()
    {
        GetComponent<Rigidbody2D>().velocity = transform.right * speed; 
    }




}
