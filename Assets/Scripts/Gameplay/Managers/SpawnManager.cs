using System;
using System.Collections;
using System.Collections.Generic;
using UnityEditor.Animations;
using UnityEngine;
using UnityEngine.Experimental.Rendering;

public class SpawnManager : MonoBehaviour
{
    [SerializeField]
    private float spawnTimer = 2f;

    [SerializeField]
    private float unitTimer;

    [SerializeField]
    public GameObject entityToSpawn;

    [SerializeField]
    private Transform spawnPoint;
    private List<List<Transform>> spawnPointsTransforms = new List<List<Transform>>();
    private int[][] spawnPoints;

    [SerializeField]
    private int spawnIndex = -1;

    [SerializeField]
    private bool multiSpawner;

    [SerializeField]
    private int spawnCountLimit;
    private float spawnRadius;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        unitTimer += Time.deltaTime;

        if (unitTimer > spawnTimer && spawnIndex < spawnCountLimit) {
            if (!multiSpawner) {
                GameObject.Instantiate(entityToSpawn, spawnPoint);
            } else {
                HandleMultiSpawn();
            }
            unitTimer = 0;

        }
    }

    private void HandleMultiSpawn() {
        if (spawnIndex == -1) { initializeSpawn(); }

        int rowCount = spawnPointsTransforms[0].Count;
        int ColCount = spawnPointsTransforms[1].Count;

        int currentIndex = 0;
        for (int i = 0; i < rowCount; i++) {
            for (int j = 0; j < ColCount; j++) {
                currentIndex++;
                if (currentIndex > spawnIndex) {
                    print("Spawing at spawnIndex: " + spawnIndex);
                    GameObject child = GameObject.Instantiate(entityToSpawn, spawnPointsTransforms[i][j]);
                    child.transform.position = spawnPointsTransforms[i][j].transform.position;
                    spawnIndex++;
                    return;
                }
            }
        }
    }

    private void initializeSpawn() {
        int i = 0;
        int j = 0;
        spawnIndex = 0;
        foreach (Transform row in transform) {
            spawnPointsTransforms.Add(new List<Transform>());
            foreach(Transform col in row) {
                spawnPointsTransforms[i].Add(col);
            }
            i++;
        }
        for (i = 0; i < spawnPointsTransforms.Count; i++) {
            spawnCountLimit += spawnPointsTransforms[i].Count;
        }
    }
}
