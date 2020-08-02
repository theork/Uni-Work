using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DroneTargetClosest : MonoBehaviour {

    private GameController gameController;
    private bool gameOver;

	void Start () {
        GameObject gameControllerObject = GameObject.FindWithTag("GameController");
        gameController = gameControllerObject.GetComponent<GameController>();
        gameOver = false;
    }

    public GameObject Target()
    {
        GameObject[] targets;

        if (gameObject.tag == "AllyDrone")
        {
            targets = GameObject.FindGameObjectsWithTag("EnemyDrone");
        }
        else
        {
            targets = GameObject.FindGameObjectsWithTag("AllyDrone");
        }

        GameObject closest = null;
        float minDistance = Mathf.Infinity;
        Vector3 currentPosition = transform.position;

        if (targets.Length == 0 && gameOver != true)
        {
            gameController.GameOver();
            gameOver = true;
            Debug.Log("No more enemies");
        }

        foreach (GameObject curTarget in targets)
        {
            Vector3 difference = curTarget.transform.position - currentPosition;
            float distance = difference.sqrMagnitude;
            if (distance < minDistance)
            {
                closest = curTarget;
                minDistance = distance;
            }
        }

        return closest;
    }
}
