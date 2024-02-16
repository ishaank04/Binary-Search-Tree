#include<iostream>
using namespace std;

struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
    struct Node *base;
};



int tree_adding (Node *parent, Node *N)
{
    int x;
    //Less than Parent
    if(parent->data>N->data)
    {
        if(parent->prev==NULL)
        {
           parent->prev=N;
           N->base=parent;
           //Because Node Is Succesfully Added
           return 1;
        }
        else
        {
          x=tree_adding (parent->prev,N);
        }
    }

    //More than Parent
    else if (parent->data<N->data)
    {
        if(parent->next==NULL)
        {
            parent->next=N;
            N->base=parent;
            //Because Node Is Succesfully Added
            return 1;
        }
        else
        {
           x=tree_adding (parent->next,N);
        }
    }
    //Parent value and the new value are equal
    else
    {
        cout<<"It is a Repeated Value. Can't add value to Tree."<<endl;
        delete N;
        //Because Node Is Not Added
        return 0;
    }
    return x;
}

int tree_deletion_process(Node *current,int g,Node *Start)
{
    Node *x=current;

    // If Node is Start
    if(g==0)
    {
      if(x->next!=NULL)
      {
      Node *a= x->next;
      Node *b= x->prev;

      while(a->prev!=NULL)
      {
          a=a->prev;
      }
      a->prev=b;
      b->base=a;
      Start=a;
      Start->base=NULL;
      delete x;
    }

    else if (x->prev!=NULL)
    {
        Start= x->prev;
        Start->base=NULL;
        delete x;
    }
    else
    {
        Start=NULL;
        delete x;
    }
    }

    //If Node is Not Start
    if(g==1)
    {
      if(x->next!=NULL)
    {
      Node *root=x->base;
      Node *a= x->next;
      a->base=root;
      Node *b= x->prev;

      if(a->data>root->data)
      {
          root->next=a;
      }
      else
      {
          root->prev=a;
      }


      while(a->prev!=NULL)
      {
          a=a->prev;
      }
      a->prev=b;
      b->base=a;
      delete x;
    }
    else if (x->prev!=NULL)
    {
        Node *root=x->base;
        Node *a = x->prev;
        root->prev=a;
        a->base=root;
        delete x;
    }
    else
    {
        Node *root=x->base;
        if(root->data>x->data)
        {
         root->prev=NULL;
         delete x;
        }
        else
        {
            root->next=NULL;
            delete x;
        }
    }
    }
return 0;
}

int tree_deleting_search(Node *current, int d,Node *Start)
{
    if (current->data<d)
  {
      if(current->next==NULL)
      {
          cout<<"Element Not Found "<<endl;
          return 0;
      }
      else if (current->next->data==d)
      {
          tree_deletion_process(current->next,1,Start);
          return 1;
      }
      else
      {
          tree_deleting_search(current->next,d,Start);
      }
  }

  else if (current->data>d)
  {
      if(current->prev==NULL)
      {
          cout<<"Element Not Found "<<endl;
          return 0;
      }
      else if (current->prev->data==d)
      {
          tree_deletion_process(current->prev,1,Start);
          return 1;
      }
      else
      {
          tree_deleting_search(current->prev,d,Start);
      }
  }

  else if(current->data==d )
  {
      tree_deletion_process(current,0,Start);
      return 1;
  }

}

int tree_searching (Node *current,int d)
{
  if (current->data<d)
  {
      if(current->next==NULL)
      {
          cout<<"Element Not Found "<<endl;
      }
      else if (current->next->data==d)
      {
          cout<<"Element Found"<<endl;
      }
      else
      {
          tree_searching(current->next,d);
      }
  }

  else if (current->data>d)
  {
      if(current->prev==NULL)
      {
          cout<<"Element Not Found "<<endl;
      }
      else if (current->prev->data==d)
      {
          cout<<"Element Found"<<endl;
      }
      else
      {
          tree_searching(current->prev,d);
      }
  }

  else if(current->data==d )
  {
      cout<<"Element Found"<<endl;
  }
}

void PreOrder (Node *x)
{
    if(x!=NULL)
    {
      cout<<x->data<<" ";
      PreOrder(x->prev);
      PreOrder(x->next);
    }
}

void Inorder(Node *x)
{
    if(x!=NULL)
    {
      Inorder(x->prev);
      cout<<x->data<<" ";
      Inorder(x->next);
    }
}

void PostOrder(Node *x)
{
    if(x!=NULL)
    {
      PostOrder(x->prev);
      PostOrder(x->next);
      cout<<x->data<<" ";
    }
}

int main()
{
Node *Start,*N,*x;
int choice,a,Node_Count=0,m,d;


 do
 {
 m=0;
 cout<<"Enter 1 to Enter Data"<<endl;
 cout<<"Enter 2 to Delete Data"<<endl;
 cout<<"Enter 3 to Search Data"<<endl;
 cout<<"Enter 4 for Pre-Order Traversal"<<endl;
 cout<<"Enter 5 for In-Order Traversal"<<endl;
 cout<<"Enter 6 for Post-Order Traversal"<<endl;
 cout<<"Enter 0 to Exit"<<endl;
 cout<<"Enter Choice: ";
 cin>>choice;

 switch(choice)
 {
    case 0:
    {
     cout<<"Exiting the Program."<<endl;
    }
    break;

    case 1:
    {
        cout<<"Enter Data To Add To The Tree: ";
        cin>>a;

        //If it is the First Node
        if(Node_Count==0)
        {
         Start= new Node;
         Start->data=a;
         Start->base=NULL;
         Start->next=NULL;
         Start->prev=NULL;
         Node_Count=1;
        }
        //If it is not the First Node
        else
        {
            N=new Node;
            N->data=a;
            N->next=NULL;
            N->prev=NULL;
            m=tree_adding(Start,N);
            Node_Count=Node_Count+m;

        }
    }
    break;

    case 2:
    {
        if(Node_Count>0)
        {
        cout<<"Enter Node You Want To Delete: ";
        cin>>d;
        m=tree_deleting_search(Start,d,Start);
        Node_Count=Node_Count-m;
        }
        else
        {
            cout<<"The Tree Is Empty. Deletion Not Possible.";
        }

    }
    break;

    case 3:
    {
        if(Node_Count>0)
        {
           cout<<"Enter Node You Want To Search: ";
           cin>>d;
           tree_searching(Start,d);
        }
        else
        {
            cout<<"The Tree Is Empty. Searching Not Possible.";
        }

    }
    break;

    case 4:
    {
      if(Node_Count>0)
        {
           PreOrder(Start);
           cout<<endl;
        }
        else
        {
            cout<<"The Tree Is Empty. Traversal Not Possible.";
        }
    }
    break;

    case 5:
    {
        if(Node_Count>0)
        {
           Inorder(Start);
           cout<<endl;
        }
        else
        {
            cout<<"The Tree Is Empty. Traversal Not Possible.";
        }
    }
    break;

    case 6:
    {
        if(Node_Count>0)
        {
           PostOrder(Start);
           cout<<endl;
        }
        else
        {
            cout<<"The Tree Is Empty. Traversal Not Possible.";
        }
    }
    break;

    default:
    {
        cout<<"Wrong Input"<<endl;
    }
 }

 }while(choice!=0);

}


