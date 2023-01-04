void viewPosts(User *user)
{
    Post *curPost = user->posts;
    while (1)
    {
        if (curPost == NULL)
        {
            return;
        }
        cout << "\t" << curPost->content << "\n\tLikes : " << curPost->likes;
        cout << "\nEnter d to delete this post, n otherwise\n";
        char temp;
        cin >> temp;
        if (temp == 'd')
        {
            if (curPost->previousPost != NULL)
            {
                Post *temp = curPost;
                curPost->previousPost->nextPost = curPost->nextPost;
                curPost = curPost->nextPost;
                free(temp);
            }
            else
            {
                user->posts = curPost->nextPost;
            }
        }
        if (curPost->previousPost)
        {
            cout << "\nEnter p to go to the previous post\n";
        }
        if (curPost->nextPost)
        {
            cout << "Enter n to go to the next post\n";
        }
        cout << "Enter x to exit\n";

        cin >> temp;
        if (temp == 'p')
        {
            curPost = curPost->previousPost;
        }
        else if (temp == 'n')
        {
            curPost = curPost->nextPost;
        }
        else if (temp == 'x')
        {
            return;
        }
    }
}