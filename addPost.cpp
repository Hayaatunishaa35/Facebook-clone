void addPost(GRAPHPTR graph, User *user)
{
    Post *post = new Post;
    post->previousPost = post->nextPost = NULL;
    post->author = user->name;
    cout << "Enter the content : ";
    cin.ignore();
    getline(cin, post->content);
    post->likes = 0;
    // posts are doubly linked, so do the appropriate operation

    if (user->posts == NULL)
    {
        user->posts = post;
    }
    else
    {
        Post *temp = user->posts;
        while (temp->nextPost != NULL)
        {
            temp = temp->nextPost;
        }

        temp->nextPost = post;
        post->previousPost = temp;
    }

    //***************ALL THE ABOVE ARE USER SPECIFIC**********

    //***************NOW COMING TO GRAPH SPECIFIC**********

    User *friendOfUser = user->next;
    while (friendOfUser != NULL)
    {
        pushIntoFeedStack(graph, friendOfUser->user_id, post);
        friendOfUser = friendOfUser->next;
    }
}