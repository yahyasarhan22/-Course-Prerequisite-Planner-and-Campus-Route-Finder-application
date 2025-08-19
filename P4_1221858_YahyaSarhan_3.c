// NAME: Yahya Sarhan                     ID: 1221858                              SEC:3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
//
#define INF INT_MAX
//
struct node // for load2
{
    char data[20];
    struct node *next;
    int in_degree;
    int stats;
};
typedef struct node1 *Add;
struct node1 // for linked list
{
    Add next;
    Add rear;
    char add_str[100];
};
struct node2 // for load 1
{
    char Bulid[20];
    int distance;
    struct node2 *next;
};
typedef struct MinHeap MinHeap;
typedef struct MinHeapNode MinHeapNode;

struct MinHeapNode
{
    int vertex;
    int dist;
};

struct MinHeap
{
    MinHeapNode **array;
    int *pos;
    int size;
    int capacity;
};
//
void Add_Edge(struct node *array_Load2[], char *des, char *head, int size_load2);
void makeEmpty_Queue(Add q);
void DeQueue(Add q);
void swapMinHeapNode(MinHeapNode **a, MinHeapNode **b);
MinHeap *createMinHeap(int capacity);
//
void Display() // for display the main menu
{
    printf("1. Load the two files.\n");
    printf("2. Calculate the shortest distance between two buildings.\n");
    printf("3. Print the shortest route between two buildings and the total distance.\n");
    printf("4. Sort the courses using the topological sort.\n");
    printf("5. Print the sorted courses.\n");
    printf("6. Exit the application.\n");
}

//////////////////////////////LOAD2////////////////////////////////////////////////////

struct node *Make_empty(struct node *temp)
{
    temp = (struct node *)malloc(sizeof(struct node));
    if (temp == NULL)
    {
        printf("the memory is full.\n");
        return NULL;
    }
    temp->next = NULL;
    return temp;
}

void Insert_Last(char *word, struct node *l) // for load2
{
    struct node *ptr = l->next;
    while (ptr != NULL)
    {
        if (strcmp(word, ptr->data) == 0)
        {
            return;
        }
        ptr = ptr->next;
    }
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    if (temp == NULL)
    {
        printf("the memory is full.\n");
        return;
    }
    ptr = l;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    strcpy(temp->data, word);
    temp->next = NULL;
    ptr->next = temp;
}

int Size_Load2(struct node *array_Load2[])
{
    FILE *input;
    input = fopen("input_courses.txt", "r");
    if (input == NULL)
    {
        printf("Failed to open file. This file does not exist.\n");
        return 0;
    }
    struct node *l = (struct node *)malloc(sizeof(struct node));
    l->next = NULL;
    char word[500];
    char *temp;
    while (fgets(word, sizeof(word), input) != NULL)
    {
        size_t len = strlen(word);
        if (len > 0 && word[len - 1] == '\n')
        {
            word[len - 1] = '\0'; // remove the new line
        }
        temp = strtok(word, "#");
        while (temp != NULL)
        {
            Insert_Last(temp, l);
            temp = strtok(NULL, "#");
        }
    }
    int count = 0;
    struct node *ptr = l->next;
    while (ptr != NULL) // to find the size of array
    {
        count++;
        ptr = ptr->next;
    }
    ptr = l->next;
    for (int i = 0; i < count; i++) // make a heads
    {
        array_Load2[i] = Make_empty(NULL);
        strcpy(array_Load2[i]->data, ptr->data);
        ptr = ptr->next;
    }
    fclose(input);
    printf("The Load File 2 Is Done.\n");
    return count;
}

void Creat_Edge(struct node *array_Load2[], int size_load2)
{
    FILE *input;
    input = fopen("input_courses.txt", "r");
    if (input == NULL)
    {
        printf("Failed to open file. This file does not exist.\n");
        return;
    }
    char word[500];
    char *des;
    char *head;
    while (fgets(word, sizeof(word), input) != NULL)
    {
        size_t len = strlen(word);
        if (len > 0 && word[len - 1] == '\n')
        {
            word[len - 1] = '\0';
        }
        des = strtok(word, "#");
        head = strtok(NULL, "#");

        while (head != NULL)
        {
            Add_Edge(array_Load2, des, head, size_load2);
            head = strtok(NULL, "#");
        }
    }
    fclose(input);

    for (int i = 0; i < size_load2; i++)
    {
        struct node *ptr = array_Load2[i];
        while (ptr != NULL)
        {
            ptr->in_degree = 0;
            ptr->stats = 0; // not visited
            ptr = ptr->next;
        }
    }

    for (int i = 0; i < size_load2; i++)
    {
        struct node *ptr = array_Load2[i]->next;
        while (ptr != NULL)
        {
            for (int j = 0; j < size_load2; j++)
            {
                if (strcmp(array_Load2[j]->data, ptr->data) == 0)
                {
                    array_Load2[j]->in_degree++;
                    break;
                }
            }
            ptr = ptr->next;
        }
    }
    printf("Created Edges  For Load 2 Done.\n");
}

void Add_Edge(struct node *array_Load2[], char *des, char *head, int size_load2)
{
    int index = -1;
    for (int i = 0; i < size_load2; i++) // find the index to insert edges
    {
        if (array_Load2[i] != NULL && strcmp(array_Load2[i]->data, head) == 0)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        printf("there is no course like this name.\n");
        return;
    }

    Insert_Last(des, array_Load2[index]);
}

Add creatQueue() // creat Queue
{
    Add q;
    q = (Add)malloc(sizeof(struct node1));
    if (q == NULL)
    {
        printf("Out Of Meomry.\n");
    }
    q->rear = q;
    q->next = NULL;
    makeEmpty_Queue(q);
    return q;
}

int isEmpty_Queue(Add q) // check if the Queua is empty or not
{
    return (q->next == NULL);
}

void makeEmpty_Queue(Add q) // make the Queue empty but the head stil
{
    if (q == NULL)
    {
        printf("The Queue is empty.\n");
        return;
    }
    else
        while (!isEmpty_Queue(q))
        {
            DeQueue(q);
        }
}

void DeQueue(Add q) // remove the element from Front/Head (FIFO => first in first out)
{
    Add firstCell;
    if (isEmpty_Queue(q))
    {
        printf("Empty Queue.\n");
        return;
    }
    else
    {
        firstCell = q->next;
        q->next = q->next->next;
        free(firstCell);
    }
}

void EnQueue(char *x, Add q) // Insert the element at Rear(Insert last)
{
    Add temp;
    temp = (Add)malloc(sizeof(struct node1));
    if (temp == NULL)
    {
        printf("Out Of Memory.\n");
        return;
    }
    else
    {
        strncpy(temp->add_str, x, sizeof(temp->add_str));
        if (q->next == NULL)
        {
            temp->next = NULL;
            q->next = temp;
            q->rear = temp;
        }
        else
        {
            temp->next = NULL;
            q->rear->next = temp;
            q->rear = temp;
        }
    }
}

void Topological_Sort(struct node *array_Load2[], int size_load2, Add q)
{
    int i = 0;
    while (i < size_load2)
    { // check if the degree zero and not visited
        if (array_Load2[i]->in_degree == 0 && array_Load2[i]->stats == 0)
        {
            EnQueue(array_Load2[i]->data, q);
            array_Load2[i]->stats = 1;
            if (array_Load2[i]->next != NULL)
            {
                struct node *ptr = array_Load2[i]->next;
                while (ptr != NULL)
                {
                    for (int j = 0; j < size_load2; j++)
                    {
                        if (strcmp(array_Load2[j]->data, ptr->data) == 0)
                        {
                            array_Load2[j]->in_degree--;
                            break;
                        }
                    }
                    ptr = ptr->next;
                }
                // free the nodes
                struct node *ptr1 = array_Load2[i]->next;
                struct node *temp = array_Load2[i]->next;
                array_Load2[i]->next = NULL;
                while (ptr1 != NULL)
                {
                    ptr1 = ptr1->next;
                    free(temp);
                    temp = ptr1;
                }
            }
            i = -1; // to start from being
        }
        i++;
    }
    printf("The Topological Sort Is Done.\n");
}

/////////////////////////////////////LOAD1/////////////////////////////////////////////////

void Insert_Last1(char *word, struct node2 *l)
{
    struct node2 *ptr = l->next;
    while (ptr != NULL)
    {
        if (strcmp(word, ptr->Bulid) == 0)
        {
            return;
        }
        ptr = ptr->next;
    }
    struct node2 *temp = (struct node2 *)malloc(sizeof(struct node2));
    if (temp == NULL)
    {
        printf("the memory is full.\n");
        return;
    }
    ptr = l;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    strcpy(temp->Bulid, word);
    temp->next = NULL;
    ptr->next = temp;
}

struct node2 *Make_empty1(struct node2 *temp)
{
    temp = (struct node2 *)malloc(sizeof(struct node2));
    if (temp == NULL)
    {
        printf("the memory is full.\n");
        return NULL;
    }
    temp->next = NULL;
    return temp;
}

int Size_Load1(struct node2 *array_Load1[])
{
    FILE *input;
    input = fopen("input_buildings.txt", "r");
    if (input == NULL)
    {
        printf("Failed to open file. This file does not exist.\n");
        return 0;
    }
    struct node2 *l = (struct node2 *)malloc(sizeof(struct node2));
    l->next = NULL;
    char word[500];
    char *temp;
    while (fgets(word, sizeof(word), input) != NULL)
    {
        size_t len = strlen(word);
        if (len > 0 && word[len - 1] == '\n')
        {
            word[len - 1] = '\0'; // remove the new line
        }
        temp = strtok(word, "#"); // take the first word

        Insert_Last1(temp, l);
        temp = strtok(NULL, "#"); // take the next word
        if (temp != NULL)
        {
            Insert_Last1(temp, l);
        }
    }
    int count = 0;
    struct node2 *ptr = l->next;
    while (ptr != NULL) // get the size
    {
        count++;
        ptr = ptr->next;
    }
    ptr = l->next;
    for (int i = 0; i < count; i++) // insert the heads(the courses)
    {
        array_Load1[i] = Make_empty1(NULL);
        strcpy(array_Load1[i]->Bulid, ptr->Bulid);
        ptr = ptr->next;
    }
    fclose(input);
    printf("The Load File 1 Is Done.\n");
    return count;
}

void insert_Bulid(struct node2 *array_Load1[], int size_load1, char *word1, char *word2, int dis)
{
    for (int i = 0; i < size_load1; i++)
    {
        // undirected graph
        if (array_Load1[i] != NULL && strcmp(array_Load1[i]->Bulid, word1) == 0)
        {
            struct node2 *temp = (struct node2 *)malloc(sizeof(struct node2));
            if (temp == NULL)
            {
                printf("the memory is full.\n");
                return;
            }
            // insert last
            struct node2 *ptr = array_Load1[i];
            while (ptr->next != NULL)
            {
                ptr = ptr->next;
            }
            strcpy(temp->Bulid, word2);
            temp->distance = dis;
            temp->next = NULL;
            ptr->next = temp;
            break;
        }
    }
    for (int i = 0; i < size_load1; i++)
    {
        if (array_Load1[i] != NULL && strcmp(array_Load1[i]->Bulid, word2) == 0)
        {
            struct node2 *temp1 = (struct node2 *)malloc(sizeof(struct node2));
            if (temp1 == NULL)
            {
                printf("the memory is full.\n");
                return;
            }
            struct node2 *ptr1 = array_Load1[i];
            while (ptr1->next != NULL)
            {
                ptr1 = ptr1->next;
            }
            strcpy(temp1->Bulid, word1);
            temp1->distance = dis;
            temp1->next = NULL;
            ptr1->next = temp1;
            break;
        }
    }
}

void insert_Buliding(struct node2 *array_Load1[], int size_load1)
{
    FILE *input;
    input = fopen("input_buildings.txt", "r");
    if (input == NULL)
    {
        printf("Failed to open file. This file does not exist.\n");
        return;
    }
    char word[500];
    char *word1;
    char *word2;
    char *word3;
    while (fgets(word, sizeof(word), input) != NULL)
    {
        size_t len = strlen(word);
        if (len > 0 && word[len - 1] == '\n')
        {
            word[len - 1] = '\0';
        }
        word1 = strtok(word, "#");
        word2 = strtok(NULL, "#");
        word3 = strtok(NULL, "#");
        int dis = atoi(word3); // convert the string to int(for distance)
        insert_Bulid(array_Load1, size_load1, word1, word2, dis);
    }
}

int get_index(struct node2 *array_Load1[], int size_load1, char *word) // to find the index
{
    for (int i = 0; i < size_load1; i++)
    {
        if (strcmp(array_Load1[i]->Bulid, word) == 0)
        {
            return i; // the correct index
        }
    }
    return -1; // not founded
}

MinHeap *createMinHeap(int capacity)
{
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode **)malloc(capacity * sizeof(MinHeapNode *));
    return minHeap;
}

void swap(MinHeap *minHeap, int ver, int dist) // dist =>the new distance for vertex
{                                              // ver =>the distance want to updated
    int i = minHeap->pos[ver];
    minHeap->array[i]->dist = dist; // make update of new distance
    while (i != 0 && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        // if the condition is true this mean the parent greater than child
        minHeap->pos[minHeap->array[i]->vertex] = (i - 1) / 2;             // swap the virtex of child to the parent
        minHeap->pos[minHeap->array[(i - 1) / 2]->vertex] = i;             // swap the virtex of parent to the child
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]); // swap hte nodes
        i = (i - 1) / 2;                                                   // update the index into parent
    }
}

void swapMinHeapNode(MinHeapNode **a, MinHeapNode **b)
{
    // swap the two nodes
    MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}

int is_min_heap(MinHeap *minHeap, int ver)
{
    if (minHeap->pos[ver] < minHeap->size)
    {
        return 1;
    }
    return 0;
}

void minHeapify(MinHeap *minHeap, int idx) // this function to make sure the heap still vaild
{
    int smallest, left, right;
    smallest = idx;      // parent
    left = 2 * idx + 1;  // left child
    right = 2 * idx + 2; // right child
    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;
    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;
    if (smallest != idx)
    {
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *idxNode = minHeap->array[idx];
        minHeap->pos[smallestNode->vertex] = idx;
        minHeap->pos[idxNode->vertex] = smallest;
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

MinHeapNode *extractMin(MinHeap *minHeap) // remove the smallest node in the heap and make sure the heap still vaild
{
    if (minHeap->size == 0)
    { // the heap is empty
        return NULL;
    }
    MinHeapNode *first = minHeap->array[0];                // store the smallest node
    MinHeapNode *last = minHeap->array[minHeap->size - 1]; // store the last node
    minHeap->array[0] = last;                              // the last element moved to first
    minHeap->pos[first->vertex] = minHeap->size - 1;       // remove the smallest node
    minHeap->pos[last->vertex] = 0;                        // update the position for last node to be the first node
    minHeap->size--;
    minHeapify(minHeap, 0);
    return first;
}

void dij(struct node2 *array_Load1[], int src, int size_load1, int dist[], int parent[])
{
    MinHeap *minHeap = createMinHeap(size_load1); // creat min heap with capacity equal to size of array
    for (int i = 0; i < size_load1; i++)
    {
        dist[i] = INF;
        minHeap->array[i] = (MinHeapNode *)malloc(sizeof(MinHeapNode));
        minHeap->array[i]->vertex = i;
        minHeap->array[i]->dist = dist[i];
        minHeap->pos[i] = i;
        parent[i] = -1; // no parent
    }
    minHeap->array[src]->dist = 0;
    dist[src] = 0;
    swap(minHeap, src, dist[src]);
    minHeap->size = size_load1;
    while (minHeap->size != 0)
    {
        MinHeapNode *minHeapNode = extractMin(minHeap);
        int u = minHeapNode->vertex;
        struct node2 *temp = array_Load1[u]->next;
        while (temp != NULL)
        {
            int v = get_index(array_Load1, size_load1, temp->Bulid);
            if (is_min_heap(minHeap, v) && dist[u] != INF)
            {
                if (temp->distance + dist[u] < dist[v])
                {
                    dist[v] = dist[u] + temp->distance;
                    parent[v] = u;
                    swap(minHeap, v, dist[v]);
                }
            }
            temp = temp->next;
        }
    }
    printf("Calculate the shortest distance between two buildings is done.\n");
}

void printPath(int parent[], int j, struct node2 *array_Load1[])
{
    // if j=-1 => there is no parent
    if (j == -1)
    {
        return;
    }
    printPath(parent, parent[j], array_Load1);
    printf(" => %s ", array_Load1[j]->Bulid);
}

void printDijkstraResults(struct node2 *array_Load1[], int end, int dist[], int parent[])
{
    printf("The distance is: %d\n", dist[end]);
    printf("The path is: ");
    printPath(parent, end, array_Load1);
    printf("\n");
}

int main()
{
    int size_load2 = 0;
    int size_load1 = 0;
    struct node *array_Load2[100];  // to load from file 2
    struct node2 *array_Load1[100]; // to load from file 1
    Add q = creatQueue();           // For Topological Sort
    char src[20], des[20];
    // dist used to store the shortest path between two building
    int dist[100], parent[100];
    int op;
    int flag_top = 0, loaded = 0, dijkis = 0, topl = 0; // flags
    Add ptr;                                            // to print Topological Sort
    do
    {
        printf("Please enter any operation:\n\n");
        Display();
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            size_load2 = Size_Load2(array_Load2);     // load2
            Creat_Edge(array_Load2, size_load2);      // load2
            size_load1 = Size_Load1(array_Load1);     // load1
            insert_Buliding(array_Load1, size_load1); // load1
            loaded = 1;
            break;
        case 2:
            if (loaded == 0)
            {
                printf("Error: File not loaded.\n");
                break;
            }
            printf("Enter the starting building: ");
            scanf("%s", src);
            printf("Enter the ending building: ");
            scanf("%s", des);
            int start = get_index(array_Load1, size_load1, src);
            int end = get_index(array_Load1, size_load1, des);
            if (start == -1 || end == -1)
            {
                printf("There Is No Building Like This Name.\n");
                break;
            }
            dij(array_Load1, start, size_load1, dist, parent);
            dijkis = 1;
            break;
        case 3:
            if (loaded == 0)
            {
                printf("Error: File not loaded.\n");
                break;
            }
            if (dijkis == 0)
            {
                printf("Error: Calculate the shortest distance between two buildings first.\n");
                break;
            }
            printDijkstraResults(array_Load1, end, dist, parent);
            break;
        case 4:
            if (loaded == 0)
            {
                printf("Error: File not loaded.\n");
                break;
            }
            if (flag_top == 0) // you can do just (1) Topological Sort
            {
                Topological_Sort(array_Load2, size_load2, q);
                flag_top = 1;
                topl = 1;
            }
            break;
        case 5:
            if (loaded == 0)
            {
                printf("Error: File not loaded.\n");
                break;
            }
            if (topl == 0)
            {
                printf("Error: Sort the courses first.\n");
                break;
            }
            ptr = q;
            while (ptr->next != NULL && flag_top == 1)
            {
                ptr = ptr->next;
                printf("%s -> ", ptr->add_str);
            }
            printf("\n");
            break;
        case 6:
            printf("Goodbye.\n");
            return 0;
        default:
            printf("The operation is invalid, try again.\n");
            break;
        }
    } while (op != 6);

    return 0;
}