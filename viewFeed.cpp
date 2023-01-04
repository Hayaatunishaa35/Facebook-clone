void viewFeed(GRAPHPTR graph, int ID)
{

    Feed *currentFeed = graph->users[ID].feed; // actually the top pointer
    if (currentFeed == NULL)
    {
        cout << "There are no posts in you feed now!\nPlease come back later!\n";
        return;
    }

    // else, view the post of a feed with likes and have a like button, and increment likes, move to feed->next, and pop the previous feed
    while (currentFeed != NULL)
    {
        cout << "\t" << currentFeed->post->author << " : \n";
        cout << "\t\t" << currentFeed->post->content << endl;
        cout << "\t\tLikes : " << currentFeed->post->likes << endl
             << endl;
        popFromFeedStack(graph, ID);
        cout << "Enter l to like the post! Enter n to move to the next post! Enter x to stop viewing the feed\n";
        char c;
        cin >> c;
        if (c == 'l')
        {
            currentFeed->post->likes++;
            currentFeed = currentFeed->next;
        }
        else if (c == 'x')
        {
            return;
        }
        else if (c == 'n')
        {
            currentFeed = currentFeed->next;
        }

        if (currentFeed == NULL)
        {
            return;
        }
    }

    cout << "All the posts have been shown !\n";
}