void sendFriendRequest(GRAPHPTR graph, int ID)
{
    User *user = &graph->users[ID];
    // view all users in the system, and using trie get the person's ID

    displayAllUsersInTheSystem(graph);
    cout << "Enter the ID of the person whom you want to befriend : ";
    int destinationUserID;
    cin >> destinationUserID;
    if (destinationUserID > graph->V || destinationUserID < 0)
    {
        return;
    }
    // trie can be used here to implement autocomplete
    enqueueFriendRequest(graph, ID, destinationUserID);
    cout << "Friend request sent to " << graph->users[destinationUserID].name << endl;
}