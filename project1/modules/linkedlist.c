struct node {
  char* line;
  struct node *next;
};

struct node* reverseLinkedList(struct node* root)
{
  struct node *conductor = root;
  struct node *previous = NULL;
  struct node *next;
  
  while (conductor->next->next != 0 && conductor != NULL) 
  {
    next = conductor->next;
    conductor->next = previous;
    previous = conductor;
    conductor = next;
  }
  return previous;
}
