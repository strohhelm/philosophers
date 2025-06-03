#include "../philo.hpp"


void print_info(t_data*info)
{
    for (size_t i = 0; i < info->nb.size();i++)
        std::cout<<"nb["<<i<<"] = "<<info->nb[i]<<std::endl;
    int l = 0;
    for (size_t i = 0; i < info->locks.size();i++)
    {
        (void)sem_getvalue(info->locks[i], &l);
         std::cout<<"locks["<<i<<"] = "<<l<<std::endl;
    }
}

t_data* get_info(t_data* p)
{
    static t_data* info = nullptr;

    if (!info)
        info = p;
    return info;
}


bool check_input(int argc, char **argv){
    if (argc < 5 || argc > 6)
        return 1;
    for (int i = 1; i < argc; i++){
        if (std::regex_match(std::string(argv[i]), std::regex("^[0-9]*$")) != 1)
            return 1;
    }
    return 0;
}

void error(std::string s){
    std::cerr<<s<<std::endl;
    exit(1);
}

t_data* extract_info(int argc, char **argv){
    t_data* info;

    info = new t_data();
    for (int i = 1; i < argc; i++){
        try{
            info->nb.push_back(std::stoi(argv[i]));
        }catch(...){
            std::cerr<<"stoi"<<std::endl;
            delete info;
            return nullptr;
        }
    }
    if (argc == 5)
        info->nb.push_back(-1);
    info->death_flag = false;
    info->finished_eating = 0;  
    for(int i = 0; i < info->nb[NB]; i++)
        info->times_last_meal.push_back(-1);
    return info;
}

void free_semaphores(t_data* info){
for (size_t i = 0; i < info->locks.size(); i++)
    {
        sem_close(info->locks[i]);
        // std::cerr<<"Closed sem "<<i<<std::endl;
        sem_unlink((SEM_VAR + std::to_string(i)).c_str());
        // std::cerr<<"Unlinked sem "<<i<<std::endl;
    }
}

bool open_semaphores(t_data* info){
    int n;
    info->locks.push_back(sem_open((SEM_VAR + std::to_string(FORKS)).c_str(), O_CREAT, 0600, info->nb[NB]));
    if (info->locks[FORKS] == SEM_FAILED)
    {
        return false;
    }
    sem_getvalue(info->locks.back(), &n);
    std::cout<<"Number of forks put on the table: " << n<<std::endl;
    info->locks.push_back(sem_open((SEM_VAR + std::to_string(PERM)).c_str(), O_CREAT, 0600, info->nb[NB] / 2));
    if (info->locks.back() == SEM_FAILED)
    {
        free_semaphores(info);
        return false;
    }
    sem_getvalue(info->locks.back(), &n);
    std::cout<<"Number of permissions: " <<n <<std::endl;
    for (int i = 2; i < info->nb[NB] + 6; i++)
    {
        info->locks.push_back(sem_open((SEM_VAR + std::to_string(i)).c_str(), O_CREAT , 0600, 1));
        if (info->locks.back() == SEM_FAILED)
            {free_semaphores(info); return false;}
    }
    return true;
}

void signal_handler(int signum)
{
    t_data* info = get_info(nullptr);
    sem_wait(info->locks[DEATH]);
    info->death_flag = true;
    (void)write(2, "INTERRUPT\n", 12);
    sem_post(info->locks[DEATH]);

}


int main(int argc, char **argv){
    if (check_input(argc, argv))
        error("Wrong input!");
    t_data* info = extract_info(argc, argv);
    (void)get_info(info); //fake globaling my way through subject constraints that i strayed away from long ago, still feels wierd to use globals..
    signal(SIGINT, signal_handler);
    if (!info)
        error("Numbers to big my dear!");
    if(!open_semaphores(info))
    {
        delete info;
        error("Something odd happened lol!");
    }
    print_info(info);
    sem_wait(info->locks[START]);
    for(int i = 0; i < info->nb[NB]; i++)
    {
        info->philos.push_back(std::thread(routine, info, i + 1));
    }
    info->philos.push_back(std::thread(watcher, info));
    for (int i = 0; i <= info->nb[NB]; i++)
        sem_post(info->locks[START]);
    for(size_t i = 0; i < info->philos.size(); i++)
    {
        info->philos[i].join();
    }
    std::cout<<"yay everyone back home!"<<std::endl;
    free_semaphores(info);
    delete info;

    return 0;
}

