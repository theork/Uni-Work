using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class GameController : MonoBehaviour {

    //public GameObject allyDrone1, allyDrone2, allyDrone3;
    //public GameObject enemyDrone1, enemyDrone2, enemyDrone3;
    //public Vector3 spawnValues;
    public Transform allySpawn;
    public Transform enemySpawn;
    public Text gameOverText, goAgainText;
    private bool restart;
    public Button goButton;
    public Dropdown setAlly1, setAlly2, setAlly3;
    private int selection1, selection2, selection3;
    

	// Use this for initialization
	void Start () {
        goButton.onClick.AddListener(ButtonClick);
	}
	
	void Update () {
        if (restart)
        {
            if (Input.GetButton("Submit"))
            {

                SceneManager.LoadScene(SceneManager.GetActiveScene().name);
            }
        }
        if (Input.GetKey("escape"))
        {
            Application.Quit();
        }
	}

    public void ButtonClick()
    {
        selection1 = setAlly1.value;
        selection2 = setAlly2.value;
        selection3 = setAlly3.value;

        FindSelection(selection1, 0);
        FindSelection(selection2, 1.5f);
        FindSelection(selection3, 3);

        ChooseEnemy(0);
        ChooseEnemy(1.5f);
        ChooseEnemy(3);

        goButton.transform.parent.gameObject.SetActive(false);
        
    }

    private void ChooseEnemy(float inc)
    {
        GameObject eMelee = (GameObject)Resources.Load("EnemyMeleeDrone");
        GameObject eSkirmish = (GameObject)Resources.Load("EnemySkirmishDrone");
        GameObject eCommando = (GameObject)Resources.Load("EnemyCommandoDrone");

        int rand = Random.Range(0, 2);

        switch (rand)
        {
            case 0:
                CreateEnemy(eMelee, inc);
                break;
            case 1:
                CreateEnemy(eSkirmish, inc);
                break;
            case 2:
                CreateEnemy(eCommando, inc);
                break;
            default:
                break;
        }
    }

    private void FindSelection(int selection, float inc)
    {
        GameObject aMelee = (GameObject)Resources.Load("AllyMeleeDrone");
        GameObject aSkirmish = (GameObject)Resources.Load("AllySkirmishDrone");
        GameObject aCommando = (GameObject)Resources.Load("AllyCommandoDrone");
        
        switch (selection)
        {
            case 0:
                CreateAlly(aMelee, inc);
                break;
            case 1:
                CreateAlly(aSkirmish, inc);
                break;
            case 2:
                CreateAlly(aCommando, inc);
                break;
            default:
                break;
        }
    }

    void CreateAlly(GameObject go, float inc)
    {
        Vector3 spawnPosition = new Vector3(allySpawn.position.x + inc, Random.Range(allySpawn.position.y, -allySpawn.position.y), allySpawn.position.z);
        Instantiate(go, spawnPosition, allySpawn.rotation);
    }

    void CreateEnemy(GameObject go, float inc)
    {
        Vector3 spawnPosition = new Vector3(enemySpawn.position.x - inc, Random.Range(enemySpawn.position.y, -enemySpawn.position.y), enemySpawn.position.z);
        Instantiate(go, spawnPosition, enemySpawn.rotation);

    }

    public void GameOver()
    {
        GameObject[] aDrones = GameObject.FindGameObjectsWithTag("AllyDrone");
        GameObject[] eDrones = GameObject.FindGameObjectsWithTag("EnemyDrone");

        foreach(GameObject ob in aDrones)
        {
            if (ob.name.Contains("Melee"))
            {                
                ob.GetComponent<MeleeMovement>().speed = 0;
                ob.GetComponent<MeleeMovement>().target = ob;
            }
            else if (ob.name.Contains("Skirmish"))
            {
                ob.GetComponent<SkirmishMovement>().speed = 0;
                ob.GetComponent<SkirmishMovement>().target = ob;
            }
            else if (ob.name.Contains("Commando"))
            {
                ob.GetComponent<CommandoMovement>().speed = 0;
                ob.GetComponent<CommandoMovement>().target = ob;
            }
        }

        foreach (GameObject ob in eDrones)
        {
            if (ob.name.Contains("Melee"))
            {
                ob.GetComponent<MeleeMovement>().speed = 0;
                ob.GetComponent<MeleeMovement>().target = ob;
            }
            else if (ob.name.Contains("Skirmish"))
            {
                ob.GetComponent<SkirmishMovement>().speed = 0;
                ob.GetComponent<SkirmishMovement>().target = ob;
            }
            else if (ob.name.Contains("Commando"))
            {
                ob.GetComponent<CommandoMovement>().speed = 0;
                ob.GetComponent<CommandoMovement>().target = ob;
            }
        }

        gameOverText.text = "Game Over";
        if(aDrones.Length > eDrones.Length)
        {
            goAgainText.text = "Ally Win!";
        }
        else if(aDrones.Length == 0 && eDrones.Length == 0)
        {
            goAgainText.text = "It's a Draw!";
        }
        else
        {
            goAgainText.text = "The Enemy Won";
        }

        restart = true;
        Invoke("goAgain", 3);

    }

    private void goAgain()
    {       
        goAgainText.text = "Press Enter to go Again";
    }
    
}