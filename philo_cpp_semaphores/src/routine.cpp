#include "../philo.hpp"

long get_time(void)
{
    struct timeval t;
    static long start_time = 0;
    long current_time;

    gettimeofday(&t, NULL);
    if (start_time == 0)
    start_time = t.tv_sec * 1000000 + (long)t.tv_usec;
    current_time = t.tv_sec * 1000000 + (long)t.tv_usec;
    return ((current_time - start_time) / 1000 );
}


bool check_death(t_data* info)
{
    bool death;
    sem_wait(info->locks[DEATH]);
        death = info->death_flag;
    sem_post(info->locks[DEATH]);
    return death;
}

long print(int nb, std::string s, t_data* info)
{
    long ret;
    sem_wait(info->locks[PRINT]);
    {
        ret = get_time();
        if (check_death(info))
        {
            // std::cout<<get_time()<<" "<<nb<<" exit while printing"<<std::endl;
            ret = -1;
        }
        else
            std::cout<<ret<<" "<<nb<<" "<<s<<std::endl;
    }
    sem_post(info->locks[PRINT]);
    return ret;
}

void return_forks(t_data* info, int nb)
{
   sem_post(info->locks[FORKS]);
   sem_post(info->locks[FORKS]);
}

void end_game(long time, t_data* info, int i, int x)
{
        sem_wait(info->locks[PRINT]);
        sem_wait(info->locks[DEATH]);
        info->death_flag = true;
        if (x)
            std::cout<<time<<" "<<i<<" died"<<std::endl;
        else
            std::cout<<time<<" nice everyone finished"<<std::endl;
        sem_post(info->locks[DEATH]);
        sem_post(info->locks[PRINT]);
}

void watcher(t_data* info)
{
    bool end = false;
    while (!end && info->nb[NB] > 0)
    {
        sem_wait(info->locks[DEATH]);
        if (info->death_flag)
            end = true;
        sem_post(info->locks[DEATH]);
        for (size_t i = 0; i < info->nb[NB] && !end; i++)
        {
            long time = get_time();
            sem_wait(info->locks[FIN]);
            if (info->finished_eating >= info->nb[NB])
            {
                end_game(time, info, 0, 0);
                end = true;
            }
            sem_post(info->locks[FIN]);
            sem_wait(info->locks[i + 5]);
            if (end && info->times_last_meal[i] > 0 && info->times_last_meal[i] <= time - info->nb[DIE])
            {
                end_game(get_time(),info, i, 1);
                end = 1;
            }
            sem_post(info->locks[i + 5]);
        }
        usleep(50);
    }
}

void routine(t_data* info, int nb) {
    sem_wait(info->locks[START]);
    int times_must_eat = info->nb[MUST];
    long start;
    while (1)
    {
        //THINKING
        start = print(nb, "is thinking", info);
        sem_wait(info->locks[nb+5]);
        info->times_last_meal[nb] = start;
        sem_post(info->locks[nb + 5]);

        sem_wait(info->locks[PERM]);
        {
            //print(nb, "got permission", info);
            sem_wait(info->locks[FORKS]);
            print (nb, "has taken a fork", info);
            sem_wait(info->locks[FORKS]);
            print(nb, "has taken a fork", info);
            start = print(nb, "is eating", info);
        }
        sem_post(info->locks[PERM]);
        if (start < 0)
            {return return_forks(info, nb);}
        //EATING
        sem_wait(info->locks[nb+5]);
        info->times_last_meal[nb] = start;
        sem_post(info->locks[nb + 5]);
        // std::cout<<"debug: "<< start<<" "<<info->nb[EAT]<<std::endl;
        while (get_time()- start <= info->nb[EAT])
        {
            // (void)write(1, "S\n", 2);
            usleep(50);
            if (check_death(info))
            {
                // std::cout<<get_time()<<" "<<nb<<" exit while eating"<<std::endl;
                return return_forks(info, nb);
            }
        }
        if (times_must_eat > 0)
        {
            times_must_eat--;
            if (times_must_eat == 0)
            {
                sem_wait(info->locks[FIN]);
                info->finished_eating++;
                sem_post(info->locks[FIN]);
            }
        }
        return_forks(info, nb);
        //SLEEPING
        start = print(nb, "is sleeping", info);
        while (get_time() < start + info->nb[SLEEP])
        {
            usleep(50);
            if (check_death(info))
            {
                // std::cout<<get_time()<<" "<<nb<<" exit while sleeping"<<std::endl;
                return;
            }
        }
    }
}
