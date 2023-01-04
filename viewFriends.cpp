void viewFriends(User *user)
{
    User *curFriend = user->next;
    while (curFriend)
    {
        cout << curFriend->name << "\n";
        curFriend = curFriend->next;
    }
}