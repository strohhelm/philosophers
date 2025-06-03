#ifndef PHILO_H
#define PHILO_H
//#include <stdio.h>
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <thread>
#include <ctime>
 
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#define SEM_FORKS "/myAwesomeForks"
#define SEM_PRINT "/myLovelyPrint"
#define SEM_DEATH "/mySuddenDeath"
#define SEM_FIN "/mySweetFinsish"
#define SEM_START "/myLittleStart"
#define SEM_PERM "/myHardcorePermission"
#define SEM_VAR "/myHardcoreVariable"

enum e_index {
    NB,
    DIE,
    EAT,
    SLEEP,
    MUST,
};

enum e_locks {
    FORKS,
    PERM,
    PRINT,
    DEATH,
    FIN,
    START,
};

typedef struct s_data {
    std::vector<int> nb;
    //[NB],[DIE],[EAT],[SLEEP],[MUST]
    std::vector<std::thread> philos;
    //[FORKS],[PERM],[PRINT],[DEATH],[FIN],[START],[philo1]...
    std::vector<sem_t*> locks;
    std::vector<long> times_last_meal;
    bool death_flag;
    size_t finished_eating;
}t_data;

void routine(t_data* info, int i);
void watcher(t_data* info);
#endif

