void friendSuggestions(GRAPHPTR graph, int ID)
{
    unordered_map<int, int> umap;
    User *user = &graph->users[ID];
    User *friendOfUser = user->next;
    while (friendOfUser)
    {
        umap.insert(make_pair(friendOfUser->user_id, 0));
        friendOfUser = friendOfUser->next;
    }
    friendOfUser = user->next;
    while (friendOfUser)
    {
        User *searchUser = &graph->users[friendOfUser->user_id];
        User *friendOfSearchUser = searchUser->next;
        while (friendOfSearchUser)
        {
            if (umap.find(friendOfSearchUser->user_id) != umap.end())
            {
                // implies that that id exists in the hash table
                umap[friendOfSearchUser->user_id]++;
            }

            friendOfSearchUser = friendOfSearchUser->next;
        }

        friendOfUser = friendOfUser->next;
    }

    // now find the keys with highest values, lower limit set to 3 mutual friends here
    cout << "Friend suggestions, filtered with no. of mutual friends greater than or equal to 2:\n";
    for (auto i = umap.begin(); i != umap.end(); i++)
    {
        // simple solution
        if (i->second >= 2)
        {
            cout << i->first << " : " << graph->users[i->first].name << endl;
        }
    }
}