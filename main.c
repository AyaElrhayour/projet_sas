#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    int day;
    int month;
    int year;
} Date;

typedef struct{
    char first_name[30];
    char last_name[30];
    char email[50];
} coWorker;

typedef struct{
    int id;
    char title[50];
    char description[100];
    Date deadline;
    char status[50];
    Date date;
    coWorker cw[10];
} task;

bool is_valid_date (int day, int month, int year){
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);

    if (year < 1900 || year > 2100)
        return false;
    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;

    //Feb check
    if (month == 2){
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            if (day > 29)
                return false;
        } else {
            if (day > 28)
                return false;
        }
    }
    if (year > tm.tm_year + 1900 || (year == tm.tm_year + 1900 && month > tm.tm_mon + 1)
        || (year == tm.tm_year + 1900 && month == tm.tm_mon + 1 && day >= tm.tm_mday))
        return true;

    return false;
}


// convert date to number if days
int date_to_days(Date date) {
    struct tm timeinfo = {0};
    timeinfo.tm_year = date.year - 1900;
    timeinfo.tm_mon = date.month - 1;
    timeinfo.tm_mday = date.day;
    timeinfo.tm_hour = 0;
    timeinfo.tm_min = 0;
    timeinfo.tm_sec = 0;

    time_t epochTime = mktime(&timeinfo);
    int days = (epochTime / (60 * 60 * 24));
    return days;
}

int days_left(Date current_date, Date given_date) {
    int current_days = date_to_days(current_date);
    int given_days = date_to_days(given_date);
    return  given_days - current_days;
}

void add_cws (task *t){
    int yes;
    char yes_holder[5];
    printf("Would you like to  add coworkers 1 if yes , other value if no :");
    scanf("%s", yes_holder);
    yes = atoi(yes_holder);
    if (yes == 1){
        int cw_number;
        char cw_holder[10];
        printf("How many co-workers you would like to add [1-10]:");
        scanf("%s", cw_holder);
        cw_number = atoi(cw_holder);
        if (cw_number > 0 && cw_number < 11){
            int j = 0;
            while (j < cw_number){
                printf("\t\t\t\t\t\t\t\tFirst name :");
                scanf("%s", t->cw[j].first_name);
                printf("\t\t\t\t\t\t\t\tLast name :");
                scanf("%s", t->cw[j].last_name);
                printf("\t\t\t\t\t\t\t\tEmail :");
                scanf("%s", t->cw[j].email);
                printf("\t\t\t\t\t\t\t\t________________________________\n");
                j++;
            }
        }
    }
}

void display_cw(task t){
    int i = 0;
    while (strlen(t.cw[i].email) != 0){
        printf("CoWorker ---> %d\n", i + 1);
        printf("First name : %s\n", t.cw[i].first_name);
        printf("Last name : %s\n", t.cw[i].last_name);
        printf("Email : %s\n", t.cw[i].email);
        i++;
    }
}

void display_task(task t){
    printf("\t\t\t\t\t\t\t\tID: %d\n", t.id);
    printf("\t\t\t\t\t\t\t\tTitle : %s\n", t.title);
    printf("\t\t\t\t\t\t\t\tDescription : %s\n", t.description);
    printf("\t\t\t\t\t\t\t\tDeadline : %d/%d/%d\n", t.deadline.day, t.deadline.month, t.deadline.year);
    printf("\t\t\t\t\t\t\t\tStatus : %s\n", t.status);
    printf("\t\t\t\t\t\t\t\tCreation Date : %d-%d-%d\n", t.date.day, t.date.month, t.date.year);
    display_cw(t);
    printf("\t\t\t\t\t\t\t\t________________________________\n");
}

void display_tasks(task tasks[], int size){
    int i= 0;
    while (i < size){
        display_task(tasks[i]);
        i++;
    }
}
void add_tasks(task *tasks, int size, int s, int flag){
    int i = 0, error = 0, print_error = 0;
    char temp, temp1, str[99], new_str[100], holder[10], holder1[10], holder2[10];

    if(flag == 1)
        i = 0;
    else if (flag > 1)
        i = size;
    while (i < s){
        tasks[i].id = i + 1;
        printf("title :");
        scanf("%c",&temp);
	    fgets(tasks[i].title, 50, stdin);
        tasks[i].title[strcspn(tasks[i].title, "\n")] = '\0';

        printf("description :");
        scanf("%c",&temp1);
	    fgets(str, 99, stdin);
        str[strcspn(str, "\n")] = '\0';

        new_str[0] = temp1;
        new_str[1] = '\0';

        strcat(new_str, str);
        strcpy(tasks[i].description, new_str);
        while (error == 0) {
            if (print_error == 1){
                printf("ERROR!! The date you entered is invalid please try again\n");
            }
            printf("Deadline\n");
            printf("day :");
            scanf("%s", holder);
            tasks[i].deadline.day = atoi(holder);
            printf("month :");
            scanf("%s", holder1);
            tasks[i].deadline.month = atoi(holder1);
            printf("year :");
            scanf("%s", holder2);
            tasks[i].deadline.year = atoi(holder2);
            if (is_valid_date(tasks[i].deadline.day, tasks[i].deadline.month, tasks[i].deadline.year)){
                error = 1;
            }else print_error = 1;
        }
        error = 0;
        print_error = 0;

        while (error == 0){
            if (print_error == 1){
                printf("ERROR!! The status you entered is invalid please try again\n");
            }
            printf("status :");
            scanf("%s", tasks[i].status);
            if (strcmp(tasks[i].status, "todo") == 0 || strcmp(tasks[i].status, "doing") == 0 || strcmp(tasks[i].status, "done") == 0){
                error = 1;
            }else print_error = 1;
        }
        error = 0;
        print_error = 0;

        time_t t;
        t = time(NULL);
        struct tm tm = *localtime(&t);

        tasks[i].date.day = tm.tm_mday;
        tasks[i].date.month = tm.tm_mon+1;
        tasks[i].date.year = tm.tm_year+1900;

        add_cws (&tasks[i]);
        i++;
    }
}
void display_tasks_sorted (task *tasks, int size, int sort_type){
    int i, j;
    task tmp;
    i = 0;
    if (sort_type == 1 ||  sort_type == 2){
        while (i < size - 1){
            j = i + 1;
            while (j < size) {
                if (sort_type == 1){
                    if (tasks[i].title[0] > tasks[j].title[0]){
                        tmp = tasks[i];
                        tasks[i] = tasks[j];
                        tasks[j] = tmp;
                    }
                }else if (sort_type == 2){
                    if (tasks[i].deadline.year > tasks[j].deadline.year){
                        tmp = tasks[i];
                        tasks[i] = tasks[j];
                        tasks[j] = tmp;
                    }else if (tasks[i].deadline.year == tasks[j].deadline.year){
                        if (tasks[i].deadline.month > tasks[j].deadline.month){
                            tmp = tasks[i];
                            tasks[i] = tasks[j];
                            tasks[j] = tmp;
                        }else if (tasks[i].deadline.month == tasks[j].deadline.month){
                            if (tasks[i].deadline.day > tasks[j].deadline.day){
                                tmp = tasks[i];
                                tasks[i] = tasks[j];
                                tasks[j] = tmp;
                            }
                        }
                    }
                }j++;
            } i++;
        }
    } else if (sort_type == 3){
        int i = 0;
        Date current_date ,  given_date;
        time_t t;
        t = time(NULL);
        struct tm tm = *localtime(&t);

        current_date.day = tm.tm_mday;
        current_date.month = tm.tm_mon+1;
        current_date.year = tm.tm_year+1900;

        while (i < size){
            given_date = tasks[i].deadline;

            if (days_left(current_date, given_date) <= 3){
                printf("%d days left\n", days_left(current_date, given_date));
                display_task(tasks[i]);
            }i++;
        }
    }
}
int count_coWorkers(task t){
    int i = 0;
    while (strlen(t.cw[i].email) != 0)
        i++;
    return i;
}
void modify_task (task *tasks, int size, int modify_option){
    int i, task_index = -1, id, error = 0, print_error = 0;
    char temp, handler[10], holder[10], holder1[10], holder2[10];

    printf("Please enter the ID of task you would like to update:");
    scanf("%s", handler);
    id = atoi(handler);

    i = 0;
    while (i < size && task_index == -1){
        if(id == tasks[i].id)
            task_index = i;
        i++;
    }
    if (task_index == -1)
        printf("The task you are looking can't be found !\n");
    else{
        printf("You are modifying the task withe the ID %d : %s\n", id, tasks[task_index].title);
        if (modify_option == 1){
            char str[99], new_str[100];
            printf("New description :");
            scanf(" %c",&temp);
            fgets(str, 99, stdin);
            str[strcspn(str, "\n")] = '\0';

            new_str[0] = temp;
            new_str[1] = '\0';

            strcat(new_str, str);
            strcpy(tasks[task_index].description, new_str);
        }else if (modify_option == 2){
            while (error == 0){
                if (print_error == 1){
                    printf("ERROR!! The status you entered is invalid please try again the status can only be(todo , doing, done)\n");
                }
                printf("New status :");
                scanf("%s", tasks[task_index].status);
                if (strcmp(tasks[task_index].status, "todo") == 0 || strcmp(tasks[task_index].status, "doing") == 0 || strcmp(tasks[task_index].status, "done") == 0){
                    error = 1;
                    if (strcmp(tasks[task_index].status, "done") == 0){
                        if (count_coWorkers(tasks[task_index]) > 0){
                            int er = 0, print_er = 0;
                            while (er ==0){
                                char h[5];
                                int o;
                                display_cw(tasks[task_index]);
                                if (print_er != 0)
                                printf("ERROR! Please enter number of the coWorker that finished this task\n");
                                scanf("%s", h);
                                o = atoi(h);
                                if (o > 0 && o <= count_coWorkers(tasks[task_index])){
                                    er = 1;
                                    if (count_coWorkers(tasks[task_index]) > 1){
                                        tasks[task_index].cw[0] = tasks[task_index].cw[o - 1];
                                        int k = 1;
                                        while (k < count_coWorkers(tasks[task_index])){
                                            tasks[task_index].cw[k].first_name[0] = '\0';
                                            tasks[task_index].cw[k].last_name[0] = '\0';
                                            tasks[task_index].cw[k].email[0] = '\0';
                                            k++;
                                        }
                                    }
                                }
                                else print_er = 1;
                            }
                        }
                    }
                }
                else print_error = 1;
            }
            error = 0;
            print_error = 0;
        }else if (modify_option == 3){
            while (error == 0){
                if (print_error == 1){
                    printf("ERROR!! The date you entered is invalid please try again\n");
                }
                printf("The new Deadline is: \n");
                printf("day :");
                scanf("%s", holder);
                tasks[task_index].deadline.day = atoi(holder);
                printf("month :");
                scanf("%s", holder1);
                tasks[task_index].deadline.month = atoi(holder1);
                printf("year :");
                scanf("%s", holder2);
                tasks[task_index].deadline.year = atoi(holder2);
                if (is_valid_date(tasks[task_index].deadline.day, tasks[task_index].deadline.month, tasks[task_index].deadline.year)){
                    error = 1;
                }else print_error = 1;
            }
            error = 0;
            print_error = 0;
        }
    }
}
int delete_task (task *tasks, int *size){
    int i, task_index = -1, id, to_continue = 0, passed = 0;
    char holder1[10], holder2[10];

    printf("PLease enter the ID of the task you would like to delete :");
    scanf("%s", holder1);
    id = atoi(holder1);
    i = 0;
    while (i < (*size) && task_index == -1){
        if(id == tasks[i].id)
            task_index = i;
        i++;
    }
    if (task_index == -1){
        printf("The task you are looking can't be found !\n");
    } else{
        printf("Are you sure you want to delete task with ID : %d title : %s\n", id, tasks[task_index].title);
        printf("Enter 1 to continue (other value) to quite :");
        scanf("%s", holder2);
        to_continue = atoi(holder2);

        if (to_continue == 1){
            i = task_index;
            while (i < (*size) - 1){
                tasks[i] = tasks[i + 1];
                i++;
            }
            (*size)--;
            passed++;
        }
    }
    if (id == 0) printf("\t\t\t\t\t  INPUT INVALID TRY AGAIN\n");
    return passed;
}
void search_task(task *tasks, int size, int search_option){
    int i, task_index = -1, id;
    char title[50], temp, holder[10];
    i = 0;
    if (search_option == 1){
        printf("Enter the ID of task you would like to search for :");
        scanf("%s", holder);
        id = atoi(holder);

        while (i < size && task_index == -1){
            if(id == tasks[i].id)
                task_index = i;
            i++;
        }
        if (id == 0)
            printf("\t\t\t\t\t  INPUT INVALID TRY AGAIN\n");
        else if (task_index == -1)
            printf("The task you are looking can't be found !\n");
        else display_task(tasks[task_index]);
    }else if (search_option == 2){
        printf("Enter the title of task you woould like to search for :");
        scanf("%c",&temp);
	    fgets(title, 50, stdin);
        title[strcspn(title, "\n")] = '\0';

        while (i < size && task_index == -1){
            if(strcmp(title, tasks[i].title) == 0)
                task_index = i;
            i++;
        }
        if (task_index == -1)
            printf("task not found !!!!\n");
        else display_task(tasks[task_index]);
    }else if (search_option == 3){
        Date date;
        printf("Enter the deadline you want search for (dd-mm-year) :");
        scanf("%d-%d-%d", &date.day, &date.month, &date.year);

        while (i < size) {
            if((date.day == tasks[i].deadline.day && date.month == tasks[i].deadline.month) && date.year == tasks[i].deadline.year){
                task_index = i;
                display_task(tasks[i]);
            }
            i++;
        }
        if (task_index == -1) printf("We aren't able to find a task with matching deadline!\n");
    }
}
int total_finished_tasks(task *tasks, int size){
    int total = 0, i= 0;
    while (i < size){
        if (strcmp(tasks[i].status, "done") == 0)
            total++;
        i++;
    } return total;
}
int total_not_finished_tasks(task *tasks, int size){
    int total = 0, i= 0;
    while (i < size){
        if (strcmp(tasks[i].status, "done") != 0)
            total++;
        i++;
    }return total;
}
void days_left_in_deadline (task *tasks, int size){
    int i;
    Date current_date, given_date;
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);

    current_date.day = tm.tm_mday;
    current_date.month = tm.tm_mon + 1;
    current_date.year = tm.tm_year + 1900;
    i = 0;
    while (i < size){
        given_date = tasks[i].deadline;
        printf("task ID %d :%d day left\n", tasks[i].id, days_left(current_date, given_date));
        i++;
    }
}
int main_menu (int error){
    int choice;
    char holder[20];

    if (error == -1)
    printf("Invalid choice! Please try again .\n");
    printf("\t\t\t\t\t\t+----------------------------MENU-----------------------------+\n");
    printf("\t\t\t\t\t\t|        [1]  Add one or multible tasks.                      |\n");
    printf("\t\t\t\t\t\t|        [2]  Disalay tasks.                                  |\n");
    printf("\t\t\t\t\t\t|        [3]  Modify a task.                                  |\n");
    printf("\t\t\t\t\t\t|        [4]  Delete a task.                                  |\n");
    printf("\t\t\t\t\t\t|        [5]  Search for a task.                              |\n");
    printf("\t\t\t\t\t\t|        [6]  Display statistics.                             |\n");
    printf("\t\t\t\t\t\t|        [7]  Quit.                                         |\n");
    printf("\t\t\t\t\t\t+-------------------------------------------------------------+\n");
    printf("\t ->Enter your choice: ");
    scanf("%s", holder);
    choice = atoi(holder);
    if (choice == 0)
        choice = -2;
    return choice;
}

int main(){
    int size = 0, s = 0, option, stop = 0, flag = 0, error = 0;
    task* tasks = NULL;

    while (stop != -1){
        option = main_menu(0);
        if (option == 1){
            char holder[10];
            printf("\t  -How many tasks you would like to add : ");
            scanf("%s", holder);
            s = atoi(holder);
            if (s == 0)
                printf("\t\t\t\t\t\t\t\t  INPUT INVALID TRY AGAIN\n");
            else{
                int size1 = size;
                size = size + s;
                if (flag > 0){
                    flag++;
                    tasks = (task*)realloc(tasks, (size * sizeof(task)));
                    if (tasks == NULL) {
                        printf("Memory allocation failed!");
                        return 1;
                    }
                }
                if (flag == 0)
                {
                    flag++;
                    tasks = (task*)malloc(size * sizeof(task));
                    if (tasks == NULL) {
                        printf("Memory allocation failed");
                        return 1;
                    }
                }

                printf("\t\t\t\t\t__________________________________adding tasks__________________________________\n\n");
                add_tasks(tasks, size1, size, flag);
            }
        }

        if (option == 2)
        {
            int sort_option;
            char holder[10];
            printf("\t\t\t\t\t\t\t<------------------display all tasks--------------->\n");
            printf("\t\t\t\t\t\t\t< how you wanna display tasks :                    >\n");
            printf("\t\t\t\t\t\t\t< 1 sorted by alphabetical order :                 >\n");
            printf("\t\t\t\t\t\t\t< 2 sorted by deadline :                           >\n");
            printf("\t\t\t\t\t\t\t< 3 tasks that has 3 days or less for deadline.    >\n");
            printf("\t\t\t\t\t\t\t< 4 display :                                      >\n");
            printf("\t\t\t\t\t\t\t<-------------------------------------------------->\n");
            printf("enter your choice:");
            scanf("%s", holder);
            sort_option = atoi(holder);
            if (sort_option >= 1 && sort_option < 4){
                printf("\t\t\t\t\t__________________________________display__________________________________\n");
                display_tasks_sorted(tasks, size, sort_option);
                if (sort_option != 3)
                    display_tasks(tasks, size);
            }
            else if (sort_option == 4)
            {
                printf("\t\t\t\t\t__________________________________display__________________________________\n");
                display_tasks(tasks, size);
            }
            else if (sort_option == 0)
            {
                printf("\t\t\t\t\t\t\t\t  INPUT INVALID TRY AGAIN\n");
            }
        }
        if (option == 3)
        {
            int modify_option;
            char holder[10];
            printf("\t\t\t\t\t\t\t<-------------------modify all tasks--------------->\n");
            printf("\t\t\t\t\t\t\t< modification options :                           >\n");
            printf("\t\t\t\t\t\t\t< 1 to modify description.                         >\n");
            printf("\t\t\t\t\t\t\t< 2 to modify status.                              >\n");
            printf("\t\t\t\t\t\t\t< 3 to modify deadline.                            >\n");
            printf("\t\t\t\t\t\t\t< 7 quit.                                         >\n");
            printf("\t\t\t\t\t\t\t<-------------------------------------------------->\n");
            printf("enter your choice:");
            scanf("%s", holder);
            modify_option = atoi(holder);
            //scanf("%d", &modify_option);
            if (modify_option >= 1 && modify_option <= 3)
                modify_task(tasks, size, modify_option);
            else if (modify_option == 0)
                printf("\t\t\t\t\t\t\t\t  INPUT INVALID TRY AGAIN\n");
        }
        if (option == 4){
            printf("\t\t\t\t\t__________________________________delete__________________________________\n");
            int passed = delete_task(tasks, &size);
            if (passed == 1){
                tasks = (task*)realloc(tasks, (size * sizeof(task)));

                if (size == 0) {
                    free(tasks);
                    tasks = NULL;
                }
            }
        }
        if (option == 5){
            int search_option;
            char handler[10];
            printf("\t\t\t\t\t\t\t<-----------------search for tasks----------------->\n");
            printf("\t\t\t\t\t\t\t< search options :                                 >\n");
            printf("\t\t\t\t\t\t\t< 1 to search by ID.                               >\n");
            printf("\t\t\t\t\t\t\t< 2 to search by title.                            >\n");
            printf("\t\t\t\t\t\t\t< 3 to search by deadline.                         >\n");
            printf("\t\t\t\t\t\t\t< 7 quit.                                         >\n");
            printf("\t\t\t\t\t\t\t<-------------------------------------------------->\n");
            printf("enter your choice:");
            scanf("%s", handler);
            search_option = atoi(handler);
            if (search_option >= 1 && search_option <= 3)
                search_task(tasks, size, search_option);
            else if (search_option == 0)
                printf("\t\t\t\t\t\t\t\t  INPUT INVALID TRY AGAIN\n");
        }
        if (option == 6)
        {
            int statistics_option;
            char handler[10];
            printf("\t\t\t\t\t\t\t<--------------------statistics-------------------->\n");
            printf("\t\t\t\t\t\t\t< statistics options :                             >\n");
            printf("\t\t\t\t\t\t\t< 1 for total number of tasks.                     >\n");
            printf("\t\t\t\t\t\t\t< 2 for finished tasks and none finished.          >\n");
            printf("\t\t\t\t\t\t\t< 3 for number of days for deadline.               >\n");
            printf("\t\t\t\t\t\t\t< 7 quit.                                          >\n");
            printf("\t\t\t\t\t\t\t<-------------------------------------------------->\n");
            printf("Enter your choice:");
            scanf("%s", handler);
            statistics_option = atoi(handler);
            if (statistics_option == 1)
            {
                printf("\t\t\t\t\t__________________________________total tasks__________________________________\n");
                printf("Total number of tasks : %d\n", size);
            }
            else if (statistics_option == 2)
            {
                printf("\t\t\t\t\t__________________________________finished tasks__________________________________\n");
                printf("The number of finished tasks : %d\n", total_finished_tasks(tasks, size));
                printf("The number of not finished tasks : %d\n", total_not_finished_tasks(tasks, size));
            }
            else if (statistics_option == 3)
            {
                printf("\t\t\t\t\t__________________________________days left in deadline__________________________________\n");
                days_left_in_deadline (tasks, size);
            }
            else if (statistics_option = 0)
            {
                printf("\t\t\t\t\t\t\t  INPUT INVALID TRY AGAIN\n");
            }
        }
        if (option == -2)
            printf("ERROR! you enterd the wrong value please try again\n");
        if (option == 7)
            stop = -1;
    }
    free(tasks);
    printf("nice, you make it :)\n");
}
