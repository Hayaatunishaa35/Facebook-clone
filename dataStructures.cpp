struct TrieNode *rootOfTrie = getNode();

// doubly linked list of posts - specific to a user
struct Post
{
    string author;
    string content;
    int likes;
    struct Post *previousPost;
    struct Post *nextPost;
};

// every newsfeed is user-specific
// it is a stack of posts LIFO
// every time a user posts something, the newsfeeds of all his/her friends get the particular post added to their stack

struct Feed
{
    struct Post *post;
    struct Feed *next;
};

// queue of friend requests
struct FriendRequest
{
    string nameOfUser;
    int idOfUser;
    struct FriendRequest *next;
};

// Graph
// every user is a node in the adjacency list
struct User
{
    int user_id;
    string name;
    struct User *next;                         // refer graph1
    struct Post *posts;                        // denotes the head of posts - points to the first post
    struct FriendRequest *friendRequestsFront; // points to the first friend request
    struct FriendRequest *friendRequestsRear;  // points to the last friend request
    struct Feed *feed;                         // stack of posts: newsfeed
    bool active;
};

struct Graph
{
    int V;
    struct User *users; // must be an array of adjacency lists, as the graph can be disconnected
};

typedef struct Graph *GRAPHPTR;

struct User *initializeFriend(int id, string name)
{
    struct User *temp = new User;
    temp->name = name;
    temp->user_id = id;
    temp->friendRequestsFront = temp->friendRequestsRear = NULL;
    temp->active = true;
    temp->next = NULL;
    temp->feed = NULL;
    temp->posts = NULL;

    return temp;
}

void addEdge(GRAPHPTR graph, int src, int destination)
{
    // append destination to src adj list
    struct User *destinationUser = initializeFriend(graph->users[destination].user_id, graph->users[destination].name);
    struct User *curUser = &graph->users[src];
    while (curUser->next != NULL)
    {
        curUser = curUser->next;
    }
    curUser->next = destinationUser;

    // append src to destinations' adj list

    destinationUser = initializeFriend(graph->users[src].user_id, graph->users[src].name);
    curUser = &graph->users[destination];
    while (curUser->next != NULL)
    {
        curUser = curUser->next;
    }
    curUser->next = destinationUser;
}

void initializeUser(struct User *user)
{
    user->name = "";
    user->next = NULL;
    user->posts = NULL;
    user->friendRequestsFront = NULL;
    user->friendRequestsRear = NULL;
    user->feed = NULL;
    user->active = false;
}

GRAPHPTR initializeGraph(int v)
{
    GRAPHPTR graph = new Graph;
    graph->V = v;
    graph->users = new User[v];
    for (int i = 0; i < v; i++)
    {
        graph->users[i].user_id = i;
        initializeUser(&graph->users[i]);
    }

    return graph;
}

void addUser(GRAPHPTR graph, string name)
{
    transform(name.begin(), name.end(), name.begin(), ::tolower);
    int i;
    for (i = 0; i < graph->V; i++)
    {
        if (graph->users[i].active == false)
        {
            graph->users[i].name = name;
            graph->users[i].active = true;
            break;
        }
    }
    insert(rootOfTrie, name);
}

void displayAllUsersInTheSystem(GRAPHPTR graph)
{
    cout << "All the users in the system : \n";

    for (int i = 0; i < graph->V; i++)
    {
        if (graph->users[i].active)
        {
            cout << graph->users[i].user_id << " : " << graph->users[i].name << endl;
        }
    }
}

int displayParticularUser(GRAPHPTR graph, string name)
{

    for (int i = 0; i < graph->V; i++)
    {
        if (graph->users[i].name == name)
        {
            cout << graph->users[i].user_id << " : " << name << endl;
        }
    }
    int id;
    cout << "Enter the ID of the required person : \n";
    cin >> id;

    return id;
}

int getUserByID(GRAPHPTR graph)
{
    // assumed displayed

    // form trie
    // use autocomplete, retrieve user, send address

    // get atleast 3 characters
    int comp;
    int flag = 0;
    string reqName = "";
    char temp;
    cout << "Enter the name of the person character by character: \n";

    while (1)
    {
        cout << "Enter the next character!\n";
        cout << reqName;
        cin >> temp;
        reqName.push_back(temp);

        cout << "The name you have entered is : " << reqName << endl
             << endl;

        if (comp = printAutoSuggestions(rootOfTrie, reqName) == 0)
        {
            cout << "No matching strings !\n";
            cout << "Enter r to remove the previously entered character and continue, c to clear the search, x to abort search and exit \n";
            cin >> temp;
            if (temp == 'r')
            {
                reqName.pop_back();
            }
            else if (temp == 'c')
            {
                reqName.clear();
            }
            else if (temp == 'x')
            {
                return -1;
            }
        }
        else if (comp = printAutoSuggestions(rootOfTrie, reqName) == -1)
        {
            cout << endl
                 << "Is this the required name ? (y/n)";
            cin >> temp;
            if (temp == 'y' || temp == 'Y')
            {
                cout << "Select the ID of the person : \n"; // as there can be more than one person with the same name, and in the trie it cannot recognize that
                return displayParticularUser(graph, reqName);
            }
        }
        cout << endl;
    }
}

struct FriendRequest *getFriendRequest()
{
    struct FriendRequest *fr = new FriendRequest;
    fr->next = NULL;
    return fr;
}

void enqueueFriendRequest(GRAPHPTR graph, int sourceUserID, int destinationUserID)
{
    struct FriendRequest *temp = getFriendRequest();
    temp->idOfUser = sourceUserID;
    temp->nameOfUser = graph->users[sourceUserID].name;
    // now coming to the enqueueing part
    if (graph->users[destinationUserID].friendRequestsRear == NULL)
    {
        graph->users[destinationUserID].friendRequestsRear = graph->users[destinationUserID].friendRequestsFront = temp;
    }
    else
    {
        graph->users[destinationUserID].friendRequestsRear->next = temp;
        graph->users[destinationUserID].friendRequestsRear = temp;
    }
}

void dequeueFriendRequest(GRAPHPTR graph, int ID)
{
    struct FriendRequest *front1 = graph->users[ID].friendRequestsFront;

    if (front1->next == NULL)
    {
        free(graph->users[ID].friendRequestsFront);
        graph->users[ID].friendRequestsFront = graph->users[ID].friendRequestsRear = NULL;
    }
    else
    {
        front1 = front1->next;
        free(graph->users[ID].friendRequestsFront);
        graph->users[ID].friendRequestsFront = front1;
    }
}

void pushIntoFeedStack(GRAPHPTR graph, int ID, Post *srcPost)
{
    if (graph->users[ID].feed == NULL)
    {
        graph->users[ID].feed = new Feed;
        graph->users[ID].feed->post = srcPost;
        graph->users[ID].feed->next = NULL;
    }
    else
    {
        Feed *tempFeed = new Feed;
        tempFeed->post = srcPost;
        tempFeed->next = graph->users[ID].feed;
        graph->users[ID].feed = tempFeed;
    }
}

void popFromFeedStack(GRAPHPTR graph, int ID)
{
    Feed *feedToBeDeleted = graph->users[ID].feed;
    graph->users[ID].feed = graph->users[ID].feed->next;
    delete feedToBeDeleted;
}