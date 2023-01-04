#include "header.cpp"
#include "dataStructures.cpp"
#include "displayFriendRequests.cpp"
#include "sendFriendRequest.cpp"
#include "addPost.cpp"
#include "viewPosts.cpp"
#include "viewFeed.cpp"
#include "viewFriends.cpp"
#include "friendSuggestions.cpp"

int main()
{
    fstream file("names.txt", ios::in);
    GRAPHPTR graph = initializeGraph(111);
    // adding a node(user) into the database
    int i = 0;
    string tempName = "Hayatunisha";
    while (file)
    {
        i++;
        if (i == 31)
        {
            break;
        }
        getline(file, tempName);
        addUser(graph, tempName);
    }
    // assume all the users have been added
    // interface

    int curID;
    int flag = 1;
    while (1)
    {
        displayAllUsersInTheSystem(graph);
        cout << "Enter your user ID : ";
        cin >> curID;
        flag = 1;
        struct User *currentUser = &graph->users[curID];
        int choice;
        while (1)
        {
            if (flag == 0)
            {
                break;
            }
            cout << "1. View your feed\n2. Post\n3. View your posts\n4. View all your friend requests\n5. View all your friends\n6. Send friend requests\n7. View suggested friends\n8. Exit\nEnter your choice : " << endl
                 << endl;

            cin >> choice;

            switch (choice)
            {
            case 1:
                viewFeed(graph, curID);
                break;
            case 2:
                addPost(graph, currentUser);
                break;
            case 3:
                viewPosts(currentUser);
                break;
            case 4:
                displayFriendRequests(graph, currentUser->user_id);
                break;
            case 5:
                viewFriends(currentUser);
                break;
            case 6:
                sendFriendRequest(graph, currentUser->user_id);
                break;
            case 7:
                friendSuggestions(graph, currentUser->user_id);
                break;

            case 8:
                cout << "Thank you !\n";
                flag = 0;
                break;
            default:
                cout << "Invalid choice\n";
            }
        }
    }
    return 0;
}
