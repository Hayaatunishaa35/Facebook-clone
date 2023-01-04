void displayFriendRequests(GRAPHPTR graph, int ID)
{
    struct FriendRequest *front1 = graph->users[ID].friendRequestsFront;
    struct FriendRequest *rear1 = graph->users[ID].friendRequestsRear;

    if (!front1 && !rear1)
    {
        cout << "No pending friend requests!" << endl;
        return;
    }
    while (1)
    {
        cout << "Friend request received from : \n";
        cout << "ID : " << front1->idOfUser << "  Name : " << front1->nameOfUser << endl;
        char choice;
        cout << "To accept friend request, enter y, to reject it, enter n :\n\n";
        cin >> choice;

        if (choice == 'y')
        {
            addEdge(graph, ID, front1->idOfUser);
        }
        // now remove that friend request from queue, after storing the next request in front1
        if (front1 == rear1)
        {
            dequeueFriendRequest(graph, ID);
            break;
        }
        front1 = front1->next;
        dequeueFriendRequest(graph, ID);
        if (front1 == NULL)
        {
            break;
        }
    }
}